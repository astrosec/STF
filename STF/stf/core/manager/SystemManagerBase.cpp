#include "SystemManagerBase.h"
#include "../mode/ModeBase.h"
#include "../datapool/Datapool.h"
#include "../functor/Functor.h"
#include "../../util/Ostream.h"

namespace stf {
namespace core {
namespace manager {

void SystemManagerBase::notify(const mode::ModeBase* value){
	util::cout << "system list change!" << util::endl;
	this->func_ = value->getlist(SpotType());
	//this->func_ = value->getlist(SpotType());
}

void SystemManagerBase::run()
{
	//util::cout << "Telman run:\n";
	if(func_ == 0 || func_->size() == 0){
	//	util::cout << "skip" << util::endl;
		return;
	}

	//�t�@���N�^�ɂ����notify���N�����Cfunc_���g�������������邱�Ƃ�����̂�it.end()�Ƃ͔�r���Ȃ�
	for(int i = 0;i < func_->size(); i++){
		((*func_)[i])();
	}

}


} /* End of namespace stf::core::manager */
} /* End of namespace stf::core */
} /* End of namespace stf */