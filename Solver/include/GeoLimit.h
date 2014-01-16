#ifndef GeoLimit_h
#define GeoLimit_h
#include <VCellException.h>
namespace spatial {
	/**
	* specify limits of a single dimension of a problem
	* @tparam T storage type for limits
	*/
	template <typename T>
	struct TGeoLimit {
		TGeoLimit(T low_ = 0,T high_ = 0)
			:lo(low_),
			hi(high_) {
				if (lo > hi) {
					VCELL_EXCEPTION(domain_error, "GeoLimit low value " << lo << " may not be higher than high value " << hi);
				}
		}
		T low( ) const {
			return lo;
		}
		T high( ) const {
			return hi;
		}
		T span( ) const {
			return hi - lo;
		}

		template <typename OTHER>
		TGeoLimit<OTHER> convert( ) const {
			OTHER otherLow = static_cast<OTHER>(lo);
			OTHER otherHigh = static_cast<OTHER>(hi);
			return TGeoLimit<OTHER>(otherLow,otherHigh);
		}
	private:
		T lo;
		T hi;
	};

	template <typename T>
	inline bool operator==(const TGeoLimit<T> &lhs,const TGeoLimit<T> &rhs) {
		return lhs.low( ) == rhs.low( ) && lhs.high( ) == rhs.high( );
	}

	/**
	* conversion functor
	*/
	template<typename FROM, typename TO> 
	struct GeoLimitConvert {
		TGeoLimit<TO> operator( )(const TGeoLimit<FROM> &in) {
			return in.convert<TO>( );
		}
	};

	typedef TGeoLimit<double> GeoLimit;
}
#endif
