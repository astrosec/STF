#ifndef datatype_DCM_h
#define datatype_DCM_h

#include "Matrix.h"

namespace stf { 
namespace datatype {
/// Z-Y-XÌÅñ]³¹éñ]sñiDCMjD
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
