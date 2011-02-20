/**
 * @file   Exp.cpp
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#include "Exp.h"

namespace stf { 
namespace util {
namespace math {


//�s��̎w����n���̃}�N���[�����W�J�܂Ōv�Z���ĕԂ��֐��D
datatype::Matrix exp(datatype::Matrix m,int n){
    assert(m.rows() == m.cols());//�����s��̂݌v�Z�\

    datatype::Matrix result(m.rows(),m.cols());
    result.unitize();

    int k = 1;
    datatype::Matrix m_n = m;

    while(k < n){
        //�w���֐�I+A+A^2/2!+...��k�Ԗڂ̍����v�Z
        int i = k - 1;
        int f = k;//k!

        while(i > 0){
            m_n *= m;
            f *= i;
            i--;
        }
        
        result += m_n / f;
        m_n = m;
        k++;
    }

    return result;
}

datatype::Matrix exp(datatype::Matrix m){
    return exp(m,4);//�������������ꍇ�̓f�t�H���g��4���܂Ōv�Z
}


} /* End of namespace stf::util::math */
} /* End of namespace stf::util */
} /* End of namespace stf */

