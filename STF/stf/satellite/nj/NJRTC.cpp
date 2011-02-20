/**
 * @file   NJRTC.cpp
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#include "NJRTC.h"


namespace stf {
namespace core {
namespace devicedriver {
namespace clock {

const datatype::Time NJRTC::getTime() const {
	return this->get<0,datatype::Time>();
}

const datatype::DateTime NJRTC::getAbsoluteTime() const {
	return this->get<1,datatype::DateTime>();
}

NJRTC::NJRTC(int instance_id, int year, int month, int date) : CDHMultiComponent< TYPELIST_2( datatype::Time, datatype::DateTime )>(instance_id, "NJRTC")//, datetime_(year,month,date)
{
	const_cast<datatype::DateTime*>(&get<1,datatype::DateTime>())->init(year,month,date,0,0,0);
	this->clock_ = this;//static�|�C���^�Ɋ��蓖��
}
void NJRTC::set_time(datatype::Time t){
	this->outputport<0,datatype::Time>().value_b_ = t;
}

void NJRTC::set_time(int sec, int millisec){
	this->outputport<0,datatype::Time>().value_b_.clear();
	this->outputport<0,datatype::Time>().value_b_.add_milliseconds(millisec);
	this->outputport<0,datatype::Time>().value_b_.add_seconds(sec);
}

void NJRTC::set_absolute_time(datatype::DateTime t){
	this->outputport<1,datatype::DateTime>().value_b_ = t;
}

void NJRTC::set_absolute_time(int year, int month, int day, int hour, int minute, int second){
	this->outputport<1,datatype::DateTime>().value_b_.init(year,month,day,hour,minute,second);
}

NJRTC::~NJRTC(void)
{

}

void NJRTC::doUpdate()
{
	const_cast<datatype::Time*>(&get<0,datatype::Time>())->add_milliseconds(this->CLOCK);
	//this->time_.add_milliseconds(this->CLOCK);
}

} /* End of namespace stf::core::devicedriver::clock */
} /* End of namespace stf::core::devicedriver */
} /* End of namespace stf::core */
} /* End of namespace stf */