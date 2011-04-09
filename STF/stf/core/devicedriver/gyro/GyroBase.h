/**
 * @file   GyroBase.h
 * @brief  ジャイロセンサの基底クラス．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_devicedriver_gyro_GyroBase_h
#define stf_core_devicedriver_gyro_GyroBase_h

#include "../../../util/stfassert.h"
#include "../../../datatype/Scalar.h"
#include "../../../datatype/StaticVector.h"
#include "../AOCSSensor.h"

namespace stf {
namespace environment {
class Simulator;
}
namespace core {
namespace devicedriver {
namespace gyro {

//! ジャイロセンサの基底クラス．
/*! 
	@tparam Env コンポーネントの環境クラス．
*/
template <class Env>
class GyroBase : public AOCSSensor<Env, datatype::StaticVector<3>, datatype::Scalar>{
public:
	GyroBase(const datatype::DCM &angle, double sigma, double tau);
	~GyroBase(){}
	virtual void do_update();
	virtual datatype::Scalar filter(const datatype::Scalar& value); 
private:
	//! バイアス分散
    double sigma_;
	//! バイアスレートの真値
	datatype::Scalar bias_rate_; 
    //! ECRVの時定数
    double tau_;
};

template <class Env>
GyroBase<Env>::GyroBase(const datatype::DCM &dcm, double sigma, double tau)
	: AOCSSensor<Env, datatype::StaticVector<3>, datatype::Scalar>( "Gyro", dcm), sigma_(sigma), tau_(tau), bias_rate_(0.0)
{

}

template <class Env>
void GyroBase<Env>::do_update(){
	stf_static_assert(0 && "Not-Implemented-Exception");
}

template<>
void GyroBase<environment::Simulator>::do_update();

} /* End of namespace stf::core::devicedriver::gyro */
} /* End of namespace stf::core::devicedriver */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_gyro_GyroBase_h
