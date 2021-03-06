/**
 * @file   SingleAxisPID.h
 * @brief  Scalarを目標値に近づける単純な1次元PID制御ブロック．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_strategy_control_SingleAxisPID_h
#define stf_core_strategy_control_SingleAxisPID_h
#include "../../../util/stfassert.h"
#include "IControlStrategy.h"
#include "../../devicedriver/IOPort.h"
#include "../StrategyBase.h"
#include "../../../datatype/Scalar.h"

namespace stf {
namespace core {
namespace strategy {
namespace control {

//! Scalarを目標値に近づける単純な1次元PID制御ブロック．
/*! 
	入力:スカラー
	出力:スカラー
*/
class SingleAxisPID : public devicedriver::InputPorts< TYPELIST_1(datatype::Scalar) >, 
	public devicedriver::OutputPorts < TYPELIST_1(datatype::Scalar) > ,
		public StrategyBase
{
public:
    SingleAxisPID( double kp, double ki, double kd, double dt, const datatype::Scalar &target);
	SingleAxisPID( double kp, double ki, double kd, double dt, const datatype::Scalar &target, 
		devicedriver::OutputPort<datatype::Scalar>* source, 
		devicedriver::InputPort<datatype::Scalar>* out);
	~SingleAxisPID(){}
	virtual void do_compute(const datatype::Time& t);
protected:
    datatype::Scalar compute_torque_(const datatype::Scalar &x);
    double kp_;
    double ki_;
    double kd_;
	double dt_;
    //! 目標quaternion.
    datatype::Scalar target_;
    //! 1ステップ前のオイラー角誤差(微分制御に使用)
    datatype::Scalar x_old_;
    //! 姿勢角の誤差積分値（積分制御に使用）．
    datatype::Scalar dx_total_;
};



} /* End of namespace stf::core::mode::strategy::control */
} /* End of namespace stf::core::mode::strategy */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_mode_storategy_control_SingleAxisPID_h
