/**
 * @file   WheelUnloading.cpp
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#include "WheelUnloading.h"

namespace stf {
namespace core {
namespace strategy {
namespace control {


WheelUnloading::WheelUnloading(int instance_id, 
		devicedriver::OutputPort<datatype::PositionInfo>* position_source,
		devicedriver::InputPort<datatype::StaticVector<3>>* torquer_out,
		devicedriver::InputPort<datatype::StaticVector<3>>* wheel_out
		) : StrategyBase(instance_id, "WheelUnloading")
{
	this->connectSource<0>(position_source);
	if(torquer_out != 0){
		torquer_out->connectSource_(&outputport<0,datatype::StaticVector<3>>());
	}
	if(wheel_out != 0){
		wheel_out->connectSource_(&outputport<1,datatype::StaticVector<3>>());
	}
}

void WheelUnloading::do_compute(const datatype::Time& t) {
	//if(t <= this->last_update_) return; //���ɕʂ̃u���b�N�o�R�ōX�V�ς݂Ȃ�Čv�Z���Ȃ�
	util::cout << "compute: Wheel Unloading" << util::endl;
	//this->last_update_ = t;
}


} /* End of namespace core::mode::strategy::control */
} /* End of namespace core::mode::strategy */
} /* End of namespace core::mode */
} /* End of namespace core */