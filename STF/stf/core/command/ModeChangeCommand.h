/**
 * @file   ModeChangeCommand.h
 * @brief  ���[�h�ύX���s���R�}���h�D
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_command_modeChangeCommand_h
#define stf_core_command_modeChangeCommand_h

#include "Command.h"

namespace stf {
namespace core {
namespace mode {
class ModeBase;
}
namespace manager {
class ModeManagerBase;
}
namespace command {

//! ���[�h�ύX���s���R�}���h
/*! 
	�f�t�H���g�ł�init�ɂ��ύX��R�}���h�̍Đݒ�͍s���Ȃ��D
	���[�h�ύX�R�}���h�̃C���X�^���X�́C�ʏ�A�v���P�[�V�����Œ�`����郂�[�h�̐��������������K�v������D
	�P��̃C���X�^���X�����clone�őS�Ẵ��[�h�ւ̕ύX����������̂ł���΁Cint*�^����Mode�C���X�^���X�ւ̃}�b�s���O�����[�U�[����������K�v������
*/ 
class modeChangeCommand : public Command {
public:
	modeChangeCommand(const datatype::Time& t, core::mode::ModeBase *mode, core::manager::ModeManagerBase *modeman)
		: Command(t,"modeChangeCommand"), mode_(mode), modeman_(modeman) {}
	~modeChangeCommand(){}
	virtual void execute();
	virtual Command* clone(const datatype::Time& t);
	virtual void init(int* params, int paramsize){}
private:
    core::mode::ModeBase *mode_;
	core::manager::ModeManagerBase *modeman_;
};

} /* End of namespace stf::core::command */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_command_modeChangeCommand_h
