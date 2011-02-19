/**
 * @file   EulerAngle.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_datatype_EulerAngle_h
#define stf_datatype_EulerAngle_h

#include "StaticVector.h"


namespace stf { 
namespace datatype {
///z-y-x���W�n�ɂ�����I�C���[�p(rad)�D�W���o�����b�N�ɒ��ӂ��Ďg�p���邱�ƁD
class EulerAngle : public StaticVector<3> {
public:
	EulerAngle() {}//: Vector(3) {}
    EulerAngle(const StaticVector<3> &rhs);
	~EulerAngle(){}
	// virtual method for IAocsData
	virtual void normalize();// -180 - 180�ɒ���
};

} /* End of namespace stf::datatype */
} /* End of namespace stf */

#endif // stf_datatype_EulerAngle_h
