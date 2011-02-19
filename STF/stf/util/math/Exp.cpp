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


//行列の指数をn次のマクローリン展開まで計算して返す関数．
datatype::Matrix exp(datatype::Matrix m,int n){
    assert(m.rows_ == m.cols_);//正方行列のみ計算可能

    datatype::Matrix result(m.rows_,m.cols_);
    result.unitize();

    int k = 1;
    datatype::Matrix m_n = m;

    while(k < n){
        //指数関数I+A+A^2/2!+...のk番目の項を計算
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
    return exp(m,4);//第二引数が無い場合はデフォルトで4次まで計算
}


} /* End of namespace stf::util::math */
} /* End of namespace stf::util */
} /* End of namespace stf */

