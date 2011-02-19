#ifndef stf_datatype_TypeConverter_h
#define stf_datatype_TypeConverter_h

#include "DCM.h"
#include "EulerAngle.h"
#include "Quaternion.h"
#include "StaticVector.h"
#include "OrbitInfo.h"

namespace stf {
namespace datatype {

///�P�ʂ�p���\���̑��ݕϊ����s�����[�e�B���e�B�D
///datatype���W���[���Ԃ̑��݌�����h�����߂ɂ��̃N���X��static���\�b�h�Ƃ��ĕϊ������܂Ƃ߂Ă���.ArgoUML��inline�𑽏d��`����o�O������̂ō��̂Ƃ��낷�ׂĊ֐��Ăяo��
class TypeConverter {
public:
    static Quaternion toQuaternion(const DCM &dcm);
    static Quaternion toQuaternion(const EulerAngle &euler_angle);
    static DCM toDCM(const Quaternion &q);
    static DCM toDCM(const EulerAngle &euler_angle);
    static EulerAngle toEulerAngle(const DCM &dcm);
    static EulerAngle toEulerAngle(const Quaternion &q);
    static DCM toDCM(double roll_deg, double pitch_deg, double yaw_deg);
	static StaticVector<2> toPolar(const StaticVector<3> &vec);
	static StaticVector<3> toRectangular(const StaticVector<2> &vec);
	static OrbitInfo toOrbitInfo(const PositionInfo &pos);
	static PositionInfo toPositionInfo(const OrbitInfo &orb);
	//static Geo toGeo(const PositionInfo &pos);
	//static Geo toGeo(const OrbitInfo &orb);
	
};

} /* End of namespace stf::datatype */
} /* End of namespace stf */

#endif // stf_datatype_TypeConverter_h
