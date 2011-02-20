/**
 * @file   CrossProduct.cpp
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#include "CrossProduct.h"
#include "../../../datatype/DCM.h"
#include "../../../datatype/OrbitCalc.h"
#include "../../../datatype/TypeConverter.h"
#include "../../../GlobalObject.h"

namespace stf {
namespace core {
namespace strategy {
namespace control {


CrossProduct::CrossProduct(int instance_id, 
		devicedriver::OutputPort<datatype::StaticVector<3>>* torquer_source,
		devicedriver::OutputPort<datatype::MagneticField>* b_source,
		devicedriver::InputPort<datatype::MagneticMoment>* mag_out
		) : StrategyBase(instance_id, "CrossProduct")
{
	this->connect_source<0>(torquer_source);
	this->connect_source<1>(b_source);
	if(mag_out != 0){
		mag_out->connect_source_(this);
	}
}

void CrossProduct::do_compute(const datatype::Time& t) {
	if(t <= this->last_update_) return; //���ɕʂ̃u���b�N�o�R�ōX�V�ς݂Ȃ�Čv�Z���Ȃ�
	util::cout << "compute: crossproduct" << util::endl;	
	// M = B * T / |B|2
	datatype::MagneticField B = this->source<1,datatype::MagneticField>().get_in_bodyframe(t);
	datatype::StaticVector<3> T = this->source<0,datatype::StaticVector<3>>().get_in_bodyframe(t);

	this->value_b_ = (B % T) / (B.norm(2) * B.norm(2));

	this->last_update_ = t;
}


} /* End of namespace core::mode::strategy::control */
} /* End of namespace core::mode::strategy */
} /* End of namespace core::mode */
} /* End of namespace core */
