/**
 * @file   OrbitInfo.h
 * @brief  �O�����֌W�̗ʂ�\��
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_datatype_OrbitInfo_h
#define stf_datatype_OrbitInfo_h
#include "StaticVector.h"
#include "../util/math.h"

namespace stf { 
namespace datatype {

//! �O��6�v�f��ێ�����N���X�D�T�C�Y��剻������邽�߁C��v�Ȍv�Z��OrbitImpl��static�ȃ��\�b�h�ɓ����邱�Ƃōs��
/*!  */
struct OrbitInfo {
	OrbitInfo() : a(0), e(0), M(0), i(0), Omega(0), omega(0), n(0) {}
	OrbitInfo(double a, double e, double M, double i, double Omega, double omega)
		: a(a), e(e), M(M), i(i), Omega(Omega), omega(omega)
	{
		n = sqrt( util::math::MU / (a * a * a) ); 
	}
	double a;//�����a(m)
	double e;//���S��
	double M;//���ϋߓ_���p
	double i;//�O���X�Ίp(rad)
	double Omega;//����_�Ԍo(rad)
	double omega;//�ߒn�_����
	double n;
};

//! �q�����W���ܓx�o�x���x�̌`���ŕێ�����N���X�D
/*!  */
struct Geo  {
	Geo() : latitude(0), longitude(0), altitude(0) {}
	double latitude;//�ܓx(rad)
	double longitude;//�o�x(rad)
	double altitude;//���x(m)
};

//! �q�����W��n�S�������W�n�ɂ�����ʒu�Ƒ��x��6�����x�N�g���ŕێ�����N���X�D
/*!  */
struct PositionInfo  {
	PositionInfo() {}
	StaticVector<3> position;
	StaticVector<3> velocity;
};

} /* End of namespace stf::datatype */
} /* End of namespace stf */

#endif // stf_datatype_OrbitInfo_h
