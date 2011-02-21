/**
 * @file   AOCSActuator.h
 * @brief  �A�N�`���G�[�^�̊��N���X�D
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_devicedriver_AOCSActuator_h
#define stf_core_devicedriver_AOCSActuator_h

#include "AOCSComponent.h"
#include "../../util/Ostream.h"

namespace stf {
namespace core {
namespace devicedriver {

//! �A�N�`���G�[�^�̊��N���X�D
/*! 
	@tparam T   �A�N�`���G�[�^���o�͂��镨���ʁD
	@tparam U   �A�N�`���G�[�^���o�͂��鎟���ł̕����ʁD3���A�N�`���G�[�^�Ȃ�T�ƈ�v�C1���Ȃ�Scalar�D
	@tparam Env �R���|�[�l���g�̊��N���X�D
*/
template<class T,class U = T,class Env = ENV>
class AOCSActuator : public AOCSComponent<T,U,Env>, public InputPorts< TYPELIST_1(U) > {
public:
	AOCSActuator(int instance_id, const datatype::String& name, const datatype::DCM& dcm) : AOCSComponent<T,U,Env>(instance_id,name,dcm){}
	virtual ~AOCSActuator(){}
	void setMaxOutput(const U& ref) { max_output_ = ref; }
    virtual void set_torque(U value) {
		if(value > this->max_output_) this->set_value(this->max_output_);//�T�`��
		else if(value < this->min_output_) this->set_value(this->min_output_);
		else 
			 this->set_value(value);
	}
protected:
	U max_output_;
	U min_output_;
	double sigma_;
private:
	AOCSActuator& operator = (const AOCSActuator& rhs);
    AOCSActuator();
	AOCSActuator(const AOCSActuator<T,U,Env>& rhs);
};

} /* End of namespace stf::core::component */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_AOCSActuator_h
