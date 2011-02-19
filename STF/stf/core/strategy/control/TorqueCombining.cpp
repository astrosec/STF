/**
 * @file   TorqueCombining.cpp
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#include "TorqueCombining.h"
#include "../../../datatype/TypeConverter.h"

namespace stf {
namespace core {
namespace strategy {
namespace control {

TorqueCombining::TorqueCombining(int instance_id) : StrategyBase(instance_id, "TorqueCombining")
{

}
TorqueCombining::TorqueCombining(int instance_id,
		devicedriver::OutputPort<datatype::StaticVector<3>>* source_1, 
		devicedriver::OutputPort<datatype::StaticVector<3>>* source_2,
		devicedriver::OutputPort<datatype::StaticVector<3>>* source_3,
		devicedriver::InputPort<datatype::StaticVector<3>>* torque_out) : StrategyBase(instance_id, "TorqueCombining")
{
	this->connectSource<0>(source_1);
	this->connectSource<1>(source_2);
	this->connectSource<2>(source_3);
	torque_out->connectSource_(this);
}


void TorqueCombining::do_compute(const datatype::Time& t)
{
	if(t > this->last_update_){//���ɕʂ̃u���b�N�o�R�ōX�V�ς݂Ȃ�Čv�Z���Ȃ�
		util::cout << "compute: torqueCombine" << util::endl;
		this->value_b_.reset();
		this->value_b_ += this->source<0,datatype::StaticVector<3>>().getValueInBodyFrame(t);
		this->value_b_ += this->source<1,datatype::StaticVector<3>>().getValueInBodyFrame(t);
		this->value_b_ += this->source<2,datatype::StaticVector<3>>().getValueInBodyFrame(t);
		this->last_update_ = t;
	}
}



} /* End of namespace stf::core::strategy::control */
} /* End of namespace stf::core::strategy */
} /* End of namespace stf::core */
} /* End of namespace stf */