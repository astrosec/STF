/**
 * @file   MTQBase.cpp
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#include "MTQBase.h"
#include "../../../environment/Simulator.h"
#include "../../datapool/Datapool.h"

namespace stf {
namespace core {
namespace devicedriver {
namespace mtq {


template <>
void MTQBase<environment::Simulator>::do_update(){
	//���`���덷�̕t����TBD
	//this->linearity_ * 0.01
	//DB�֋L�^
	if(this->datapool_ != 0){
		datapool_->set<MTQBase<environment::Simulator>>(this->datapool_hold_index_,this->value_);
	}
}

// �V�~�����[�^�p�̓��ꉻ�ŃR���X�g���N�^�D
// �g���N�\�[�X�Ƃ��ăV�~�����[�^�Ɏ����I�ɓo�^
template<>
MTQBase<environment::Simulator>::MTQBase(int instance_id, const datatype::DCM &dcm, double max_torque, double min_torque, double linearity) 
	: AOCSActuator<datatype::MagneticMoment, datatype::Scalar, environment::Simulator>(instance_id, "MTQ", dcm), linearity_(linearity)
{
	this->max_output_ = max_torque;
	this->min_output_ = min_torque;	
	this->environment_->attachMagneticSource(this);
}

} /* End of namespace stf::core::devicedriver::mtq */
} /* End of namespace stf::core::devicedriver */
} /* End of namespace stf::core */
} /* End of namespace stf */
