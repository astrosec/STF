/**
 * @file   ModeManagerBase.cpp
 * @brief  モードの管理を行う機能マネージャ基底クラス．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#include "ModeManagerBase.h"
#include "../mode/Mode.h"
#include "../../util/Trace.h"
#include "../../core/datapool/Datapool.h"

namespace stf {
namespace core {
namespace manager {

// Oberver
void ModeManagerBase::change_mode(const core::mode::Mode *mode)
{
	util::Trace trace(util::Trace::kManager, "modeChange ModeManager");
	trace.debug(mode->name());
	current_mode_ = mode;
	this->eventdatapool_->set(event::ModeChange);
	this->notify_observers(*mode);
}

void ModeManagerBase::notify(const mode::Mode* value){
	this->component_ = value->get_list(SpotType());
}

void ModeManagerBase::run()
{
	printf(this->name_.to_char());
	printf("\n");
	util::Trace trace(util::Trace::kManager, "run ModeManager");
}

const datatype::String& ModeManagerBase::get_current_modename() const {
	return this->current_mode_->name();
}

} /* End of namespace stf::core::manager */
} /* End of namespace stf::core */
} /* End of namespace stf */
