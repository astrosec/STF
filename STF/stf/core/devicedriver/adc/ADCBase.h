/**
 * @file   ADCBase.h
 * @brief  AD変換器ドライバの抽象クラス．
 * Abstract class of AD converter driver.
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_devicedriver_ADCBase_h
#define stf_core_devicedriver_ADCBase_h

#include "../../../util/stfassert.h"
#include "../CDHComponent.h"
#include "ConvertPolicy.h"
#include "../../../datatype/Environments.h"

namespace stf {
namespace core {
namespace devicedriver {

//! AD変換器ドライバの抽象クラス．Abstract class of AD converter driver
/*! 
	アプリケーションに応じて，これを継承したAD変換器クラスで適切なdo_updateを実装することで実体化が可能になる．
	//Depending on the application, it is possible to materialize 
	//by implementing appropriate do_update in the AD converter class that inherits this.
	@tparam NUM AD変換対象のチャネル数．Number of channels for AD conversion
	@tparam Env コンポーネントの環境クラス．  Environment class of the component
*/
template<class Env, int NUM>
class ADCBase : public CDHComponent<Env, datatype::Voltage, NUM>  {
public:
	ADCBase() :  CDHComponent<Env, datatype::Voltage, NUM>("ADCBase") {}
	virtual ~ADCBase(){}
protected:
};

//! ADCのデジタル値を物理値に変換して保持するコンポーネント．
//A component that converts the digital value of the ADC into a physical value and holds it
/*! 
	変換本体はポリシークラスのconvertが受け持つ．クラスTはdoubleからのimplicitなコンストラクタ，またはdoubleを右辺に取るoperator=を持っている必要がある(Scalar,Voltageなど).
	//The conversion body is handled by the policy class convert. 
	//Class T must have an implicit constructor from double, 
	//or operator= that takes a double on the right (Scalar, Voltage, etc.).
	@tparam T                保持する物理値の型．Type of physical value to hold.
	@tparam NUM              保持する物理値のチャネル数．Number of physical value channels to retain
	@tparam ADCNUM           対象のADCが持つ総チャネル数．The total number of channels that the target ADC has.
	@tparam Env              コンポーネントの環境クラス．Environment class of the component.
	@tparam ConversionPolicy convert関数の実装を決定する変換ポリシークラス．//Transformation policy class that determines the implementation of the function
*/
template<class Env, class T, int NUM, int ADCNUM = NUM, class ConversionPolicy = FirstOrderConvert>
class MultiSensor : public CDHComponent<Env, T, NUM>, public ConversionPolicy {
public:
	MultiSensor( ADCBase<Env, ADCNUM>* adc, int offset) : adcsource_(adc), offset_(offset), CDHComponent<Env, T, NUM>( "TempSensor")
	{
		stf_assert(offset + NUM <= ADCNUM);//ADCの範囲をこえない  Do not exceed ADC range
	}
	virtual void do_update(){
		for(int i = 0; i < NUM; i++){
			this->value_[i] = convert((*adcsource_)[i + offset_].value());
		}
	}
	virtual ~MultiSensor(){}
private:
	ADCBase<Env, ADCNUM>* adcsource_;
	int offset_;
};

} /* End of namespace stf::core::component */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_ADCBase_h
