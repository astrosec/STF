/**
 * @file   Exp.h
 * @brief  行列の指数関数を計算する関数．
 * A function that calculates the exponential function of a matrix.
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef util_math_Exp_h
#define util_math_Exp_h

#include"../../util/stfassert.h"
#include"../../datatype/Matrix.h"
#include"../../datatype/StaticMatrix.h"

namespace stf { 
namespace util {
namespace math {

//! 行列の指数をn次のマクローリン展開まで計算して返す関数．
//Function that computes and returns the exponent of a 
//matrix up to the n-th order Maclaurin expansion
datatype::Matrix exp(const datatype::Matrix& m, int n);

//! 行列の指数を4次のマクローリン展開まで計算して返す関数．
//A function that computes and returns the exponent of
//a matrix up to the fourth-order Maclaurin expansion
datatype::Matrix exp(const datatype::Matrix& m);

//! 行列の指数をn次のマクローリン展開まで計算して返す関数．
template<int rows>
datatype::StaticMatrix<rows, rows> exp(const datatype::StaticMatrix<rows, rows>& m, int n){
    datatype::StaticMatrix<rows, rows> result;
    result.unitize();

    int k = 1;
    datatype::StaticMatrix<rows, rows> m_n;
	m_n.unitize();
	int f = 1;

    while(k < n){
        //指数関数I+A+A^2/2!+...のk番目の項を計算
        m_n *= m;
		f   *= k;       
        result += m_n / f;
        k++;
    }
    return result;
}

//! 行列の指数を4次のマクローリン展開まで計算して返す関数．
template<int rows>
inline datatype::StaticMatrix<rows, rows> exp(const datatype::StaticMatrix<rows, rows>& m){
	return exp(m, 4);
}

} /* End of namespace stf::util::math */
} /* End of namespace stf::util */
} /* End of namespace stf */

#endif // util_math_Exp_h
