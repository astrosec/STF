#ifndef stf_core_devicedriver_PRISMMTQ_PRISMMTQ_h
#define stf_core_devicedriver_PRISMMTQ_PRISMMTQ_h

#include "../../core/devicedriver/mtq/MTQBase.h"
#include "../../interface/Iterator.h"

namespace stf {
namespace core {
namespace devicedriver {
namespace mtq {

template<class T>
class PRISMMTQ : public MTQBase<T> {
public:
	~PRISMMTQ(){}
	//1Nm�o�́C���`���덷5��
	PRISMMTQ(int instance_id, const datatype::DCM &angle) : MTQBase(instance_id, angle, 1, -1, 5){}
	virtual void doUpdate(){}
private:
	PRISMMTQ(){}
};


} /* End of namespace stf::core::devicedriver::mtq */
} /* End of namespace stf::core::devicedriver */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_PRISMMTQ_PRISMMTQ_h
