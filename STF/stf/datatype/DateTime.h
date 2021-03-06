/**
 * @file   DateTime.h
 * @brief  ユリウス暦による絶対時刻を保持するクラス．時間間隔などの計算にはTimeを使う．
 * A class that holds absolute time according to the Julian calendar. Use Time to calculate time intervals.
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef datatype_DateTime_h
#define datatype_DateTime_h
#include"../util/stfassert.h"
#include "Time.h"

namespace stf { 
namespace datatype {

//! グレゴリオ暦による絶対時刻を秒精度で保持する．
	//Holds absolute time according to Gregorian calendar with second precision.
/*! */
class DateTime {
public:
    DateTime(): date_(0), hour_(0), minute_(0), second_(0) {}

	DateTime(int date, int hour, int minute, int second) : date_(date), hour_(hour), minute_(minute), second_(second) {}

	DateTime(int year, int month, int day, int hour = 0, int minute = 0, int second = 0) 
	{
		init(year, month, day, hour, minute, second);
	}

    DateTime(const DateTime &rhs){
		this->second_ = rhs.second_;
		this->minute_ = rhs.minute_;
		this->hour_ = rhs.hour_;
		this->date_ = rhs.date_;
	}

	virtual ~DateTime(){}

	inline void init(int year, int month, int day, int hour, int minute, int second);

	int seconds() const { return this->second_; }
    inline void add_seconds(int second);
    inline int total_seconds() const;

	int minutes() const { return this->minute_; }
    inline void add_minutes(int minutes);
    inline int total_minutes() const;

	int hours() const { return this->hour_; }
    inline void add_hours(int hours);
    inline int total_hours() const;

	int dates() const { return this->date_; }
    inline void add_dates(int dates);

	inline double get_julian() const;
    inline void clear();
    inline DateTime &operator=(const DateTime &rhs);
    inline DateTime &operator+=(const Time &rhs);
    inline DateTime &operator-=(const Time &rhs);

private:
    friend inline bool operator ==(const DateTime&, const DateTime&);
    friend inline bool operator !=(const DateTime&, const DateTime&);
    friend inline bool operator >(const DateTime&, const DateTime&);
    friend inline bool operator <(const DateTime&, const DateTime&);
    friend inline bool operator >=(const DateTime&, const DateTime&);
    friend inline bool operator <=(const DateTime&, const DateTime&);

	int to_julianday_(int year, int month, int day);

	int date_;
	int hour_;
	int minute_;
	int second_;
};


//////////////////////////////////
//  Inline Methods for DateTime //
//////////////////////////////////
inline void DateTime::init(int year, int month, int day, int hour, int minute, int second)
{
	stf_assert(month > 0 && month < 13);
	stf_assert(day > 0 && day < 32);
	stf_assert(hour >= 0 && hour < 24);
	stf_assert(minute >= 0 && minute < 60);
	stf_assert(second >= 0 && second < 60);

	this->date_  = to_julianday_(year, month, day);
	this->hour_ = hour;
	this->minute_ = minute;
	this->second_ = second;
}

inline void DateTime::add_seconds(int second)
{
	this->second_ += second;
	while(this->second_ >= 60){
		this->second_ -= 60;
		this->add_minutes(1);
	}
	while(this->second_ < 0){
		this->second_ += 60;
		this->add_minutes(-1);
	}
}

inline int DateTime::total_seconds() const 
{
    return this->second_ + 60 * this->total_minutes();
}

inline void DateTime::add_minutes(int minutes)
{
	this->minute_ += minutes;
	while(this->minute_ >= 60){
		this->minute_ -= 60;
		this->add_hours(1);
	}
	while(this->minute_ < 0){
		this->minute_ += 60;
		this->add_hours(-1);
	}
}

inline int DateTime::total_minutes() const 
{
	return this->minute_ + 60 * this->total_hours();
}

inline void DateTime::add_hours(int hours)
{
	this->hour_ += hours;
	while(this->hour_ >= 24){
		this->hour_ -= 24;
		this->add_dates(1);
	}
	while(this->hour_ < 0){
		this->hour_ += 24;
		this->add_dates(-1);
	}
}

inline int DateTime::total_hours() const 
{
	return this->hour_ + 24 * this->date_;
}

inline void DateTime::add_dates(int dates)
{
	this->date_ += dates;
}

inline double DateTime::get_julian() const
{
	return this->date_ + ( this->hour_ + (this->minute_ + (this->second_ / 60)) / 60 )/ 24 ;
}

inline void DateTime::clear()
{
	this->date_ = 0;
	this->hour_ = 0;
	this->second_ = 0;
	this->minute_ = 0;
}

inline DateTime &DateTime::operator+=(const Time &rhs){
	this->add_seconds( rhs.seconds() );
    return *this;
}

inline DateTime &DateTime::operator-=(const Time &rhs){
	this->add_seconds( -rhs.seconds() );
    return *this;
}

inline DateTime &DateTime::operator=(const DateTime &rhs){
	this->second_ = rhs.second_;
	this->minute_ = rhs.minute_;
	this->hour_ = rhs.hour_;
	this->date_ = rhs.date_;
    return *this;
}

inline int DateTime::to_julianday_(int year, int month, int day)
{
	return 367 * year - (int)(7 * (double)(year + (int)(((double)month + 9) / 12)) / 4) + (int)(275 * (double)month / 9) + day + 1721014;
}

//////////////////////////
//  Free Methods        //
//////////////////////////

inline const DateTime operator + (const DateTime& time1, const Time& time2){
	DateTime temp = time1;
	temp += time2;
	return temp;
}

inline const DateTime operator - (const DateTime& time1, const Time& time2){
	DateTime temp = time1;
	temp -= time2;
	return temp;
}

inline bool operator==(const DateTime &time1, const DateTime &time2){
	if(time1.second_ == time2.second_)
		if(time1.minute_ == time2.minute_)
			if(time1.hour_ == time2.hour_)
				if(time1.date_ == time2.date_)
					return true;
    return false;
}

inline bool operator!=(const DateTime &time1, const DateTime &time2){
    return !(time1 == time2);
}

inline bool operator>(const DateTime &time1, const DateTime &time2){
	if(time1.date_ > time2.date_) return true;
	if(time1.date_ < time2.date_) return false;
	if(time1.hour_ > time2.hour_) return true;
	if(time1.hour_ < time2.hour_) return false;
	if(time1.minute_ > time2.minute_) return true;
	if(time1.minute_ < time2.minute_) return false;
	if(time1.second_ > time2.second_) return true;
	return false;
}

inline bool operator>=(const DateTime &time1, const DateTime &time2){
	if(time1.date_ > time2.date_) return true;
	if(time1.date_ < time2.date_) return false;
	if(time1.hour_ > time2.hour_) return true;
	if(time1.hour_ < time2.hour_) return false;
	if(time1.minute_ > time2.minute_) return true;
	if(time1.minute_ < time2.minute_) return false;
	if(time1.second_ < time2.second_) return false;
	return true;
}

inline bool operator<(const DateTime &time1, const DateTime &time2){
    return !(time1 > time2);
}

inline bool operator<=(const DateTime &time1, const DateTime &time2){
    return !(time1 >= time2);
}

} /* End of namespace stf::datatype */
} /* End of namespace stf */
#endif // datatype_DateTime_h
