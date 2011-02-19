#ifndef stf_core_strategy_control_Bdot_h
#define stf_core_strategy_control_Bdot_h

#include "../StrategyBase.h"
#include "../../../datatype/Magnetic.h"
#include "../../devicedriver/IOPort.h"

namespace stf {
namespace datatype {
class Time;
}
namespace core {
namespace strategy {
namespace control {

///B-Dot�����v�Z���鐧��u���b�N�D
//����:�q�����W�n�ł�3������D
//�o��:3���o�͎��C���[�����g�D
//�p�����[�^:
//    k:�Q�C���D
class Bdot
	: virtual public StrategyBase, 
	public devicedriver::InputPorts< TYPELIST_1( datatype::MagneticField ) >,
	public devicedriver::OutputPorts< TYPELIST_1( datatype::MagneticMoment ) >
{
public:
	Bdot(int instance_id,double k) : StrategyBase(instance_id, "Bdot"), k_(k) {}
	Bdot(int instance_id,double k, 
		devicedriver::OutputPort<datatype::MagneticField>* mag_source,
		devicedriver::InputPort<datatype::MagneticMoment>* torque_out = 0
		);
	~Bdot(){}
	virtual void do_compute(const datatype::Time& t);
protected:
	double k_;//gain of B-dot, including time
	datatype::MagneticField mag_before_;
};


} /* End of namespace stf::core::strategy::control */
} /* End of namespace stf::core::strategy */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_strategy_control_input_Bdot_h
