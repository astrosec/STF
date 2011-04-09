/**
 * @file   EarthSensorBase.h
 * @brief  地球センサの基底クラス
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_devicedriver_earthsensor_EarthSensorBase_h
#define stf_core_devicedriver_earthsensor_EarthSensorBase_h

#include "../../../util/stfassert.h"
#include "../AOCSSensor.h"
#include "../../../datatype/StaticVector.h"

namespace stf {
namespace environment {
class Simulator;
}
namespace core {
namespace devicedriver {
namespace earthsensor {

//! 地球センサの基底クラス．
/*! 
	@tparam Env コンポーネントの環境クラス．
*/
template <class Env>
class EarthSensorBase : public AOCSSensor<Env, datatype::StaticVector<2>, datatype::StaticVector<2>>{
public:
	EarthSensorBase(const datatype::DCM &angle, double err_deg, int sigma = 3);
	virtual ~EarthSensorBase(){}
	virtual void do_update();
	virtual datatype::StaticVector<2> filter(const datatype::StaticVector<2>& value); 
private:
    EarthSensorBase();
	double err_deg_;
	int sigma_;
};

template <class Env>
EarthSensorBase<Env>::EarthSensorBase(const datatype::DCM& dcm, double err_deg, int sigma)
	: AOCSSensor<datatype::StaticVector<2>, datatype::StaticVector<2>, T>("EarthSensor", dcm), err_deg_(err_deg), sigma_(sigma)
{

}

template <class Env>
void EarthSensorBase<Env>::do_update(){
	stf_static_assert(0 && "Not-Implemented-Exception");
}

//シミュレータ用の特殊化
template<>
void EarthSensorBase<environment::Simulator>::do_update();


} /* End of namespace stf::core::devicedriver::earthsensor */
} /* End of namespace stf::core::devicedriver */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_earthsensor_EarthSensorBase_h
