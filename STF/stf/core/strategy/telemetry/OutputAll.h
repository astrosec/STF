/**
 * @file   OutputAll.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_strategy_telemetry_OutputAll_h
#define stf_core_strategy_telemetry_OutputAll_h
#include "ITelemetryStrategy.h"
#include "../../../GlobalObject.h"
#include "../StrategyBase.h"
#include "../../datapool/Datapool.h"
#include "../../event/EventBase.h"
#include "../../devicedriver/tmhandler/ITelemetryStoragable.h"
#include "../../../interface/Iterator.h"
#include "../../../util/Ostream.h"
#include "../../../datatype/IAocsData.h"
#include "../../devicedriver/clock/DummyClock.h"
#include "../../../datatype/List.h"
#include "../../../interface/Iterator.h"

namespace stf {
namespace core {
namespace strategy {
namespace telemetry {

template<class T, int SCALE>
class OutputAll : public StrategyBase,  virtual public ITelemetryStrategy, virtual public interface::Iterator{
public:
	OutputAll(int instance_id,devicedriver::tmhandler::ITelemetryStoragable* storage,
		const core::datapool::AocsDataPool* pool,
		const core::datapool::EventDataPool* eventpool
		) : StrategyBase(instance_id,"OutputAll"), storage_(storage),datapooliter_(pool)
	{
		this->createindex_(pool);
		this->tmlistiter_ = this->tmlist_.begin();
	}
	~OutputAll(){}
	virtual void write_to_telemetry();
	virtual void add_tmlist(interface::Iterator* tm){ this->tmlist_.add(*tm);}
	virtual void remove_tmlist(interface::Iterator* tm) { this->tmlist_.remove(*tm);}
    virtual void init();
	virtual bool end();
	virtual void operator ++();
	virtual double operator()();
protected:
	datatype::List<interface::Iterator> tmlist_;
	datatype::List<interface::Iterator>::iterator tmlistiter_;
	devicedriver::tmhandler::ITelemetryStoragable* storage_;
	core::datapool::AocsDataPoolIterator datapooliter_;
	//const core::datapool::EventDataPool* eventpool_;
	void write_(const double* data, int length);
	void createindex_(const core::datapool::AocsDataPool* pool);
};

template<class T, int SCALE>
void OutputAll<T,SCALE>::init(){
	this->datapooliter_.init();
	datatype::List<interface::Iterator>::iterator it = tmlist_.begin();
	while(it != tmlist_.end()){
		(*it).init();
		++it;
	}
	this->tmlistiter_ = this->tmlist_.begin();
}

template<class T, int SCALE>
bool OutputAll<T,SCALE>::end(){
	if(!this->datapooliter_.end()) return false;
	datatype::List<interface::Iterator>::iterator it = tmlist_.begin();
	while(it != tmlist_.end()){
		if(!(*it).end()) return false;
		++it;
	}
	return true;//���ׂẴC�e���[�^�������������Ă����Ƃ�����true
}

template<class T, int SCALE>
void OutputAll<T,SCALE>::operator ++(){
	if(!this->datapooliter_.end()){
		++(this->datapooliter_);
	}
	else{
		++(*this->tmlistiter_);
		if((*this->tmlistiter_).end()){
			++this->tmlistiter_;
		}
	}	
}

template<class T, int SCALE>
double OutputAll<T,SCALE>::operator()(){
	if(!this->datapooliter_.end()){
		this->datapooliter_();
	}
	else{
		(*this->tmlistiter_)();
	}
}

template<class T, int SCALE>
void OutputAll<T,SCALE>::write_to_telemetry(){
	(*this->storage_) << this->clock_->getTime().total_milliseconds();
	this->datapooliter_.init();
	while(!datapooliter_.end()){
		(*this->storage_) << (T)(SCALE * datapooliter_());
		++datapooliter_;
	}
	
	this->storage_->endl();	
}

template<class T, int SCALE>
void OutputAll<T,SCALE>::createindex_(const core::datapool::AocsDataPool* pool)
{
	(*this->storage_) << "Time(ms)";
	for(int i = 0; i < pool->rows(); i++){
		if(pool->isCreated(i)){
			const double* data = pool->get(i)->toStream();
			for(int j = 0; j < pool->get(i)->getStreamLength(); j++){
				(*this->storage_) << pool->getname(i).toChar();
			}
		}
	}
	this->storage_->endl();
}

template<class T, int SCALE>
void OutputAll<T,SCALE>::write_(const double* data, int length)
{
	for(int i = 0; i < length; i++){
		(*this->storage_) << data[i];
	}
}



} /* End of namespace stf::core::strategy::telemetry */
} /* End of namespace stf::core::strategy */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_strategy_telemetry_OutputAll_h