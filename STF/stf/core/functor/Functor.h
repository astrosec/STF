/**
 * @file   Functor.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_functor_Functor_h
#define stf_core_functor_Functor_h
#include "../../util/Ostream.h"
#include "../../RootObject.h"
#include "../../datatype/String.h"
#include "../datapool/Datapool.h"
#include "../../GlobalObject.h"
#include "InputFunctor.h"
#include "OutputFunctor.h"


namespace stf {
namespace core {
namespace mode {
class ModeBase;
}
namespace functor {

class IFunctor {
public:
	virtual void operator()() const = 0;
};

template<class T>
class IUnAryFunctor {
public:
	virtual int operator()(const T& arg) const = 0; 
};

template <class InputFunctor,class OutputFunctor>
class Functor : virtual public IFunctor{
public:
	Functor(const InputFunctor* in,const OutputFunctor* out) : in_(in), out_(out) {}
	virtual void operator()() const {
		if((*in_)()){//�����Ȃ��Cbool�ltrue���A���Ă�����
			(*out_)();//�w��̓�������{
		}
	}
private:
	const InputFunctor* in_;
	const OutputFunctor* out_;
};

template <class InputFunctor,class OutputFunctor,class Arg>
class UnAryFunctor : public IFunctor{
public:
	UnAryFunctor(const InputFunctor* in,const OutputFunctor* out,const Arg& arg) : in_(in), out_(out), arg_(arg) {}
	virtual int operator()() const {
		if((*in_)()){//�����Ȃ��Cbool�ltrue���A���Ă�����
			return (*out_)(arg_);//�w��̓�������{
		}
		return 0;
	}
private:
	const InputFunctor* in_;
	const OutputFunctor* out_;
	const Arg& arg_;
};



} /* End of namespace stf::core::fuctor */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_functor_Functor_h
