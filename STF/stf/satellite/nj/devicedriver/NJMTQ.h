/**
 * @file   NJMTQ.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_devicedriver_NJMTQ_NJMTQ_h
#define stf_core_devicedriver_NJMTQ_NJMTQ_h

#include "../../../core/devicedriver/mtq/MTQBase.h"
#include "../../../interface/Iterator.h"

namespace stf {
namespace core {
namespace devicedriver {
namespace mtq {

template<class T>
class NJMTQ : public MTQBase<T> {
public:
	~NJMTQ(){}
	//1Nm出力，線形性誤差5％
	NJMTQ( const datatype::DCM &angle) : MTQBase( angle, 1, -1, 5){}
	virtual void do_update(){}
private:
	NJMTQ(){}
};


} /* End of namespace stf::core::devicedriver::mtq */
} /* End of namespace stf::core::devicedriver */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_NJMTQ_NJMTQ_h
