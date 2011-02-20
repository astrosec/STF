/**
 * @file   DummyCommandReceiver.h
 * @brief  �R�}���h���V�[�o�̃f�o�b�O�p�N���X�D�O���e�L�X�g�t�@�C������R�}���h��ǂݍ���
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_devicedriver_cmhandler_DummyCommandReceiver_h
#define stf_core_devicedriver_cmhandler_DummyCommandReceiver_h

#include <fstream>
#include <string>
#include "ICommandReceiver.h"
#include "../../../RootObject.h"
#include "../../../datatype/List.h"

namespace stf {
namespace core {
namespace manager {
class CommandManagerBase;
}
namespace command {
class Command;
}
namespace devicedriver {
namespace cmhandler {

//! �R�}���h���V�[�o�̃f�o�b�O�p�N���X�D�O���e�L�X�g�t�@�C������R�}���h��ǂݍ���
/*! 
	�������K�v�ȃR�}���h�ɂ��Ă͕W���o�͂Ƀ��b�Z�[�W�Ƃ��ēf���o��.
	�O���t�@�C������ǂݍ��܂ꂽ�R�}���h��last_command�ɕ�����Ƃ��Ċi�[����邾���Ȃ̂ŁC
	��������R�}���h�I�u�W�F�N�g�ɕR�Â����Ƃ͂�����p�������A�v���P�[�V�����ŗL�̃f�o�b�O�R�}���h�N���X�ōs��
*/
class DummyCommandReceiver: virtual public ICommandReceiver, public RootObject {
public:
	DummyCommandReceiver(int instance_id, core::manager::CommandManagerBase* manager, const std::string &filename = "");
    ~DummyCommandReceiver() { }
    virtual void receive_command();
	virtual void send_packet(const datatype::String& msg);
	virtual void send_packet(int msg);
	virtual void add_command(command::Command*);
protected:
	core::manager::CommandManagerBase* manager_;
	std::ifstream* ifs_;
	std::string last_command_;
};


} /* End of namespace stf::core::devicedriver::cmhandler */
} /* End of namespace stf::core::devicedriver */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_cmhandler_ICommandReceiver_h
