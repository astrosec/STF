/**
 * @file   NJEKF.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_strategy_control_NJEKF_h
#define stf_core_strategy_control_NJEKF_h

#include "../../core/strategy/control/EKF.h"
#include "../../interface/ITelemetable.h"
#include "../../interface/Iterator.h"
#include "../../core/event/SubjectBase.h"
#include "../../core/event/Event.h"

namespace stf {
namespace interface {
template<int U> class NJEKFIterator;
}
namespace core {
namespace strategy {
namespace control {

template<int U> class NJEKFIterator;

// �t���[�����[�N��EKF���p������NJ�p�̃J���}���t�B���^�D
// �C�e���[�^�ɂ��Ǝ��̃e�����g���������\�ł���_�C
// Observer�p�^�[���ɂ���ă��[�h�ύX�̃^�C�~���O�Ńp�����[�^������������_���ėpEKF�Ƃ̈Ⴂ�D
class NJEKF : public EKF, virtual public event::Observer<event::ModeChangeEvent>
{
public:
	NJEKF(int instance_id, mode::ModeBase* missionmode) : EKF(instance_id), missionmode_(missionmode){}
	virtual ~NJEKF(){}
	virtual void notify(const mode::ModeBase* value){ 
		if(value == missionmode_) return; //�����ϑ����[�h�̏ꍇ�̓��Z�b�g���Ȃ�
		this->init(); 
	}
private:
	template<int U>friend class interface::NJEKFIterator;
	const mode::ModeBase* missionmode_;
};


} /* End of namespace stf::core::strategy::control */
} /* End of namespace stf::core::strategy */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_strategy_control_input_NJEKF_h
