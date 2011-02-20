/**
 * @file   SwitchCommand.h
 * @brief  �@��̃X�C�b�`���O���s���R�}���h�D
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_command_SwitchCommand_h
#define stf_core_command_SwitchCommand_h

#include "Command.h"
#include "../devicedriver/ISwitchable.h"

namespace stf {
namespace core {
namespace command {

//! �@��̃X�C�b�`���O���s���R�}���h�D
/*! 
	ISwitchable�C���^�[�t�F�[�X���������I�u�W�F�N�g�ɑ΂��āCon�܂���off�����s�D
 */
class SwitchCommand : public Command {
public:
	SwitchCommand(const datatype::Time& t, devicedriver::ISwitchable* sw, bool on)
		: Command(t,"SwitchCommand"), sw_(sw), on_(on) {}
	~SwitchCommand(){}
	virtual void execute(){
		if(on_) this->sw_->on();
		else    this->sw_->off();
	}
private:
    SwitchCommand(const SwitchCommand &rhs);
    SwitchCommand &operator=(const SwitchCommand &rhs);
	devicedriver::ISwitchable* sw_;
	bool on_;
};

} /* End of namespace stf::core::command */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_command_SwitchCommand_h
