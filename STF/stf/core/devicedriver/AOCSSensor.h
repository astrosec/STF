/**
 * @file   AOCSSensor.h
 * @brief  �Z���T�̊��N���X�D
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

//! �Z���T�̊��N���X�D
/*! 
	@tparam T   �Z���T�����͂��镨���ʁD
	@tparam U   �Z���T�����͂��鎟���ł̕����ʁD3���Z���T�Ȃ�T�ƈ�v�C1���Ȃ�Scalar�D
	@tparam Env �R���|�[�l���g�̊��N���X�D
*/
template<class T,class U = T,class Env = ENV>
class AOCSSensor : public AOCSComponent<T,U,Env> {
public:
	AOCSSensor(int instance_id, const datatype::String& name, const datatype::DCM& dcm) : AOCSComponent<T,U,Env>(instance_id,name,dcm){}
	AOCSSensor(int instance_id, const datatype::String& name) : AOCSComponent<T,U,Env>(instance_id,name){}
	virtual ~AOCSSensor(){}
	void set_sigma(double ref) { sigma_ = ref; }
	//! �^�l����m�C�Y���f�������������ϑ��l���v�Z����֐��D
	/*! �e���v���[�g�N���X���̃����o�֐��́C�g�p���Ȃ�������̉�����Ȃ��̂ŁC�t���C�g�R�[�h�ɃI�[�o�[�w�b�h�͖����D */
	virtual U filter(const U& value) = 0; 
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
