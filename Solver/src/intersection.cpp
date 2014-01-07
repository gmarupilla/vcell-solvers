#include <vector>
#include <algorithm>
#include <fstream>
#include <intersection.h>
#include <TPoint.h>
#include <World.h>
#include <Logger.h>
#include <stack_container.h>
#include <MBridge/MBPolygon.h>
#include <MBridge/FronTierAdapt.h>
#include <MovingBoundaryCollections.h>
//temp
#include <iomanip>

#include "clipper.hpp"
//#define TIMEIT 
#ifdef TIMEIT 
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef max
#endif
namespace ClipperLib {
	static cInt const hiRange = 0x3FFFFFFFFFFFFFFFLL;
}
namespace {
	moving_boundary::WorldMax<ClipperLib::cInt> clipperWorldMax(ClipperLib::hiRange);
	using spatial::TPoint;
	using spatial::Volume;
	using spatial::Axis;
	using spatial::cX;
	using spatial::cY;

	/**
	* functor object for for_each; must use reference instead of contained value because
	* Func is passed by value in for_each
	*/
	template <class T>
	struct MaxValue {
		T & max;
		MaxValue(T &storage ):max(storage) {}

		//default copy constructor works great

		template<int N>
		void operator( )(const TPoint<T,N> &point) {
			for (int i = 0; i < N; i++) {
				const T val =  point(static_cast<Axis>(i));
				const T abs = std::abs(val); 
				max = std::max(max,abs);
			}
		}
	};

	/**
	* scale vcell to clipper 
	*/
	struct VtoCScaler {
		typedef ClipperLib::cInt cInt;
		typedef ClipperLib::cUInt cUInt;
		const cUInt scale;
		VtoCScaler(cUInt scale_):scale(scale_){}
		template <class T>
		ClipperLib::IntPoint operator( )(const TPoint<T,2> &point) {
			cInt x = static_cast<cInt>(point(cX) * scale);
			cInt y = static_cast<cInt>(point(cY) * scale);
			return ClipperLib::IntPoint(x,y);
		}
	};

	/**
	* scale clipper to vcell
	*/
	template <class T>
	struct CtoVScaler {
		const double scale;
		CtoVScaler(double scale_):scale(scale_){}
		TPoint<T,2> operator( )(const ClipperLib::IntPoint & point) {
			T x = point.X * scale;
			T y = point.Y * scale;
			return TPoint<T,2>(x,y); 
		}
	};
	/**
	* vcell to clipper 
	*/
	struct VtoCBridge { 
		//typedef ClipperLib::cInt cInt;
		ClipperLib::IntPoint operator( )(const TPoint<int,2> &point) {
			return ClipperLib::IntPoint(point(cX), point(cY));
		}
	};

	template <typename T>
	inline int checkedCast(T in) {
		assert(in < static_cast<T>(std::numeric_limits<int>::max( )) );
		return static_cast<int>(in);
	}
	/**
	* clipper to vcell
	*/
	struct CtoVBridge {
		TPoint<int,2> operator( )(const ClipperLib::IntPoint & point) {
			return TPoint<int,2>(checkedCast(point.X),checkedCast(point.Y));
		}
	};


	/**
	* move results from clipper into Volume 
	* @param result in/out parameter 
	* @param results clipper output 
	* @param inverseScale clipper to problem domain scale factor 
	*/
	template <class CT, class VT>
	void transformClipperResults(Volume<CT,VT,2> &result, ClipperLib::Paths & results, double inverseScale) { 
		typedef TPoint<CT,2> POINT;
		switch (results.size( )){
		case 0:
			{
				result.clear( );
				return;
			}

		case 1:
			{
				ClipperLib::Path interSect =  results.front( );
				CtoVScaler<double> inverseScaler(inverseScale);
				std::transform(interSect.begin( ),interSect.end( ),result.fillingIterator(interSect.size( )),inverseScaler);
				result.close( );
				return; 
			}

		default:
			std::vector<std::vector<POINT> > data;
			CtoVScaler<double> inverseScaler(inverseScale);
			for (ClipperLib::Paths::iterator iter = results.begin( ); iter != results.end( );++iter) {
				ClipperLib::Path interSect = *iter;
				result.nextSection( );
				std::vector<POINT> chunk;
				size_t expected = interSect.size( );
				std::transform(interSect.begin( ),interSect.end( ),result.fillingIterator(expected),inverseScaler);
				result.close( );
			}
		}
	}
	/**
	* move results from clipper into Volume 
	* @param result in/out parameter 
	* @param results clipper output 
	*/
	template <class VT>
	void transformClipperResults(Volume<int,VT,2> &result, ClipperLib::Paths & results) { 
		typedef TPoint<int,2> POINT;
		switch (results.size( )){
		case 0:
			{
				result.clear( );
				return;
			}

		case 1:
			{
				CtoVBridge bridge;
				ClipperLib::Path interSect =  results.front( );
				std::transform(interSect.begin( ),interSect.end( ),result.fillingIterator(interSect.size( )),bridge);
				result.close( );
				return; 
			}

		default:
			{
				std::vector<std::vector<POINT> > data;
				CtoVBridge bridge;
				for (ClipperLib::Paths::iterator iter = results.begin( ); iter != results.end( );++iter) {
					ClipperLib::Path interSect = *iter;
					result.nextSection( );
					std::vector<POINT> chunk;
					size_t expected = interSect.size( );
					std::transform(interSect.begin( ),interSect.end( ),result.fillingIterator(expected),bridge);
					result.close( );
				}
			}
		}
	}
	/**
	* debug
	*/
	void dump(std::ostream &sink, const char *var, ClipperLib::Path &p) {
		for (ClipperLib::Path::const_iterator iter = p.begin( );iter != p.end( ); ++iter) {
			sink << '\t' << var << ".push_back(IntPoint(" << iter->X << ',' << iter->Y << "));" << std::endl; 
		}
	}

	void copyInto(const ClipperLib::Path &source,matlabBridge::Polygon & dest) {
		for (ClipperLib::Path::const_iterator iter = source.begin( ); iter != source.end( ); ++iter) {
			dest.add(static_cast<double>(iter->X),static_cast<double>(iter->Y));
		}
	}

	void AddPath(ClipperLib::Clipper &c, ClipperLib::Path &path, ClipperLib::PolyType pt) {
		const bool r = c.AddPath(path,pt,true);
		if (r) {
			return;
		}
		VCELL_EXCEPTION(logic_error,"bad clipper add");
	}
	/**
	** scaling implementation
	* @tparam COORD_TYPE supports Volume<COORD_TYPE,VALUE_TYPE>
	* @tparam VALUE_TYPE supports Volume<COORD_TYPE,VALUE_TYPE>
	* @tparam POINT_TYPE input point type  (e.g. TPOINT<?,2> )
	*/
	template <class COORD_TYPE,class VALUE_TYPE,class POINT_TYPE> 
	struct IntersectImpl {
		typedef typename std::vector<POINT_TYPE> PVector;
		typedef typename std::vector<PVector> VectorOfVector; 

		/**
		* returns intersection of a and b
		* @param result in/out parameter * @param a polygon
		* @param b other polygon
		*/
		static void intersections(Volume<COORD_TYPE,VALUE_TYPE,2> &result, const PVector &a,const PVector &b) {
			COORD_TYPE maxValue = std::numeric_limits<COORD_TYPE>::min( );
			MaxValue<COORD_TYPE> mvFunctor(maxValue);
			std::for_each(a.begin( ), a.end( ),mvFunctor);
			std::for_each(b.begin( ), b.end( ),mvFunctor);
			assert(maxValue >= 0);

			ClipperLib::cInt scale = ClipperLib::hiRange / static_cast<ClipperLib::cInt>(maxValue); 
			static long double inverseScale = 1.0L/scale; 

			ClipperLib::Path clipperA(a.size( ));
			ClipperLib::Path clipperB(b.size());
			VtoCScaler scaler(scale);
			std::transform(a.begin( ),a.end( ),clipperA.begin( ),scaler);
			std::transform(b.begin( ),b.end( ),clipperB.begin( ),scaler);
			matlabBridge::Polygon pa("-g",2);
			copyInto(clipperA,pa);
			matlabBridge::Polygon pb("-b",2);
			copyInto(clipperB,pb);
			std::ofstream id("idebug.m");
			id << pa << pb;
			std::ofstream code("frag.txt");
			dump(code,"polyA",clipperA);
			dump(code,"polyB",clipperB);


			ClipperLib::Clipper c;
			AddPath(c,clipperA,ClipperLib::ptSubject);
			AddPath(c,clipperB,ClipperLib::ptClip);
			ClipperLib::Paths results;
#ifdef TIMEIT
			LARGE_INTEGER start;
			LARGE_INTEGER stop;
			QueryPerformanceCounter(&start);
#endif
			c.Execute(ClipperLib::ctIntersection,results,ClipperLib::pftEvenOdd,ClipperLib::pftEvenOdd);
#ifdef TIMEIT
			QueryPerformanceCounter(&stop);
			std::cout << clipperA.size( ) << " by " << clipperB.size( ) << " ticks " << (stop.QuadPart - start.QuadPart) << std::endl;
#endif
			transformClipperResults(result,results,inverseScale);
#ifdef CLIPPER_DUMP
			static int count = 0;
			count++;
			static std::ofstream cDebug("clipperDebug.txt");
			cDebug << count << std::endl; 
			dump(cDebug,"a",clipperA);
			dump(cDebug,"b",clipperB);
			//dump(cDebug,3,results);
#endif
		}

		static void intersectionsManySingle(Volume<COORD_TYPE,VALUE_TYPE,2> &result, const VectorOfVector & vOfVa,const PVector &b) {
			COORD_TYPE maxValue = std::numeric_limits<COORD_TYPE>::min( );
			MaxValue<COORD_TYPE> mvFunctor(maxValue);
			for (VectorOfVector::const_iterator iter = vOfVa.begin( ); iter != vOfVa.end( ); ++iter) {
				std::for_each(iter->begin( ), iter->end( ),mvFunctor);
			}
			std::for_each(b.begin( ), b.end( ),mvFunctor);
			assert(maxValue >= 0);

			ClipperLib::cInt scale = ClipperLib::hiRange / static_cast<ClipperLib::cInt>(maxValue); 
			static long double inverseScale = 1.0L/scale; 

			VtoCScaler scaler(scale);

			ClipperLib::Clipper c;
			for (VectorOfVector::const_iterator iter = vOfVa.begin( ); iter != vOfVa.end( ); ++iter) {
				const PVector & vectorA = *iter;
				ClipperLib::Path clipperA(vectorA.size( ));
				std::transform(vectorA.begin( ),vectorA.end( ),clipperA.begin( ),scaler);
				AddPath(c,clipperA,ClipperLib::ptSubject);
			}

			ClipperLib::Path clipperB(b.size());

			std::transform(b.begin( ),b.end( ),clipperB.begin( ),scaler);

			AddPath(c,clipperB,ClipperLib::ptClip);
			ClipperLib::Paths results;
			c.Execute(ClipperLib::ctIntersection,results,ClipperLib::pftEvenOdd,ClipperLib::pftEvenOdd);
			transformClipperResults(result,results,inverseScale);
		}

		static void intersectionsManyMany(Volume<COORD_TYPE,VALUE_TYPE,2> &result, const VectorOfVector & vOfVa,const VectorOfVector & vOfVb) {
			COORD_TYPE maxValue = std::numeric_limits<COORD_TYPE>::min( );
			MaxValue<COORD_TYPE> mvFunctor(maxValue);
			for (VectorOfVector::const_iterator iter = vOfVa.begin( ); iter != vOfVa.end( ); ++iter) {
				std::for_each(iter->begin( ), iter->end( ),mvFunctor);
			}
			for (VectorOfVector::const_iterator iter = vOfVb.begin( ); iter != vOfVb.end( ); ++iter) {
				std::for_each(iter->begin( ), iter->end( ),mvFunctor);
			}
			assert(maxValue >= 0);
			ClipperLib::cInt scale = ClipperLib::hiRange / static_cast<ClipperLib::cInt>(maxValue); 
			static long double inverseScale = 1.0L/scale; 
			//typedef TPoint<REAL,2> POINT;

			VtoCScaler scaler(scale);

			ClipperLib::Clipper c;

			for (VectorOfVector::const_iterator iter = vOfVa.begin( ); iter != vOfVa.end( ); ++iter) {
				const PVector & vectorA = *iter;
				ClipperLib::Path clipperA(vectorA.size( ));
				std::transform(vectorA.begin( ),vectorA.end( ),clipperA.begin( ),scaler);
				AddPath(c,clipperA,ClipperLib::ptSubject);
			}

			for (VectorOfVector::const_iterator iter = vOfVb.begin( ); iter != vOfVb.end( ); ++iter) {
				const PVector & vectorB = *iter;
				ClipperLib::Path clipperB(vectorB.size( ));
				std::transform(vectorB.begin( ),vectorB.end( ),clipperB.begin( ),scaler);
				AddPath(c,clipperB,ClipperLib::ptSubject);
			}

			ClipperLib::Paths results;
			c.Execute(ClipperLib::ctIntersection,results,ClipperLib::pftEvenOdd,ClipperLib::pftEvenOdd);
			transformClipperResults(result,results,inverseScale);
		}
	};

	template <class VALUE_TYPE,class POINT_TYPE> 
	struct IntersectImpl<int,VALUE_TYPE,POINT_TYPE> {
		typedef typename std::vector<POINT_TYPE> PVector;
		typedef typename std::vector<PVector> VectorOfVector; 
		static void intersections(Volume<int,VALUE_TYPE,2> &result, const PVector &a,const PVector &b) {
			ClipperLib::Path clipperA(a.size( ));
			ClipperLib::Path clipperB(b.size());
			VtoCBridge bridge;
			std::transform(a.begin( ),a.end( ),clipperA.begin( ),bridge);
			std::transform(b.begin( ),b.end( ),clipperB.begin( ),bridge);
			matlabBridge::Polygon pa("-g",2);
			copyInto(clipperA,pa);
			matlabBridge::Polygon pb("-b",2);
			copyInto(clipperB,pb);
			std::ofstream id("idebug.m");
			id << pa << pb;
			std::ofstream code("frag.txt");
			dump(code,"polyA",clipperA);
			dump(code,"polyB",clipperB);


			ClipperLib::Clipper c;
			AddPath(c,clipperA,ClipperLib::ptSubject);
			AddPath(c,clipperB,ClipperLib::ptClip);
			ClipperLib::Paths results;
#ifdef TIMEIT
			LARGE_INTEGER start;
			LARGE_INTEGER stop;
			QueryPerformanceCounter(&start);
#endif
			c.Execute(ClipperLib::ctIntersection,results,ClipperLib::pftEvenOdd,ClipperLib::pftEvenOdd);
#ifdef TIMEIT
			QueryPerformanceCounter(&stop);
			std::cout << clipperA.size( ) << " by " << clipperB.size( ) << " ticks " << (stop.QuadPart - start.QuadPart) << std::endl;
#endif
			transformClipperResults(result,results);
		}

		static void intersectionsManySingle(Volume<int,VALUE_TYPE,2> &result, const VectorOfVector & vOfVa,const PVector &b) {
			ClipperLib::Clipper c;
			VtoCBridge bridge;
			for (VectorOfVector::const_iterator iter = vOfVa.begin( ); iter != vOfVa.end( ); ++iter) {
				const PVector & vectorA = *iter;
				ClipperLib::Path clipperA(vectorA.size( ));
				std::transform(vectorA.begin( ),vectorA.end( ),clipperA.begin( ),bridge);
				AddPath(c,clipperA,ClipperLib::ptSubject);
			}

			ClipperLib::Path clipperB(b.size());

			std::transform(b.begin( ),b.end( ),clipperB.begin( ),bridge);

			AddPath(c,clipperB,ClipperLib::ptClip);
			ClipperLib::Paths results;
			c.Execute(ClipperLib::ctIntersection,results,ClipperLib::pftEvenOdd,ClipperLib::pftEvenOdd);
			transformClipperResults(result,results);
		}
		static void intersectionsManyMany(Volume<int,VALUE_TYPE,2> &result, const VectorOfVector & vOfVa,const VectorOfVector & vOfVb) {
			ClipperLib::Clipper c;
			VtoCBridge bridge;

			for (VectorOfVector::const_iterator iter = vOfVa.begin( ); iter != vOfVa.end( ); ++iter) {
				const PVector & vectorA = *iter;
				ClipperLib::Path clipperA(vectorA.size( ));
				std::transform(vectorA.begin( ),vectorA.end( ),clipperA.begin( ),bridge);
				AddPath(c,clipperA,ClipperLib::ptSubject);
			}

			for (VectorOfVector::const_iterator iter = vOfVb.begin( ); iter != vOfVb.end( ); ++iter) {
				const PVector & vectorB = *iter;
				ClipperLib::Path clipperB(vectorB.size( ));
				std::transform(vectorB.begin( ),vectorB.end( ),clipperB.begin( ),bridge);
				AddPath(c,clipperB,ClipperLib::ptSubject);
			}

			ClipperLib::Paths results;
			c.Execute(ClipperLib::ctIntersection,results,ClipperLib::pftEvenOdd,ClipperLib::pftEvenOdd);
			transformClipperResults(result,results);
		}
	};
}

namespace spatial {
	template <typename COORD_TYPE,typename VALUE_TYPE,class POINT_TYPE>
	void intersections(Volume<COORD_TYPE,VALUE_TYPE,2> &result, const std::vector<POINT_TYPE> &a,const std::vector<POINT_TYPE> &b) {
		IntersectImpl<COORD_TYPE,VALUE_TYPE,POINT_TYPE>::intersections(result, a,b);
	}

	template <typename COORD_TYPE,typename VALUE_TYPE,class POINT_TYPE>
	void intersectionsManySingle(Volume<COORD_TYPE,VALUE_TYPE,2> &result, const std::vector<std::vector<POINT_TYPE> > & vOfVa,const std::vector<POINT_TYPE> &b) {
		IntersectImpl<COORD_TYPE,VALUE_TYPE,POINT_TYPE>::intersectionsManySingle(result, vOfVa,b);

	}
	template <typename COORD_TYPE,typename VALUE_TYPE,class POINT_TYPE>
	void intersectionsManyMany(Volume<COORD_TYPE,VALUE_TYPE,2> &result, const std::vector<std::vector<POINT_TYPE> > & vOfVa,const std::vector<std::vector<POINT_TYPE> > & vOfVb) {
		IntersectImpl<COORD_TYPE,VALUE_TYPE,POINT_TYPE>::intersectionsManyMany(result, vOfVa,vOfVb); 
	}
}

namespace T1 {
	typedef std::vector <spatial::TPoint<double,2> > PointVector; 
	template void spatial::intersections(spatial::Volume<double,double,2> &result, const PointVector &,const PointVector &) ;



	typedef std::vector <PointVector> VectorOfVectors;
	template void spatial::intersectionsManySingle(spatial::Volume<double,double,2> &result, const VectorOfVectors &,const PointVector &) ;

	template void spatial::intersectionsManyMany(spatial::Volume<double,double,2> &result, const VectorOfVectors &,const VectorOfVectors &) ;
}

namespace T2 {
	typedef std::vector <spatial::TPoint<int,2> > PointVector; 
	template void spatial::intersections(spatial::Volume<int,double,2> &result, const PointVector &,const PointVector &) ;

	typedef std::vector <PointVector> VectorOfVectors;
	template void spatial::intersectionsManySingle(spatial::Volume<int,double,2> &result, const VectorOfVectors &,const PointVector &) ;

	template void spatial::intersectionsManyMany(spatial::Volume<int,double,2> &result, const VectorOfVectors &,const VectorOfVectors &) ;
}
