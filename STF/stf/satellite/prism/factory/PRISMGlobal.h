/**
 * @file   PRISMGlobal.h
 * @brief  PRISM�̃I�u�W�F�N�g�Q��ێ�����N���X�D
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef satellite_prism_PRISMGlobal_h
#define satellite_prism_PRISMGlobal_h
#include "../../../GlobalObject.h"

#include "../../../core/devicedriver/Includes.h"
#include "../../../core/manager/Includes.h"
#include "../../../core/datapool/Datapool.h"
#include "../../../core/mode/Mode.h"
#include "../../../core/strategy/control/IControlStrategy.h"
#include "../../../core/strategy/telemetry/ITelemetryStrategy.h"
#include "../../../datatype/SatelliteModel.h"

#include "../strategy/includes.h"
#include "../devicedriver/includes.h"
#include "../manager/PRISMCustomManager.h"
#include "../PRISMIterator.h"

namespace stf {

template <class Env>
struct PRISMGlobal : public Global<Env>{
	//! �q����OBC�������擾
	virtual const datatype::Time get_global_time(){
		return this->pr_clock->get_time();
	}

	//! �q����RTC�������擾
	virtual const datatype::DateTime get_global_datetime(){
		return this->pr_clock->get_datetime();
	}

	//! �q���̎��ʓ������f�����擾
	virtual const datatype::SatelliteModel get_satellitemodel() const{
		return this->prism_body_;
	}

	//! Aocs�f�[�^�v�[���̃n���h�����擾�D
	virtual const core::datapool::AocsDataPool* get_datapool() const {
		return this->pr_aocsdatapool;
	}

	//! Event�f�[�^�v�[���̃n���h�����擾�D
	virtual const core::datapool::EventDataPool* get_eventdatapool() const {
		return this->pr_eventdatapool;
	}

	/////////////////////////////////////////////////////
	// Mass Model
	/////////////////////////////////////////////////////
	datatype::SatelliteModel prism_body_;

	/////////////////////////////////////////////////////
	// Data Pool
	/////////////////////////////////////////////////////
	datapool::AocsDataPool* pr_aocsdatapool;
	datapool::EventDataPool* pr_eventdatapool;

	/////////////////////////////////////////////////////
	// Mode
	/////////////////////////////////////////////////////
	mode::Mode* pr_safemode;
	mode::Mode* pr_dpmode;
	mode::Mode* pr_dsmode;
	mode::Mode* pr_dmode;
	mode::Mode* pr_amode;
	mode::Mode* pr_resetmode;

	/////////////////////////////////////////////////////
	// Manager
	/////////////////////////////////////////////////////
	manager::ModeManagerBase* pr_modeman;
	manager::UnitManagerBase* pr_uniman1; // 10Hz, �ʏ�̃Z���T�C�A�N�`���G�[�^
	manager::UnitManagerBase* pr_uniman2; // 25Hz, AD�ϊ�
	manager::ControlManagerBase* pr_conman;
	manager::TelemetryManagerBase* pr_telman1;// CDH�e����
	manager::TelemetryManagerBase* pr_telman2;// AOCS�e����
	manager::SystemManagerBase* pr_sysman;
	manager::CommandManagerBase* pr_commman;
	manager::PRISMCustomManager<Env>* pr_customman;

	/////////////////////////////////////////////////////
	// Strategy
	/////////////////////////////////////////////////////
	core::strategy::control::IControlStrategy* pr_controlstrategy;
	core::strategy::telemetry::PRISMTelemetryStrategy<Env, 1000>* pr_tmstrategy;
	core::strategy::telemetry::PRISMTelemetryStrategy<Env, 1000>* pr_aocstmstrategy;

	/////////////////////////////////////////////////////
	// Device Driver
	/////////////////////////////////////////////////////
	//MTQ
	devicedriver::mtq::PRISMMTQ<Env>* pr_mtqx;
	devicedriver::mtq::PRISMMTQ<Env>* pr_mtqy;
	devicedriver::mtq::PRISMMTQ<Env>* pr_mtqz;
	devicedriver::CompositeOutput<devicedriver::mtq::PRISMMTQ<Env>, 3>* pr_mtq;

	//Gyro
	devicedriver::gyro::PRISMGyro<Env>* pr_gyrox;
	devicedriver::gyro::PRISMGyro<Env>* pr_gyroy;	
	devicedriver::gyro::PRISMGyro<Env>* pr_gyroz;
	devicedriver::CompositeInput<devicedriver::gyro::PRISMGyro<Env>, 3>* pr_gyro;

	//Sun Sensor
	devicedriver::sunsensor::PRISMSunSensor<Env>* pr_sspx;
	devicedriver::sunsensor::PRISMSunSensor<Env>* pr_sspy;
	devicedriver::sunsensor::PRISMSunSensor<Env>* pr_sspz;
	devicedriver::sunsensor::PRISMSunSensor<Env>* pr_ssmx;
	devicedriver::sunsensor::PRISMSunSensor<Env>* pr_ssmy;
	devicedriver::sunsensor::PRISMSunSensor<Env>* pr_ssmz;
	devicedriver::CompositeInput<devicedriver::sunsensor::PRISMSunSensor<Env>, 6>* pr_ss;

	//Magnetrometer
	devicedriver::magnetometer::PRISMTAM<Env>* pr_tam;
	//GPS
	devicedriver::gps::DummyGPS<Env>* pr_gpsdummy;
	//
	devicedriver::clock::PRISMDummyClock<Env>* pr_clock;
	
	devicedriver::PRISMADC<Env>* pr_adc;

	devicedriver::PRISMTempSensor<Env>* pr_tempsensor;
	devicedriver::PRISMCurrentSensor<Env>* pr_currentsensor;
	devicedriver::PRISMVoltageSensor<Env>* pr_voltagesensor;

	// Command / Telemetry Handler 
	devicedriver::cmhandler::PRISMCommandReceiver<Env>* pr_commandreceiver;
	devicedriver::tmhandler::PRISMTelemetryHandler<Env>* pr_tmhandler;

	/////////////////////////////////////////////////////
	// Iterator
	/////////////////////////////////////////////////////
	// CDH/AOCS�̃X�e�[�^�X�ƃe�������_�E�������N���邽�߂̃C�e���[�^
	interface::PRISMTelemetryIterator<Env, 100, 1>* pr_statusiterator;
	interface::PRISMTelemetryIterator<Env, 100, 4>* pr_telemetryiterator;
	interface::PRISMTelemetryIterator<Env, 100, 1>* pr_aocsstatusiterator;
	interface::PRISMTelemetryIterator<Env, 100, 4>* pr_aocstelemetryiterator;

	/////////////////////////////////////////////////////
	// Command-Prototypes
	/////////////////////////////////////////////////////
	// CDH
	command::Command* pr_c_alv;//�����M��
	command::Command* pr_c_hta;//�q�[�^�[�L��
	command::Command* pr_c_htd;//�q�[�^�[����
	command::Command* pr_c_htg;//�q�[�^�[��Ԏ擾
	command::Command* pr_c_hts;//�q�[�^�[��Ԑݒ�
	command::Command* pr_c_rtg;//RTC�����擾
	command::Command* pr_c_rts;//RTC�����Z�b�g
	command::Command* pr_c_tmg;//OBC�����擾
	command::Command* pr_c_tms;//OBC�����Z�b�g
	command::Command* pr_c_tlg;//�e�����g���擾
	command::Command* pr_c_tos;//�ڍח����擾�J�n�����̐ݒ�
	command::Command* pr_c_trs;//�ڍח����擾�J�n�����̐ݒ�
	command::Command* pr_c_tss;//�ڍח����擾
	command::Command* pr_c_sgs;//�X�e�[�^�X�擾
	// Power
	command::Command* pr_c_pd;//�d��OFF
	command::Command* pr_c_pu;//�d��ON
	command::Command* pr_c_mds;//�Z�[�t���[�h�ڍs
	command::Command* pr_c_mdn;//�m�[�}�����[�h�ڍs
	command::Command* pr_c_md;//���[�h�擾
	command::Command* pr_c_hth;//�d�r�q�[�^�[��Ԏ擾
	command::Command* pr_c_hdt;//�d�r�q�[�^�[��Ԑݒ�
	// ADCS
	command::Command* pr_c_aen0;//AOCS�n�L��
	command::Command* pr_c_aen1;//AOCS�n����
	command::Command* pr_c_ams;//AOCS���[�h�ύX
	command::Command* pr_c_amG;//AOCS���[�h�擾
	command::Command* pr_c_atw;//AOCS�e�����g���̗L���E����
	command::Command* pr_c_atg;//AOCS�e�����g���擾
	command::Command* pr_c_atr;//AOCS�e�����g���J�n�����̐ݒ�
	command::Command* pr_c_ato;//
	command::Command* pr_c_aps;//AOCS�p�����[�^�Z�b�g
	command::Command* pr_c_apg;//AOCS�p�����[�^�擾
	//command::Command* pr_c_amq;
	//
	core::manager::HeaterControl<Env>* pr_heater;
	core::manager::HeaterControl<Env>* pr_battheater;
};

} /* End of namespace stf */

#endif // satellite_prism_PRISMGlobal_h