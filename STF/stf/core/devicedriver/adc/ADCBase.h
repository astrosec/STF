/**
 * @file   ADCBase.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_devicedriver_ADCBase_h
#define stf_core_devicedriver_ADCBase_h

#include "../CDHComponent.h"
#include "../../../datatype/Envitonments.h"
#include "ConvertPolicy.h"

namespace stf {
namespace core {
namespace devicedriver {

//! AD�ϊ���h���C�o�D
/*! 
	@tparam NUM AD�ϊ��Ώۂ̃`���l�����D
	@tparam Env �R���|�[�l���g�̊��N���X�D
*/
template<int NUM, class Env = ENV>
class ADCBase : public CDHComponent< datatype::Voltage, NUM, Env >  {
public:
	ADCBase(int instance_id) :  CDHComponent<datatype::Voltage,NUM,Env>(instance_id,"ADCBase") {}
	//virtual void do_update(){}
	virtual ~ADCBase(){}
protected:
	//typename Env::GPIO<NUM> gpio_;
};

//! ADC�̃f�W�^���l�𕨗��l�ɕϊ����ĕێ�����R���|�[�l���g�D
/*! 
	�ϊ��{�̂̓|���V�[�N���X��convert���󂯎��D�N���XT��double�����implicit�ȃR���X�g���N�^�C�܂���double���E�ӂɎ��operator=�������Ă���K�v������(Scalar,Voltage�Ȃ�).
	@tparam T                �ێ����镨���l�̌^�D
	@tparam NUM              �ێ����镨���l�̃`���l�����D
	@tparam ADCNUM           �Ώۂ�ADC�������`���l�����D
	@tparam Env              �R���|�[�l���g�̊��N���X�D
	@tparam ConversionPolicy convert�֐��̎��������肷��ϊ��|���V�[�N���X�D
*/
template<class T, int NUM, int ADCNUM = NUM, class Env = ENV, class ConversionPolicy = FirstOrderConvert>
class MultiSensor : public CDHComponent< T, NUM, Env >, public ConversionPolicy {
public:
	MultiSensor(int instance_id, ADCBase<ADCNUM,Env>* adc, int offset) : adcsource_(adc), offset_(offset), CDHComponent< T, NUM, Env >(instance_id,"TempSensor")
	{
		assert(offset + NUM <= ADCNUM);//ADC�͈̔͂������Ȃ�
	}
	virtual void do_update(){
		for(int i = 0; i < NUM; i++){
			this->value_[i] = convert((*adcsource_)[i + offset_].value());
		}
	}
	virtual ~MultiSensor(){}
private:
	ADCBase<ADCNUM,Env>* adcsource_;
	int offset_;
};

} /* End of namespace stf::core::component */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_ADCBase_h
