/**
 * @file   Envitonments.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_datatype_Current_h
#define stf_datatype_Current_h

#include <assert.h>
#include "Scalar.h"

namespace stf { 
namespace datatype {

///�d����\������N���X�D
class Current : public Scalar {
public:
	Current() {}
	Current(double value) : Scalar(value) {}
	Current(const Current& rhs) : Scalar(rhs.value_){}
	Current& operator = (const Current& rhs) { value_ = rhs.value_; return *this;}
	~Current(){}
private:

};

///�d����\������N���X�D
class Voltage : public Scalar {
public:
	Voltage() {}
	Voltage(double value) : Scalar(value) {}
	Voltage(const Voltage& rhs) : Scalar(rhs.value_){}
	Voltage& operator = (const Voltage& rhs) { value_ = rhs.value_; return *this;}
	~Voltage(){}
private:

};

///���x��\������N���X�D
class Temperature : public Scalar {
public:
	Temperature() {}
	Temperature(double value) : Scalar(value) {}
	Temperature(const Temperature& rhs) : Scalar(rhs.value_){}
	Temperature& operator = (const Temperature& rhs) { value_ = rhs.value_; return *this;}
	~Temperature(){}
private:

};


} /* End of namespace stf::datatype */
} /* End of namespace stf */

#endif // stf_datatype_Current_h
