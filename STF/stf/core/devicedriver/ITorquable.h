#ifndef interface_ITorquable_h
#define interface_ITorquable_h

#include "../../datatype/Vector.h"
#include "../../datatype/StaticVector.h"

namespace stf {
namespace core {
namespace devicedriver {

class ITorquable {
public:
	///
    //virtual double getTorque() const  = 0;
	///�@�V�����g���N�̎w�ߒl���Z�b�g���܂��D�f�o�C�X�ւ̑��M��doUpdate�ɂ���Ď��s����܂�
    virtual void setTorque(double value)  = 0;

	///
    //virtual datatype::Vector getTorqueInBodyFrame() const  = 0;
    virtual ~ITorquable() { }
};

} /* End of namespace stf::core::component */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // interface_ITorquable_h
