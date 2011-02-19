#ifndef stf_core_strategy_control_WheelUnloading_h
#define stf_core_strategy_control_WheelUnloading_h

#include "../StrategyBase.h"
#include "../../devicedriver/IOPort.h"
#include "../../devicedriver/rw/RWBase.h"

#include "../../../datatype/StaticVector.h"
#include "../../../datatype/List.h"
#include "../../../datatype/OrbitInfo.h"

namespace stf {
namespace core {
namespace strategy {
namespace control {


//RW�̃A�����[�f�B���O��MTQ���g�p���čs�����߂̐���u���b�N�D
//�o�͉\�ȃg���N�������v�Z���邽�߂ɋO������K�v�Ƃ���ق��C
//�|�[�g�Ƃ͕ʂɊp�^���ʂ��Q�Ƃ��邽�߂ɑΏۃz�C�[���𒼐ڐڑ�����K�v������D
//����:�O�����|�[�g
//�o��:RW�o�̓g���N�CMTQ�o�̓g���N
class WheelUnloading
	: virtual public StrategyBase, 
	public devicedriver::InputPorts< TYPELIST_1( datatype::PositionInfo ) >,
	public devicedriver::OutputPorts< TYPELIST_2( datatype::StaticVector<3>, datatype::StaticVector<3> ) >
{
public:
	WheelUnloading(int instance_id) : StrategyBase(instance_id, "WheelUnloading"){}
	WheelUnloading(int instance_id, 
		devicedriver::OutputPort<datatype::PositionInfo>* position_source,
		devicedriver::InputPort<datatype::StaticVector<3>>* torquer_out = 0,
		devicedriver::InputPort<datatype::StaticVector<3>>* wheel_out = 0
		);
	~WheelUnloading(){}
	void add_wheel(core::devicedriver::rw::RWBase<ENV>* wheel) { this->unloading_wheels_.add(*wheel); }
	virtual void do_compute(const datatype::Time& t);
protected:
	datatype::List< core::devicedriver::rw::RWBase<ENV> > unloading_wheels_;

};


} /* End of namespace stf::core::strategy::control */
} /* End of namespace stf::core::strategy */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_strategy_control_input_WheelUnloading_h
