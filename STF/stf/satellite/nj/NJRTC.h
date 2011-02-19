#ifndef stf_core_devicedriver_clock_NJRTC_h
#define stf_core_devicedriver_clock_NJRTC_h
#include "../../core/devicedriver/Includes.h"
#include "../../RootObject.h"
#include "../../util/TypeList.h"

namespace stf {
namespace core {
namespace devicedriver {
namespace clock {

class NJRTC : public CDHMultiComponent< TYPELIST_2( datatype::Time, datatype::DateTime ) >, virtual public ITimeClock, virtual public IAbsoluteTimeClock
{
public:
	NJRTC(int instance_id, int year, int month, int date);
	~NJRTC(void);
	virtual const datatype::Time getTime() const; 
	virtual const datatype::DateTime getAbsoluteTime() const;
	virtual void set_absolute_time(datatype::DateTime t);
	virtual void set_absolute_time(int year, int month, int day, int hour, int minute, int second);
	virtual void set_time(datatype::Time t);
	virtual void set_time(int sec, int millisec);
	virtual void doUpdate();
private:
	NJRTC(const NJRTC& rhs);
	NJRTC& operator =(const NJRTC& rhs);
	static const int CLOCK = 100;
};

} /* End of namespace stf::core::devicedriver::clock */
} /* End of namespace stf::core::devicedriver */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_clock_NJRTC_h
