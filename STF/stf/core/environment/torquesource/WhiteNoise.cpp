/**
 * @file   WhiteNoise.cpp
 * @brief  ホワイトノイズを発生させるトルク源．Torque source that produces white noise
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#include "WhiteNoise.h"
#include "../../../util/math/Rand.h"

namespace stf {
namespace core {
namespace environment {
namespace torquesource {


WhiteNoise::~WhiteNoise()
{
}

WhiteNoise::WhiteNoise(double sigma, double mu): sigma_(sigma), mu_(mu), NoiseBase(0)
{
}


double WhiteNoise::get_torque() const 
{
    return this->sigma_;//TBD:分散を返すのはインターフェースとして正しい？s returning the variance correct for an interface?
}


datatype::StaticVector<3> WhiteNoise::get_torque_bodyframe() const 
{
    datatype::StaticVector<3> v;
    for(int i = 0; i < 3; i++){
        v[i] = util::math::WhiteNoise(this->sigma_, this->mu_);
    }
    return v;
}


void WhiteNoise::set_torque(double value)
{
    this->sigma_ = value;
}


} /* End of namespace stf::core::environment::torquesource */
} /* End of namespace stf::core::environment */
} /* End of namespace stf::core */
} /* End of namespace stf */
