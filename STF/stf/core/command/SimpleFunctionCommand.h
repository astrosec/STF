/**
 * @file   SimpleFunctionCommand.h
 * @brief  引数なしのファンクタやメンバ関数を起動するコマンド．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_command_SimpleFunctionCommand_h
#define stf_core_command_SimpleFunctionCommand_h

#include "Command.h"
#include "../functor/Functor.h"
#include "../devicedriver/cmhandler/ICommandReceiver.h"
#include "../../util/Trace.h"

namespace stf {
namespace core {
namespace command {

//! 引数なしファンクタを起動するコマンド．
/*! 
*/
class SimpleFunctorCommand : public Command {
public:
	SimpleFunctorCommand(const datatype::Time& t, functor::IFunctor* func)
		: func_(func), Command(t, "SimpleFunctionCommand") {}
	~SimpleFunctorCommand(){}
	virtual void init(int* params, int paramsize){}
	virtual Command* clone(const datatype::Time& t){
		return new SimpleFunctorCommand(t, func_);
	}
	virtual void execute(){
		util::Trace trace(util::Trace::kCommand, name_);
		(*func_)();
	}
private:
	functor::IFunctor* func_;
};

//! 引数なし，戻り値型Uのメンバ関数を呼び出し，返答をコマンドパケットに送出する
/*! 
	@tparam T メンバ関数を保持するクラス．
	@tparam U メンバ関数の戻り値型．
*/ 
template<class T, class U>
class SimpleMemberFunctionCommand : public Command {
	typedef U (T::*Func)(void);
public:
	SimpleMemberFunctionCommand(const datatype::Time& t, T* obj, Func f) : Command(t, "SimpleMemberFuncCommand"), obj_(obj), f_(f) {}
	~SimpleMemberFunctionCommand(){}
	virtual void init(int* params, int paramsize){}
	virtual Command* clone(const datatype::Time& t){
		return new SimpleMemberFunctionCommand<T, U>(t, obj_, f_);
	}
	virtual void execute(){
		util::Trace trace(util::Trace::kCommand, name_);
		U response = (*obj_.*f_)();
		this->rcv_->send_packet(U);
	}
private:
	T* obj_;
	Func f_;
};

//! 引数なし，戻り値voidのメンバ関数を呼び出す
/*! 
	@tparam T メンバ関数を保持するクラス．
*/ 
template<class T>
class SimpleMemberFunctionCommand<T, void> : public Command {
	typedef void (T::*Func)(void);
public:
	SimpleMemberFunctionCommand(const datatype::Time& t, T* obj, Func f) : Command(t, "SimpleMemberFuncCommand(void)"), obj_(obj), f_(f) {}
	~SimpleMemberFunctionCommand(){}
	virtual void init(int* params, int paramsize){}
	virtual Command* clone(const datatype::Time& t){
		return new SimpleMemberFunctionCommand<T, void>(t, obj_, f_);
	}
	virtual void execute(){
		(*obj_.*f_)();
	}
private:
	T* obj_;
	Func f_;
};



} /* End of namespace stf::core::command */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_command_SimpleFunctionCommand_h
