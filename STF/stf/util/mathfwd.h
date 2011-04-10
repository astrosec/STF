/**
 * @file   mathfwd.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.04.10
 */
#ifndef stf_util_mathfwd_h
#define stf_util_mathfwd_h

namespace stf {
namespace datatype {
class Matrix;
}
namespace util {

namespace math {
	//! �����������߂�Ccmath�̃��b�p�D
	double sqrt(double s);
	//! ��Βl�����߂�Ccmath�̃��b�p�D
	double abs(double s);
	//! ���������߂�Ccmath�̃��b�p�D
	double Sin(double s);
	//! �]�������߂�Ccmath�̃��b�p�D
	double Cos(double s);
	
	//! �s��̎w����n���̃}�N���[�����W�J�܂Ōv�Z���ĕԂ��֐��D
	datatype::Matrix exp(const datatype::Matrix& m, int n);
	
	//! �s��̎w����4���̃}�N���[�����W�J�܂Ōv�Z���ĕԂ��֐��D
	datatype::Matrix exp(const datatype::Matrix& m);
}


}
}


#endif