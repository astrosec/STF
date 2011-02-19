#ifndef stf_core_devicedriver_magnetometer_NJFineTAM_h
#define stf_core_devicedriver_magnetometer_NJFineTAM_h

#include "../../core/devicedriver/magnetometer/TAMBase.h"

namespace stf {
namespace core {
namespace devicedriver {
namespace magnetometer {
template <class T>
class NJFineTAM : public TAMBase<T>{
public:  
	// 3-Sigma��1�x���x
	NJFineTAM(int instance_id, const datatype::DCM &angle) : TAMBase(instance_id,angle){}
	~NJFineTAM(){}
	virtual void doUpdate(){}
private:
	NJFineTAM(){}
};

} /* End of namespace stf::core::devicedriver::magnetometer */
} /* End of namespace stf::core::devicedriver */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_magnetometer_NJFineTAM_h
