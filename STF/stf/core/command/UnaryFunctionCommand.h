/**
 * @file   UnaryFunctionCommand.h
 * @brief  �P�����̃t�@���N�^�⃁���o�֐����N������R�}���h�D
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_command_UnaryFunctionCommand_h
#define stf_core_command_UnaryFunctionCommand_h

#include "Command.h"
#include "../functor/Functor.h"

namespace stf {
namespace core {
namespace command {

//! 1�����̃t�@���N�^���N������R�}���h�D
/*! ������int�̏ꍇ�Cinit�֐��ň����̍Đݒ肪�\�D
	@code
	UnaryFunctorCommand<int> command_prototype(t, functor, 0);

	UnaryFunctorCommand<int>* newcommand = command_prototype.clone();
	int[] param = { 1 };
	//������1�ɕύX
	newcommand->init(param, 1);
	@endcode
	@tparam T �t�@���N�^�N�����̈����^�D
*/
template<class T>
class UnaryFunctorCommand : public Command {
public:
	UnaryFunctorCommand(const datatype::Time& t, functor::IUnAryFunctor<T>* func, T arg)
		: func_(func), arg_(arg), Command(t,"UnaryFunctorCommand") {}
	~UnaryFunctorCommand(){}
	virtual void init(int* params, int paramsize){}
	virtual Command* clone(const datatype::Time& t){
		return new UnaryFunctorCommand<T>(t,func_,arg_);
	}
	virtual void execute(){
		(*func_)(arg_);
	}
private:
	functor::IUnAryFunctor<T>* func_;
	T arg_;
};

template<>
void UnaryFunctorCommand<int>::init(int* params, int paramsize);

//! 1�����̃����o�֐����N������R�}���h�D
/*! �߂�l�^U�̃����o�֐����Ăяo���C�ԓ����R�}���h�p�P�b�g�ɑ��o����. 
	@tparam T   �����o�֐���ێ�����N���X�D
	@tparam U   �����o�֐��̖߂�l�^�D
	@tparam ARG �����o�֐��̈����^�D
*/
template<class T, class U, class ARG>
class UnAryMemberFunctionCommand : public Command {
	typedef U (T::*Func)(ARG);
public:
	UnAryMemberFunctionCommand(const datatype::Time& t, T* obj, Func f, ARG arg)
    : Command(t,"UnAryMemberFuncCommand"), obj_(obj), f_(f), arg_(arg) {}
	~UnAryMemberFunctionCommand(){}
	virtual void init(int* params, int paramsize){}
	virtual Command* clone(const datatype::Time& t){
		return new UnAryMemberFunctionCommand<T,U,ARG>(t,obj_,f_,arg_);
	}
	virtual void execute(){
		U response = (*obj_.*f_)(arg_);
		this->rcv_->send_packet(response);
	}
private:
	T* obj_;
	Func f_;
	ARG arg_;
};

//! 1�����̃����o�֐����N������R�}���h�D(void���ꉻ��)
/*! �߂�l�^void�̃����o�֐����Ăяo��. 
	@tparam T   �����o�֐���ێ�����N���X�D
	@tparam ARG �����o�֐��̈����^�D
*/
template<class T, class ARG>
class UnAryMemberFunctionCommand<T,void,ARG> : public Command {
	typedef void (T::*Func)(ARG);
public:
	UnAryMemberFunctionCommand(const datatype::Time& t, T* obj, Func f, ARG arg)
    : Command(t,"UnAryMemberFuncCommand"), obj_(obj), f_(f), arg_(arg) {}
	~UnAryMemberFunctionCommand(){}
	virtual void init(int* params, int paramsize){}
	virtual Command* clone(const datatype::Time& t){
		return new UnAryMemberFunctionCommand<T,void,ARG>(t,obj_,f_,arg_);
	}
	virtual void execute(){
		(*obj_.*f_)(arg_);
	}
private:
	T* obj_;
	Func f_;
	ARG arg_;
};


} /* End of namespace stf::core::command */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_command_UnaryFunctorCommand_h
