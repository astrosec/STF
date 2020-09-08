/**
 * @file   ConvertPolicy.h
 * @brief  あるdouble値から別のdouble値への変換に使用するポリシークラス．
 * Policy class used to convert from one double value to another
 *         AD変換値から物理値への変換規則などを，テンプレート引数によって外部から与えるために用いる．
 * Used to externally give conversion rules from AD conversion values to physical values by template arguments
 * @code
 *  template<class ConvertPolicy, int NumOfIO>
 *	class ADConverter : public ConvertPolicy{
 *  public:
 *    void do_update(){
 *        for(int i = 0; i < NumOfIO; i++) 
 *            ad_voltage_[i] = convert(ad_digital_[i]);//convertはConvertPolicyが実装する
 *                                                 convert is implemented by ConvertPolicy
 *    }
 *  private:
 *    unsigned short ad_digital_[NumOfIO];
 *    double ad_voltage_[NumOfIO];
 *  };
 * @endcode
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_devicedriver_ConvertPolicy_h
#define stf_core_devicedriver_ConvertPolicy_h

namespace stf {
namespace core {
namespace devicedriver {

//! 1次関数による変換を行うポリシークラス
	//Policy class that performs conversion by primary function
/*! 
	y = sf * x + offset;
*/
class FirstOrderConvert {
public:
	void set(double sf, double offset){ scale_factor_ = sf; offset_ = offset; }
	double convert(double input) { return scale_factor_ * input + offset_; }
private:
	double scale_factor_;
	double offset_;
};

//! 2次関数による変換を行うポリシークラス
//Policy class that performs conversion by quadratic function
/*! 
	y = a * x^2 + b * x + c;
*/
class SecondOrderConvert {
public:
	void set(double a, double b, double c){ a_ = a; b_ = b; c_ = c; }
	double convert(double input) { return input * ( a_ * input + b_ ) + c_; }
private:
	double a_;
	double b_;
	double c_;
};

//! 3次関数による変換を行うポリシークラス
//Policy class that performs conversion by cubic function
/*! 
	y = a * x^3 + b * x^2 + c * x + d;
*/
class ThirdOrderConvert {
public:
	void set(double a, double b, double c, double d){ a_ = a; b_ = b; c_ = c; d_ = d; }
	double convert(double input) { return input * ( input * ( input * a_ + b_ ) + c_ ) + d_; }
private:
	double a_;
	double b_;
	double c_;
	double d_;
};

} /* End of namespace stf::core::component */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_ConvertPolicy_h
