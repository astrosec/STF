/**
 * @file   CommandManagerBase.h
 * @brief  コマンドの処理を行う機能マネージャ基底クラス．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef core_manager_CommandManagerBase_h
#define core_manager_CommandManagerBase_h
#include "../../util/stfassert.h"
#include "ManagerBase.h"
#include "../event/Event.h"
#include "../event/SubjectBase.h"
#include "../../util/loki/TypeManip.h"

namespace stf {
namespace core {
namespace devicedriver {
namespace cmhandler {
class ICommandReceiver;
} /* End of namespace core::devicedriver::cmhandler */
} /* End of namespace core::devicedriver */
namespace command {
class Command;
} /* End of namespace core::command */
namespace strategy {
namespace control {
class IControlStrategy;
} /* End of namespace core::strategy::control */
} /* End of namespace core::strategy */
namespace mode {
class Mode;
} /* End of namespace core::mode */
} /* End of namespace core */

namespace core {
namespace manager {

//! コマンドの処理を行う機能マネージャ基底クラス．
/*! 
	ユーザーはこのクラスを書き換えることが許可されない．
	機能マネージャの振る舞いをカスタマイズしたい場合，派生クラス側で仮想関数を実装する（Generation-Gapパターン）．
*/
class CommandManagerBase : public ManagerBase, virtual public event::Observer<event::ModeChangeEvent>{
public:
	CommandManagerBase() : ManagerBase("CommandManager"), list_index_(0), crit_list_index_(0)
	{
		for(int i = 0; i < NUM_OF_LIST; i++)
			this->commandList_[i] = 0;
	}
	virtual ~CommandManagerBase(){};
    virtual void run();
	virtual bool runnable() const { return true; }
	virtual void notify(const mode::Mode* value);
	void add_command( command::Command* cmd ){
		list_index_++;
		list_index_ %= NUM_OF_LIST;
		commandList_[list_index_] = cmd;
	}
	void set_receiver(devicedriver::cmhandler::ICommandReceiver* comm_receiver){
		this->comm_receiver_ = comm_receiver;
	}
private:
	void execute_command_(const datatype::Time& t);
	void remove_command_(int i);
	static const int NUM_OF_LIST = 10;
	command::Command* commandList_[NUM_OF_LIST];
	devicedriver::cmhandler::ICommandReceiver* comm_receiver_;
	int list_index_;
	int crit_list_index_;
};


} /* End of namespace stf::core::manager */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // core_manager_CommandManagerBase_h
