/**
 * @file   TRIAD.cpp
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#include "TRIAD.h"
#include "../../../datatype/DateTime.h"
#include "../../../datatype/DCM.h"
#include "../../../datatype/OrbitCalc.h"
#include "../../../datatype/TypeConverter.h"
#include "../../../GlobalObject.h"

namespace stf {
namespace core {
namespace strategy {
namespace control {

//TRIAD���ʂ̌v�Z�𖳖����O��ԂɓZ�߂�D
namespace {
datatype::Quaternion estimate_(
	datatype::StaticVector<3> v1, datatype::StaticVector<3> v2, 
	datatype::StaticVector<3> w1, datatype::StaticVector<3> w2)
{
	//util::cout << v1 << "," << v2 << "," << w1 << "," << w2 << util::endl;
	datatype::StaticVector<3> r1 = v1;
	datatype::StaticVector<3> s1 = w1;
	datatype::StaticVector<3> r2 = (r1 % v2) / (r1 % v2).norm(2);
	datatype::StaticVector<3> s2 = (s1 % w2) / (s1 % w2).norm(2);
	datatype::StaticVector<3> r3 = r1 % r2;
	datatype::StaticVector<3> s3 = s1 % s2;
	datatype::DCM dcm;
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			dcm[i][j] = s1[i] * r1[j] + s2[i] * r2[j] + s3[i] * r3[j];
			dcm[i][j] = s1[i] * r1[j] + s2[i] * r2[j] + s3[i] * r3[j];
			dcm[i][j] = s1[i] * r1[j] + s2[i] * r2[j] + s3[i] * r3[j];
		}
	}
	//util::cout << dcm;
	return datatype::TypeConverter::toQuaternion(dcm);
}
}

TRIAD::TRIAD(int instance_id, 
		devicedriver::OutputPort<datatype::StaticVector<2>>* body_vector1,
		devicedriver::OutputPort<datatype::StaticVector<2>>* inertial_vector1,
		devicedriver::OutputPort<datatype::StaticVector<2>>* body_vector2,
		devicedriver::OutputPort<datatype::StaticVector<2>>* inertial_vector2,
		devicedriver::InputPort<datatype::Quaternion>* q_out
		) : StrategyBase(instance_id, "TRIAD")
{
	this->connectSource<0>(body_vector1);
	this->connectSource<1>(inertial_vector1);
	this->connectSource<2>(body_vector2);
	this->connectSource<3>(inertial_vector2);
	if(q_out != 0){
		q_out->connectSource_(this);
	}
}

void TRIAD::do_compute(const datatype::Time& t) {
	if(t <= this->last_update_) return; //���ɕʂ̃u���b�N�o�R�ōX�V�ς݂Ȃ�Čv�Z���Ȃ�
	util::cout << "compute: GenericTRIAD" << util::endl;
	datatype::StaticVector<3> v1 = datatype::TypeConverter::toRectangular(
		this->source<0,datatype::StaticVector<2>>().getValueInBodyFrame(t));

	datatype::StaticVector<3> v2 = datatype::TypeConverter::toRectangular(
		this->source<2,datatype::StaticVector<2>>().getValueInBodyFrame(t));

	datatype::StaticVector<3> w1 = datatype::TypeConverter::toRectangular(
		this->source<1,datatype::StaticVector<2>>().getValueInBodyFrame(t));

	datatype::StaticVector<3> w2 = datatype::TypeConverter::toRectangular(
		this->source<3,datatype::StaticVector<2>>().getValueInBodyFrame(t));

	this->value_b_ = estimate_(v1, v2, w1, w2);
	this->last_update_ = t;
}


SunEarthTRIAD::SunEarthTRIAD(int instance_id, 
		devicedriver::OutputPort<datatype::StaticVector<2>>* sunvector_source,
		devicedriver::OutputPort<datatype::StaticVector<2>>* earthvector_source,
		devicedriver::OutputPort<datatype::PositionInfo>* position_source,	
		devicedriver::OutputPort<datatype::DateTime>* time_source,
		devicedriver::InputPort<datatype::Quaternion>* q_out
		) : StrategyBase(instance_id, "TRIAD")
{
	this->connectSource<0>(sunvector_source);
	this->connectSource<1>(earthvector_source);
	this->connectSource<2>(position_source);
	this->connectSource<3>(time_source);
	if(q_out != 0){
		q_out->connectSource_(this);
	}
}

void SunEarthTRIAD::do_compute(const datatype::Time& t) {
	if(t <= this->last_update_) return; //���ɕʂ̃u���b�N�o�R�ōX�V�ς݂Ȃ�Čv�Z���Ȃ�
	util::cout << "compute: SunEarthTRIAD" << util::endl;
	//�Z���T����擾�����q������W�n�ɂ�����n���C���z����
	datatype::StaticVector<2> w_sun = this->source<0,datatype::StaticVector<2>>().getValueInBodyFrame(t);
	datatype::StaticVector<2> w_earth = this->source<1,datatype::StaticVector<2>>().getValueInBodyFrame(t);
	//�O���������ƂɌv�Z���ꂽ�q���ʒu�ɂ�����n���C���z����
	datatype::StaticVector<3> v1 = datatype::OrbitCalc::getSunDirection3D(this->source<3,datatype::DateTime>().getValueInBodyFrame());
	datatype::StaticVector<3> v2 = datatype::OrbitCalc::getEarthDirection3D(this->source<2,datatype::PositionInfo>().getValueInBodyFrame(t));

	datatype::StaticVector<3> w1 = datatype::TypeConverter::toRectangular(w_sun);
	datatype::StaticVector<3> w2 = datatype::TypeConverter::toRectangular(w_earth);

	this->value_b_ = estimate_(v1, v2, w1, w2);
	this->last_update_ = t;
}

SunMagTRIAD::SunMagTRIAD(int instance_id, 
		devicedriver::OutputPort<datatype::StaticVector<2>>* sunvector_source,
		devicedriver::OutputPort<datatype::MagneticField>* magvector_source,
		devicedriver::OutputPort<datatype::PositionInfo>* position_source,
		devicedriver::OutputPort<datatype::DateTime>* time_source,
		devicedriver::InputPort<datatype::Quaternion>* q_out
		) : StrategyBase(instance_id, "TRIAD")
{
	this->connectSource<0>(sunvector_source);
	this->connectSource<1>(magvector_source);
	this->connectSource<2>(position_source);
	this->connectSource<3>(time_source);
	if(q_out != 0){
		q_out->connectSource_(this);
	}
}

void SunMagTRIAD::do_compute(const datatype::Time& t) {
	if(t <= this->last_update_) return; //���ɕʂ̃u���b�N�o�R�ōX�V�ς݂Ȃ�Čv�Z���Ȃ�
		util::cout << "compute: SunMagTRIAD" << util::endl;
	//�Z���T����擾�����q������W�n�ɂ�����n���C���z����
	datatype::StaticVector<2> w_sun = this->source<0,datatype::StaticVector<2>>().getValueInBodyFrame(t);
	datatype::MagneticField w_mag = this->source<1,datatype::MagneticField>().getValueInBodyFrame(t);
	//�O���������ƂɌv�Z���ꂽ�q���ʒu�ɂ�����n���C���z����
	datatype::DateTime time = this->source<3,datatype::DateTime>().getValueInBodyFrame();

	datatype::MagneticField v_mag = 
		datatype::OrbitCalc::getMagneticFieldDirection(this->source<2,datatype::PositionInfo>().getValueInBodyFrame(t),time);
	datatype::StaticVector<3> v1 = datatype::OrbitCalc::getSunDirection3D(time);
	datatype::StaticVector<3> w1 = datatype::TypeConverter::toRectangular(w_sun);

	this->value_b_ = estimate_(v1, v_mag, w1, w_mag);
	this->last_update_ = t;
}

SunMagTRIAD2::SunMagTRIAD2(int instance_id, 
		devicedriver::clock::IAbsoluteTimeClock* clock,
		devicedriver::OutputPort<datatype::StaticVector<2>>* sunvector_source,
		devicedriver::OutputPort<datatype::MagneticField>* magvector_source,
		devicedriver::OutputPort<datatype::PositionInfo>* position_source,
		devicedriver::InputPort<datatype::Quaternion>* q_out
		) : StrategyBase(instance_id, "TRIAD"), clock_(clock)
{
	if(sunvector_source != 0) this->connectSource<0>(sunvector_source);
	if(magvector_source != 0) this->connectSource<1>(magvector_source);
	if(position_source != 0) this->connectSource<2>(position_source);

	if(q_out != 0){
		q_out->connectSource_(this);
	}
}

void SunMagTRIAD2::do_compute(const datatype::Time& t) {
	if(t <= this->last_update_) return; //���ɕʂ̃u���b�N�o�R�ōX�V�ς݂Ȃ�Čv�Z���Ȃ�
		util::cout << "compute: SunMagTRIAD" << util::endl;
	//�Z���T����擾�����q������W�n�ɂ�����n���C���z����
	datatype::StaticVector<2> w_sun = this->source<0,datatype::StaticVector<2>>().getValueInBodyFrame(t);
	datatype::MagneticField w_mag = this->source<1,datatype::MagneticField>().getValueInBodyFrame(t);
	//�O���������ƂɌv�Z���ꂽ�q���ʒu�ɂ�����n���C���z����
	datatype::DateTime time = this->clock_->getAbsoluteTime();

	datatype::MagneticField v_mag = 
		datatype::OrbitCalc::getMagneticFieldDirection(this->source<2,datatype::PositionInfo>().getValueInBodyFrame(t),time);
	datatype::StaticVector<3> v1 = datatype::OrbitCalc::getSunDirection3D(time);
	datatype::StaticVector<3> w1 = datatype::TypeConverter::toRectangular(w_sun);

	this->value_b_ = estimate_(v1, v_mag, w1, w_mag);
	this->last_update_ = t;
}

} /* End of namespace core::mode::strategy::control */
} /* End of namespace core::mode::strategy */
} /* End of namespace core::mode */
} /* End of namespace core */
