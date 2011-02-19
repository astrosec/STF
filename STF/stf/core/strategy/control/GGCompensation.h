/**
 * @file   GGCompensation.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_strategy_control_GGCompensation_h
#define stf_core_strategy_control_GGCompensation_h

#include "../StrategyBase.h"
#include "../../../datatype/StaticVector.h"
#include "../../../datatype/Quaternion.h"
#include "../../../datatype/OrbitInfo.h"
#include "../../devicedriver/IOPort.h"

namespace stf {
namespace datatype {
class Time;
}
namespace core {
namespace strategy {
namespace control {


//�d�͌X�΃g���N���v�Z���C�t�����̃g���N���o�͂���GG�⏞����u���b�N�D
class GGCompensation
	: virtual public StrategyBase, 
	public devicedriver::InputPorts< TYPELIST_2( datatype::Quaternion, datatype::PositionInfo ) >,
	public devicedriver::OutputPorts< TYPELIST_1( datatype::StaticVector<3> ) >
{
public:
	GGCompensation(int instance_id) : StrategyBase(instance_id, "GGCompensation"){}
	GGCompensation(int instance_id, 
		devicedriver::OutputPort<datatype::Quaternion>* q_source,
		devicedriver::OutputPort<datatype::PositionInfo>* position_source,
		devicedriver::InputPort<datatype::StaticVector<3>>* torque_out = 0
		);
	~GGCompensation(){}
	virtual void do_compute(const datatype::Time& t);
protected:
};



} /* End of namespace stf::core::strategy::control */
} /* End of namespace stf::core::strategy */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_strategy_control_input_GGCompensation_h
