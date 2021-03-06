/**
 * @file   PRISMTAM.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_devicedriver_magnetometer_PRISMTAM_h
#define stf_core_devicedriver_magnetometer_PRISMTAM_h

#include "../../../core/devicedriver/magnetometer/TAMBase.h"

namespace stf {
namespace core {
namespace devicedriver {
namespace magnetometer {
template <class T>
class PRISMTAM : public TAMBase<T>{
public:  
	// 3-Sigmaで1度精度 3-degree accuracy with Sigma
	PRISMTAM( const datatype::DCM &angle) : TAMBase(angle){}
	~PRISMTAM(){}
	virtual void do_update(){}
private:
	PRISMTAM(){}
};

} /* End of namespace stf::core::devicedriver::magnetometer */
} /* End of namespace stf::core::devicedriver */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_magnetometer_PRISMTAM_h
