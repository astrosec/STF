/**
 * @file   AOCSSensor.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_devicedriver_AOCSSensor_h
#define stf_core_devicedriver_AOCSSensor_h

#include "AOCSComponent.h"

namespace stf {
namespace core {
namespace devicedriver {

///センサの基本クラス．
template<class T,class U = T,class Env = ENV>
class AOCSSensor : public AOCSComponent<T,U,Env> {
public:
	AOCSSensor(int instance_id, const datatype::String& name, const datatype::DCM& dcm) : AOCSComponent<T,U,Env>(instance_id,name,dcm){}
	AOCSSensor(int instance_id, const datatype::String& name) : AOCSComponent<T,U,Env>(instance_id,name){}
	virtual ~AOCSSensor(){}
	void setSigma(double ref) { sigma_ = ref; }
	// 真値からノイズモデルを加味した観測値を計算する関数．
	// テンプレートクラス内のメンバ関数は，使用しない限り実体化されないので，フライトコードにオーバーヘッドは無い．
	virtual U inputFilter(const U& value) = 0; 
protected:

private:
	AOCSSensor& operator = (const AOCSSensor& rhs);
    AOCSSensor();
	AOCSSensor(const AOCSSensor<T,U,Env>& rhs);
};

} /* End of namespace stf::core::component */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_AOCSSensor_h
