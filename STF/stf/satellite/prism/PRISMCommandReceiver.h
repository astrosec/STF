#ifndef stf_core_devicedriver_cmhandler_PRISMCommandReceiver_h
#define stf_core_devicedriver_cmhandler_PRISMCommandReceiver_h

#include <fstream>
#include <cstdio>
#include <cstring>
#include "../../datatype/String.h"
#include "../../core/devicedriver/cmhandler/ICommandReceiver.h"
#include "../../RootObject.h"
#include "../../environment/Simulator.h"
#include "../../core/command/Command.h"
#include "../../core/manager/CommandManager.h"

namespace stf {
template<class T> struct PRISMGlobal;
namespace core {
namespace devicedriver {
namespace cmhandler {


template<class T>
core::command::Command* __prism_powercmd_analyze(char* cmd, int* params, int paramlength, const datatype::Time& t, const stf::PRISMGlobal<T>* g);
template<class T>
core::command::Command* __prism_cdhcmd_analyze(char* cmd, int* params, int paramlength, const datatype::Time& t, const stf::PRISMGlobal<T>* g);
template<class T>
core::command::Command* __prism_adcscmd_analyze(char* cmd, int* params, int paramlength, const datatype::Time& t, const stf::PRISMGlobal<T>* g);

template<>
core::command::Command* __prism_powercmd_analyze<environment::Simulator>(char* cmd, int* params, int paramlength, const datatype::Time& t, const PRISMGlobal<environment::Simulator>*);
template<>
core::command::Command* __prism_cdhcmd_analyze<environment::Simulator>(char* cmd, int* params, int paramlength, const datatype::Time& t, const PRISMGlobal<environment::Simulator>*);
template<>
core::command::Command* __prism_adcscmd_analyze<environment::Simulator>(char* cmd, int* params, int paramlength, const datatype::Time& t, const PRISMGlobal<environment::Simulator>*);


//
// �ʐM�nCPU�Ƃ̃C���^�[�t�F�[�X�𐬂��R�}���h���V�[�o�̃f�o�b�O�p��ۃN���X�D
//  �v���^�̃R�}���h�i�ʐM�n����̗v�������ƂɁC�K�؂Ȓl��Ԃ��j�ɑ΂��Ă�
template<class T>
class PRISMCommandReceiver: virtual public ICommandReceiver, public RootObject {
public:
    virtual void receiveCmd();
	virtual void sendPacket(const datatype::String& msg);
	virtual void sendPacket(int msg);
	virtual void addCmd(command::Command*);
	PRISMCommandReceiver(int instance_id, core::manager::CommandManagerBase* manager, const datatype::String& filename,PRISMGlobal<T>* global)
		: RootObject(instance_id,"PRISMReceiver"), manager_(manager), global_(global){
			this->ifs_ = new typename T::InputStream(filename.toChar());
	}
    ~PRISMCommandReceiver() { }
private:
	void analyzeCommand_(char* cmd);
	core::manager::CommandManagerBase* manager_;
	PRISMGlobal<T>* global_;
	typename T::InputStream* ifs_;
};

//�O���f�o�C�X����R�}���h�̎�M���s���D
template<class T>
void PRISMCommandReceiver<T>::receiveCmd()
{
}

//�f�o�b�O�p�̓��ꉻ�D�O���t�@�C������1�s���ǂݍ��݁C
template<> void PRISMCommandReceiver<environment::Simulator>::receiveCmd();


// �f�o�b�O�p�Ȃ̂ő��M�@�ɑ���ς��ɃR���\�[���ɏo�͂���
template<class T>
void PRISMCommandReceiver<T>::sendPacket(const datatype::String& msg)
{
	util::cout << "downlink:" << msg << "at:" << this->clock_->getTime() << util::endl;
}

// �f�o�b�O�p�Ȃ̂ő��M�@�ɑ���ς��ɃR���\�[���ɏo�͂���
template<class T>
void PRISMCommandReceiver<T>::sendPacket(int msg)
{
	util::cout << "downlink:" << msg << "at:" << this->clock_->getTime() << util::endl;
}
template<class T>
void PRISMCommandReceiver<T>::addCmd(command::Command* cmd)
{
	this->manager_->addCommand(cmd);
	cmd->connectReceiver(this);
}


//�R�}���h�����߂��āC�Ή�����I�u�W�F�N�g�𓊂���
template<class T>
void PRISMCommandReceiver<T>::analyzeCommand_(char* cmd)
{
	char subsystem;
	char* cmd;
	char* params;
	int paramlength;
	//�R�}���h���ߕ�

	//
	const datatype::Time t = this->clock_->getTime();
	switch(subsystem)
	{
	case 'p':
		this->addCmd(__prism_powercmd_analyze(cmd, params, paramlength,t,this->global_));
		break;

	case 'c':
		this->addCmd(__prism_cdhcmd_analyze(cmd, params, paramlength,t,this->global_));
		break;
	case 'a':
		this->addCmd(__prism_adcscmd_analyze(cmd, params, paramlength,t,this->global_));
		break;
	default:
		util::cout << "command parse error" << util::endl;
		break;
	}

}


} /* End of namespace stf::core::devicedriver::cmhandler */
} /* End of namespace stf::core::devicedriver */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_cmhandler_ICommandReceiver_h
