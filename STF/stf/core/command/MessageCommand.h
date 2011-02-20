/**
 * @file   MessageCommand.h
 * @brief  �\�ߌ��߂�ꂽ���b�Z�[�W���o�͂���R�}���h�D
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_command_UnaryFunctorCommand_h
#define stf_core_command_UnaryFunctorCommand_h

#include "Command.h"
#include "../functor/Functor.h"
#include "../../datatype/String.h"

namespace stf {
namespace core {
namespace command {

//! �\�ߌ��߂�ꂽ���b�Z�[�W���o�͂���R�}���h�D
/*! �R���X�g���N�^�Ŏw�肵�����b�Z�[�W�����̂܂ܕԓ�����D�����m�F��C
	@tparam Num ���s����R�}���h�̐��D
*/
class MessageCommand : public Command {
public:
	 MessageCommand(const datatype::Time& t, const datatype::String& msg)
		: msg_(msg), Command(t,"UnaryFunctorCommand") {}
	~ MessageCommand(){}
	virtual void init(int* params, int paramsize){}
	virtual Command* clone(const datatype::Time& t){
		return new MessageCommand(t,msg_);
	}
	virtual void execute(){
		this->rcv_->send_packet(msg_);
	}
private:
	datatype::String msg_;
};


} /* End of namespace stf::core::command */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_command_UnaryFunctorCommand_h
