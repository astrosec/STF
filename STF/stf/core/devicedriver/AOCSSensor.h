/**
 * @file   AOCSSensor.h
 * @brief  センサの基底クラス．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_devicedriver_AOCSSensor_h
#define stf_core_devicedriver_AOCSSensor_h

#include "AOCSComponent.h"
#include "IOPort.h"

namespace stf {
namespace core {
namespace devicedriver {

//! センサの基底クラス．
/*! 
	@tparam T   センサが入力する物理量．
	@tparam U   センサが入力する次元での物理量．3軸センサならTと一致，1軸ならScalar．
	@tparam Env コンポーネントの環境クラス．
*/
template<class T, class U, class Env>
class AOCSSensor : public AOCSComponent<T,U,Env>, public OutputPorts< TYPELIST_1(U) > {
public:
	AOCSSensor(int instance_id, const datatype::String& name, const datatype::DCM& dcm)
		: AOCSComponent<T, U, Env>(instance_id, name, dcm){}

	AOCSSensor(int instance_id, const datatype::String& name)
		: AOCSComponent<T, U, Env>(instance_id, name){}

	virtual ~AOCSSensor(){}

	//! 真値からノイズモデルを加味した観測値を計算する関数．
	/*! テンプレートクラス内のメンバ関数は，使用しない限り実体化されないので，フライトコードにオーバーヘッドは無い． */
	virtual U filter(const U& value) = 0; 
};

} /* End of namespace stf::core::component */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_AOCSSensor_h
