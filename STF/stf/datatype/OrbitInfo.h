/**
 * @file   OrbitInfo.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_datatype_OrbitInfo_h
#define stf_datatype_OrbitInfo_h
#include "assert.h"
#include "IAocsData.h"
#include "StaticVector.h"
#include "../util/math.h"
namespace stf { 
namespace datatype {

//�O��6�v�f��ێ�����N���X�D�T�C�Y��剻������邽�߁C��v�Ȍv�Z��OrbitImpl��static�ȃ��\�b�h�ɓ����邱�Ƃōs��
struct OrbitInfo : public IAocsData {
public:
	OrbitInfo() {}
	OrbitInfo(double a, double e, double M, double i, double Omega, double omega)
		: a(a), e(e), M(M), i(i), Omega(Omega), omega(omega)
	{
		n = sqrt( util::math::MU / (a * a * a) ); 
	}
	~OrbitInfo(){}
	virtual void normalize(){}
	virtual void reset(){};
	virtual const double* toStream() const { return 0; };
	virtual int getStreamLength() const { return 7; };
	double a;//�����a(m)
	double e;//���S��
	double M;//���ϋߓ_���p
	double i;//�O���X�Ίp(rad)
	double Omega;//����_�Ԍo(rad)
	double omega;//�ߒn�_����
	double n;
private:

};

struct Geo : public IAocsData {
	virtual void normalize(){}
	virtual void reset(){};
	virtual const int* serialize() const { return 0;}
	double latitude;//�ܓx(rad)
	double longitude;//�o�x(rad)
	double altitude;//���x(m)
};

struct PositionInfo : public IAocsData {
public:
	PositionInfo() {}
	~PositionInfo() {}
	virtual void normalize(){}
	virtual void reset(){};
	virtual const double* toStream() const { return 0; };
	virtual int getStreamLength() const { return 7; };
	StaticVector<3> position;//�n�S�������W�n�ɂ�����q���̈ʒu�D
	StaticVector<3> velocity;//
private:

};

} /* End of namespace stf::datatype */
} /* End of namespace stf */

#endif // stf_datatype_OrbitInfo_h
