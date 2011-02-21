/**
 * @file   ITimeClock.h
 * @brief  Time型のカウントが可能であることを示す抽象インターフェース．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_devicedriver_clock_ITimeClock_h
#define stf_core_devicedriver_clock_ITimeClock_h

#include "../../../datatype/Time.h"
#include "../IDataUpdatable.h"

namespace stf {
namespace core {
namespace devicedriver {
namespace clock {

//! Time型のカウントが可能であることを示す抽象インターフェース．
/*! 
	CPU時刻などのラッパーに使う事ができるインターフェース．
	IDataUpdatable::doUpdateによって時刻情報を更新することを想定している．
*/
class ITimeClock : virtual public IDataUpdatable
{
public:
	virtual const datatype::Time get_time() const = 0;
	virtual void set_time(datatype::Time) = 0;
	virtual void set_time(int sec, int millisec) = 0;
	virtual ~ITimeClock(void){}
};


} /* End of namespace stf::core::devicedriver::clock */
} /* End of namespace stf::core::devicedriver */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_clock_ITimeClock_h
