/**
 * @file   MagneticMomentToTorque.cpp
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#include "MagneticMomentToTorque.h"

namespace stf {
namespace core {
namespace strategy {
namespace control {


MagneticMomentToTorque::MagneticMomentToTorque(int instance_id, 
		devicedriver::OutputPort<datatype::MagneticMoment>* mag_body_source,
		devicedriver::OutputPort<datatype::MagneticMoment>* mag_out_source,
		devicedriver::InputPort<datatype::StaticVector<3>>* torque_out
		) : StrategyBase(instance_id, "MagneticMomentToTorque")
{
	this->connectSource<0>(mag_body_source);
	this->connectSource<1>(mag_out_source);
	if(torque_out != 0){
		torque_out->connectSource_(this);
	}
}

void MagneticMomentToTorque::do_compute(const datatype::Time& t) {
	if(t <= this->last_update_) return; //���ɕʂ̃u���b�N�o�R�ōX�V�ς݂Ȃ�Čv�Z���Ȃ�
	util::cout << "compute: MM->Torque" << util::endl;
	// T = M * B
	this->value_b_ = 
		this->source<1,datatype::MagneticMoment>().getValueInBodyFrame(t) % 
		this->source<0,datatype::MagneticMoment>().getValueInBodyFrame(t);

	this->last_update_ = t;
}


} /* End of namespace core::mode::strategy::control */
} /* End of namespace core::mode::strategy */
} /* End of namespace core::mode */
} /* End of namespace core */
