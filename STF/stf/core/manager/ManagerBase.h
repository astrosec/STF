/**
 * @file   ManagerBase.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_manager_ManagerBase_h
#define stf_core_manager_ManagerBase_h

#include "../../RootObject.h"

namespace stf {
namespace core {

namespace mode {
class ModeBase;
} /* End of namespace core::mode */

namespace manager {

class ManagerBase : public RootObject {
public:
	ManagerBase(int instance_id, const datatype::String& name) : mode_(0), RootObject(instance_id, name) {}
	virtual ~ManagerBase(){}
    virtual void run() = 0;
	virtual bool runnable() const { return true; }
protected:
    const core::mode::ModeBase *mode_;
	DISALLOW_COPY_AND_ASSIGN(ManagerBase);
};
} /* End of namespace stf::core::manager */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_manager_ManagerBase_h