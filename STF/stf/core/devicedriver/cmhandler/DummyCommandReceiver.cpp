#include "DummyCommandReceiver.h"
#include "../../command/Command.h"
#include "../../manager/CommandManagerBase.h"
#include "../../../datatype/String.h"
#include "../../../util/Ostream.h"
#include "../../devicedriver/clock/ITimeClock.h"

namespace stf {
namespace core {
namespace devicedriver {
namespace cmhandler {

// �f�o�b�O�p�Ȃ̂ŃR���\�[������̓��͖͂����ƍl����
void DummyCommandReceiver::receiveCmd()
{

}

// �f�o�b�O�p�Ȃ̂ő��M�@�ɑ���ς��ɃR���\�[���ɏo�͂���
void DummyCommandReceiver::sendPacket(const datatype::String& msg)
{
	util::cout << "downlink:" << msg << "at:" << this->clock_->getTime() << util::endl;
}

// �f�o�b�O�p�Ȃ̂ő��M�@�ɑ���ς��ɃR���\�[���ɏo�͂���
void DummyCommandReceiver::sendPacket(int msg)
{
	util::cout << "downlink:" << msg << "at:" << this->clock_->getTime() << util::endl;
}

void DummyCommandReceiver::addCmd(command::Command* cmd)
{
	this->manager_->addCommand(cmd);
	cmd->connectReceiver(this);
}

} /* End of namespace stf::core::devicedriver::cmhandler */
} /* End of namespace stf::core::devicedriver */
} /* End of namespace stf::core */
} /* End of namespace stf */

