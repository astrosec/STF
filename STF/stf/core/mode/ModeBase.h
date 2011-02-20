/**
 * @file   ModeBase.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_mode_ModeBase_h
#define stf_core_mode_ModeBase_h

#include "../../RootObject.h"
#include "../../datatype/String.h"
#include "ModeHotSpot.h"

namespace stf {
namespace core {
namespace mode {

class ModeBase : public RootObject , virtual public StrategyHolder{
public:
	ModeBase(int instance_id, const datatype::String& name) : RootObject(instance_id, name){};
	virtual const datatype::String& name() const { return this->name_; }
	~ModeBase(){}
private:
	ModeBase() : RootObject(0,"err!/ModeBase"){}
};

} /* End of namespace stf::core::mode */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_mode_ModeBase_h
