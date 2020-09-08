/**
 * @file   SequenceCommand.h
 * @brief  複数コマンドをシーケンシャルに実行するコマンド．
 * A command that executes multiple commands sequentially
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_command_SequenceCommand_h
#define stf_core_command_SequenceCommand_h
#include "../../util/stfassert.h"
#include "Command.h"
#include "../../datatype/Time.h"
#include "../../util/Trace.h"

namespace stf {
namespace core {
namespace command {

//! 複数個のコマンドをシーケンシャルに実行するコマンド．
	//A command that executes multiple commands sequentially
/*! 引数がintの場合，init関数で引数の再設定が可能．
//If the argument is int, it can be reset by the init function
	@tparam Num 実行するコマンドの数．Number of commands to execute
*/
template<int Num>
class SequenceCommand : public Command {
public:
	SequenceCommand(const datatype::Time& t)
		: Command(t, "SequenceCommand"), index_(-1){
			for(int i = 0; i < Num; i++) commands_[i] = 0;
	}
	~SequenceCommand(){
		if(index_ != -1){
			for(int i = 0; i <= index_; i++)
				delete commands_[i];
		}
	}
	virtual bool can_execute(const datatype::Time& t){
		if(index_ == -1) return false; //コマンドが1つもない No command
		if(this->time_ > t) return false; //まだ開始時刻ではない  Not yet the start time
		for(int i = 0; i < index_; i++){
			if(!commands_[i]->can_execute(t)) return false; //すべてのコマンドが実行可能になるまで実行しない
			//Do not run until all commands are ready
		}
		return true;
	}
	void add_command(Command* command){
		index_++;
		stf_assert(index_ < Num);
		commands_[index_] = command;
	}
	virtual void execute(){
		stf_assert(index_ >= 0);
		util::Trace trace(util::Trace::kCommand, name_);
		for(int i = 0; i < index_; i++){
			commands_[i]->execute();//順番に実行 Run sequentially
		}
	}
private:
	Command* commands_[Num];
	int index_;
};

} /* End of namespace stf::core::command */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_command_SequenceCommand_h
