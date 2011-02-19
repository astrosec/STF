/**
 * @file   DummyCommandReceiver.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_devicedriver_cmhandler_DummyCommandReceiver_h
#define stf_core_devicedriver_cmhandler_DummyCommandReceiver_h

#include "ICommandReceiver.h"
#include "../../../RootObject.h"

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
//
// �ʐM�nCPU�Ƃ̃C���^�[�t�F�[�X�𐬂��R�}���h���V�[�o�̃f�o�b�O�p��ۃN���X�D
//  �v���^�̃R�}���h�i�ʐM�n����̗v�������ƂɁC�K�؂Ȓl��Ԃ��j�ɑ΂��Ă�
class DummyCommandReceiver: virtual public ICommandReceiver, public RootObject {
public:
    virtual void receiveCmd();
	virtual void sendPacket(const datatype::String& msg);
	virtual void sendPacket(int msg);
	virtual void addCmd(command::Command*);
	DummyCommandReceiver(int instance_id, core::manager::CommandManagerBase* manager)
		: RootObject(instance_id,"DummyReceiver"), manager_(manager){}
    ~DummyCommandReceiver() { }
private:
	core::manager::CommandManagerBase* manager_;
};


} /* End of namespace stf::core::devicedriver::cmhandler */
} /* End of namespace stf::core::devicedriver */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_cmhandler_ICommandReceiver_h
