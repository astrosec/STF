#ifndef stf_datatype_OrbitCalc_h
#define stf_datatype_OrbitCalc_h


namespace stf {
namespace datatype {

class DateTime;
template<int> class StaticVector;
struct PositionInfo;
class MagneticField;
class Quaternion;

///�O����������AOCS�ɕK�v�ȗʂ��v�Z����static���\�b�h�Q�D
///�Ă΂��x�Ɍv�Z���s���̂ŁC�v�Z���׌y���ɂ͌Ăяo�����ŃL���b�V�������Ȃǂ̍H�v���K�v
class OrbitCalc {
public:
	//J2000���W�n�ɂ����鑾�z�����x�N�g�����v�Z�D
    static StaticVector<2> getSunDirection2D(const DateTime& time);
	//J2000���W�n�ɂ�����n�������x�N�g�����v�Z�D
    static StaticVector<2> getEarthDirection2D(const PositionInfo& p);
	//J2000���W�n�ɂ����鑾�z�����x�N�g�����v�Z�D
    static StaticVector<3> getSunDirection3D(const DateTime& time);
	//J2000���W�n�ɂ�����n�������x�N�g�����v�Z�D
    static StaticVector<3> getEarthDirection3D(const PositionInfo& p);
	//�q�����W�n�ɂ�����n�������x�N�g�����v�Z�D
	static StaticVector<3> getEarthDirectionInBodyFrame(const PositionInfo& p, const Quaternion& q);
	//�q�����W�n�ɂ����鑾�z�����x�N�g�����v�Z�D
	static StaticVector<3> getSunDirectionInBodyFrame(const DateTime& time, const Quaternion& q);
	//IGRF���g�p���Č��݂̉q���ʒu�ɂ�����J2000���W�n�ł̎�����v�Z�D
	static MagneticField getMagneticFieldDirection(const PositionInfo& p, const DateTime& time);
};

} /* End of namespace stf::datatype */
} /* End of namespace stf */

#endif // stf_datatype_OrbitCalc_h
