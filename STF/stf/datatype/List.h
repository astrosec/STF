/**
 * @file   List.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
/////////////////////////////////
//  List.h                     //
//  Simple Template Container  //
//            Taiga.Noumi      //
/////////////////////////////////

////
/* �@�\���ŏ����ɍi�����R���e�i�N���X�D
/* �Eassert���L���Ȃ��[]���Z�q�ɔ͈͊O�`�F�b�N������
/* �E�f�[�^�̒ǉ��͖����̂ݑΉ��C�f�[�^�̍폜�͔C�ӈʒu�ɑ΂��ĉ\
/* �E�K������ŏ��̗v�f���폜����remove,�K������S�v�f���폜����removeAll��p��
/* �E�f�[�^�Q�Ƃƒǉ���O(1)�C�I�u�W�F�N�g�������Ɏ�����폜��O(n)
/* �E�C�e���[�^�̃C���^�[�t�F�[�X��C++�W���R���e�i�Ƃقړ���
/*
/*  //sample
/*  datatype::Quaternion q1(1,0,0,0);
/*  datatype::Quaternion q2(0,1,0,0);
/*  datatype::List<datatype::Quaternion> list;
/*  list.add(q1);
/*  list.add(q2);
/*  list.add(q3);
/*
/*  //�C�e���[�^���g���ėv�f�ɃA�N�Z�X
/*  datatype::List<datatype::Quaternion>::iterator it = list.begin();
/*  while(it != list.end()){
/*      std::cout << (*it).conjugate();//*it���g���ėv�f�ɃA�N�Z�X
/*      ++it;                          //��u�C���N�������g���T�|�[�g���邪�C�O�u�̂ق����ꎞ�I�u�W�F�N�g����炸����
/*  }
/*  for(it = list.begin(); it != list.end(); ++it){
/*      std::cout << (*it).conjugate();//��Ɠ������Ƃ�for����
/*  }
/*  for(int i = 0; i < list.size(); i++){
/*      std::cout << list[i].conjugate();//�C�e���[�^���g��Ȃ��ꍇ
/*  }
/*
/*/
////

#ifndef stf_datatype_List_h
#define stf_datatype_List_h
#include<assert.h>

namespace stf { 
namespace datatype {

template<class T>
class List {
public:
	explicit List() : size_(0),capacity_(3){ data_ = new T*[capacity_];};
	~List(){};
	// inner class
	class _iterator{
	private:
		T *point_;//���݂̗v�f
		const List<T> *list_;//���X�g
		int index_;
	public:
		_iterator(const _iterator &rhs): point_(rhs.point_), list_(rhs.list_), index_(rhs.index_){};
		_iterator(): point_(0), list_(0), index_(0) {};
		_iterator(const List<T>* container, int index=0): point_((*container).data_[index]), list_(container), index_(index) {};
		~_iterator(){};
		int index() const { return index_; } //getter
        T& operator *(){return *point_;}
        bool operator==(const _iterator &rhs){
			if(point_ == rhs.point_)  //�w���Ă���I�u�W�F�N�g�������
              if(index_ == rhs.index_)//�C���f�b�N�X���ꏏ�̏ꍇ
                return true;
			return false;
		}
		bool operator!=(const _iterator &rhs){return !(*this == rhs);}
		//�O�u�C���N�������g
		_iterator &operator++(){ 
			index_++;
			point_ = list_->data_[index_];
			return *this;
		}
		//��u�C���N�������g
		_iterator operator++(int dummy){		
			return (*this)++;
		}
		//�O�u�f�N�������g        
        _iterator &operator--(){
            index--;
            point_ = list_->data_[index_];
            return *this;
        }
		//��u�f�N�������g 
        _iterator &operator--(int dummy){
            return (*this)--;
        }
	};
	typedef typename List<T>::_iterator iterator;
	// public methods
	T& operator [](int index){assert(index < size_ && index >= 0); return *(data_[index]);}
	const T& operator [](int index) const {assert(index < size_ && index >= 0); return *(data_[index]);}
	_iterator begin() const{return _iterator(this,0);}
	_iterator end() const{return _iterator(this,size_);}
	int size() const{return size_;}
	int capacity() const{return capacity_;}
	void clear(){
		delete [] data_;
		data_ = new T*[3];
		size_ = 0;
		capacity_ = 3;
	}
	void add(T& data){
        size_++;
        //���1�ȏ�̋󂫃X���b�g���o����悤��capacity_���m�ۂ���
		if(size_ < capacity_){
			data_[size_-1] = &data;
            data_[size_] = 0;//�Ō�̃|�C���^��NULL�Ŗ��߂�
		}else{
			T** tempdata = new T*[2 * capacity_];
			for(int i = 0; i < capacity_; i++)
				tempdata[i] = data_[i];//�|�C���^���R�s�[
			delete [] data_;
			data_ = tempdata;
			data_[size_-1] = &data;
            data_[size_] = 0;//�Ō�̃|�C���^��NULL�Ŗ��߂�
			capacity_ *= 2;
		}
	}
    void push_back(T& data){//std::vector�ƌ݊������������邽�߂̊֐�
        add(data);
    }
    void remove(T& data){
        int i = 0;
        while(i < size_){
            if(data_[i] == &data){
                removeat_(i);
                return;
            }
            i++;
        }
    }
    void removeAll(T& data){
        int i = 0;
        while(i < size_){
          if(data_[i] == &data) removeat_(i);
          else i++;
        }
    }
	List(const List<T>& rhs){}//�R�s�[�R���X�g���N�^�C���s����Ȃ�
private:
	T** data_;
	int capacity_;//���݊m�ۂ���Ă���z��T�C�Y
	int size_;//�g�p����Ă���z��T�C�Y
    T& operator =(const List<T>& rhs){}//�R�s�[�C���s����Ȃ�
    //i�Ԗڂ̗v�f���폜
    void removeat_(int index){
        assert(size_ != 0);
        size_ --;
        for(int i = index; i < size_; i++)
          data_[i] = data_[i+1];
        data_[size_] = 0;
        if(size_ * 3 < capacity_){
            capacity_ /= 2;
			T** tempdata = new T*[capacity_];
			for(int i = 0; i < size_; i++)
			  tempdata[i] = data_[i];//�|�C���^���R�s�[
			delete [] data_;
			data_ = tempdata;
            data_[size_] = 0;//�Ō�̃|�C���^��NULL�Ŗ��߂�
        }
    }
};

} /* End of namespace stf::datatype */
} /* End of namespace stf */

#endif // stf_datatype_List_h
