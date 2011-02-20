/**
 * @file   OrbitCalc.cpp
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#include <assert.h>
#include "OrbitCalc.h"
#include "../util/math.h"
#include "TypeConverter.h"
#include "OrbitInfo.h"
#include "Magnetic.h"
#include "StaticVector.h"
#include "DateTime.h"
#include "Quaternion.h"

#include "../environment/sgp4/sgp4ext.h"
#include "../environment/sgp4/sgp4unit.h"
#include "../environment/sgp4/orbitutil.h"
#include "../environment/models/igrf.h"

namespace stf {
namespace datatype {

StaticVector<2> OrbitCalc::getSunDirection2D(const DateTime& time){
	//����n���h�u�b�NP.280. �n�����S����̑��z�����x�N�g�������߂�
	double T  = (time.get_julius() - 2451545.0) / 36525 ;
	double M = util::math::DEG2RAD * (357.5256 + 35999.045 * T);
	double lambda = util::math::DEG2RAD * (282.94 + M + (6892 / 3600) * sin(M) + (72/3600) * sin(2*M) - (0.002652 - (1250.09115 / 3600) * T));
	double eta = util::math::DEG2RAD * 23.43929111;//���ω����X�p
	StaticVector<3> v;
	v[0] = cos(lambda);
	v[1] = sin(lambda) * cos(eta);
	v[2] = sin(lambda) * sin(eta);
	return TypeConverter::toPolar(v);
}

StaticVector<2> OrbitCalc::getEarthDirection2D(const PositionInfo& p){
	return TypeConverter::toPolar(-p.position);
}


StaticVector<3> OrbitCalc::getEarthDirection3D(const PositionInfo& p){
	return (-p.position) / (p.position.norm(2));
}

StaticVector<3> OrbitCalc::getSunDirection3D(const DateTime& time){
	//����n���h�u�b�NP.280. �n�����S����̑��z�����x�N�g�������߂�
	double T  = (time.get_julius() - 2451545.0) / 36525 ;
	double M = util::math::DEG2RAD * (357.5256 + 35999.045 * T);
	double lambda = util::math::DEG2RAD * (282.94 + M + (6892 / 3600) * sin(M) + (72/3600) * sin(2*M) - (0.002652 - (1250.09115 / 3600) * T));
	double eta = util::math::DEG2RAD * 23.43929111;//���ω����X�p
	StaticVector<3> v;
	v[0] = cos(lambda);
	v[1] = sin(lambda) * cos(eta);
	v[2] = sin(lambda) * sin(eta);
	return v;
}

//�q�����W�n�ɂ�����n�������x�N�g�����v�Z�D
StaticVector<3> OrbitCalc::getEarthDirectionInBodyFrame(const PositionInfo& p, const Quaternion& q){
	return - (datatype::TypeConverter::toDCM(q) * p.position) ;
}

//�q�����W�n�ɂ����鑾�z�����x�N�g�����v�Z�D
StaticVector<3> OrbitCalc::getSunDirectionInBodyFrame(const DateTime& time, const Quaternion& q){
	return datatype::TypeConverter::toDCM(q) * getSunDirection3D(time);
}


MagneticField OrbitCalc::getMagneticFieldDirection(const PositionInfo& p, const DateTime& time){
	double decyear = 0.0;

	sgp4::JdToDecyear(time.get_julius(), &decyear);

	double side = sgp4::gstime(time.get_julius());

	double pos[3];
	for(int i = 0; i < 3; i++) pos[i] = p.position[i] / 1000;

	double lat,lon,alt;
	sgp4::TransECIToGeo(side, pos, &lon, &lat, &alt);

	double mag[3];
	igrf::IgrfCalc(decyear,lat,lon,alt,side,mag);
	
	datatype::MagneticField m;
	for(int i = 0; i < 3; i++) m[i] = mag[i];

	/*util::cout << "dec:" << decyear << util::endl; 	
	util::cout << "side:" << side << util::endl; 	
	util::cout << "pos:" << p.position << util::endl; 
	util::cout << "lat:" << lat << "lon:" << lon << "alt:" << alt << util::endl; 	
	util::cout << "mag:" << m << util::endl; 
	util::cout << util::endl;*/
	return m;
}


} /* End of namespace stf::datatype */
} /* End of namespace stf */

