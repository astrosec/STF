/**
 * @file   TAMBase.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_devicedriver_magnetometer_TAMBase_h
#define stf_core_devicedriver_magnetometer_TAMBase_h

#include "../../../datatype/Magnetic.h"

#include "../AOCSSensor.h"

namespace stf {
namespace environment {
class Simulator;
}
namespace core {
namespace devicedriver {
namespace magnetometer {


//3���o�͂̎��C�Z���T�D
template <class T>
class TAMBase : public AOCSSensor<datatype::MagneticField,datatype::MagneticField,T>{
public:
	TAMBase(int instance_id, const datatype::DCM &angle);
	virtual ~TAMBase(){}
	virtual void doUpdate();
	virtual datatype::MagneticField inputFilter(const datatype::MagneticField& value); 
private:
    TAMBase();
	double err_deg_;
	int sigma_;
};

template <class T>
TAMBase<T>::TAMBase(int instance_id, const datatype::DCM& dcm)
	: AOCSSensor<datatype::MagneticField,datatype::MagneticField,T>(instance_id, "TAM", dcm)
{

}

template <class T>
void TAMBase<T>::doUpdate(){

}

//�V�~�����[�^�p�̓��ꉻ
template <>
void TAMBase<environment::Simulator>::doUpdate();
template <>
datatype::MagneticField TAMBase<environment::Simulator>::inputFilter(const datatype::MagneticField& value); 

} /* End of namespace stf::core::devicedriver::magnetometer */
} /* End of namespace stf::core::devicedriver */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_sunsensor_TAMBase_h