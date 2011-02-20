/**
 * @file   CommandManagerBase.cpp
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#include "CommandManagerBase.h"
#include "../../util/Ostream.h"
#include "../../datatype/Time.h"
#include "../command/Command.h"
#include "../devicedriver/clock/ITimeClock.h"

namespace stf {
namespace core {
namespace manager {

void CommandManagerBase::run(){
	execute_command_(this->clock_->get_time());
}

void CommandManagerBase::execute_command_(const datatype::Time& t){
	//�����̓����O�o�b�t�@�����C�������₷���̂ŃR�}���h�̊m�F�����͔z��̌�납��
	//���s�����ɐ���̂���R�}���h�̓g�����U�N�V�����Ƃ��Ď�������̂Ŗ��͖����͂�
	for(int i = NUM_OF_LIST - 1 ; i >= 0 ; i--){
		if(this->commandList_[i] == 0) continue;
		if(this->commandList_[i]->can_execute(t)){
			this->commandList_[i]->execute();
			remove_command_(i);
		}
	}
}

void CommandManagerBase::remove_command_(int index){
	delete this->commandList_[index];
	for(int i = index; i < NUM_OF_LIST - 1 ; i++){
		this->commandList_[i] = this->commandList_[i + 1];
	}
	this->commandList_[NUM_OF_LIST] = 0;
}

void CommandManagerBase::notify(const mode::ModeBase* value){
	util::cout <<  "strategychange:" << util::endl;
}

} /* End of namespace stf::core::manager */
} /* End of namespace stf::core */
} /* End of namespace stf */
