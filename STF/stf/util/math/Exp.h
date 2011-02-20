/**
 * @file   Exp.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef util_math_Exp_h
#define util_math_Exp_h

#include<assert.h>
#include"../../datatype/Matrix.h"
#include"../../datatype/StaticMatrix.h"

namespace stf { 
namespace util {
namespace math {


//�s��̎w����n���̃}�N���[�����W�J�܂Ōv�Z���ĕԂ��֐��D
datatype::Matrix exp(const datatype::Matrix& m, int n);

datatype::Matrix exp(const datatype::Matrix& m);

template<int rows>
datatype::StaticMatrix<rows,rows> exp(const datatype::StaticMatrix<rows,rows>& m, int n){
    datatype::StaticMatrix<rows,rows> result;
    result.unitize();

    int k = 1;
    datatype::StaticMatrix<rows,rows> m_n;
	m_n.unitize();
	int f = 1;

    while(k < n){
        //�w���֐�I+A+A^2/2!+...��k�Ԗڂ̍����v�Z
        m_n *= m;
		f   *= k;       
        result += m_n / f;
        k++;
    }
    return result;
}

template<int rows>
inline datatype::StaticMatrix<rows,rows> exp(const datatype::StaticMatrix<rows,rows>& m){
	return exp(m,4);
}

} /* End of namespace stf::util::math */
} /* End of namespace stf::util */
} /* End of namespace stf */

#endif // util_math_Exp_h
