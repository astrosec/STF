/**
 * @file   PRISMGlobal.h
 * @brief  PRISMのオブジェクト群を保持するクラス．
 *  A class that holds PRISM objects
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
	//! 衛星のOBC時刻を取得  Get satellite OBC time
	virtual const datatype::Time get_global_time(){
		return this->pr_clock->get_time();
	}

	//! 衛星のRTC時刻を取得  Get satellite RTC time
	virtual const datatype::DateTime get_global_datetime(){
		return this->pr_clock->get_datetime();
	}

	//! 衛星の質量特性モデルを取得  Acquires satellite mass characteristics model
	virtual const datatype::SatelliteModel get_satellitemodel() const{
		return this->prism_body_;
	}

	//! Aocsデータプールのハンドラを取得．Get Aocs datapool handler
	virtual const core::datapool::AocsDataPool* get_datapool() const {
		return this->pr_aocsdatapool;
	}

	//! Eventデータプールのハンドラを取得．Get Event Data Pool Handler
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
	manager::UnitManagerBase* pr_uniman1; // 10Hz, 通常のセンサ，アクチュエータ Normal sensor, actuator
	manager::UnitManagerBase* pr_uniman2; // 25Hz, AD変換  AD conversion
	manager::ControlManagerBase* pr_conman;
	manager::TelemetryManagerBase* pr_telman1;// CDHテレメ CDH telemetry
	manager::TelemetryManagerBase* pr_telman2;// AOCSテレメ  AOCS Telemetry
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
	// CDH/AOCSのステータスとテレメをダウンリンクするためのイテレータ
	// Iterator for downlinking CDH/AOCS status and telemetry
	interface::PRISMTelemetryIterator<Env, 100, 1>* pr_statusiterator;
	interface::PRISMTelemetryIterator<Env, 100, 4>* pr_telemetryiterator;
	interface::PRISMTelemetryIterator<Env, 100, 1>* pr_aocsstatusiterator;
	interface::PRISMTelemetryIterator<Env, 100, 4>* pr_aocstelemetryiterator;

	/////////////////////////////////////////////////////
	// Command-Prototypes
	/////////////////////////////////////////////////////
	// CDH
	command::Command* pr_c_alv;//生存信号  Survival signal
	command::Command* pr_c_hta;//ヒーター有効  Heater effective
	command::Command* pr_c_htd;//ヒーター無効  Heater disabled
	command::Command* pr_c_htg;//ヒーター状態取得  Get heater status
	command::Command* pr_c_hts;//ヒーター状態設定  Heater status setting
	command::Command* pr_c_rtg;//RTC時刻取得  RTC is always available
	command::Command* pr_c_rts;//RTC時刻セット RTC time set
	command::Command* pr_c_tmg;//OBC時刻取得 OBC always get
	command::Command* pr_c_tms;//OBC時刻セット  OBC time set
	command::Command* pr_c_tlg;//テレメトリ取得  Telemetry acquisition
	command::Command* pr_c_tos;//詳細履歴取得開始時刻の設定 Set detailed history acquisition start time
	command::Command* pr_c_trs;//詳細履歴取得開始時刻の設定 Set detailed history acquisition start time
	command::Command* pr_c_tss;//詳細履歴取得 Get detailed history
	command::Command* pr_c_sgs;//ステータス取得  Status acquisition
	// Power
	command::Command* pr_c_pd;//電源OFF  Power off
	command::Command* pr_c_pu;//電源ON Power ON
	command::Command* pr_c_mds;//セーフモード移行 Enter safe mode
	command::Command* pr_c_mdn;//ノーマルモード移行 Normal mode transition
	command::Command* pr_c_md;//モード取得 Mode acquisition
	command::Command* pr_c_hth;//電池ヒーター状態取得 Battery heater status acquisition
	command::Command* pr_c_hdt;//電池ヒーター状態設定 Battery heater status setting
	// ADCS
	command::Command* pr_c_aen0;//AOCS系有効 AOCS is valid
	command::Command* pr_c_aen1;//AOCS系無効 Invalid AOCS system
	command::Command* pr_c_ams;//AOCSモード変更 Change AOCS mode
	command::Command* pr_c_amG;//AOCSモード取得 AOCS mode acquisition
	command::Command* pr_c_atw;//AOCSテレメトリの有効・無効 AOCS telemetry enabled/disabled
	command::Command* pr_c_atg;//AOCSテレメトリ取得 AOCS telemetry acquisition
	command::Command* pr_c_atr;//AOCSテレメトリ開始時刻の設定 AOCS telemetry start time setting
	command::Command* pr_c_ato;//
	command::Command* pr_c_aps;//AOCSパラメータセット AOCS parameter set
	command::Command* pr_c_apg;//AOCSパラメータ取得  AOCS parameter acquisition
	//command::Command* pr_c_amq;
	//
	core::manager::HeaterControl<Env>* pr_heater;
	core::manager::HeaterControl<Env>* pr_battheater;
};

} /* End of namespace stf */

#endif // satellite_prism_PRISMGlobal_h