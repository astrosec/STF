/**
 * @file   NJSunSensor.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_devicedriver_NJSunSensor_NJSunSensor_h
#define stf_core_devicedriver_NJSunSensor_NJSunSensor_h

#include "../../../core/devicedriver/sunsensor/SunSensorBase.h"

namespace stf {
namespace core {
namespace devicedriver {
namespace sunsensor {
template <class T>
class NJSunSensor : public SunSensorBase<T>{
public:  
	// 3-Sigmaで1度精度
	NJSunSensor( const datatype::DCM &angle) : SunSensorBase( angle, 1, 3){}
	~NJSunSensor(){}
	virtual void do_update(){}
private:
	NJSunSensor(){}
};

} /* End of namespace stf::core::devicedriver::sunsensor */
} /* End of namespace stf::core::devicedriver */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_NJSunSensor_NJSunSensor_h
