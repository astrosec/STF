/**
 * @file   GGCompensation.cpp
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#include "GGCompensation.h"
#include "../../../datatype/DateTime.h"
#include "../../../datatype/DCM.h"
#include "../../../datatype/OrbitCalc.h"
#include "../../../datatype/TypeConverter.h"
#include "../../../datatype/SatelliteModel.h"
#include "../../../GlobalObject.h"
#include "../../../datatype/StaticMatrix.h"

namespace stf {
namespace core {
namespace strategy {
namespace control {


GGCompensation::GGCompensation(int instance_id, 
		devicedriver::OutputPort<datatype::Quaternion>* q_source,
		devicedriver::OutputPort<datatype::PositionInfo>* position_source,
		devicedriver::InputPort<datatype::StaticVector<3>>* torque_out
		) : StrategyBase(instance_id, "GGCompensation")
{
	this->connect_source<0>(q_source);
	this->connect_source<1>(position_source);
	if(torque_out != 0){
		torque_out->connect_source_(this);
	}
}

void GGCompensation::do_compute(const datatype::Time& t) {
	if(t <= this->last_update_) return; //���ɕʂ̃u���b�N�o�R�ōX�V�ς݂Ȃ�Čv�Z���Ȃ�
	util::cout << "compute: ggcompensation" << util::endl;
	// �O�����Ǝp����񂩂�C�@�̍��W�ɂ�����n�������x�N�g�����Z�o
	datatype::StaticVector<3> R = datatype::OrbitCalc::getEarthDirectionInBodyFrame(
		this->source<1,datatype::PositionInfo>().get_in_bodyframe(t),
		this->source<0,datatype::Quaternion>().get_in_bodyframe(t));

	double r = R.norm(2);
	datatype::StaticVector<3> u = R / r;
	
	//TBD
	datatype::StaticMatrix<3,3> I;
	//datatype::StaticMatrix<3,3> I = Global<ENV>::get_satellitemodel().getI();

	//�d�͌X�΃g���N��ł������悤�ȃg���N���o��
	this->value_b_ = ( 3 * util::math::MU / ( r * r * r ) ) * u % (I * u);

	this->last_update_ = t;
}


} /* End of namespace core::mode::strategy::control */
} /* End of namespace core::mode::strategy */
} /* End of namespace core::mode */
} /* End of namespace core */
