#ifndef datatype_Time_h
#define datatype_Time_h
#include<assert.h>
#include "../util/Ostream.h"

namespace stf { 
namespace datatype {

class Time {
public:
    Time();
    Time(int second, double millisecond);
    Time(const Time &rhs);
    virtual ~Time();
    inline void addSeconds(int seconds);
    inline void addMilliSeconds(double milliSeconds);
	inline int seconds() const { return this->seconds_; }
	inline double milliseconds() const { return this->milliseconds_; }
    inline double totalMilliseconds() const ;
    inline double totalSeconds() const;
    inline void clear();
    inline Time &operator=(const Time &rhs);
    inline Time &operator+=(const Time &rhs);
    inline Time &operator-=(const Time &rhs);
    inline Time &operator/=(int rhs);
    inline Time &operator*=(int rhs);
    int seconds_;
    double milliseconds_;
private:
    friend inline bool operator ==(const Time&,const Time&);
    friend inline bool operator !=(const Time&,const Time&);
    friend inline bool operator >(const Time&,const Time&);
    friend inline bool operator <(const Time&,const Time&);
    friend inline bool operator >=(const Time&,const Time&);
    friend inline bool operator <=(const Time&,const Time&);
	friend inline const Time operator +(const Time&,const Time&);
	friend inline const Time operator -(const Time&,const Time&);
	friend inline const Time operator *(int,const Time&);
	friend inline const Time operator *(const Time&,int);
	friend inline const Time operator /(const Time&,int);

//	friend std::ostream &operator << (std::ostream&, const Time&);
};

////////////////////////////////
//  Inline Methods for Time //
////////////////////////////////


inline void Time::addSeconds(int seconds)
{
    this->seconds_ += seconds;
    assert(this->seconds_ >= 0);
}

inline void Time::addMilliSeconds(double milliSeconds)
{
    this->milliseconds_ += milliSeconds;
    int u = (int)(this->milliseconds_ / 1000);
    this->seconds_ += u;
    this->milliseconds_ -= u * 1000;  
    assert(this->seconds_ >= 0);
}

inline double Time::totalMilliseconds() const 
{
    return 1000 * this->seconds_ + this->milliseconds_;
}

inline void Time::clear()
{
    this->seconds_ = 0;
    this->milliseconds_ = 0.0;
}

inline double Time::totalSeconds() const 
{
    return this->seconds_ + 0.001 * this->milliseconds_;
}

inline Time &Time::operator+=(const Time &rhs){
    this->milliseconds_ += rhs.milliseconds_;
    if(this->milliseconds_ > 1000.0){//桁上がり
        this->seconds_ ++;
        this->milliseconds_ -= 1000;
    }else if(this->milliseconds_ < 0.0){
        this->seconds_ --;
        this->milliseconds_ += 1000;
    }
    this->seconds_ += rhs.seconds_;
    assert(this->seconds_ >= 0);
    return *this;
}

inline Time &Time::operator-=(const Time &rhs){
    this->milliseconds_ -= rhs.milliseconds_;
    if(this->milliseconds_ > 1000.0){//桁上がり
        this->seconds_ ++;
        this->milliseconds_ -= 1000;
    }else if(this->milliseconds_ < 0.0){
        this->seconds_ --;
        this->milliseconds_ += 1000;
    }
    this->seconds_ -= rhs.seconds_;
    assert(this->seconds_ >= 0);
    return *this;
}

inline Time &Time::operator/=(int rhs){
    int r = this->seconds_ % rhs;
    this->seconds_ /= rhs;
    this->milliseconds_ += r * 1000;
    this->milliseconds_ /= rhs;
    assert(this->seconds_ >= 0);
    return *this;
}

inline Time &Time::operator*=(int rhs){
    this->seconds_ *= rhs;
    this->milliseconds_ *= rhs;
    int u = (int)(this->milliseconds_ / 1000);
    this->seconds_ += u;
    this->milliseconds_ -= u * 1000;
    assert(this->seconds_ >= 0);
    return *this;
}

inline Time &Time::operator=(const Time &rhs){
    this->seconds_ = rhs.seconds_;
    this->milliseconds_ = rhs.milliseconds_;
    return *this;
}

inline const Time operator + (const Time& time1, const Time& time2){
	Time temp = time1;
	temp += time2;
	return temp;
}

inline const Time operator - (const Time& time1, const Time& time2){
	Time temp = time1;
	temp -= time2;
	return temp;
}

inline const Time operator * (const Time& time, int factor){
	Time temp = time;
	return temp *= factor;
}

inline const Time operator * (int factor, const Time& time){
	return time * factor;
}

inline const Time operator / (const Time& time, int factor){
	Time temp = time;
	return temp /= factor;
}

inline bool operator==(const Time &time1, const Time &time2){
    if(time1.milliseconds_ == time2.milliseconds_ && time1.seconds_ == time2.seconds_) return true;
    return false;
}

inline bool operator!=(const Time &time1, const Time &time2){
    return !(time1 == time2);
}

inline bool operator>(const Time &time1, const Time &time2){
    if(time1.seconds_ > time2.seconds_){
        return true;
    }else if((time1.seconds_ == time2.seconds_) && (time1.milliseconds_ > time2.milliseconds_)){
        return true;
    }
    return false;
}

inline bool operator>=(const Time &time1, const Time &time2){
    if(time1.seconds_ > time2.seconds_){
        return true;
    }else if((time1.seconds_ == time2.seconds_) && (time1.milliseconds_ >= time2.milliseconds_)){
        return true;
    }
    return false;
}

inline bool operator<(const Time &time1, const Time &time2){
    return !(time1 > time2);
}

inline bool operator<=(const Time &time1, const Time &time2){
    return !(time1 >= time2);
}

} /* End of namespace stf::datatype */
} /* End of namespace stf */
#endif // datatype_Time_h
