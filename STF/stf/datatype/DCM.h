/**
 * @file   DCM.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef datatype_DCM_h
#define datatype_DCM_h

#include "Matrix.h"

namespace stf { 
namespace datatype {
/// Z-Y-X�̏��ŉ�]�������]�s��iDCM�j�D
class DCM : public Matrix {
public:
    DCM();
    DCM(const Matrix &rhs);
    ~DCM();
	// virtual method for IAocsData
	virtual void normalize();
};

} /* End of namespace stf::datatype */
} /* End of namespace stf */

#endif // datatype_DCM_h
