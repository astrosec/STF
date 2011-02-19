/**
 * @file   EKF.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_strategy_control_EKF_h
#define stf_core_strategy_control_EKF_h

#include "../StrategyBase.h"
#include "../../devicedriver/IOPort.h"

#include "../../../datatype/StaticVector.h"
#include "../../../datatype/Quaternion.h"

#include "../../../datatype/Matrix.h"
#include "../../../datatype/Vector.h"

#include "EKFParamaters.h"

namespace stf {
namespace datatype {
class Time;
}
namespace core {
namespace devicedriver {
template<class T,class U,class Env> class AOCSComponent;
}
namespace strategy {
namespace control {

class EKF : public StrategyBase,
	public devicedriver::InputPorts< TYPELIST_2( datatype::Quaternion, datatype::StaticVector<3> ) >,
	public devicedriver::OutputPorts< TYPELIST_2( datatype::Quaternion, datatype::StaticVector<3> ) >
{
public:
    EKF(int instance_id, const EKFParamaters &params);
	EKF(int instance_id, const EKFParamaters &params, 
		OutputPort<datatype::Quaternion>* q_source, OutputPort<datatype::StaticVector<3>>* omega_source,
		InputPort<datatype::Quaternion>* q_out = 0, InputPort<datatype::StaticVector<3>>* omega_out = 0
		);
    EKF(int instance_id);
	virtual ~EKF(){}
	virtual void init(const EKFParamaters &params);
    virtual void init();
    virtual void update(const datatype::Quaternion &input,const datatype::Time& t);
    virtual void propagate(const datatype::StaticVector<3>& omega,const datatype::Time& t);
	virtual void reset();
	virtual void do_compute(const datatype::Time& t);//�`���C�X�V����
protected:
    EKFParamaters params_;
	datatype::StaticVector<3> omega_;
    datatype::Quaternion q_;
    datatype::Vector bref_;
	//�`���p�x(sec)
	double dt_;
    datatype::Matrix A_;
    datatype::Matrix B_;
    datatype::Matrix G_;
    datatype::Matrix F_;
    datatype::Matrix H_;
    datatype::Matrix P_;
    datatype::Matrix K_;
    datatype::Matrix Q_;
    datatype::Matrix R_;
    datatype::Vector x_;
    datatype::Matrix Ht_;
    datatype::Matrix Omega_;
    double tau_;
};


} /* End of namespace stf::core::strategy::control */
} /* End of namespace stf::core::strategy */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_strategy_control_input_EKF_h
