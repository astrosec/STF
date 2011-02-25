/**
 * @file   RateDumping.cpp
 * @brief  レートダンピング則による3軸独立のトルク計算を行う制御ブロック．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#include "RateDumping.h"
#include "../../../datatype/Time.h"
#include "../../../util/Trace.h"

namespace stf {
namespace core {
namespace strategy {
namespace control {


RateDumping::RateDumping(int instance_id, double kp, double ki, double kd, double dt)
	: kp_(kp), kd_(kd), ki_(ki), dt_(dt), StrategyBase(instance_id, "RateDumping")
{
}

RateDumping::RateDumping(int instance_id, double kp, double ki, double kd, double dt,
		devicedriver::OutputPort<datatype::StaticVector<3>>* omega_source,
		devicedriver::InputPort<datatype::StaticVector<3>>* torque_target ) : kp_(kp), kd_(kd), ki_(ki), dt_(dt), StrategyBase(instance_id, "RateDumping")
{
	this->connect_source<0>(omega_source);
	torque_target->connect_source_(this);
}


void RateDumping::do_compute(const datatype::Time& t)
{
	if(t > this->last_update_){//既に別のブロック経由で更新済みなら再計算しない
		util::Trace trace(util::Trace::kControlBlock,name_);

		this->value_ = compute_torque_(this->source<0,datatype::StaticVector<3>>().get_value(t));
		this->last_update_ = t;
	}
}



datatype::StaticVector<3> RateDumping::compute_torque_(const datatype::StaticVector<3>& input)
{
	datatype::StaticVector<3> omage_diff = (input - this->omega_before_) / this->dt_;
	this->omega_before_ = input;
	this->omega_total_ += input * this->dt_;
	datatype::StaticVector<3> v;

	v[0] = - this->kp_ * input[0] - this->kd_ * omage_diff[0] - this->ki_ * this->omega_total_[0];
	v[1] = - this->kp_ * input[1] - this->kd_ * omage_diff[1] - this->ki_ * this->omega_total_[1];
	v[2] = - this->kp_ * input[2] - this->kd_ * omage_diff[2] - this->ki_ * this->omega_total_[2];

	return v;
}

} /* End of namespace stf::core::strategy::control */
} /* End of namespace stf::core::strategy */
} /* End of namespace stf::core */
} /* End of namespace stf */

