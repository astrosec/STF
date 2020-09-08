/**
 * @file   ModeChangeCommand.h
 * @brief  モード変更を行うコマンド．
 * Command to change mode
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_command_modeChangeCommand_h
#define stf_core_command_modeChangeCommand_h

#include "Command.h"

namespace stf {
namespace core {
namespace mode {
class Mode;
}
namespace manager {
class ModeManagerBase;
}
namespace command {

//! モード変更を行うコマンド  Command to change mode
/*! 
	デフォルトではinitによる変更先コマンドの再設定は行われない．
	//By default, init does not reset the changed command.
	モード変更コマンドのインスタンスは，通常アプリケーションで定義されるモードの数だけ実装される必要がある．
	//Instances of the mode change command must be implemented for the number of modes that are usually defined in the application.
	単一のインスタンスからのcloneで全てのモードへの変更を実装するのであれば，int*型からModeインスタンスへのマッピングをユーザーが実装する必要がある
	//If you want to implement changes to all modes in a clone from a single instance, 
	//you need to implement the mapping from int* type to Mode instance
*/ 
class modeChangeCommand : public Command {
public:
	modeChangeCommand(const datatype::Time& t, core::mode::Mode *mode, core::manager::ModeManagerBase *modeman)
		: Command(t, "modeChangeCommand"), mode_(mode), modeman_(modeman) {}
	~modeChangeCommand(){}
	virtual void execute();
	virtual Command* clone(const datatype::Time& t);
	virtual void init(int* params, int paramsize){}
private:
    core::mode::Mode *mode_;
	core::manager::ModeManagerBase *modeman_;
};

} /* End of namespace stf::core::command */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_command_modeChangeCommand_h
