/**
 * @file   DCM.h
 * @brief  Z-Y-X�̏��ŉ�]�������]�s��iDCM�j�D
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef datatype_DCM_h
#define datatype_DCM_h

#include "StaticMatrix.h"

namespace stf { 
namespace datatype {

//! Z-Y-X�̏��ŉ�]�������]�s��iDCM�j�D
/*! */
class DCM : public StaticMatrix<3,3> {
public:
    DCM();
    DCM(const StaticMatrix<3,3> &rhs);
	~DCM(){}
	//! �l��-pi�`pi�ɒ�������
	virtual void normalize();
};

} /* End of namespace stf::datatype */
} /* End of namespace stf */

#endif // datatype_DCM_h
