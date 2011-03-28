/*
	���`��ԃN���X
	2011/3/19 Taiga Noumi

	�o�^�����_�����Ƃɐ��`��Ԍ��ʂ�Ԃ��ȒP�ȃN���X�D
	�X���b�h�Z�[�t�ł͂Ȃ��C���`��Ԏ��̌��������l������Ȃ��D
	��ԕs�\�ȏ󋵁i�_�̓o�^�����[���C�_�͈̔͊O���w��j�ł̓v���O�������~������D

	--sample1--

	#include<iostream>
	#include"Linear.hpp"

	int main(void){
		Linear<double,double> LI;

		//(x,y)�̒l�y�A��o�^
		LI.insert(0, 1);
		LI.insert(1, 2);

		//�l����肾��
		std::cout << LI[0] << std::endl; //"1"
		std::cout << LI[1] << std::endl; //"2"
		std::cout << LI[0.5] << std::endl; //"1.5"
	}

	--sample2--
	
	#include"Linear.hpp"
	#include "boost/assign.hpp"
	#include <complex>

	int main(void){
		using namespace boost::assign;
		
		//boost::assign�ɂ�鏉����
		Linear<> LI = map_list_of
        (1, 0)
        (2, 0.5)
        (3, 0.3)
        (4, 0.1)
        (5, -0.1);

		std::cout << LI[3.5] << std::endl; //"0.2"
		
		//���f���̕��
		Linear<double, std::complex<double> > LI2 = map_list_of
		(0, std::complex<double>(-1, 1))
		(1, std::complex<double>(1, 0.5))
		(2, std::complex<double>(3, 0.2));
		
		std::cout << LI2[0.5] << std::endl; //"(0, 0.75)"
		std::cout << LI2[1.5] << std::endl; //"(2, 0.35)"
	}

*/
#include <assert.h>
#include <functional>
#include <algorithm>
#include <map>

#if (defined(_MSC_VER) && (_MSC_VER >= 1600)) || defined(__GXX_EXPERIMENTAL_CXX0X__)
// C++0x���g�p�����o�[�W�����DVC2010�ł͂����炪�g����
template<typename X = double, typename Y = double>
class Linear {
public:
	typedef std::map<X, Y> Points;

	Linear(){}

	template<class Iter>
	Linear(Iter first, Iter last): points_(first, last){}

	Linear(const Points& points) : points_(points){}

	~Linear(){}

	void insert(X x, Y y){ points_[x] = y; }

	Y operator[] (X x) const{
		assert(!points_.empty());
		return points_.find(x) == points_.end() ? get_value_(x) : points_.at(x);
	}

private:	
	static bool greater_(typename Points::value_type p, X x){ return p.first > x ? true : false; }

	Y get_value_(X x) const{
		//x�𒴂���ŏ���point���w���C�e���[�^
		auto it_h = std::find_if(points_.begin(), points_.end(), std::bind2nd(std::ptr_fun(greater_), x));

		//����͕�O���K�v�ɂȂ�悤�ȃP�[�X��assert�Œe��
		assert(it_h != points_.begin() && it_h != points_.end());
		
		//x�������ő��point���w���C�e���[�^
		auto it_l = it_h;
		it_l--;
		
		return linear_((*it_l).first, (*it_l).second, (*it_h).first, (*it_h).second, x);
	}

	Y linear_(X x1, Y y1, X x2, Y y2, X x) const{
		return (x - x1) * (y2 - y1) / (x2 - x1) + y1;
	}
	
	Points points_;
};

#else

//C++0x���g�p���Ȃ��o�[�W�����DVC2008��0x�I�v�V����������GCC�ł͂����炪�R���p�C�������
template<typename X = double, typename Y = double>
class Linear {
public:
	typedef std::map<X, Y> Points;

	Linear(){}

	template<class Iter>
	Linear(Iter first, Iter last): points_(first, last){}

	Linear(const Points& points) : points_(points){}

	~Linear(){}

	void insert(X x, Y y){ points_[x] = y; }

	Y operator[] (X x) {
		assert(!points_.empty());
		return points_.find(x) == points_.end() ? get_value_(x) : points_[x];
	}

private:	
	static bool greater_(typename Points::value_type p, X x){ return p.first > x ? true : false; }

	Y get_value_(X x) const{
		//x�𒴂���ŏ���point���w���C�e���[�^
		Points::const_iterator it_h = std::find_if(points_.begin(), points_.end(), std::bind2nd(std::ptr_fun(greater_), x));

		//����͕�O���K�v�ɂȂ�悤�ȃP�[�X��assert�Œe��
		assert(it_h != points_.begin() && it_h != points_.end());
		
		//x�������ő��point���w���C�e���[�^
		Points::const_iterator it_l = it_h;
		it_l--;
		
		return linear_((*it_l).first, (*it_l).second, (*it_h).first, (*it_h).second, x);
	}

	Y linear_(X x1, Y y1, X x2, Y y2, X x) const{
		return (x - x1) * (y2 - y1) / (x2 - x1) + y1;
	}
	
	Points points_;
};

#endif