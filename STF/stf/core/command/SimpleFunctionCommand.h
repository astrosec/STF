/**
 * @file   SimpleFunctionCommand.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_command_SimpleFunctionCommand_h
#define stf_core_command_SimpleFunctionCommand_h

#include "Command.h"
#include "../functor/Functor.h"
#include "../devicedriver/cmhandler/ICommandReceiver.h"

namespace stf {
namespace core {
namespace command {

// �����Ȃ��t�@���N�^���N������
class SimpleFunctorCommand : public Command {
public:
	SimpleFunctorCommand(const datatype::Time& t, functor::IFunctor* func)
		: func_(func), Command(t,"SimpleFunctionCommand") {}
	~SimpleFunctorCommand(){}
	virtual void init(int* params, int paramsize){}
	virtual Command* clone(const datatype::Time& t){
		return new SimpleFunctorCommand(t,func_);
	}
	virtual void execute(){
		(*func_)();//trigger functor
	}
private:
	functor::IFunctor* func_;
};

// �����Ȃ��C�߂�l�^U�̃����o�֐����Ăяo���C�ԓ����R�}���h�p�P�b�g�ɑ��o����
template<class T, class U>
class SimpleMemberFunctionCommand : public Command {
	typedef U (T::*Func)(void);
public:
	SimpleMemberFunctionCommand(const datatype::Time& t, T* obj, Func f) : Command(t,"SimpleMemberFuncCommand"), obj_(obj), f_(f) {}
	~SimpleMemberFunctionCommand(){}
	virtual void init(int* params, int paramsize){}
	virtual Command* clone(const datatype::Time& t){
		return new SimpleMemberFunctionCommand<T,U>(t,obj_,f_);
	}
	virtual void execute(){
		U response = (*obj_.*f_)();//trigger functor
		this->rcv_->sendPacket(U);
	}
private:
	T* obj_;
	Func f_;
};

template<class T>
class SimpleMemberFunctionCommand<T,void> : public Command {
	typedef void (T::*Func)(void);
public:
	SimpleMemberFunctionCommand(const datatype::Time& t, T* obj, Func f) : Command(t,"SimpleMemberFuncCommand(void)"), obj_(obj), f_(f) {}
	~SimpleMemberFunctionCommand(){}
	virtual void init(int* params, int paramsize){}
	virtual Command* clone(const datatype::Time& t){
		return new SimpleMemberFunctionCommand<T,void>(t,obj_,f_);
	}
	virtual void execute(){
		(*obj_.*f_)();//trigger functor
	}
private:
	T* obj_;
	Func f_;
};



} /* End of namespace stf::core::command */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_command_SimpleFunctionCommand_h
