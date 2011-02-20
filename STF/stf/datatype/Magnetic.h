/**
 * @file   Magnetic.h
 * @brief  ���C�֌W�̕����ʂ�\��
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_datatype_MagneticField_h
#define stf_datatype_MagneticField_h

#include "StaticVector.h"
namespace stf { 
namespace datatype {

//! 3�����������x(T)��\���D
/*! */
class MagneticField : public StaticVector<3> {
public:
	MagneticField(){}
    MagneticField(const StaticVector<3> &rhs);
    MagneticField(const Vector &rhs);
    MagneticField(const MagneticField &rhs);
    MagneticField(double m0,double m1, double m2);
	~MagneticField(){}
private:
};

//! 3�������C���[�����g(Am2)��\���D
/*! */
class MagneticMoment : public StaticVector<3> {
public:
	MagneticMoment(){}
    MagneticMoment(const StaticVector<3> &rhs);
    MagneticMoment(const Vector &rhs);
    MagneticMoment(const MagneticMoment &rhs);
    MagneticMoment(double m0,double m1, double m2);
	~MagneticMoment(){}
private:
};

} /* End of namespace stf::datatype */
} /* End of namespace stf */

#endif // stf_datatype_MagneticField_h
