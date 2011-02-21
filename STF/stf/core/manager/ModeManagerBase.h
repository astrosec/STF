/**
 * @file   ModeManagerBase.h
 * @brief  モードの管理を行う機能マネージャ基底クラス．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_manager_ModeManagerBase_h
#define stf_core_manager_ModeManagerBase_h

#include "ManagerBase.h"
#include "../../datatype/List.h"
#include "../event/ModeChangeEvent.h"
#include "../event/SubjectBase.h"
#include "../../util/loki/TypeManip.h"

namespace stf {
namespace core {
namespace event {
template<class evt> class Observer;
class ModeChangeEvent;
}
namespace devicedriver {
class ISwitchable;
}
namespace mode {
class ModeBase;
} /* End of namespace stf::core::mode */

namespace manager {

//! モードの管理を行う機能マネージャ基底クラス．
/*! 
	ユーザーはこのクラスを書き換えることが許可されない．
	機能マネージャの振る舞いをカスタマイズしたい場合，派生クラス側で仮想関数を実装する（Generation-Gapパターン）．
*/
class ModeManagerBase : public ManagerBase, virtual public event::SubjectBase<event::ModeChangeEvent>,virtual public event::Observer<event::ModeChangeEvent>{
public:
	typedef core::devicedriver::ISwitchable HotSpot;
	typedef Loki::Type2Type<core::devicedriver::ISwitchable> SpotType;

	ModeManagerBase(int instance_id) : ManagerBase(instance_id, "ModeManager"),current_mode_(0), component_(0) {}
	virtual ~ModeManagerBase(){}

	virtual void change_mode(const mode::ModeBase *newmode);
	const datatype::String& get_current_modename() const;
    virtual void run();
	virtual bool runnable() const { return true; }
	virtual void notify(const mode::ModeBase* value);
protected:
    const core::mode::ModeBase *current_mode_;
	const datatype::List<HotSpot>* component_;
};

} /* End of namespace stf::core::manager */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif //stf_core_manager_ModeManagerBase_h
