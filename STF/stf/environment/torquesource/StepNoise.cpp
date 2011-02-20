/**
 * @file   StepNoise.cpp
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#include "../Simulator.h"
#include "StepNoise.h"

namespace stf {
namespace environment {
namespace torquesource {

StepNoise::StepNoise(double magnitude, stf::environment::Simulator *env)
: magnitude_(magnitude), NoiseBase(env)
{
    vector_[0] = 1;//�f�t�H���g��X���܂��̃g���N
}

StepNoise::StepNoise(double magnitude, const datatype::StaticVector<3> &vector, const int &startTimeInSecond, stf::environment::Simulator *env)
: magnitude_(magnitude), vector_(vector), starttime_(startTimeInSecond,0), NoiseBase(env)
{
}

StepNoise::~StepNoise()
{
}

double StepNoise::get_torque() const 
{
    return this->magnitude_;
}

void StepNoise::set_torque(double value)
{
    this->magnitude_ = value;
}

datatype::StaticVector<3> StepNoise::get_torque_bodyframe() const 
{
	if(this->starttime_ >= this->environment_->getTrueTime())
        return this->magnitude_ * this->vector_;
    datatype::StaticVector<3> v;
    return v;
}

StepNoise::StepNoise()
: magnitude_(0), NoiseBase(0)
{
}

} /* End of namespace stf::environment::torquesource */
} /* End of namespace stf::environment */
} /* End of namespace stf */
