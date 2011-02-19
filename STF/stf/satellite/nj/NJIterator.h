#ifndef stf_satellite_nj_NJIterator_h
#define stf_satellite_nj_NJIterator_h

#include "../../interface/Iterator.h"
#include "NJEKF.h"
#include "NJRMMEKF.h"
#include "NJTRIAD.h"

namespace stf {
namespace interface {

template<int SCALE,int SIZE, class BASE>
class NJIteratorBase : public Iterator {
public:
	NJIteratorBase(const BASE* data) : data_(data), index_(0) {}
	virtual void init(){ index_ = 0;}
	virtual bool end(){ if(index_ == SIZE) return true; return false;}
	virtual void operator ++() { index_ ++; }
protected:
	int index_;
	const BASE* data_;
};

// NJ�̃e�����g���ɕK�v��EKF�̃e�����g���o�͂��`�B
template<int SCALE>
class NJEKFIterator : public NJIteratorBase<SCALE,13,core::strategy::control::NJEKF> {
public:
	NJEKFIterator(const core::strategy::control::NJEKF* data): NJIteratorBase<SCALE,13,core::strategy::control::NJEKF>(data) {}
	virtual double operator()() {
		if(index_ < 4) return (SCALE * data_->q_[index_]);
		if(index_ < 7) return (SCALE * data_->bref_[index_ - 4]);
		return (SCALE * data_->P_[index_ - 7][index_ - 7]);
	}
private:
};

// NJ�̃e�����g���ɕK�v��EKF�̃e�����g���o�͂��`�B
template<int SCALE>
class NJRMMEKFIterator : public NJIteratorBase<SCALE,3,core::strategy::control::NJRMMEKF> {
public:
	NJRMMEKFIterator(const core::strategy::control::NJRMMEKF* data): NJIteratorBase<SCALE,3,core::strategy::control::NJRMMEKF>(data) {}
	virtual double operator()() {		
		return data_->value_b_[index_];
	}
private:
};

// TRIAD����Quaternion�̐���l���e�����g���Ƃ��ďo�́D
template<int SCALE>
class NJSunMagTRIADIterator : public NJIteratorBase<SCALE,4,core::strategy::control::NJSunMagTRIAD> {
public:
	NJSunMagTRIADIterator(const core::strategy::control::NJSunMagTRIAD* data): NJIteratorBase<SCALE,4,core::strategy::control::NJSunMagTRIAD>(data) {}
	virtual double operator()() {
		return data_->value_b_[index_];
	}
private:
};

} /* End of namespace stf::interface */
} /* End of namespace stf */

#endif //  stf_satellite_prism_NJIterator_h
