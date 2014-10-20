#include "gtest/gtest.h"
#include <limits>
#include <random>
#include <fstream>
#include <vcellutil.h>
#include <NumericConvert.h>
#include <MPoint.h>
#include <vcellstring.h>
#include <Mesh.h>
#include <persistcontainer.h>
#include <Volume.h>
#include <Segment.h>
#include <SVector.h>
#include "mockpoint.inc"
using namespace vcell_util; 
namespace {
	double dx = 2.0 / 3 - 0.0001;
	double dy = 2.0 / 7 + 0.0001;
	double dz = 14.0 / 5 + 0.0301;
	void binaryOpen(std::ofstream &out, const char *name) {
		using std::ios;
		out.open(name,ios::trunc|ios::binary);
		out.exceptions(ios::badbit|ios::failbit|ios::eofbit);
	}

	void binaryOpen(std::ifstream &in, const char *name) {
		using std::ios;
		in.open(name, ios::binary);
		in.exceptions(ios::badbit|ios::failbit);
	}
}

TEST(vcellutil,multiply) {
	ASSERT_TRUE(validMultiply(3,4));
	ASSERT_FALSE(validMultiply<char>(127,127));
}

TEST(persist,tcheck) {
	ASSERT_TRUE(typeid(spatial::TPoint<double,2>) == typeid(const spatial::TPoint<double,2>)); 
	std::cout << "dtt " << vcell_persist::getTypeToken(typeid(double)) << std::endl;
}

TEST(persist,prim) {
	const short five = 5;
	const long seven = 7; 
	const double pi =3.14159;
	{
		std::ofstream out;
		binaryOpen(out,"prim.dat");
		vcell_persist::WriteFormatter wf(out,1,true);
		vcell_persist::binaryWrite(out,five);
		vcell_persist::binaryWrite(out,seven);
		vcell_persist::binaryWrite(out,pi);
	}
	{
		std::ifstream in;
		binaryOpen(in,"prim.dat");
		vcell_persist::ReadFormatter wf(in,1);
		short f;
		long s;
		double p;
		vcell_persist::binaryRead(in,f);
		vcell_persist::binaryRead(in,s);
		vcell_persist::binaryRead(in,p);
		ASSERT_TRUE(f == five);
		ASSERT_TRUE(s == seven);
		ASSERT_TRUE(p == pi);
		ASSERT_TRUE(typeid(int) == typeid(signed int));
	}

}
TEST(persist,TPoint) {

	{
		std::ofstream out;
		binaryOpen(out,"tpoint.dat");
		spatial::TPoint<double,2> d(dx,dy);
		d.registerType( );
		d.persist(out);
		spatial::TPoint<int,3> e(7,24,25);
		e.registerType( );
		e.persist(out);
		spatial::TPoint<int,3> other(e); 
	}

	{
		std::ifstream in;
		binaryOpen(in,"tpoint.dat");
		spatial::TPoint<double,2> d(in);
		spatial::TPoint<int,3> e(in);
		ASSERT_TRUE(d(spatial::cX) == dx);
		ASSERT_TRUE(d(spatial::cY) == dy);
	}

}

TEST(persist,TPointVector) {
	std::minstd_rand g;
	std::uniform_int_distribution<short> sd(2,30);
	using std::ios;
	typedef spatial::TPoint<double,2> DPoint;
	const int vecSize = sd(g);
	DPoint::registerType( );

	std::vector<DPoint> vec;
	for (int i = 0; i < vecSize; i++) {
		DPoint d(dx + i ,dy -i);
		vec.push_back(d);
	}
	{
		std::ofstream out;
		binaryOpen(out,"tpointvec.dat");
		vcell_persist::persist(out,vec);
		std::vector<int> vec3;
		vec3.push_back(0);
		vec3.push_back(0);
		vec3.push_back(7);
		vcell_persist::persist<int>(out,vec3);
	}

	{
		std::ifstream in;
		binaryOpen(in,"tpointvec.dat");
		in.exceptions(ios::badbit|ios::failbit);
		std::vector<DPoint> vec2;
		vcell_persist::restore(in,vec2);
		for (int i = 0; i < vecSize; i++) {
			const DPoint &back = vec2[i];
			ASSERT_TRUE(back(spatial::cX) == dx + i); 
			ASSERT_TRUE(back(spatial::cY) == dy - i); 
		}
		std::vector<int> vec3;
		vcell_persist::restore(in,vec3);
		ASSERT_TRUE(vec3[2] == 7);
	}
}
namespace {
	struct PromiscousME : public spatial::MeshElement<double, 2> {
		 PromiscousME ( const size_t *n, const double *values)  
			 :spatial::MeshElement<double, 2>(n,values) {} 
		void setForTesting(spatial::SurfacePosition sp) {
			setPos(sp);
		}
	};

}
TEST(persist,MPoint) {
	spatial::MeshElement<double,2>::registerType( );
	size_t i[2] = {5,7};
	double r[2] = {3.4, 8.5};
	spatial::SurfacePosition sp = spatial::boundarySurface;
	{
		std::ofstream out;
		binaryOpen(out,"mpoint.dat");
		spatial::MPoint<double,2> a(i,r);
		a.persist(out);
		PromiscousME b(i,r);
		b.setForTesting(sp);
		b.persist(out);
	}

	{
		std::ifstream in;
		binaryOpen(in,"mpoint.dat");
		spatial::MPoint<double,2> d(in);
		ASSERT_TRUE(d(spatial::cX) == r[0]); 
		ASSERT_TRUE(d(spatial::cY) == r[1]);
		ASSERT_TRUE(d.indexOf(0) == i[0]);
		ASSERT_TRUE(d.indexOf(1) == i[1]);
		spatial::MeshElement<double,2> f(in);
		ASSERT_TRUE(f(spatial::cX) == r[0]); 
		ASSERT_TRUE(f(spatial::cY) == r[1]);
		ASSERT_TRUE(f.indexOf(0) == i[0]);
		ASSERT_TRUE(f.indexOf(1) == i[1]);
		ASSERT_TRUE(f.mPos( ) == sp);
	}
}
TEST(persist,Mesh) {
	std::array<short,2> origin = {{2,3}};
	std::array<short,2> sizes = {{5,6}};
	std::array<size_t,2> npoints = {{11,17}};
	std::array<short,2> intervals; 
	size_t cv = 0;
	{
		std::ofstream out;
		binaryOpen(out,"mesh.dat");
		spatial::MeshDef<short,2> md(origin,sizes,npoints);
		md.registerType( );
		md.persist(out);
		intervals[0] = md.interval(spatial::cX); 
		intervals[1] = md.interval(spatial::cY); 
		cv = md.checkvalue( );
	}
	{
		std::ifstream in;
		binaryOpen(in,"mesh.dat");
		spatial::MeshDef<short,2> back(in); 
		ASSERT_TRUE(back.startCorner(spatial::cX) == origin[0]) ; 
		ASSERT_TRUE(back.startCorner(spatial::cY) == origin[1]) ; 

		ASSERT_TRUE(back.interval(spatial::cX) == intervals[0]) ; 
		ASSERT_TRUE(back.interval(spatial::cY) == intervals[1]) ; 

		ASSERT_TRUE(back.numCells(spatial::cX) == npoints[0]) ;
		ASSERT_TRUE(back.numCells(spatial::cY) == npoints[1]) ;
		ASSERT_TRUE(back.checkvalue( ) == cv);
	}
}
TEST(persist,volume) {
	using spatial::Volume;
	typedef spatial::TPoint<double,2> Point;
	typedef Volume<double,double,2> VType;
	VType::registerType( );
	VType empty(0);
	VType single(1); 
	for (int i = 0 ; i < 3; i++) {
		single.add(Point(i,2*i));
	}
	single.close( );
	double vol = single.volume( );
	{
		std::ofstream out;
		binaryOpen(out,"volume.dat");
		empty.persist(out);
		single.persist(out);
	}
	std::ifstream in;
	binaryOpen(in,"volume.dat");
	VType eback(in);
	VType sback(in);
	ASSERT_TRUE(sback.volume( ) == vol);
}

TEST(persist,segment) {
	{
		spatial::TPoint<double,2> d(dx,dy);
		spatial::TPoint<double,2> e(dx + 1,dy + 1);
		spatial::Segment<double,2> s1(d,e);
		spatial::Segment<double,2> s2(e,d);
		ASSERT_TRUE(s1.a( )(spatial::cX) == dx);
		ASSERT_TRUE(s1.a( )(spatial::cY) == dy);
		ASSERT_TRUE(s2.a( )(spatial::cX) == dx);
		ASSERT_TRUE(s2.a( )(spatial::cY) == dy);
		ASSERT_TRUE(s1.b( )(spatial::cX) == dx + 1);
		ASSERT_TRUE(s1.b( )(spatial::cY) == dy + 1);
		ASSERT_TRUE(s2.b( )(spatial::cX) == dx + 1);
		ASSERT_TRUE(s2.b( )(spatial::cY) == dy + 1);
		s1.registerType( );
		std::ofstream out;
		binaryOpen(out,"segment.dat");
		s1.persist(out);
		s2.persist(out);
	}

	{
		std::ifstream in;
		binaryOpen(in,"segment.dat");
		spatial::Segment<double,2> back1(in);
		spatial::Segment<double,2> back2(in);
		ASSERT_TRUE(back1.a( )(spatial::cX) == dx);
		ASSERT_TRUE(back1.a( )(spatial::cY) == dy);
		ASSERT_TRUE(back2.a( )(spatial::cX) == dx);
		ASSERT_TRUE(back2.a( )(spatial::cY) == dy);
		ASSERT_TRUE(back1.b( )(spatial::cX) == dx + 1);
		ASSERT_TRUE(back1.b( )(spatial::cY) == dy + 1);
		ASSERT_TRUE(back2.b( )(spatial::cX) == dx + 1);
		ASSERT_TRUE(back2.b( )(spatial::cY) == dy + 1);
	}
}
TEST(persist,doubleRegister) {

	struct Dummy {};
	vcell_persist::Registrar::reg<Dummy>("dummy");
	try {
		vcell_persist::Registrar::reg<Dummy>("whammy");
	} catch (std::invalid_argument &) {
		return;
	}
	FAIL( ) << " exception should have been thrown";
}
TEST(persist,vector) {
	spatial::TPoint<double,2> d(dx,dy);
	spatial::TPoint<double,2> e(dx + 1,dy + 1);
	spatial::SVector<double,2> v1(d,e);

	spatial::TPoint<double,3> f (dx,dy,dz);
	spatial::TPoint<double,3> g (dx + 1,dy - 1 ,dz + 2);
	spatial::SVector<double,3> v2(f,g);
	v1.registerType( );
	v2.registerType( );
	{
		std::ofstream out;
		binaryOpen(out,"svector.dat");
		vcell_persist::WriteFormatter(out,7,true);
		v1.persist(out);
		v2.persist(out);
	}
	{
		std::ofstream out;
		binaryOpen(out,"svector2.dat");
		vcell_persist::WriteFormatter(out,7,false);
		v1.persist(out);
		v2.persist(out);
	}

	{
		std::ifstream in;
		binaryOpen(in,"svector.dat");
		vcell_persist::ReadFormatter(in,7);
		spatial::SVector<double,2> back1(in);
		spatial::SVector<double,3> back2(in);
		ASSERT_TRUE(back1 == v1);
		ASSERT_TRUE(back2 == v2);
	}

	{
		std::ifstream in;
		binaryOpen(in,"svector2.dat");
		vcell_persist::ReadFormatter(in,7);
		spatial::SVector<double,2> back1(in);
		spatial::SVector<double,3> back2(in);
		ASSERT_TRUE(back1 == v1);
		ASSERT_TRUE(back2 == v2);
	}
}

TEST(persist, offset) {
	using namespace spatial; 
	ElementOffset<2>::registerType( );
	spatial::MeshDef<double,2> sample(arrayInit<double>(-3.2,7), arrayInit<double>(0.34,3.4),arrayInit<size_t>(30,40) );


	Mesh<double,2,MockPoint > snap(sample);
	std::array<size_t,2> indexes = { 3, 4 };

	MockPoint *one = snap.query(indexes);
	indexes[0] = 7;
	indexes[1] = 12;
	MockPoint *two = snap.query(indexes);
	{
		ElementOffset<2> eo = one->offset(*two);
		std::ofstream out;
		binaryOpen(out,"offset.dat");
		eo.persist(out);
	}
	std::ifstream in;
	binaryOpen(in,"offset.dat");
	ElementOffset<2> eback(in);

	MockPoint *back = snap.element(*one,eback);

	ASSERT_TRUE(two == back);
}

/*
TEST(persist,rback) {
	const std::type_info & ti = typeid(spatial::TPoint<double,2>);
	std::cout << ti.name( ) << std::endl;
	std::ifstream in("tpoint.dat");
	spatial::TPoint<double,2> d(in);
	spatial::TPoint<int,3> e(in);
}
*/
TEST(persist,npc) {
	std::string x("me");
	x.push_back(03);
	std::string pretty = vcell_util::convertNonPrintable(x);
	std::cout << x << ", " << pretty << std::endl; 
}
