#ifndef core_component_Composite_h
#define core_component_Composite_h
#include <assert.h>
#include "AOCSComponent.h"
#include "AOCSActuator.h"
#include "AOCSSensor.h"
#include "../../datatype/Matrix.h"
#include "../../datatype/List.h"
#include "../../datatype/Quaternion.h"
#include "../../util/Ostream.h"
#include "../datapool/Datapool.h"

namespace stf {
namespace core {
namespace devicedriver {
//
// Composite
//  AOCSComponent�̏W���̂�\���N���X�D
//  Composite�f�U�C���p�^�[�����g���C�P�̂�AOCSComponent�Ɠ����̈������ł���D
//  �K�v�ȕ����ʂ��R���|�[�l���g�P�Ƃ̃C���^�[�t�F�[�X�œ����Ȃ��ꍇ
// �i�����ƂɒʐM�n�����Ⴄ�A�N�`���G�[�^��C�������̊ϑ��l��g�ݍ��킹��O��̃Z���T�Ȃǁj�Ɏg���D

template<class Leaf,int Numbers>
class CompositeInput : public AOCSSensor<typename Leaf::Target> {
public:
	CompositeInput(int instance_id, const datatype::DCM& dcm) : AOCSSensor<typename Leaf::Target>(instance_id,"Composite",dcm), index_(0)
	{
		for(int i = 0; i < Numbers; i++) childs_[index_] = 0;
	}
	virtual ~CompositeInput(){}
	virtual void doUpdate();
	virtual void aggregate();
	virtual typename Leaf::Target inputFilter(const typename Leaf::Target& value){ return value; }//composite�̓t�B���^�����̂܂ܕԂ�
	void appendChild(Leaf* c);
protected:
private:
	Leaf* childs_[Numbers];
	unsigned char index_;//max 255 childs
};

template<class Leaf,int Numbers>
class CompositeOutput : public AOCSActuator<typename Leaf::Target> {
public:
	CompositeOutput(int instance_id, const datatype::DCM& dcm) : AOCSActuator<typename Leaf::Target>(instance_id,"Composite",dcm), output_mat_(Numbers,3), index_(0)
	{
		for(int i = 0; i < Numbers; i++) childs_[index_] = 0;
		output_mat_.unitize(); //�f�t�H���g�Ńg���N���z�s��͒P�ʍs��
	}
	virtual ~CompositeOutput(){}
	virtual void doUpdate();
	virtual void distribute();
	virtual void matrixset();//�^���t�s���p���ăg���N���z�s��𐶐�
	void appendChild(Leaf* c);
protected:
private:
	Leaf* childs_[Numbers];
	datatype::Matrix output_mat_;//�g���N���z�s��
	unsigned char index_;//max 255 childs
};

template <class Leaf,int Numbers>
void CompositeInput<Leaf,Numbers>::appendChild(Leaf* c){
	assert(index_ < Numbers);
	childs_[index_] = c;
	index_++;
}

template <class Leaf,int Numbers>
void CompositeOutput<Leaf,Numbers>::appendChild(Leaf* c){
	assert(index_ < Numbers);
	childs_[index_] = c;
	index_++;
	if(index_ == Numbers){//�q���o�������
		this->matrixset();
	}
}

//Input:�e����q�֍ċA�I��Update�����s����D
// ���Z���T����l���擾���e�Z���T�I�u�W�F�N�g�����[�J���ɕێ������l��Composite�ɏW��Body���W�n�ł̒l�Ƃ���DB�ɓo�^
template <class Leaf,int Numbers>
void CompositeInput<Leaf,Numbers>::doUpdate(){
	for(unsigned char i = 0; i < Numbers; ++i){
		if(childs_[i] != 0)
			childs_[i]->doUpdate();
	}
	aggregate();
	if(this->datapool_ != 0){
		datapool_->set<CompositeInput<Leaf,Numbers>>(datapool_hold_index_,this->value_);
	}
}

//���[�t�R���|�[�l���g���擾�����l���������郁�\�b�h�D
//�K�v�ɉ����ĕ������ꉻ���g���C�����ʂƃA�v���P�[�V�����ɑ΂��ēK�؂ȍ������s��
template <class Leaf,int Numbers>
void CompositeInput<Leaf,Numbers>::aggregate(){
	typename Leaf::Target v;
	int updatedsensors = 0;
	for(unsigned char i = 0; i < Numbers; ++i){
		if(childs_[i] != 0){
			if(childs_[i]->getLastUpdateTime() > this->getLastUpdateTime()){//�Â����̂̓X�L�b�v�H
				v += childs_[i]->getValueInBodyFrame();//�P�����Z�ō����ł���H
				updatedsensors ++;
			}
		}
	}
	if(updatedsensors == 0){//�q�����X�V���Ă��Ȃ��̂Ŏ������������Ȃ�
		return;
	}
	v.normalize();//�����ʂ𐳋K��
	this->setValueInBodyFrame(v);
}


//Output:�e����q�֍ċA�I��Update�����s����D
// Body���W�n�ł̎w�ߒl��DB����ǂݍ��݁��e�Z���T�փg���N�𕪔z���e�Z���T�I�u�W�F�N�g�����[�J���ɕێ������l�����A�N�`���G�[�^�ɑ��M
template <class Leaf,int Numbers>
void CompositeOutput<Leaf,Numbers>::doUpdate(){
	if(this->datapool_ != 0){
		this->datapool_->set<CompositeOutput<Leaf,Numbers>>(datapool_hold_index_,this->value_b_);//
	}
	distribute();
	for(unsigned char i = 0; i < Numbers; ++i){
		if(childs_[i] != 0)
			childs_[i]->doUpdate();
	}
}

//���[�t�R���|�[�l���g�ɏo�́i�g���N���j�𕪔z���郁�\�b�h�D
//�K�v�ɉ����ĕ������ꉻ���g���C�����ʂƃA�v���P�[�V�����ɑ΂��ēK�؂ȕ��z���s��
template <class Leaf,int Numbers>
void CompositeOutput<Leaf,Numbers>::distribute(){
	//util::cout << value_;
	//util::cout << output_mat_;
	datatype::Vector v = this->output_mat_ * this->value_;
	for(int i = 0; i < Numbers; i++){
		childs_[i]->setTorque(v[i]);
	}

}

//�q�R���|�[�l���g��Z���܂��̃g���N���o���Ɖ��肵�āC
//�^���t�s��ŃG�l���M�[�ŏ��̃g���N���z�s����v�Z�D
template <class Leaf,int Numbers>
void CompositeOutput<Leaf,Numbers>::matrixset(){
	datatype::Matrix m(3,Numbers);
	for(int i = 0; i < Numbers; i++){
		datatype::DCM d = this->childs_[i]->getDCM();
		for(int j = 0; j < 3; j++)
			m[j][i] = d[j][2];
	}
	this->output_mat_ = m.trans() * ( m * m.trans() ).inverse();
}


} /* End of namespace stf::core::component */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // core_component_Composite_h
