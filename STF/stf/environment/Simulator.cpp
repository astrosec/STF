/**
 * @file   Simulator.cpp
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#include "Simulator.h"
//#include "core/devicedriver/gyro/Tamagawa_FOG.h"
//#include "core/strategy/input/EKF.h"

#include "../datatype/EulerAngle.h"
#include "../datatype/TypeConverter.h"
#include "../util/math/Rand.h"
#include "../util/math/RungeKutta.h"
#include "../datatype/OrbitCalc.h"
//#include "core/devicedriver/gyro/GyroDriver.h"

namespace stf {
namespace environment {

Simulator* Simulator::singleton_ = new Simulator();

void Simulator::init(Global<Simulator>* global, double stepTimeInSecond, double maxTimeInSecond, const datatype::OrbitInfo& orbit,  std::ofstream *ostream)
{
	util::math::WhiteNoise_init(0);
    this->global_ = global;
    this->timestep_.add_milliseconds(stepTimeInSecond * 1000);
    this->max_time_.add_milliseconds(maxTimeInSecond * 1000);
	this->orbit_.setOrbitElement(orbit);
    if(ostream != 0)
        this->ofstream_ = ostream;
}

Simulator& Simulator::getInstance(){
	return *singleton_;
}

Simulator::~Simulator()
{
	this->ofstream_->close();
}

datatype::MagneticField Simulator::getMagneticField(const core::devicedriver::AOCSComponent<datatype::MagneticField,datatype::MagneticField,Simulator> &component) const
{
	return component.getDCM().inverse() * this->orbit_.getMagneticField();
}

datatype::StaticVector<3> Simulator::getAngularVelocity(const core::devicedriver::AOCSComponent<datatype::StaticVector<3>,datatype::StaticVector<3>,Simulator> &component) const 
{
	datatype::StaticVector<3> v  = component.getDCM().inverse() * this->true_angular_velocity_;
	return v;
}

datatype::Scalar Simulator::getAngularVelocity(const core::devicedriver::AOCSComponent<datatype::StaticVector<3>,datatype::Scalar,Simulator> &component) const 
{
	datatype::StaticVector<3> v  = component.getDCM().inverse() * this->true_angular_velocity_;
	return v[2];
}

datatype::Quaternion Simulator::getQuaternion(const core::devicedriver::AOCSComponent<datatype::Quaternion,datatype::Quaternion,Simulator> &component) const 
{
	datatype::Quaternion q = datatype::TypeConverter::toQuaternion(component.getDCM()).conjugate();
	return  q * this->true_quaternion_;
}

datatype::StaticVector<2> Simulator::getSunDirection(const core::devicedriver::AOCSComponent<datatype::StaticVector<2>,datatype::StaticVector<2>,Simulator> &component) const 
{
	return datatype::TypeConverter::toPolar(component.getDCM().inverse() * datatype::OrbitCalc::getSunDirectionInBodyFrame(this->orbit_.getTime(), this->true_quaternion_));
}

datatype::StaticVector<2> Simulator::getEarthDirection(const core::devicedriver::AOCSComponent<datatype::StaticVector<2>,datatype::StaticVector<2>,Simulator> &component) const 
{
	return datatype::TypeConverter::toPolar(component.getDCM().inverse() * datatype::OrbitCalc::getEarthDirectionInBodyFrame(this->orbit_.getSatellitePosition(), this->true_quaternion_));
}

const datatype::PositionInfo Simulator::getTrueSatellitePosition() const
{
	return this->orbit_.getSatellitePosition();
}

datatype::Time Simulator::getTime(const core::devicedriver::clock::ITimeClock &component) const 
{
    return this->true_time_;
}

void Simulator::start()
{
    std::cout << "Simulator Start" << std::endl;
    while(this->true_time_ < this->max_time_){
        this->runOneCycle();
    }
}

void Simulator::runOneCycle()
{
	if(this->ofstream_ != 0){
		//Logging
		(*this->ofstream_) 
			<< this->true_time_.total_seconds() << ","
			<< this->true_quaternion_[0] << ","
			<< this->true_quaternion_[1] << ","
			<< this->true_quaternion_[2] << ","
			<< this->true_quaternion_[3] << ","
			<< this->true_angular_velocity_[0] << ","
			<< this->true_angular_velocity_[1] << ","
			<< this->true_angular_velocity_[2] << ","
			<< this->true_torque_[0] << ","
			<< this->true_torque_[1] << ","
			<< this->true_torque_[2] << ","
			<< this->noise_torque_[0] << ","
			<< this->noise_torque_[1] << ","
			<< this->noise_torque_[2] << "\n";
            /*<< this->global_->fog1->bias_rate_ << ","
            << this->global_->fog2->bias_rate_ << ","
            << this->global_->fog3->bias_rate_ << ","
            << this->global_->ekf->q_[0] << ","
            << this->global_->ekf->q_[1] << ","
            << this->global_->ekf->q_[2] << ","
            << this->global_->ekf->q_[3] << ","
            << this->global_->ekf->bref_[0] << ","
            << this->global_->ekf->bref_[1] << ","
            << this->global_->ekf->bref_[2] << "\n";*/
	}

	datatype::List<core::manager::ManagerBase>::iterator itr = this->global_->getFunctionManager()->begin();
	while( itr !=  this->global_->getFunctionManager()->end() ){
		(*itr).run();
		++itr;
	}

    this->true_torque_.reset();//�g���N����U���Z�b�g���C�O���\�[�X����v�Z���Ȃ���
    std::vector<TorqueSource*>::iterator it = this->torque_sources_.begin();
    while( it != this->torque_sources_.end()){
		this->true_torque_ += (*it)->getValueInBodyFrame();
        ++it;
    }
	this->noise_torque_.reset();
	std::vector< torquesource::NoiseBase* >::iterator it2 = this->noise_sources_.begin();
    while( it2 != this->noise_sources_.end()){
		this->noise_torque_ += (*it2)->getTorqueInBodyFrame();
        ++it2;
    }

    //���X�e�b�v�̌v�Z
    datatype::Vector acc(3);//�p�����x
	acc[0] = this->true_torque_[0] + this->noise_torque_[0];
    acc[1] = this->true_torque_[1] + this->noise_torque_[1];
    acc[2] = this->true_torque_[2] + this->noise_torque_[2];//TBD:�q���̎��ʓ����Ŋ���K�v

    datatype::Vector omega(3);//�p���x��n+1����n�{at
	omega[0] = this->true_angular_velocity_[0] + acc[0] * this->timestep_.total_seconds();
    omega[1] = this->true_angular_velocity_[1] + acc[1] * this->timestep_.total_seconds();
    omega[2] = this->true_angular_velocity_[2] + acc[2] * this->timestep_.total_seconds();

    Omega_[0][1] = -omega[0];
    Omega_[0][2] = -omega[1];
    Omega_[0][3] = -omega[2];
    Omega_[1][2] =  omega[2];
    Omega_[1][3] = -omega[1];
    Omega_[2][3] =  omega[0];
    for(int i = 0; i < 4; i++)
      for(int j = 0; j < 4; j++)
        if(i > j) Omega_[i][j] = -Omega_[j][i];

    this->true_quaternion_ += util::math::RungeKutta::slope(true_quaternion_,0.5 * Omega_,timestep_.total_seconds());
    this->true_angular_velocity_ = omega;
	this->step_();
}

void Simulator::attachTorqueSource(TorqueSource* source)
{
    this->torque_sources_.push_back(source);
}

void Simulator::attachNoiseSource(torquesource::NoiseBase* source)
{
	this->noise_sources_.push_back(source);
}

void Simulator::attachMagneticSource(MagneticSource* source)
{
	this->mag_sources_.push_back(source);
}

Simulator::Simulator()
: true_torque_(3),Omega_(4,4), orbit_()
{
	util::math::WhiteNoise_init(0);
}

} /* End of namespace core::environment */
} /* End of namespace core */