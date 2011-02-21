/**
 * @file   OrbitCalc.h
 * @brief  軌道関係情報を計算するメソッドをstaticメンバとしてまとめたクラス．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_datatype_OrbitCalc_h
#define stf_datatype_OrbitCalc_h


namespace stf {
namespace datatype {

class DateTime;
template<int> class StaticVector;
struct PositionInfo;
class MagneticField;
class Quaternion;

//! 軌道関係情報を計算するメソッドをstaticメンバとしてまとめたクラス．
/*!  */
class OrbitCalc {
public:
	///J2000座標系における太陽方向ベクトルを計算．
    static StaticVector<2> getSunDirection2D(const DateTime& time);
	///J2000座標系における地球方向ベクトルを計算．
    static StaticVector<2> getEarthDirection2D(const PositionInfo& p);
	///J2000座標系における太陽方向ベクトルを計算．
    static StaticVector<3> getSunDirection3D(const DateTime& time);
	///J2000座標系における地球方向ベクトルを計算．
    static StaticVector<3> getEarthDirection3D(const PositionInfo& p);
	///衛星座標系における地球方向ベクトルを計算．
	static StaticVector<3> getEarthDirectionInBodyFrame(const PositionInfo& p, const Quaternion& q);
	///衛星座標系における太陽方向ベクトルを計算．
	static StaticVector<3> getSunDirectionInBodyFrame(const DateTime& time, const Quaternion& q);
	///IGRFを使用して現在の衛星位置におけるJ2000座標系での磁場を計算．
	static MagneticField getMagneticFieldDirection(const PositionInfo& p, const DateTime& time);
};

} /* End of namespace stf::datatype */
} /* End of namespace stf */

#endif // stf_datatype_OrbitCalc_h
