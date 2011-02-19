#ifndef util_math_Exp_h
#define util_math_Exp_h

#include<assert.h>
#include"../../datatype/Matrix.h"

namespace stf { 
namespace util {
namespace math {


//�s��̎w����n���̃}�N���[�����W�J�܂Ōv�Z���ĕԂ��֐��D
datatype::Matrix exp(datatype::Matrix m,int n);

datatype::Matrix exp(datatype::Matrix m);

} /* End of namespace stf::util::math */
} /* End of namespace stf::util */
} /* End of namespace stf */

#endif // util_math_Exp_h
