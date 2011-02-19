/**
 * @file   EKFParamaters.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef aocs_core_strategy_control_EKFParamaters_h
#define aocs_core_strategy_control_EKFParamaters_h

#include "../../../datatype/Quaternion.h"
#include "../../../datatype/Matrix.h"
#include "../../../datatype/Vector.h"


namespace stf {
namespace core {
namespace strategy {
namespace control {

struct EKFParamaters {
public:
    EKFParamaters();
    datatype::Quaternion q0;//q�����l
    datatype::Vector b0;//b�����l
    datatype::Matrix P0;//�����U�s�񏉊��l
    double w_q;//�V�X�e���m�C�Y
	double w_b;//�V�X�e���m�C�Y
    double v;//�ϑ��m�C�Y�x�N�g��
    double timestep;//�`�����ԍ��ݕ�(sec)
    double tau;//�o�C�A�X���[�g�����_���m�C�Y�̎��萔(non-zero)
	double MinimunGain;//�J���}���Q�C��K�̑Ίp�����ɐݒ肳���ŏ��l�D0�̏ꍇ�͍ŏ��l��ݒ肵�Ȃ��ʏ��KF
	bool calcSensorGap;//�Z���T�o�͒x���̏���
    ~EKFParamaters();
};

} /* End of namespace stf::core::strategy::control */
} /* End of namespace stf::core::strategy */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // aocs_strategy_input_EKFParamaters_h
