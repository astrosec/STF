/**
 * @file   NJMC.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_devicedriver_NJMC_NJMC_h
#define stf_core_devicedriver_NJMC_NJMC_h

#include "../../../core/devicedriver/MTQ/MTQBase.h"
#include "../../../interface/Iterator.h"

namespace stf {
namespace core {
namespace devicedriver {
namespace mtq {

template<class T>
class NJMC : public MTQBase<T> {
public:
	~NJMC(){}
	//1Nm出力，線形性誤差5％
	NJMC( const datatype::DCM &angle) : MTQBase( angle, 1, -1, 5){}
	virtual void do_update(){}
private:
	NJMC(){}
};


} /* End of namespace stf::core::devicedriver::mtq */
} /* End of namespace stf::core::devicedriver */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_NJMC_NJMC_h
