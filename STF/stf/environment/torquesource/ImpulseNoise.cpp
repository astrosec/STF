/**
 * @file   ImpulseNoise.cpp
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#include "ImpulseNoise.h"
#include "../Simulator.h"

namespace stf {
namespace environment {
namespace torquesource {

ImpulseNoise::ImpulseNoise(double magnitude, const datatype::Vector &vector, const int &startTimeInSecond, const double &durationInMillisec, environment::Simulator *env)
: NoiseBase(env), vector_(vector), magnitude_(magnitude), starttime_(startTimeInSecond,0), duration_(0,durationInMillisec)
{
}

ImpulseNoise::ImpulseNoise(double magnitude, stf::environment::Simulator *env)
: NoiseBase(env), magnitude_(magnitude)
{
	this->duration_.add_seconds(1);
    datatype::Vector v(3);
    v[2] = 1;//Z軸まわりの1秒トルクをデフォルトとする．
    this->vector_ = v;
}

ImpulseNoise::~ImpulseNoise()
{
}

double ImpulseNoise::get_torque() const 
{
    return this->magnitude_;
}

datatype::Vector ImpulseNoise::get_torque_bodyframe() const 
{
    if(this->starttime_ <= this->environment_->getTrueTime())
        if(this->starttime_ + this->duration_ > this->environment_->getTrueTime())
            return this->magnitude_ * this->vector_;//計算時間刻みがインパルスより十分細かくないと不正確

    datatype::Vector v(3);
    return v;
}

void ImpulseNoise::set_torque(double value)
{
    this->magnitude_ = value;
}

ImpulseNoise::ImpulseNoise() : NoiseBase(0)
{
}

} /* End of namespace stf::environment::torquesource */
} /* End of namespace stf::environment */
} /* End of namespace stf */
