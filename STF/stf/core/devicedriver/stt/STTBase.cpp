/**
 * @file   STTBase.cpp
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#include "STTBase.h"
#include "../../../datatype/TypeConverter.h"
#include "../../../environment/Simulator.h"
#include "../../datapool/Datapool.h"
#include "../../../util/math/Rand.h"
#include "../../../util/math.h"

namespace stf {
namespace core {
namespace devicedriver {
namespace stt {

//STT�{�̂�Quaternion
//�V�~�����[�^���ł�STT���W�n�ł̐^�l���擾����
template <>
void STTBase<environment::Simulator>::doUpdate(){
	count_++;
	if(count_ >= 5){
		this->setValue(inputFilter(this->environment_->getQuaternion(*this)));
		if(this->datapool_ != 0){
			datapool_->set<STTBase<environment::Simulator>>(datapool_hold_index_,this->value_);
		}
		count_ = 0;
	}
}
template <>
datatype::Quaternion STTBase<environment::Simulator>::inputFilter(const datatype::Quaternion& value){
	datatype::EulerAngle angle;
	angle[0] = util::math::WhiteNoise(this->err_arcsec_ * util::math::ARCSEC2RAD ,0) / 3;
	angle[1] = util::math::WhiteNoise(this->err_arcsec_ * util::math::ARCSEC2RAD, 0) / 3;
	angle[2] = util::math::WhiteNoise(this->err_arcsec_ * util::math::ARCSEC2RAD, 0) / 3;
	return datatype::TypeConverter::toQuaternion(angle) * value;
}

/*STTBase::STTBase(const datatype::DCM &angle, interface::IEnvironment *env)
: set_angle_(angle), core::devicedriver::EnvironmentActor(env)
{
}

datatype::Quaternion STTBase::getQuaternion() const 
{
    return this->environment_->getQuaternion(*this);
}

datatype::Quaternion STTBase::getVirtualQuaternion(datatype::Quaternion q_true) const 
{
    datatype::Quaternion q = q_true;
    for(int i = 0; i < 4; i++)
        q[i] += util::math::WhiteNoise(sigma_,0);//TBD:q�͌����܂��̐��x������
    return q;
}*/

} /* End of namespace stf::core::devicedriver::stt */
} /* End of namespace stf::core::devicedriver */
} /* End of namespace stf::core */
} /* End of namespace stf */
