/**
 * @file   RWBase.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_devicedriver_rw_RWBase_h
#define stf_core_devicedriver_rw_RWBase_h

#include "../../../datatype/DCM.h"
#include "../../../datatype/Quaternion.h"
#include "../../../datatype/StaticVector.h"
#include "../../../datatype/Scalar.h"
#include "../AOCSActuator.h"

namespace stf {
namespace environment {
class Simulator;
}
namespace core {
namespace devicedriver {
namespace rw {

template<class T>
class RWBase : public AOCSActuator<datatype::StaticVector<3>, datatype::Scalar, T>{
public:
    RWBase();
	RWBase(int instance_id, const datatype::DCM &dcm, double max_torque, double min_torque, double max_angular_momentum);
    virtual ~RWBase();
	virtual void doUpdate();
	virtual double getAngularMomentum() { return this->angular_momentum_;}
	virtual bool isSaturated() const{ if(this->angular_momentum_ >= this->max_angular_momentum_) return true; return false; }//�z�C�[�����O�a���Ă�����true
private:
    double max_angular_momentum_;
	double angular_momentum_;//��������уA�����[�f�B���O����u���b�N�Ŏg�p����p�^���ʁD
};

template<class T>
RWBase<T>::RWBase()
{
}

template<class T>
RWBase<T>::RWBase(int instance_id, const datatype::DCM &dcm, double max_torque, double min_torque, double max_angular_momentum) :
AOCSActuator<datatype::StaticVector<3>, datatype::Scalar, T>(instance_id, "RW", dcm), max_angular_momentum_(max_angular_momentum)
{
	this->max_output_ = max_torque;	
	this->min_output_ = min_torque;
}

template<class T>
RWBase<T>::~RWBase()
{
}

template<class T>
void RWBase<T>::doUpdate(){
//	this->datapool_.get< 0, RWBase >();
}

template <>
void RWBase<environment::Simulator>::doUpdate();

template<>
RWBase<environment::Simulator>::RWBase(int instance_id, const datatype::DCM &dcm, double max_torque, double min_torque, double max_angular_momentum);


} /* End of namespace stf::core::devicedriver::rw */
} /* End of namespace stf::core::devicedriver */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_mtq_RWBase_h
