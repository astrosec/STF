/**
 * @file   IAbsoluteTimeClock.h
 * @brief  DateTime�^�̃J�E���g���\�ł��邱�Ƃ��������ۃC���^�[�t�F�[�X�D
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_devicedriver_clock_IAbsoluteTimeClock_h
#define stf_core_devicedriver_clock_IAbsoluteTimeClock_h

#include "../../../datatype/DateTime.h"
#include "../IDataUpdatable.h"

namespace stf {
namespace core {
namespace devicedriver {
namespace clock {

//! DateTime�^�̃J�E���g���\�ł��邱�Ƃ��������ۃC���^�[�t�F�[�X�D
/*! 
	GPS��RTC�̃��b�p�[�Ɏg�������ł���C���^�[�t�F�[�X�D
	IDataUpdatable::doUpdate�ɂ���Ď��������X�V���邱�Ƃ�z�肵�Ă���D
*/
class IAbsoluteTimeClock : virtual public IDataUpdatable
{
public:
	virtual const datatype::DateTime get_datetime() const = 0;
	virtual void set_absolute_time(datatype::DateTime) = 0;
	virtual void set_absolute_time(int year, int month, int day, int hour, int minute, int second) = 0;
	virtual ~IAbsoluteTimeClock(void){}
};

} /* End of namespace stf::core::devicedriver::clock */
} /* End of namespace stf::core::devicedriver */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_clock_ITimeClock_h
