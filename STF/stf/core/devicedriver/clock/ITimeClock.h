/**
 * @file   ITimeClock.h
 * @brief  Time�^�̃J�E���g���\�ł��邱�Ƃ��������ۃC���^�[�t�F�[�X�D
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

//! Time�^�̃J�E���g���\�ł��邱�Ƃ��������ۃC���^�[�t�F�[�X�D
/*! 
	CPU�����Ȃǂ̃��b�p�[�Ɏg�������ł���C���^�[�t�F�[�X�D
	IDataUpdatable::doUpdate�ɂ���Ď��������X�V���邱�Ƃ�z�肵�Ă���D
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
