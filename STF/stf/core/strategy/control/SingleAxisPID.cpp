#include "SingleAxisPID.h"
#include "../../../datatype/TypeConverter.h"

namespace stf {
namespace core {
namespace strategy {
namespace control {


SingleAxisPID::SingleAxisPID(int instance_id, double kp, double ki, double kd, double dt, const datatype::Scalar &target)
	: kp_(kp), kd_(kd), ki_(ki), dt_(dt), target_(target), StrategyBase(instance_id, "SingleAxisPID")
{
}

SingleAxisPID::SingleAxisPID(int instance_id, double kp, double ki, double kd, double dt, const datatype::Scalar &target, 
		devicedriver::OutputPort<datatype::Scalar>* source, 
		devicedriver::InputPort<datatype::Scalar>* out)
	: kp_(kp), kd_(kd), ki_(ki), dt_(dt), target_(target), StrategyBase(instance_id, "SingleAxisPID")
{
	this->connectSource<0>(source);
	out->connectSource_(this);
}

void SingleAxisPID::do_compute(const datatype::Time& t)
{
	assert(this->prevholder_ != 0);//input source������
	if(t > this->last_update_){//���ɕʂ̃u���b�N�o�R�ōX�V�ς݂Ȃ�Čv�Z���Ȃ�
		util::cout << "compute: SingleAxisPID" << util::endl;
		this->value_b_ = computeTorque_(this->source<0,datatype::Scalar>().getValueInBodyFrame(t));
		this->last_update_ = t;
	}
}


datatype::Scalar SingleAxisPID::computeTorque_(const datatype::Scalar &x)
{
	this->dx_total_ += (x - target_) * this->dt_;

	//�I�C���[�p��Z-Y-X�\���Ȃ̂ɑ΂��ăg���N��X-Y-Z�̏��D���Ԃɒ���
	datatype::Scalar output;	
	output = this->kp_ * (x - target_)
		      + this->kp_ * ( x - x_old_) / this->dt_ 
			  + this->ki_ * dx_total_;

	this->x_old_ = x;

	return output;
}



} /* End of namespace stf::core::strategy::control */
} /* End of namespace stf::core::strategy */
} /* End of namespace stf::core */
} /* End of namespace stf */