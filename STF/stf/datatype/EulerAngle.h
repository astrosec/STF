/**
 * @file   EulerAngle.h
 * @brief  z-y-x�I�C���[�p(rad)�D
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_datatype_EulerAngle_h
#define stf_datatype_EulerAngle_h

#include "StaticVector.h"

namespace stf { 
namespace datatype {

//! 3-2-1(z-y-x)Euler Angle��\������D�P��rad
/*! */
class EulerAngle : public StaticVector<3> {
public:
	EulerAngle() {}
    EulerAngle(const StaticVector<3> &rhs);
	~EulerAngle(){}
	//! �s�񎮂��P�ɒ�������
	virtual void normalize();
};

} /* End of namespace stf::datatype */
} /* End of namespace stf */

#endif // stf_datatype_EulerAngle_h
