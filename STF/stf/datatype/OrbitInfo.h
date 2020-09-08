/**
 * @file   OrbitInfo.h
 * @brief  軌道情報関係の量を表す Represents the amount of orbital information relationship
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_datatype_OrbitInfo_h
#define stf_datatype_OrbitInfo_h
#include "StaticVector.h"
#include "../util/math.h"

namespace stf { 
namespace datatype {

//! 軌道6要素を保持するクラス．サイズ肥大化を避けるため，主要な計算はOrbitImplのstaticなメソッドに投げることで行う
	//A class that holds 6 orbital elements. To avoid size bloat, the main calculation is done by throwing it in a static method of OrbitImpl.
/*!  */
struct OrbitInfo {
	OrbitInfo() : a(0), e(0), M(0), i(0), Omega(0), omega(0), n(0) {}
	OrbitInfo(double a, double e, double M, double i, double Omega, double omega)
		: a(a), e(e), M(M), i(i), Omega(Omega), omega(omega)
	{
		n = util::math::sqrt( util::math::MU / (a * a * a) ); 
	}
	double a; //!< 長半径(m)  Long radius (m)
	double e; //!< 離心率  Eccentricity
	double M; //!< 平均近点離角  Average near point off angle
	double i; //!< 軌道傾斜角(rad) Orbital inclination angle (rad)
	double Omega;//!< 昇交点赤経(rad)  Ascending intersection RA (rad)
	double omega;//!< 近地点引数  Perigee argument
	double n;
};

//! 衛星座標を緯度経度高度の形式で保持するクラス．A class that holds satellite coordinates in the form of latitude longitude
/*!  */
struct Geo  {
	Geo() : latitude(0), longitude(0), altitude(0) {}
	double latitude; //!< 緯度(rad)  Latitude (rad)
	double longitude;//!< 経度(rad)  Longitude (rad)
	double altitude; //!< 高度(m)   Height (m)
};

//! 衛星座標を地心慣性座標系における位置と速度の6次元ベクトルで保持するクラス．
//A class that holds satellite coordinates as a 6-dimensional vector of position and velocity in the geocentric inertial coordinate system
/*!  */
struct PositionInfo  {
	PositionInfo() {}
	StaticVector<3> position; //!< 地球中心からの位置(m) Position from the center of the earth (m)
	StaticVector<3> velocity; //!< 速度ベクトル(m/s)  Velocity vector (m/s)
};

} /* End of namespace stf::datatype */
} /* End of namespace stf */

#endif // stf_datatype_OrbitInfo_h
