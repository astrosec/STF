/**
 * @file   NJFactory.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef factory_NJFactory_h
#define factory_NJFactory_h

#include "../GlobalObject.h"
#include "../factory/SatelliteFactory.h"

#include "../core/strategy/control/Includes.h"

#include "../core/manager/Includes.h"
#include "../core/devicedriver/Includes.h"
#include "../core/datapool/Datapool.h"
#include "../core/command/Includes.h"
#include "../core/event/Includes.h"
#include "../core/functor/InputFunctor.h"
#include "../core/functor/OutputFunctor.h"
#include "../core/datapool/Datapool.h"

#include "../core/strategy/telemetry/Includes.h"

#include "../InstanceID.h"
#include "nj/NJGlobal.h"

namespace stf {
namespace factory {

template<class Env>
class NJFactory : public SatelliteFactory<Env>{
public:
	NJFactory(){ this->global_ = new NJGlobal<Env>();}
	virtual ~NJFactory(){ delete this->global_; }
	virtual void createComponent();
	virtual void createFunctionManager();
	virtual void createControlHotSpot();
	virtual void createTelemetryHotSpot();
	virtual void createCommandHotSpot();
	virtual void createFunctorHotSpot();
	virtual void createDataUpdateHotSpot();
	virtual void createSwitchHotSpot();
	virtual void createAdditionalHotSpot();
	virtual void createMode();
	virtual void createDataPoolConnection();
	virtual Global<Env>* returnCreatedObject(){
		return this->global_;
	}
private:
	NJGlobal<Env>* global_;
};

template<class Env>
void NJFactory<Env>::createMode(){
	this->global_->nj_sfem = new core::mode::ModeBase(ID_SAFEMODE,"NJ_SAFEMODE");
	this->global_->nj_stbm = new core::mode::ModeBase(ID_SAFEMODE,"NJ_STBMODE");
	this->global_->nj_inim = new core::mode::ModeBase(ID_SAFEMODE,"NJ_INITIALMODE");
	this->global_->nj_ctrm = new core::mode::ModeBase(ID_SAFEMODE,"NJ_COARSECONTROLMODE");
	this->global_->nj_ccdm = new core::mode::ModeBase(ID_SAFEMODE,"NJ_FINECONTROLMODE");
	this->global_->nj_mism = new core::mode::ModeBase(ID_SAFEMODE,"NJ_MISSIONMODE");
	this->global_->nj_rwum = new core::mode::ModeBase(ID_SAFEMODE,"NJ_UNLOADINGMODE");
	this->global_->nj_estm_fog = new core::mode::ModeBase(ID_SAFEMODE,"NJ_ESTM_FOG");
	this->global_->nj_estm_rmm = new core::mode::ModeBase(ID_SAFEMODE,"NJ_ESTM_RMM");
	this->global_->nj_estm_rw = new core::mode::ModeBase(ID_SAFEMODE,"NJ_ESTM_RW");
	this->global_->nj_estm_mc = new core::mode::ModeBase(ID_SAFEMODE,"NJ_ESTM_MC");
}

template<class Env>
void NJFactory<Env>::createComponent(){
	typedef devicedriver::mtq::NJMTQ<Env> MTQ;
	typedef devicedriver::CompositeOutput<MTQ,3> ThreeAxisMTQ;
	typedef devicedriver::mtq::NJMC<Env> MC;
	typedef devicedriver::CompositeOutput<MC,3> ThreeAxisMC;
	typedef devicedriver::rw::NJRW<Env> RW;
	typedef devicedriver::CompositeOutput<RW,4> SkewRW;
	typedef devicedriver::stt::NJSTT<Env> STT;
	typedef devicedriver::CompositeInput<STT,2> TwoAxisSTT;
	typedef devicedriver::sunsensor::NJSunSensor<Env> Sunsensor;
	typedef devicedriver::CompositeInput<Sunsensor,6> SixAxisSunsensor;
	typedef devicedriver::clock::NJRTC RTC;
	typedef devicedriver::gps::NJGPS<Env> GPS;
	typedef devicedriver::gyro::NJGyro<Env> GYRO;
	typedef devicedriver::CompositeInput<GYRO,3> ThreeAxisGyro;
	typedef devicedriver::gyro::NJFOG<Env> FOG;
	typedef devicedriver::CompositeInput<FOG,3> ThreeAxisFOG;
	typedef devicedriver::magnetometer::NJCoarseTAM<Env> ST4;
	typedef devicedriver::magnetometer::NJFineTAM<Env> ST5;

	//DataPool
	this->global_->nj_aocsdatapool = new core::datapool::AocsDataPool(0);
	this->global_->nj_eventdatapool = new core::datapool::EventDataPool(0);

	// MTQ
	this->global_->nj_mtqx = new MTQ(ID_MTQ_X,datatype::TypeConverter::toDCM(0,-90,0));
	this->global_->nj_mtqy = new MTQ(ID_MTQ_Y,datatype::TypeConverter::toDCM(0,0,90));
	this->global_->nj_mtqz = new MTQ(ID_MTQ_Z,datatype::TypeConverter::toDCM(0,0,0));
	this->global_->nj_mtq = new ThreeAxisMTQ(ID_MTQ,datatype::TypeConverter::toDCM(0,0,0));
	this->global_->nj_mtq->appendChild(this->global_->nj_mtqx);
	this->global_->nj_mtq->appendChild(this->global_->nj_mtqy);
	this->global_->nj_mtq->appendChild(this->global_->nj_mtqz);

	//MC
	this->global_->nj_mcx = new MC(ID_MTQ_X,datatype::TypeConverter::toDCM(0,-90,0));
	this->global_->nj_mcy = new MC(ID_MTQ_Y,datatype::TypeConverter::toDCM(0,0,90));
	this->global_->nj_mcz = new MC(ID_MTQ_Z,datatype::TypeConverter::toDCM(0,0,0));
	this->global_->nj_mc = new ThreeAxisMC(ID_MTQ,datatype::TypeConverter::toDCM(0,0,0));
	this->global_->nj_mc->appendChild(this->global_->nj_mcx);
	this->global_->nj_mc->appendChild(this->global_->nj_mcy);
	this->global_->nj_mc->appendChild(this->global_->nj_mcz);

	// Gyro
	this->global_->nj_gyrox = new GYRO(ID_GYRO_X,datatype::TypeConverter::toDCM(0,-90,0));
	this->global_->nj_gyroy = new GYRO(ID_GYRO_Y,datatype::TypeConverter::toDCM(0,0,90));
	this->global_->nj_gyroz = new GYRO(ID_GYRO_Z,datatype::TypeConverter::toDCM(0,0,0));
	this->global_->nj_gyro =  new ThreeAxisGyro(ID_GYRO,datatype::TypeConverter::toDCM(0,0,0));
	this->global_->nj_gyro->appendChild(this->global_->nj_gyrox);
	this->global_->nj_gyro->appendChild(this->global_->nj_gyroy);
	this->global_->nj_gyro->appendChild(this->global_->nj_gyroz);

	this->global_->nj_fogx = new FOG(ID_FOG_X,datatype::TypeConverter::toDCM(0,-90,0));
	this->global_->nj_fogy = new FOG(ID_FOG_Y,datatype::TypeConverter::toDCM(0,0,90));
	this->global_->nj_fogz = new FOG(ID_FOG_Z,datatype::TypeConverter::toDCM(0,0,0));
	this->global_->nj_fog =  new ThreeAxisFOG(ID_FOG,datatype::TypeConverter::toDCM(0,0,0));
	this->global_->nj_fog->appendChild(this->global_->nj_fogx);
	this->global_->nj_fog->appendChild(this->global_->nj_fogy);
	this->global_->nj_fog->appendChild(this->global_->nj_fogz);

	// Sun Sensor
	this->global_->nj_sspx = new Sunsensor(ID_SS_PX,datatype::TypeConverter::toDCM(0,-90,0));
	this->global_->nj_sspy = new Sunsensor(ID_SS_PY,datatype::TypeConverter::toDCM(0,0,90));
	this->global_->nj_sspz = new Sunsensor(ID_SS_PZ,datatype::TypeConverter::toDCM(0,0,0));
	this->global_->nj_ssmx = new Sunsensor(ID_SS_MX,datatype::TypeConverter::toDCM(180,-90,0));
	this->global_->nj_ssmy = new Sunsensor(ID_SS_MY,datatype::TypeConverter::toDCM(180,0,90));
	this->global_->nj_ssmz = new Sunsensor(ID_SS_MZ,datatype::TypeConverter::toDCM(180,0,0));
	this->global_->nj_ss = new SixAxisSunsensor(ID_SS,datatype::TypeConverter::toDCM(0,0,0));
	this->global_->nj_ss->appendChild(this->global_->nj_sspx);
	this->global_->nj_ss->appendChild(this->global_->nj_sspy);
	this->global_->nj_ss->appendChild(this->global_->nj_sspz);
	this->global_->nj_ss->appendChild(this->global_->nj_ssmx);
	this->global_->nj_ss->appendChild(this->global_->nj_ssmy);
	this->global_->nj_ss->appendChild(this->global_->nj_ssmz);

	// MagnetoMeter
	this->global_->nj_st4 = new ST4(ID_TAM,datatype::TypeConverter::toDCM(0,0,0));
	this->global_->nj_st5 = new ST5(ID_TAM,datatype::TypeConverter::toDCM(0,0,0));

	// Star Tracker
	this->global_->nj_sttx = new STT(ID_STT_X,datatype::TypeConverter::toDCM(0,-90,0));
	this->global_->nj_stty = new STT(ID_STT_Y,datatype::TypeConverter::toDCM(0,0,0));
	this->global_->nj_stt = new TwoAxisSTT(ID_STT,datatype::TypeConverter::toDCM(0,0,0));
	this->global_->nj_stt->appendChild(this->global_->nj_sttx);
	this->global_->nj_stt->appendChild(this->global_->nj_stty);

	// Reaction Wheel
	this->global_->nj_rw1 = new RW(ID_RW_1,datatype::TypeConverter::toDCM(0,0,0));
	this->global_->nj_rw2 = new RW(ID_RW_2,datatype::TypeConverter::toDCM(0,0,0));
	this->global_->nj_rw3 = new RW(ID_RW_3,datatype::TypeConverter::toDCM(0,0,0));
	this->global_->nj_rw4 = new RW(ID_RW_4,datatype::TypeConverter::toDCM(0,0,0));
	this->global_->nj_rw  = new SkewRW(ID_RW,datatype::TypeConverter::toDCM(0,0,0));
	this->global_->nj_rw->appendChild(this->global_->nj_rw1);
	this->global_->nj_rw->appendChild(this->global_->nj_rw2);
	this->global_->nj_rw->appendChild(this->global_->nj_rw3);
	this->global_->nj_rw->appendChild(this->global_->nj_rw4);

	// GPS,RTC
	this->global_->nj_rtc = new RTC(ID_RTC, YEAR, MONTH, DATE);
	this->global_->nj_gps = new GPS(ID_GPS);

	// ADC, ���x�v�C�d���v�C�d���v
	this->global_->nj_adc  = new devicedriver::NJADC<Env>(ID_ADC);
	this->global_->nj_temp1 = new devicedriver::NJCoarseTempSensor<Env>(ID_TEMPSENSOR,global_->nj_adc);
	this->global_->nj_temp2 = new devicedriver::NJFineTempSensor<Env>(ID_TEMPSENSOR,global_->nj_adc);
	this->global_->nj_currentsensor = new devicedriver::NJCurrentSensor<Env>(ID_CURRENTSENSOR,global_->nj_adc);
	this->global_->nj_voltagesensor = new devicedriver::NJVoltageSensor<Env>(ID_VOLTAGESENSOR,global_->nj_adc);

	// SDCard, Command Recv
	this->global_->nj_tmhandler = new devicedriver::tmhandler::NJTelemetryHandler<Env>("NJTelemetry.csv",false);
	this->global_->nj_commandreceiver = new devicedriver::cmhandler::NJCommandReceiver<Env>(0,this->global_->nj_commman,"command.txt",this->global_);

	// Other Components
	this->global_->nj_tdi = new devicedriver::nj::NJTDI<Env>();
	this->global_->nj_batterymanager = new devicedriver::nj::NJBatteryManager<Env>();
	this->global_->nj_battheater = new devicedriver::nj::NJHeaterManager<Env>();
	this->global_->nj_rx = new devicedriver::nj::NJRX<Env>();
	this->global_->nj_tx = new devicedriver::nj::NJTX<Env>();
}

template<class Env>
void NJFactory<Env>::createFunctionManager(){
	this->global_->nj_modeman = new core::manager::ModeManager(ID_MODEMANAGER);
	this->global_->nj_conman = new core::manager::ControlManager(ID_CONTROLMANAGER);
	this->global_->nj_uniman1 = new core::manager::UnitManager(ID_UNITMANAGER);
	this->global_->nj_uniman2 = new core::manager::UnitManager(ID_UNITMANAGER);
	this->global_->nj_telman = new core::manager::TelemetryManager(ID_TELEMETRYMANAGER);
	this->global_->nj_cusman = new core::manager::CustomManager(ID_CUSTOMMANAGER);
	this->global_->nj_sysman = new core::manager::SystemManager(ID_SYSTEMMANAGER);
	this->global_->nj_commman = new core::manager::CommandManager(ID_COMMANDMANAGER);
}

template<class Env>
void NJFactory<Env>::createControlHotSpot(){
	typedef core::strategy::control::ControlBlock CONTROLLER;
	typedef core::strategy::control::PID SimplePID;
	typedef core::strategy::control::DynamicPID PID;
	typedef core::strategy::control::NJSunMagTRIAD TRIAD;
	typedef core::strategy::control::SolarPointing SOLAR_POINTING;
	typedef core::strategy::control::CrossProduct CROSS_PRODUCT;
	typedef core::strategy::control::NJEKF EKF;
	typedef core::strategy::control::NJRMMEKF RMMEKF;
	typedef core::strategy::control::nj::QuaternionAveraging QUATERNION_AVE;
	typedef core::strategy::control::RateDumping RATE_DUMPING;
	typedef core::strategy::control::LiniarCorrection<datatype::MagneticMoment> RMMCOMP;
	typedef core::strategy::control::Combining_3<datatype::MagneticMoment> MAG_COMBINE_3;
	typedef core::strategy::control::Combining_2<datatype::MagneticMoment> MAG_COMBINE_2;
	typedef core::strategy::control::nj::StarImageEKF STAR_EKF;
	typedef core::strategy::control::nj::LongRangeSpinController SPINAXIS_CONTROLLER;
	typedef core::strategy::control::nj::MidRangeSpinController MIDRANGE_SPINCONTROLLER;
	typedef core::strategy::control::WheelUnloading UNLOADING;
	typedef core::strategy::control::nj::QuaternionForRMMEstimation QUATERNION_RMMESTM;
	typedef core::strategy::control::nj::MCConstantOutput MC_CONSTANT;
	typedef core::strategy::control::nj::RWConstantOutput RW_CONSTANT;

	CONTROLLER* NJ_CONTROLLER_SFEM = new CONTROLLER(0);
	CONTROLLER* NJ_CONTROLLER_INIM = new CONTROLLER(0);
	CONTROLLER* NJ_CONTROLLER_CTRM = new CONTROLLER(0);
	CONTROLLER* NJ_CONTROLLER_CCDM = new CONTROLLER(0);
	CONTROLLER* NJ_CONTROLLER_MISM = new CONTROLLER(0);
	CONTROLLER* NJ_CONTROLLER_RWUM = new CONTROLLER(0);
	CONTROLLER* NJ_CONTROLLER_STBM = new CONTROLLER(0);
	CONTROLLER* NJ_CONTROLLER_ESTM_FOG = new CONTROLLER(0);
	CONTROLLER* NJ_CONTROLLER_ESTM_RMM = new CONTROLLER(0);
	CONTROLLER* NJ_CONTROLLER_ESTM_RW = new CONTROLLER(0);
	CONTROLLER* NJ_CONTROLLER_ESTM_MC = new CONTROLLER(0);

	/////////////////////////////////////
	// �Z�[�t���[�h�p�̎p������u���b�N
	// �p������:�Ȃ�
	// �p������:�Ȃ�
	this->global_->nj_sfem->add_list(NJ_CONTROLLER_SFEM);

	/////////////////////////////////////
	// �X�^���o�C���[�h�p�̎p������u���b�N
	// �p������:�Ȃ�
	// �p������:���C�Z���T�݂̂̑��z�ߑ�����(����n���h�u�b�N9.3.3.3)
	SOLAR_POINTING* stbm_pointing = new SOLAR_POINTING(0,1);

	stbm_pointing->connectSource<0>(this->global_->nj_st4);
	stbm_pointing->connectSource<1>(this->global_->nj_ss);

	NJ_CONTROLLER_STBM->setActuator(this->global_->nj_mtq,stbm_pointing);
	this->global_->nj_stbm->add_list(NJ_CONTROLLER_STBM);

	//////////////////////////////////////
    // �������艻���[�h�p�̎p������u���b�N
	// �p������:�Ȃ�(�p���x�̂ݎ擾)
	// �p������:Date-Dumping + CrossProduct
	RATE_DUMPING* inim_ratedumping = new RATE_DUMPING(0, 1, 0.1, 0.1, STEPTIME);
	CROSS_PRODUCT* inim_crossproduct = new CROSS_PRODUCT(0);

	inim_ratedumping->connectSource<0>(this->global_->nj_gyro);

	inim_crossproduct->connectSource<0>(inim_ratedumping);
	inim_crossproduct->connectSource<1>(this->global_->nj_st4);

	NJ_CONTROLLER_INIM->setActuator(this->global_->nj_mtq, inim_crossproduct);
	this->global_->nj_inim->add_list(NJ_CONTROLLER_INIM);

	//////////////////////////////////////
    // �e�p�����䃂�[�h�p�̎p������u���b�N
	// �p������:ST4 & SunsensorTRIAD(EKF�Ȃ�) + EKF(FOG)
	// �p������:Quaternion FB
	TRIAD* ctrm_triad = new TRIAD(0);
	EKF* ctrm_ekf = new EKF(0, this->global_->nj_mism);
	SimplePID* ctrm_pid = new SimplePID(0, 1, 0.01, 0.5, STEPTIME, *(new datatype::Quaternion));
	CROSS_PRODUCT* ctrm_crossproduct = new CROSS_PRODUCT(0);

	ctrm_crossproduct->connectSource<0>(ctrm_pid);
	ctrm_crossproduct->connectSource<1>(this->global_->nj_st4);

	ctrm_pid->connectSource<0>(ctrm_ekf);
	ctrm_pid->connectSource<1>(ctrm_ekf);//TRIAD���璼��Quaternion���Ƃ�̂ł͂Ȃ�EKF�����ނ��ƂŁC�I���ɂ�FOG����̓`���l�������I�ɗp������

	ctrm_ekf->connectSource<0>(ctrm_triad);
	ctrm_ekf->connectSource<1>(this->global_->nj_fog);

	ctrm_triad->connectSource<0>(this->global_->nj_ss);
	ctrm_triad->connectSource<1>(this->global_->nj_st4);
	ctrm_triad->connectSource<2>(this->global_->nj_gps);

	NJ_CONTROLLER_CTRM->setActuator(this->global_->nj_mtq, ctrm_crossproduct);
	this->global_->nj_ctrm->add_list(NJ_CONTROLLER_CTRM);

	//////////////////////////////////////
	//���p�����䃂�[�h�p�̎p������u���b�N
	// �p������:STT-FOG EKF & RMM�⏞
	// �p������:
	EKF* ccdm_ekf = new EKF(0, this->global_->nj_mism);//->����l�������p���̂Ŋϑ����[�h�ł��g��
	RMMEKF* ccdm_rmmekf = new RMMEKF(0);//->����l�������p���̂Ŋϑ����[�h�ł��g��
	QUATERNION_AVE* ccdm_q_average = new QUATERNION_AVE(0);
	RMMCOMP* ccdm_rmmcomp = new RMMCOMP(0,-1);
	PID* ccdm_pid = new PID(0, 0.1, 0.001, 0.004, STEPTIME);

	ccdm_rmmcomp->connectSource<0>(ccdm_rmmekf);

	ccdm_rmmekf->connectSource<0>(this->global_->nj_st5);
	ccdm_rmmekf->connectSource<1>(ccdm_ekf);

	ccdm_pid->connectSource<0>(ccdm_ekf);
	ccdm_pid->connectSource<1>(ccdm_ekf);
	

	ccdm_ekf->connectSource<0>(ccdm_q_average);
	ccdm_ekf->connectSource<1>(this->global_->nj_fog);

	ccdm_q_average->connectSource<0>(this->global_->nj_sttx);
	ccdm_q_average->connectSource<1>(this->global_->nj_stty);

	//����g���N��RW�֏o��
	NJ_CONTROLLER_CCDM->setActuator(this->global_->nj_rw, ccdm_pid);
	//���肳�ꂽ�c�����C���[�����g�̕⏞�����͎��C�L�����Z���֏o��
	NJ_CONTROLLER_CCDM->setActuator(this->global_->nj_mc, ccdm_rmmcomp);

	this->global_->nj_ccdm->add_list(NJ_CONTROLLER_CCDM);

	////////////////////////////////////
	//�ϑ����[�h�p�̎p������u���b�N�D����EKF��X�s�����̒�������������Đ����䃂�[�h�̐���u���b�N�������p��
	// �p������F����EKF?
	// �p������F
	STAR_EKF* mism_starekf = new STAR_EKF(0);
	PID* mism_pid = new PID(0, 0.1, 0.001, 0.004, STEPTIME);
	SPINAXIS_CONTROLLER* mism_spincond = new SPINAXIS_CONTROLLER(0);

	mism_pid->connectSource<0>(ccdm_ekf);//Quaternion�̓W���C���o�C�A�XEKF����擾
	mism_pid->connectSource<1>(mism_starekf);//�p���x�͐���EKF����擾�D�����擾���s���ɂ̓W���C���o�C�A�XEKF�̒l�����̂܂ܓ`�������
	mism_pid->connectSource<2>(mism_spincond);//�����v���Ɋ�Â��ĖڕWQuaterion���X�V

	mism_starekf->connectSource<0>(ccdm_ekf);
	mism_starekf->connectSource<1>(this->global_->nj_rw);

	//����g���N��RW�֏o��
	NJ_CONTROLLER_MISM->setActuator(this->global_->nj_rw, mism_pid);
	//RMM�͐����䃂�[�h�Ɠ����o�H�ŃL�����Z����
	NJ_CONTROLLER_MISM->setActuator(this->global_->nj_mc, ccdm_rmmcomp);

	//////////////////////////////////////
	//�A�����[�f�B���O���[�h�p�̎p������u���b�N
	// �p������FSTT-�T���Z���TQUEST
	// �p������FMTQ-RW���U
	UNLOADING* unloading = new UNLOADING(0);
	CROSS_PRODUCT* unloading_crossp = new CROSS_PRODUCT(0);
	
	unloading->add_wheel(this->global_->nj_rw1);
	unloading->add_wheel(this->global_->nj_rw2);
	unloading->add_wheel(this->global_->nj_rw3);
	unloading->add_wheel(this->global_->nj_rw4);
	
	unloading->connectSource<0>(this->global_->nj_gps);

	unloading_crossp->connectSource<0>(&unloading->outputport<1,datatype::StaticVector<3>>());

	NJ_CONTROLLER_RWUM->setActuator(this->global_->nj_rw, &unloading->outputport<0,datatype::StaticVector<3>>());
	NJ_CONTROLLER_RWUM->setActuator(this->global_->nj_mtq, unloading_crossp);

	/////////////////////////////////////
	// RMM����p�̎p������u���b�N
	// �p������FSTT-FOG EKF
	// �p������F6�ʈ�莞�Ԃ����z�w������
	PID* estmrmm_pid = new PID(0, 0.1, 0.01, 0.01, STEPTIME);
	datatype::Time t(1000,0);
	QUATERNION_RMMESTM* estmrmm_q = new QUATERNION_RMMESTM(0,this->global_->nj_rtc,t);//1000�b���Ƃɕʂ̖ʂ𑾗z�w��������

	estmrmm_pid->connectSource<0>(ccdm_ekf);
	estmrmm_pid->connectSource<1>(ccdm_ekf);
	estmrmm_pid->connectSource<2>(estmrmm_q);

	NJ_CONTROLLER_ESTM_RMM->setActuator(this->global_->nj_rw, estmrmm_pid);
	this->global_->nj_estm_rmm->add_list(NJ_CONTROLLER_ESTM_RMM);

	/////////////////////////////////////
	// FOG����p�̎p������u���b�N
	// �p������FSTT-FOG EKF
	// �p������FFOG3�����ꂼ��}1e-3rad/s,�}1e-2rad/s�̌v12���[�h
	PID* estmfog_pid = new PID(0, 0.1, 0.01, 0.01, STEPTIME);

	NJ_CONTROLLER_ESTM_FOG->setActuator(this->global_->nj_rw, estmfog_pid);
	this->global_->nj_estm_fog->add_list(NJ_CONTROLLER_ESTM_FOG);

	/////////////////////////////////////
	// MC����p�̎p������u���b�N
	// �p������FSTT-FOG EKF
	// �p������FMC3�����ꂼ��}0.2Am2,�}0.4Am2,�}0.6Am2�̌v18���[�h
	MC_CONSTANT* estmmc = new MC_CONSTANT(0, this->global_->nj_rtc, t);

	NJ_CONTROLLER_ESTM_MC->setActuator(this->global_->nj_mc, estmmc);
	this->global_->nj_estm_mc->add_list(NJ_CONTROLLER_ESTM_MC);

	/////////////////////////////////////
	// RW����p�̎p������u���b�N
	// �p������FSTT-FOG EKF
	// �p������FRW4��ꂼ��}5e-5Nm,�}2.5e-5Nm�̌v16���[�h
	RW_CONSTANT* estmrw = new RW_CONSTANT(0, this->global_->nj_rtc, t);

	//NJ_CONTROLLER_ESTM_RW->setActuator(this->global_->nj_rw1, &estmrw->outputport<0,datatype::StaticVector<3>>());
	this->global_->nj_estm_rw->add_list(NJ_CONTROLLER_ESTM_RW);

	///////////////////////////////////////////////////
	// ����u���b�N�ւ̃A�N�Z�X���K�v�ȏ���������

	// EKF�̏�ԗʂ��e�����g���ɏo��
	this->global_->nj_telemetrystrategy->add_tmlist(new interface::NJEKFIterator<1000>(ccdm_ekf));
	this->global_->nj_telemetrystrategy->add_tmlist(new interface::NJRMMEKFIterator<1000>(ccdm_rmmekf));
	this->global_->nj_telemetrystrategy->add_tmlist(new interface::NJSunMagTRIADIterator<1000>(ctrm_triad));
}

template<class Env>
void NJFactory<Env>::createCommandHotSpot(){

}

template<class Env>
void NJFactory<Env>::createTelemetryHotSpot(){
	this->global_->nj_telemetrystrategy = new core::strategy::telemetry::SelectingOutput<unsigned int, 1000>
		(0,this->global_->nj_tmhandler,this->global_->nj_aocsdatapool,this->global_->nj_eventdatapool);

	//ADC�̎擾�l��S�`���l���e�����g���ɒǉ�
	this->global_->nj_telemetrystrategy->add_tmlist(new interface::CDHComponentIterator<datatype::Voltage,__NJ__ADC__CHANNELS,Env>(this->global_->nj_adc));

}

template<class Env>
void NJFactory<Env>::createDataUpdateHotSpot(){
	// �S���[�h���ʂ�ON�̋@��͍ŏ��ɂ܂Ƃ߂ă��X�g�ɉ�����
	datatype::List<core::devicedriver::IDataUpdatable> defaultUpdateList;
	defaultUpdateList.add(*this->global_->nj_rtc);
	defaultUpdateList.add(*this->global_->nj_adc);
	defaultUpdateList.add(*this->global_->nj_currentsensor);
	defaultUpdateList.add(*this->global_->nj_voltagesensor);
	defaultUpdateList.add(*this->global_->nj_temp1);
	defaultUpdateList.add(*this->global_->nj_temp2);
	defaultUpdateList.add(*this->global_->nj_batterymanager);
	defaultUpdateList.add(*this->global_->nj_battheater);
	defaultUpdateList.add(*this->global_->nj_rx);

	datatype::List<core::devicedriver::IDataUpdatable>::iterator it = defaultUpdateList.begin();
	while(it != defaultUpdateList.end()){
		this->global_->nj_sfem->add_list(&(*it));
		this->global_->nj_stbm->add_list(&(*it));
		this->global_->nj_ctrm->add_list(&(*it));
		this->global_->nj_ccdm->add_list(&(*it));
		this->global_->nj_mism->add_list(&(*it));
		this->global_->nj_rwum->add_list(&(*it));
		this->global_->nj_estm_fog->add_list(&(*it));
		this->global_->nj_estm_rmm->add_list(&(*it));
		this->global_->nj_estm_rw->add_list(&(*it));
		this->global_->nj_estm_mc->add_list(&(*it));
		++it;
	}
	//�ȉ��e���[�h�ŗL�̃R���|�[�l���g�Q

	//Safe Mode ->default�̂�

	//Standby Mode
	this->global_->nj_stbm->add_list((core::devicedriver::IDataUpdatable*)(this->global_->nj_ss));
	this->global_->nj_stbm->add_list((core::devicedriver::IDataUpdatable*)(this->global_->nj_gyro));
	this->global_->nj_stbm->add_list((core::devicedriver::IDataUpdatable*)(this->global_->nj_st4));
	this->global_->nj_stbm->add_list((core::devicedriver::IDataUpdatable*)(this->global_->nj_gps));

	//Coarse Control Mode
	this->global_->nj_ctrm->add_list((core::devicedriver::IDataUpdatable*)(this->global_->nj_ss));
	this->global_->nj_ctrm->add_list((core::devicedriver::IDataUpdatable*)(this->global_->nj_gyro));
	this->global_->nj_ctrm->add_list((core::devicedriver::IDataUpdatable*)(this->global_->nj_st4));
	this->global_->nj_ctrm->add_list((core::devicedriver::IDataUpdatable*)(this->global_->nj_gps));
	this->global_->nj_ctrm->add_list((core::devicedriver::IDataUpdatable*)(this->global_->nj_mtq));

	//Fine Control Mode
	this->global_->nj_ccdm->add_list((core::devicedriver::IDataUpdatable*)(this->global_->nj_stt));
	this->global_->nj_ccdm->add_list((core::devicedriver::IDataUpdatable*)(this->global_->nj_rw));
	this->global_->nj_ccdm->add_list((core::devicedriver::IDataUpdatable*)(this->global_->nj_fog));
	this->global_->nj_ccdm->add_list((core::devicedriver::IDataUpdatable*)(this->global_->nj_st5));
	this->global_->nj_ccdm->add_list((core::devicedriver::IDataUpdatable*)(this->global_->nj_gps));
	this->global_->nj_ccdm->add_list((core::devicedriver::IDataUpdatable*)(this->global_->nj_mc));
	this->global_->nj_ccdm->add_list((core::devicedriver::IDataUpdatable*)(this->global_->nj_tdi));

	//Mission Mode
	this->global_->nj_mism->add_list((core::devicedriver::IDataUpdatable*)(this->global_->nj_stt));
	this->global_->nj_mism->add_list((core::devicedriver::IDataUpdatable*)(this->global_->nj_rw));
	this->global_->nj_mism->add_list((core::devicedriver::IDataUpdatable*)(this->global_->nj_fog));
	this->global_->nj_mism->add_list((core::devicedriver::IDataUpdatable*)(this->global_->nj_st5));
	this->global_->nj_mism->add_list((core::devicedriver::IDataUpdatable*)(this->global_->nj_gps));
	this->global_->nj_mism->add_list((core::devicedriver::IDataUpdatable*)(this->global_->nj_mc));
	this->global_->nj_mism->add_list((core::devicedriver::IDataUpdatable*)(this->global_->nj_tdi));

	//Unloading Mode
	this->global_->nj_rwum->add_list((core::devicedriver::IDataUpdatable*)(this->global_->nj_stt));
	this->global_->nj_rwum->add_list((core::devicedriver::IDataUpdatable*)(this->global_->nj_rw));
	this->global_->nj_rwum->add_list((core::devicedriver::IDataUpdatable*)(this->global_->nj_fog));
	this->global_->nj_rwum->add_list((core::devicedriver::IDataUpdatable*)(this->global_->nj_st4));
	this->global_->nj_rwum->add_list((core::devicedriver::IDataUpdatable*)(this->global_->nj_gps));
	this->global_->nj_rwum->add_list((core::devicedriver::IDataUpdatable*)(this->global_->nj_mc));
	this->global_->nj_rwum->add_list((core::devicedriver::IDataUpdatable*)(this->global_->nj_mtq));

	//Estimation Mode - RMM
	this->global_->nj_estm_rmm->add_list((core::devicedriver::IDataUpdatable*)(this->global_->nj_fog));
	this->global_->nj_estm_rmm->add_list((core::devicedriver::IDataUpdatable*)(this->global_->nj_stt));
	this->global_->nj_estm_rmm->add_list((core::devicedriver::IDataUpdatable*)(this->global_->nj_mc));
	this->global_->nj_estm_rmm->add_list((core::devicedriver::IDataUpdatable*)(this->global_->nj_st5));
	this->global_->nj_estm_rmm->add_list((core::devicedriver::IDataUpdatable*)(this->global_->nj_gps));

	//Estimation Mode - FOG
	this->global_->nj_estm_fog->add_list((core::devicedriver::IDataUpdatable*)(this->global_->nj_fog));
	this->global_->nj_estm_fog->add_list((core::devicedriver::IDataUpdatable*)(this->global_->nj_stt));
	this->global_->nj_estm_fog->add_list((core::devicedriver::IDataUpdatable*)(this->global_->nj_mc));
	this->global_->nj_estm_fog->add_list((core::devicedriver::IDataUpdatable*)(this->global_->nj_rw));
	this->global_->nj_estm_fog->add_list((core::devicedriver::IDataUpdatable*)(this->global_->nj_st5));
	this->global_->nj_estm_fog->add_list((core::devicedriver::IDataUpdatable*)(this->global_->nj_gps));
	this->global_->nj_estm_fog->add_list((core::devicedriver::IDataUpdatable*)(this->global_->nj_mtq));

	//Estimation Mode - MC
	this->global_->nj_estm_mc->add_list((core::devicedriver::IDataUpdatable*)(this->global_->nj_fog));
	this->global_->nj_estm_mc->add_list((core::devicedriver::IDataUpdatable*)(this->global_->nj_stt));
	this->global_->nj_estm_mc->add_list((core::devicedriver::IDataUpdatable*)(this->global_->nj_mc));
	this->global_->nj_estm_mc->add_list((core::devicedriver::IDataUpdatable*)(this->global_->nj_rw));
	this->global_->nj_estm_mc->add_list((core::devicedriver::IDataUpdatable*)(this->global_->nj_st5));
	this->global_->nj_estm_mc->add_list((core::devicedriver::IDataUpdatable*)(this->global_->nj_gps));

	//Estimation Mode - RW
	this->global_->nj_estm_rw->add_list((core::devicedriver::IDataUpdatable*)(this->global_->nj_fog));
	this->global_->nj_estm_rw->add_list((core::devicedriver::IDataUpdatable*)(this->global_->nj_stt));
	this->global_->nj_estm_rw->add_list((core::devicedriver::IDataUpdatable*)(this->global_->nj_mc));
	this->global_->nj_estm_rw->add_list((core::devicedriver::IDataUpdatable*)(this->global_->nj_rw));
	this->global_->nj_estm_rw->add_list((core::devicedriver::IDataUpdatable*)(this->global_->nj_st5));
	this->global_->nj_estm_rw->add_list((core::devicedriver::IDataUpdatable*)(this->global_->nj_gps));

}

template<class Env>
void NJFactory<Env>::createSwitchHotSpot(){
	// �S���[�h���ʂ�ON�̋@��͍ŏ��ɂ܂Ƃ߂ă��X�g�ɉ�����
	datatype::List<core::devicedriver::ISwitchable> defaultSwitchList;
	defaultSwitchList.add(*this->global_->nj_rtc);
	defaultSwitchList.add(*this->global_->nj_adc);
	defaultSwitchList.add(*this->global_->nj_currentsensor);
	defaultSwitchList.add(*this->global_->nj_voltagesensor);
	defaultSwitchList.add(*this->global_->nj_temp1);
	defaultSwitchList.add(*this->global_->nj_temp2);
	defaultSwitchList.add(*this->global_->nj_batterymanager);
	defaultSwitchList.add(*this->global_->nj_battheater);
	defaultSwitchList.add(*this->global_->nj_rx);

	datatype::List<core::devicedriver::ISwitchable>::iterator it = defaultSwitchList.begin();
	while(it != defaultSwitchList.end()){
		this->global_->nj_sfem->add_list(&(*it));
		this->global_->nj_stbm->add_list(&(*it));
		this->global_->nj_ctrm->add_list(&(*it));
		this->global_->nj_ccdm->add_list(&(*it));
		this->global_->nj_mism->add_list(&(*it));
		this->global_->nj_rwum->add_list(&(*it));
		this->global_->nj_estm_fog->add_list(&(*it));
		this->global_->nj_estm_rmm->add_list(&(*it));
		this->global_->nj_estm_rw->add_list(&(*it));
		this->global_->nj_estm_mc->add_list(&(*it));
		++it;
	}
	//�ȉ��e���[�h�ŗL�̃R���|�[�l���g�Q

	//Safe Mode ->default�̂�

	//Standby Mode
	this->global_->nj_stbm->add_list((core::devicedriver::ISwitchable*)(this->global_->nj_ss));
	this->global_->nj_stbm->add_list((core::devicedriver::ISwitchable*)(this->global_->nj_gyro));
	this->global_->nj_stbm->add_list((core::devicedriver::ISwitchable*)(this->global_->nj_st4));
	this->global_->nj_stbm->add_list((core::devicedriver::ISwitchable*)(this->global_->nj_gps));

	//Coarse Control Mode
	this->global_->nj_ctrm->add_list((core::devicedriver::ISwitchable*)(this->global_->nj_ss));
	this->global_->nj_ctrm->add_list((core::devicedriver::ISwitchable*)(this->global_->nj_gyro));
	this->global_->nj_ctrm->add_list((core::devicedriver::ISwitchable*)(this->global_->nj_st4));
	this->global_->nj_ctrm->add_list((core::devicedriver::ISwitchable*)(this->global_->nj_gps));
	this->global_->nj_ctrm->add_list((core::devicedriver::ISwitchable*)(this->global_->nj_mtq));

	//Fine Control Mode
	this->global_->nj_ccdm->add_list((core::devicedriver::ISwitchable*)(this->global_->nj_stt));
	this->global_->nj_ccdm->add_list((core::devicedriver::ISwitchable*)(this->global_->nj_rw));
	this->global_->nj_ccdm->add_list((core::devicedriver::ISwitchable*)(this->global_->nj_fog));
	this->global_->nj_ccdm->add_list((core::devicedriver::ISwitchable*)(this->global_->nj_st5));
	this->global_->nj_ccdm->add_list((core::devicedriver::ISwitchable*)(this->global_->nj_gps));
	this->global_->nj_ccdm->add_list((core::devicedriver::ISwitchable*)(this->global_->nj_mc));
	this->global_->nj_ccdm->add_list((core::devicedriver::ISwitchable*)(this->global_->nj_tdi));

	//Mission Mode
	this->global_->nj_mism->add_list((core::devicedriver::ISwitchable*)(this->global_->nj_stt));
	this->global_->nj_mism->add_list((core::devicedriver::ISwitchable*)(this->global_->nj_rw));
	this->global_->nj_mism->add_list((core::devicedriver::ISwitchable*)(this->global_->nj_fog));
	this->global_->nj_mism->add_list((core::devicedriver::ISwitchable*)(this->global_->nj_st5));
	this->global_->nj_mism->add_list((core::devicedriver::ISwitchable*)(this->global_->nj_gps));
	this->global_->nj_mism->add_list((core::devicedriver::ISwitchable*)(this->global_->nj_mc));
	this->global_->nj_mism->add_list((core::devicedriver::ISwitchable*)(this->global_->nj_tdi));

	//Unloading Mode
	this->global_->nj_rwum->add_list((core::devicedriver::ISwitchable*)(this->global_->nj_stt));
	this->global_->nj_rwum->add_list((core::devicedriver::ISwitchable*)(this->global_->nj_rw));
	this->global_->nj_rwum->add_list((core::devicedriver::ISwitchable*)(this->global_->nj_fog));
	this->global_->nj_rwum->add_list((core::devicedriver::ISwitchable*)(this->global_->nj_st4));
	this->global_->nj_rwum->add_list((core::devicedriver::ISwitchable*)(this->global_->nj_gps));
	this->global_->nj_rwum->add_list((core::devicedriver::ISwitchable*)(this->global_->nj_mc));
	this->global_->nj_rwum->add_list((core::devicedriver::ISwitchable*)(this->global_->nj_mtq));

	//Estimation Mode - RMM
	this->global_->nj_estm_rmm->add_list((core::devicedriver::ISwitchable*)(this->global_->nj_fog));
	this->global_->nj_estm_rmm->add_list((core::devicedriver::ISwitchable*)(this->global_->nj_stt));
	this->global_->nj_estm_rmm->add_list((core::devicedriver::ISwitchable*)(this->global_->nj_mc));
	this->global_->nj_estm_rmm->add_list((core::devicedriver::ISwitchable*)(this->global_->nj_st5));
	this->global_->nj_estm_rmm->add_list((core::devicedriver::ISwitchable*)(this->global_->nj_gps));

	//Estimation Mode - FOG
	this->global_->nj_estm_fog->add_list((core::devicedriver::ISwitchable*)(this->global_->nj_fog));
	this->global_->nj_estm_fog->add_list((core::devicedriver::ISwitchable*)(this->global_->nj_stt));
	this->global_->nj_estm_fog->add_list((core::devicedriver::ISwitchable*)(this->global_->nj_mc));
	this->global_->nj_estm_fog->add_list((core::devicedriver::ISwitchable*)(this->global_->nj_rw));
	this->global_->nj_estm_fog->add_list((core::devicedriver::ISwitchable*)(this->global_->nj_st5));
	this->global_->nj_estm_fog->add_list((core::devicedriver::ISwitchable*)(this->global_->nj_gps));
	this->global_->nj_estm_fog->add_list((core::devicedriver::ISwitchable*)(this->global_->nj_mtq));

	//Estimation Mode - MC
	this->global_->nj_estm_mc->add_list((core::devicedriver::ISwitchable*)(this->global_->nj_fog));
	this->global_->nj_estm_mc->add_list((core::devicedriver::ISwitchable*)(this->global_->nj_stt));
	this->global_->nj_estm_mc->add_list((core::devicedriver::ISwitchable*)(this->global_->nj_mc));
	this->global_->nj_estm_mc->add_list((core::devicedriver::ISwitchable*)(this->global_->nj_rw));
	this->global_->nj_estm_mc->add_list((core::devicedriver::ISwitchable*)(this->global_->nj_st5));
	this->global_->nj_estm_mc->add_list((core::devicedriver::ISwitchable*)(this->global_->nj_gps));

	//Estimation Mode - RW
	this->global_->nj_estm_rw->add_list((core::devicedriver::ISwitchable*)(this->global_->nj_fog));
	this->global_->nj_estm_rw->add_list((core::devicedriver::ISwitchable*)(this->global_->nj_stt));
	this->global_->nj_estm_rw->add_list((core::devicedriver::ISwitchable*)(this->global_->nj_mc));
	this->global_->nj_estm_rw->add_list((core::devicedriver::ISwitchable*)(this->global_->nj_rw));
	this->global_->nj_estm_rw->add_list((core::devicedriver::ISwitchable*)(this->global_->nj_st5));
	this->global_->nj_estm_rw->add_list((core::devicedriver::ISwitchable*)(this->global_->nj_gps));

}

template<class Env>
void NJFactory<Env>::createFunctorHotSpot(){
	////////////////////////////////
	// ���[�h�ύX�֌W�̃t�@���N�^
	
	//MEMS�W���C���̒l��0.001rad/s�ȉ��ɂȂ����珉�����艻���[�h���e�p�����䃂�[�h��
	this->global_->nj_inim->add_list(
		new functor::Functor<functor::Is_Under<datatype::StaticVector<3>>,functor::ModeChangeFunc>
			(
			new functor::Is_Under<datatype::StaticVector<3>>(this->global_->nj_aocsdatapool,this->global_->nj_gyro->getDataPoolKey(),0.001),
			new functor::ModeChangeFunc(this->global_->nj_modeman, *this->global_->nj_ctrm)
			)
		);

	//MEMS�W���C���̒l��0.002rad/s�ȏ�ɂȂ�����e�p�����䃂�[�h���������艻���[�h��
	this->global_->nj_ctrm->add_list(
		new functor::Functor<functor::Is_Over<datatype::StaticVector<3>>,functor::ModeChangeFunc>
			(
			new functor::Is_Over<datatype::StaticVector<3>>(this->global_->nj_aocsdatapool,this->global_->nj_gyro->getDataPoolKey(),0.002),
			new functor::ModeChangeFunc(this->global_->nj_modeman, *this->global_->nj_inim)
			)
		);

	//FOG�̒l��0.0001rad/s�ȉ��ɂȂ�����e�p�����䃂�[�h�����p�����䃂�[�h��
	this->global_->nj_ctrm->add_list(
		new functor::Functor<functor::Is_Under<datatype::StaticVector<3>>,functor::ModeChangeFunc>
			(
			new functor::Is_Under<datatype::StaticVector<3>>(this->global_->nj_aocsdatapool,this->global_->nj_fog->getDataPoolKey(),0.0001),
			new functor::ModeChangeFunc(this->global_->nj_modeman, *this->global_->nj_ccdm)
			)
		);

	//FOG�̒l��0.0002rad/s�ȏ�ɂȂ����琸�p�����䃂�[�h���e�p�����䃂�[�h��
	this->global_->nj_ccdm->add_list(
		new functor::Functor<functor::Is_Over<datatype::StaticVector<3>>,functor::ModeChangeFunc>
			(
			new functor::Is_Over<datatype::StaticVector<3>>(this->global_->nj_aocsdatapool,this->global_->nj_fog->getDataPoolKey(),0.0002),
			new functor::ModeChangeFunc(this->global_->nj_modeman, *this->global_->nj_ctrm)
			)
		);

	//FOG�̒l��0.00001rad/s�ȉ��ɂȂ����琸�p�����䃂�[�h���ϑ����[�h��
	this->global_->nj_ctrm->add_list(
		new functor::Functor<functor::Is_Under<datatype::StaticVector<3>>,functor::ModeChangeFunc>
			(
			new functor::Is_Under<datatype::StaticVector<3>>(this->global_->nj_aocsdatapool,this->global_->nj_fog->getDataPoolKey(),0.00001),
			new functor::ModeChangeFunc(this->global_->nj_modeman, *this->global_->nj_ccdm)
			)
		);

	//FOG�̒l��0.00002rad/s�ȏ�ɂȂ�����ϑ����[�h�����p�����䃂�[�h��
	this->global_->nj_ccdm->add_list(
		new functor::Functor<functor::Is_Over<datatype::StaticVector<3>>,functor::ModeChangeFunc>
			(
			new functor::Is_Over<datatype::StaticVector<3>>(this->global_->nj_aocsdatapool,this->global_->nj_fog->getDataPoolKey(),0.00002),
			new functor::ModeChangeFunc(this->global_->nj_modeman, *this->global_->nj_ctrm)
			)
		);
	typedef devicedriver::rw::RWBase<Env> RW;

	//RW��1�ł��O�a������A�����[�f�B���O���[�h��
	functor::IFunctor* rwfunc1 = new functor::Functor<functor::Getter_Is<RW>,functor::ModeChangeFunc>
		(
			new functor::Getter_Is<RW>(this->global_->nj_rw1, &RW::isSaturated),
			new functor::ModeChangeFunc(this->global_->nj_modeman, *this->global_->nj_ctrm)
		);
	functor::IFunctor* rwfunc2 = new functor::Functor<functor::Getter_Is<RW>,functor::ModeChangeFunc>
		(
			new functor::Getter_Is<RW>(this->global_->nj_rw2, &RW::isSaturated),
			new functor::ModeChangeFunc(this->global_->nj_modeman, *this->global_->nj_ctrm)
		);
	functor::IFunctor* rwfunc3 = new functor::Functor<functor::Getter_Is<RW>,functor::ModeChangeFunc>
		(
			new functor::Getter_Is<RW>(this->global_->nj_rw3, &RW::isSaturated),
			new functor::ModeChangeFunc(this->global_->nj_modeman, *this->global_->nj_ctrm)
		);
	functor::IFunctor* rwfunc4 = new functor::Functor<functor::Getter_Is<RW>,functor::ModeChangeFunc>
		(
			new functor::Getter_Is<RW>(this->global_->nj_rw4, &RW::isSaturated),
			new functor::ModeChangeFunc(this->global_->nj_modeman, *this->global_->nj_ctrm)
		);

	this->global_->nj_mism->add_list(rwfunc1);
	this->global_->nj_mism->add_list(rwfunc2);
	this->global_->nj_mism->add_list(rwfunc3);
	this->global_->nj_mism->add_list(rwfunc4);

	this->global_->nj_ctrm->add_list(rwfunc1);
	this->global_->nj_ctrm->add_list(rwfunc2);
	this->global_->nj_ctrm->add_list(rwfunc3);
	this->global_->nj_ctrm->add_list(rwfunc4);

	this->global_->nj_ccdm->add_list(rwfunc1);
	this->global_->nj_ccdm->add_list(rwfunc2);
	this->global_->nj_ccdm->add_list(rwfunc3);
	this->global_->nj_ccdm->add_list(rwfunc4);

	//RW�̊p�^���ʂ�������ꂽ��ӂ����ёe���䃂�[�h��
}

template<class Env>
void NJFactory<Env>::createAdditionalHotSpot(){

}

template<class Env>
void NJFactory<Env>::createDataPoolConnection(){
	this->global_->nj_mtqx->connect(global_->nj_aocsdatapool,10,"NJ_MTQ1");
	this->global_->nj_mtqy->connect(global_->nj_aocsdatapool,10,"NJ_MTQ2");
	this->global_->nj_mtqz->connect(global_->nj_aocsdatapool,10,"NJ_MTQ3");
	this->global_->nj_mtq->connect(global_->nj_aocsdatapool,10,"NJ_MTQ");

	this->global_->nj_sttx->connect(global_->nj_aocsdatapool,10,"NJ_STTX");
	this->global_->nj_stty->connect(global_->nj_aocsdatapool,10,"NJ_STTY");
	this->global_->nj_stt->connect(global_->nj_aocsdatapool,10,"NJ_STT");

	this->global_->nj_rw1->connect(global_->nj_aocsdatapool,10,"NJ_RW1");
	this->global_->nj_rw2->connect(global_->nj_aocsdatapool,10,"NJ_RW2");
	this->global_->nj_rw3->connect(global_->nj_aocsdatapool,10,"NJ_RW3");
	this->global_->nj_rw4->connect(global_->nj_aocsdatapool,10,"NJ_RW4");
	this->global_->nj_rw->connect(global_->nj_aocsdatapool,10,"NJ_RW");

	this->global_->nj_fogx->connect(global_->nj_aocsdatapool,10,"NJ_FOGX");
	this->global_->nj_fogy->connect(global_->nj_aocsdatapool,10,"NJ_FOGY");
	this->global_->nj_fogz->connect(global_->nj_aocsdatapool,10,"NJ_FOGZ");
	this->global_->nj_fog->connect(global_->nj_aocsdatapool,10,"NJ_FOG");

	this->global_->nj_gyrox->connect(global_->nj_aocsdatapool,10,"NJ_GYROX");
	this->global_->nj_gyroy->connect(global_->nj_aocsdatapool,10,"NJ_GYROY");
	this->global_->nj_gyroz->connect(global_->nj_aocsdatapool,10,"NJ_GYROZ");
	this->global_->nj_gyro->connect(global_->nj_aocsdatapool,10,"NJ_GYRO");

	this->global_->nj_st4->connect(global_->nj_aocsdatapool,10,"NJ_ST4");
	this->global_->nj_st5->connect(global_->nj_aocsdatapool,10,"NJ_ST5");

	this->global_->nj_gps->connect(global_->nj_aocsdatapool,10,"NJ_GPS");
}


} /* End of namespace stf::factory */
} /* End of namespace stf */




#endif // factory_NJFactory_h