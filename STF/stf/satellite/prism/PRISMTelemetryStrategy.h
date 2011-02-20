/**
 * @file   PRISMTelemetryStrategy.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_strategy_telemetry_PRISMTelemetryStrategy_h
#define stf_core_strategy_telemetry_PRISMTelemetryStrategy_h
#include "../../core/strategy/telemetry/SelectingOutput.h"

namespace stf {
namespace interface {
template<int SCALE, int DEPTH> class PRISMTelemetryIterator;
}
namespace core {
namespace strategy {
namespace telemetry {

// PRISM�̃e�����g���iAOCS/CDH/�ڍ�/�e�����j��S������Strategy.
// ��{�I�ɂ�SelectingOutput�̎����������p���ł��邪�C�O���C�e���[�^�֎��������J����_�C
// �����ɂ���ĊJ�n�ƏI���𐧌䂷��_���قȂ�D
template<int SCALE>
class PRISMTelemetryStrategy : public SelectingOutput<short,SCALE> {
public:
	PRISMTelemetryStrategy(int instance_id,devicedriver::tmhandler::ITelemetryStoragable* storage,
		const core::datapool::AocsDataPool* pool,
		const core::datapool::EventDataPool* eventpool,
		const devicedriver::clock::PRISMDummyClock* clock
		) : SelectingOutput<short,SCALE>(instance_id, storage, pool, eventpool), clock_(clock){}
	void setstate(bool enable) { is_enabled_ = enable; }
	virtual void write_to_telemetry(){
		if(is_enabled_)
			if( this->start_obc_ >= this->clock_->getTime() || this->start_rtc_ >= this->clock_->getAbsoluteTime() ){
				SelectingOutput<short,SCALE>::write_to_telemetry();
			}
	}
	void set_time(int second){
		this->start_obc_.clear();
		this->start_obc_.add_seconds(second);
	}
	void setRTCTime(int year,int month,int date,int hour,int minute,int second){
		this->start_rtc_.init(year,month,date,hour,minute,second);
	}
private:
	// �ǂ��炩����������C���e�����L���t���O�������Ă�����擾�J�n�D�f�[�^�������ς��ɂȂ�C���㏑���֎~���[�h�̂Ƃ��擾��~�D
	datatype::DateTime start_rtc_;
	datatype::Time start_obc_;
	const devicedriver::clock::PRISMDummyClock* clock_;
	bool is_enabled_;
	template<int SCALE, int DEPTH> friend class PRISMTelemetryIterator;
};

} /* End of namespace stf::core::strategy::telemetry */
} /* End of namespace stf::core::strategy */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_strategy_telemetry_OutputAll_h