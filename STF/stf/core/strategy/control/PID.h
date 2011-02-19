/**
 * @file   PID.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_strategy_control_PID_h
#define stf_core_strategy_control_PID_h
#include <assert.h>
#include "IControlStrategy.h"
#include "../../devicedriver/IOPort.h"
#include "../../manager/ControlManager.h"
#include "../StrategyBase.h"


#include "../../../datatype/StaticVector.h"
#include "../../../datatype/Quaternion.h"
#include "../../../datatype/EulerAngle.h"
#include "../../../datatype/OrbitInfo.h"

namespace stf {
namespace datatype {
class Time;
}
namespace core {
namespace strategy {
namespace control {

// Quaternion�Ɗp���x����t�B�[�h�o�b�N������s��3��PID�����D�ڕWQuaternion�͊����n�ɑ΂��ČŒ�
class PID : public devicedriver::InputPorts< TYPELIST_2(datatype::Quaternion, datatype::StaticVector<3>) >, 
		public devicedriver::OutputPorts < TYPELIST_1(datatype::StaticVector<3>) > ,
		public StrategyBase
{
public:
    PID(int instance_id, double kp, double ki, double kd, double dt, const datatype::Quaternion &target);
	PID(int instance_id, double kp, double ki, double kd, double dt, const datatype::Quaternion &target, 
		devicedriver::OutputPort<datatype::Quaternion>* q_source, 
		devicedriver::OutputPort<datatype::StaticVector<3>>* omega_source, 
		devicedriver::InputPort<datatype::StaticVector<3>>* torque_out);
	~PID(){}
	void setPIDGain(double kp, double ki, double kd){
		kp_ = kp;
		ki_ = ki;
		kd_ = kd;
	}
	virtual void do_compute(const datatype::Time& t);
protected:
	datatype::StaticVector<3> computeTorque_(const datatype::EulerAngle& x, const datatype::EulerAngle& x_delta, const datatype::EulerAngle& x_total);
    double kp_;
    double ki_;
    double kd_;
	double dt_;
    //�ڕWquaternion.
    datatype::Quaternion q_target_;
    //1�X�e�b�v�O�̃I�C���[�p�덷(��������Ɏg�p)
    datatype::EulerAngle e_before_;
    //�p���p�̌덷�ϕ��l�i�ϕ�����Ɏg�p�j�D
    datatype::EulerAngle e_total_;
};

// Quaternion����t�B�[�h�o�b�N������s��3��PID�����.
class QuaternionPID : public PID
{
public:
    QuaternionPID(int instance_id, double kp, double ki, double kd, double dt, const datatype::Quaternion &target);
	QuaternionPID(int instance_id, double kp, double ki, double kd, double dt, const datatype::Quaternion &target, 
		devicedriver::OutputPort<datatype::Quaternion>* q_source, 
		devicedriver::InputPort<datatype::StaticVector<3>>* torque_out);
	~QuaternionPID(){}
	virtual void do_compute(const datatype::Time& t);
private:
};

// �n���w���̃|�C���e�B���O������s��3��PID�����.
class EarthPointingPID : public devicedriver::InputPorts< TYPELIST_3(datatype::Quaternion, datatype::StaticVector<3>, datatype::PositionInfo) >, 
		public devicedriver::OutputPorts < TYPELIST_1(datatype::StaticVector<3>) > ,
		public StrategyBase
{
public:
	EarthPointingPID(int instance_id, double kp, double ki, double kd, double dt, const datatype::StaticVector<3>& target);
	EarthPointingPID(int instance_id, double kp, double ki, double kd, double dt, const datatype::StaticVector<3>& target,
		devicedriver::OutputPort<datatype::Quaternion>* q_source, 
		devicedriver::OutputPort<datatype::StaticVector<3>>* omega_source, 
		devicedriver::OutputPort<datatype::PositionInfo>* position_source,
		devicedriver::InputPort<datatype::StaticVector<3>>* torque_out);

	~EarthPointingPID(){}
	void setPIDGain(double kp, double ki, double kd){
		kp_ = kp;
		ki_ = ki;
		kd_ = kd;
	}
	virtual void do_compute(const datatype::Time& t);
protected:
    double kp_;
    double ki_;
    double kd_;
	double dt_;
	//���ҍ��W�n�ɂ�����ڕW�̒n�������x�N�g���B
	datatype::StaticVector<3> target_earthvector_;
	//���݂̒n�������x�N�g���D
	datatype::StaticVector<3> earthvector_;
    //1�X�e�b�v�O�̃I�C���[�p�덷(��������Ɏg�p)
    datatype::EulerAngle e_before_;
    //�p���p�̌덷�ϕ��l�i�ϕ�����Ɏg�p�j�D
    datatype::EulerAngle e_total_;
};

// �ڕWQuaternion���O�����璀�����͂���PID�R���g���[���D
class DynamicPID : public devicedriver::InputPorts< TYPELIST_3(datatype::Quaternion, datatype::StaticVector<3>, datatype::Quaternion) >, 
		public devicedriver::OutputPorts < TYPELIST_1(datatype::StaticVector<3>) > ,
		public StrategyBase
{
public:
	DynamicPID(int instance_id, double kp, double ki, double kd, double dt);
	DynamicPID(int instance_id, double kp, double ki, double kd, double dt,
		devicedriver::OutputPort<datatype::Quaternion>* q_source, 
		devicedriver::OutputPort<datatype::StaticVector<3>>* omega_source, 
		devicedriver::OutputPort<datatype::Quaternion>* reference_source,
		devicedriver::InputPort<datatype::StaticVector<3>>* torque_out);

	~DynamicPID(){}
	void setPIDGain(double kp, double ki, double kd){
		kp_ = kp;
		ki_ = ki;
		kd_ = kd;
	}
	virtual void do_compute(const datatype::Time& t);
protected:
    double kp_;
    double ki_;
    double kd_;
	double dt_;
    //1�X�e�b�v�O�̃I�C���[�p�덷(��������Ɏg�p)
    datatype::EulerAngle e_before_;
    //�p���p�̌덷�ϕ��l�i�ϕ�����Ɏg�p�j�D
    datatype::EulerAngle e_total_;
};

} /* End of namespace stf::core::mode::strategy::control */
} /* End of namespace stf::core::mode::strategy */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_mode_storategy_control_PID_h
