/**
 * @file   NJADC.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_devicedriver_NJADC_h
#define stf_core_devicedriver_NJADC_h


#include "../../../core/devicedriver/CDHComponent.h"
#include "../../../core/devicedriver/adc/ADCBase.h"

namespace stf {
namespace core {
namespace devicedriver {

#define NJ__ADC__CHANNELS     128
#define NJ__VOLTAGE__CHANNELS  32
#define NJ__CURRENT__CHANNELS  12
#define NJ__TEMP1__CHANNELS     32
#define NJ__TEMP2__CHANNELS     32
#define NJ__VOLTAGE__OFFSET     0
#define NJ__CURRENT__OFFSET    25
#define NJ__TEMP1__OFFSET       60
#define NJ__TEMP2__OFFSET       96

template<class Env>
class NJADC : public ADCBase<Env, NJ__ADC__CHANNELS>{
public:
	NJADC(){}
	virtual void do_update(){
		//TBD
	}
};

//電流センサ
template<class Env>
class NJCurrentSensor : public MultiSensor<Env, datatype::Current, NJ__CURRENT__CHANNELS, NJ__ADC__CHANNELS> {
public:
	NJCurrentSensor( ADCBase<Env, NJ__ADC__CHANNELS>* adc) 
		: MultiSensor<Env, datatype::Current, NJ__CURRENT__CHANNELS, NJ__ADC__CHANNELS>( adc, NJ__CURRENT__OFFSET){}
};

//電圧センサ
template<class Env>
class NJVoltageSensor : public  MultiSensor<Env, datatype::Voltage, NJ__VOLTAGE__CHANNELS, NJ__ADC__CHANNELS> {
public:
	NJVoltageSensor( ADCBase<Env, NJ__ADC__CHANNELS>* adc)
		:  MultiSensor<Env, datatype::Voltage, NJ__VOLTAGE__CHANNELS, NJ__ADC__CHANNELS>( adc, NJ__VOLTAGE__OFFSET){}
};

//2線式温度計
template<class Env>
class NJCoarseTempSensor : public  MultiSensor<Env, datatype::Temperature, NJ__TEMP1__CHANNELS, NJ__ADC__CHANNELS> {
public:
	NJCoarseTempSensor( ADCBase<Env, NJ__ADC__CHANNELS>* adc)
		:  MultiSensor<Env, datatype::Temperature, NJ__TEMP1__CHANNELS, NJ__ADC__CHANNELS>( adc,  NJ__TEMP1__OFFSET){}
};

//4線式温度計
template<class Env>
class NJFineTempSensor : public  MultiSensor<Env, datatype::Temperature, NJ__TEMP2__CHANNELS, NJ__ADC__CHANNELS> {
public:
	NJFineTempSensor( ADCBase<Env, NJ__ADC__CHANNELS>* adc)
		:  MultiSensor<Env, datatype::Temperature, NJ__TEMP2__CHANNELS, NJ__ADC__CHANNELS>( adc,  NJ__TEMP2__OFFSET){}
};

} /* End of namespace stf::core::component */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_NJADC_h
