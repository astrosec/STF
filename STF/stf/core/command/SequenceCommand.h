/**
 * @file   SequenceCommand.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_command_SequenceCommand_h
#define stf_core_command_SequenceCommand_h
#include <assert.h>
#include "Command.h"
#include "../../datatype/Time.h"

namespace stf {
namespace core {
namespace command {

template<int Num>
class SequenceCommand : public Command {
public:
	SequenceCommand(const datatype::Time& t)
		: Command(t,"SequenceCommand"), index_(-1){
			for(int i = 0; i < Num; i++) commands_[i] = 0;
	}
	~SequenceCommand(){
		if(index_ != -1){
			for(int i = 0; i <= index_; i++)
				delete commands_[i];
		}
	}
	virtual bool canExecute(const datatype::Time& t){
		if(index_ == -1) return false; //�R�}���h��1���Ȃ�
		if(this->time_ > t) return false; //�܂��J�n�����ł͂Ȃ�
		for(int i = 0; i < index_; i++){
			if(!commands_[i]->canExecute(t)) return false; //���ׂẴR�}���h�����s�\�ɂȂ�܂Ŏ��s���Ȃ�
		}
		return true;
	}
	void addCommand(Command* command){
		index_++;
		assert(index_ < Num);
		commands_[index_] = command;
	}
	virtual void execute(){
		for(int i = 0; i < index_; i++){
			commands_[i]->execute();//���ԂɎ��s
		}
	}
private:
    SequenceCommand(const SequenceCommand &rhs);
    SequenceCommand &operator=(const SequenceCommand &rhs);
	Command* commands_[Num];
	int index_;
};

} /* End of namespace stf::core::command */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_command_SequenceCommand_h
