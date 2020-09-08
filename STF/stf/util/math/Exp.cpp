/**
 * @file   Exp.cpp
 * @brief  行列の指数関数を計算する関数．
 * Function that computes the exponential function of a matrix
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#include "Exp.h"

namespace stf { 
namespace util {
namespace math {


//行列の指数をn次のマクローリン展開まで計算して返す関数．
//A function that computes and returns the exponent 
//of a matrix up to the n-th order Maclaurin expansion.
datatype::Matrix exp(const datatype::Matrix& m, int n){
    stf_assert(m.rows() == m.cols());//正方行列のみ計算可能

    datatype::Matrix result(m.rows(), m.cols());
    result.unitize();

    int k = 1;
    datatype::Matrix m_n = m;

    while(k < n){
        //指数関数I+A+A^2/2!+...のk番目の項を計算
		//Calculates the kth term of the exponential function I+A+A^2/2!+...
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

datatype::Matrix exp(const datatype::Matrix& m){
    return exp(m, 4);//第二引数が無い場合はデフォルトで4次まで計算
	//If there is no second argument, calculate up to 4th order by default
}


} /* End of namespace stf::util::math */
} /* End of namespace stf::util */
} /* End of namespace stf */

