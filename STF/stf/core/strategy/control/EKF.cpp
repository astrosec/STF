/**
 * @file   EKF.cpp
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#include "EKF.h"
#include "../../../util/math.h"
#include "../../../util/math/Exp.h"
#include "../../../util/math/RungeKutta.h"

namespace stf {
namespace core {
namespace strategy {
namespace control {

EKF::EKF(int instance_id, const EKFParamaters &params)
: A_(6,6),B_(6,6),G_(6,6),F_(6,6),H_(3,6),Ht_(6,3),P_(6,6),K_(6,6),Q_(6,6),
R_(3,3),x_(6),bref_(3),Omega_(4,4), StrategyBase(instance_id, "EKF")
{	
    this->params_ = params;//copy
    init();   
}

EKF::EKF(int instance_id, const EKFParamaters &params, 
		devicedriver::OutputPort<datatype::Quaternion>* q_source, OutputPort<datatype::StaticVector<3>>* omega_source,
		devicedriver::InputPort<datatype::Quaternion>* q_out, InputPort<datatype::StaticVector<3>>* omega_out
		)
: A_(6,6),B_(6,6),G_(6,6),F_(6,6),H_(3,6),Ht_(6,3),P_(6,6),K_(6,6),Q_(6,6),
R_(3,3),x_(6),bref_(3),Omega_(4,4), StrategyBase(instance_id, "EKF")
{
    this->params_ = params;//copy
	this->connectSource<0>(q_source);
	this->connectSource<1>(omega_source);
	if(q_out != 0){
		q_out->connectSource_(this);
	}
	if(omega_out != 0){
		omega_out->connectSource_(this);
	}
    init();  
}

EKF::EKF(int instance_id)
: A_(6,6),B_(6,6),G_(6,6),F_(6,6),H_(3,6),Ht_(6,3),P_(6,6),K_(6,6),Q_(6,6),
R_(3,3),x_(6),bref_(3),Omega_(4,4), StrategyBase(instance_id, "EKF")
{
	params_.tau = 1000;
	params_.timestep = 0.1;
	params_.w_b = params_.w_q = 0.01;
	params_.v = 0;
	params_.MinimunGain = 0;
	params_.calcSensorGap = false;
	for(int i = 0; i < 6; i++)
		params_.P0[i][i] = 1.0;
    init();
}


void EKF::init(const EKFParamaters &params)
{
    this->params_ = params;//copy
    init();   
}


void EKF::init()
{
	//�S�Ă̒l������������D�R���X�g���N�^����ĂԂق��C��}�j���[�o���Z���T�ُ펞�̃��Z�b�g�ɂ��g����
    assert(tau_ != 0);

    this->P_ = params_.P0;
    this->q_ = params_.q0;
    this->bref_ = params_.b0;
    this->dt_ = params_.timestep;
    this->tau_ = params_.tau;
    //w,v����Q,R�𐶐�
    for(int i = 0; i < 3; i++)
	{
        Q_[i][i] = params_.w_q * params_.w_q;
		Q_[i+3][i+3] = params_.w_b * params_.w_b;
        R_[i][i] = params_.v * params_.v;
	}
    //�Œ�l�̍s��⏉���l���K�v�ȍs��ɒl����
    //B
    B_[0][0] = B_[1][1] = B_[2][2] = -0.5;
    B_[3][3] = B_[4][4] = B_[5][5] = 1;
    //H �v�Z���׍팸�̂��߁C�]�n�s��������Ă���
    H_[0][0] = H_[1][1] = H_[2][2] = 1;
	Ht_[0][0] = Ht_[1][1] = Ht_[2][2] = 1;
    //A(���ςł��郶�ȊO�����������Ă���)
    A_[0][3] = A_[1][4] = A_[2][5] = -0.5;
    A_[3][3] = A_[4][4] = A_[5][5] = -1 / this->tau_;
    //F
    F_ = util::math::exp(A_ * dt_,4);
}


void EKF::do_compute(const datatype::Time& t)
{
	if(this->getLastOutputtime<1>() >= t) return; //�`���ς݂Ȃ̂ŉ������Ȃ�
	//util::cout << "t:" << t << "u:" << this->getLastOutputtime<0>() << "p:" << this->getLastOutputtime<1>() << "stt:" << this->getLastInputTime<0>() << util::endl;
	util::cout << "compute: EKF" << util::endl;	
	if(this->getLastOutputtime<0>() < t && this->getLastInputTime<0>() >= this->getLastOutputtime<0>()){
		update( this->source<0,datatype::Quaternion>().getValueInBodyFrame(t), t );
		//util::cout << "update:" << util::endl;
	}
	//util::cout << "propagate:" << util::endl;
	propagate( this->source<1,datatype::StaticVector<3>>().getValueInBodyFrame(t), t );

}


void EKF::update(const datatype::Quaternion &input,const datatype::Time& t)
{
    q_.normalize();
    //�J���}���Q�C���̌v�Z
    this->K_ = P_ * H_.trans() * ( H_ * P_ * H_.trans() + R_ ).inverse();
    //�����U�s��̍X�V
    P_ = P_ - K_ * H_ * P_;
    //�ϑ��ʔ�����y�̌v�Z�D�ϑ����ꂽq�Ƀ��f������`������qref�̋�����������|����
    datatype::Vector y(3);
    datatype::Quaternion q_tmp = q_.conjugate() * input;

    //q_tmp[0](�`1)���ȗ�����3�v�f�ŏ�ԗʂ��\��
    y[0] = q_tmp[1];
    y[1] = q_tmp[2];
    y[2] = q_tmp[3];
    //x�̐���l���X�V
    x_ = K_ * y;
    //���ԗʂ̍X�V
    datatype::Quaternion q_update;
    q_update[0] = 1 - x_[0] * x_[0] - x_[1] * x_[1] - x_[2] * x_[2];
    q_update[1] = x_[0];
    q_update[2] = x_[1];
    q_update[3] = x_[2];
    q_update.normalize();

    q_ = q_ * q_update;
    q_.normalize();//�X�V�̃^�C�~���O�Ő��K�������Ă���(TBD)

    bref_[0] += x_[3];
    bref_[1] += x_[4];
    bref_[2] += x_[5];

	this->outputport<0,datatype::Quaternion>().value_b_ = this->q_;
	//this->setLastOutputtime<0>(t);
	this->setLastOutputtime<0>(t);
}


void EKF::propagate(const datatype::StaticVector<3>& omega,const datatype::Time& t)
{
    //�����_�ł̐���p���x�Ń��CA���X�V
    this->omega_[0] = omega[0] - this->bref_[0] ;//- this->x_[3];
    this->omega_[1] = omega[1] - this->bref_[1] ;//- this->x_[4];
    this->omega_[2] = omega[2] - this->bref_[2] ;//- this->x_[5];

    //��ԕϐ��̓`��
    //�t�@�C���X�R�[�v��static�ϐ�Omega�����݂̃C���X�^���X�ōX�V
    Omega_[0][1] = -this->omega_[0];
    Omega_[0][2] = -this->omega_[1];
    Omega_[0][3] = -this->omega_[2];
    Omega_[1][2] =  this->omega_[2];
    Omega_[1][3] = -this->omega_[1];
    Omega_[2][3] =  this->omega_[0];
    for(int i = 0; i < 4; i++)
      for(int j = 0; j < 4; j++)
        if(i > j) Omega_[i][j] = -Omega_[j][i];

    //A,F,G�̍X�V
    A_[0][1] =  this->omega_[2];
    A_[0][2] = -this->omega_[1];
    A_[1][0] = -this->omega_[2];
    A_[1][2] =  this->omega_[0];
    A_[2][0] =  this->omega_[1];
    A_[2][1] = -this->omega_[0];
    F_ = util::math::exp(A_ * dt_,3);//TBD:exp�̃}�N���[�����W�J��3���܂Ŏ��Dt>1�̂Ƃ��͑e���ߎ��ɂȂ��Ă��܂�
    G_ = B_ * dt_ + 0.5 * A_ * B_ * dt_ * dt_;//exp(A(t-tau))��3���܂œW�J���Đϕ�

    //RK��q,b�̊�l��`��(������ԗʂ͓`�����Ȃ�)
    this->q_ += util::math::RungeKutta::slope(q_,0.5 * Omega_,dt_);
    this->bref_ += util::math::RungeKutta::slope(bref_,-1 / tau_,dt_);

    //�����U�s��̓`��
    this->P_ = F_ * P_ * F_.trans() + G_ * Q_ * G_.trans();

	this->outputport<0,datatype::Quaternion>().value_b_ = this->q_;
	this->outputport<1,datatype::StaticVector<3>>().value_b_ = this->omega_;
	this->setLastOutputtime<1>(t);
}


void EKF::reset()
{
	//�덷�����U�s��̂ݏ���������
	this->P_ = this->params_.P0; 
}

} /* End of namespace stf::core::strategy::control */
} /* End of namespace stf::core::strategy */
} /* End of namespace stf::core */
} /* End of namespace stf */
