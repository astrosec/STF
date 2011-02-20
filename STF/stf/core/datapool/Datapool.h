/**
 * @file   Datapool.h
 * @brief  STF�����f�[�^�Ƀ^�C���^�O��t�����Ċi�[����f�[�^�v�[��
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_datapool_Datapool_h
#define stf_core_datapool_Datapool_h
#include<assert.h>
#include "../../datatype/IAocsData.h"
#include "../../datatype/List.h"
#include "../../RootObject.h"
#include "../../datatype/Time.h"
#include "../../datatype/StaticVector.h"
#include "../../datatype/String.h"
#include "../devicedriver/clock/ITimeClock.h"
#include "../../interface/Iterator.h"
#include "../../util/loki/TypeManip.h"

namespace stf {
namespace core {
namespace datapool {

//�����O�o�b�t�@�^��IAocsData-Time�^�v�����i�[����N���X�D
template<class Base>
class Tuple
{
public:
	template <class T>
	Tuple(int capacity, Loki::Type2Type<T>, const datatype::String& name) : capacity_(capacity), index_(0), name_(name){
		assert(capacity > 0);
		this->data_ = new Base*[capacity];
		for(int i = 0; i < capacity; i++)
			this->data_[i] = new T;
		this->time_ = new datatype::Time[capacity];
	}
	~Tuple(){
		delete[] data_;
		delete[] time_;
	}
	template <class T>
	void set(const datatype::Time& time, const T& value){
		index_ ++;
		index_ %= capacity_;
		*(static_cast<T*>(data_[index_])) = value;//copy
		time_[index_] = time;//copy
		//T& dd = (static_cast<T*>(data_))[index_];
		//Base* ddd = &dd;
		Base* d = data_[index_];
	}
	template <class T>
	const T& get(){
		return *(static_cast<T*>(data_[index_]));
	}
	const datatype::Time& gettime(){
		return time_[index_];
	}
	template <class T>
	void print(){
		util::cout << "Index:" << this->index_ << util::endl;
		util::cout << "Time  /  Record" << util::endl;
		for(int i = 0; i < capacity_; i++){
			util::cout << time_[i] << "   " <<(static_cast<T*>(data_))[i] << util::endl;
		}
	}
	int size() const { return capacity_; }
	int index() const { return index_; }
	const Base* get_data_at(int index) const{ 
		assert(index < capacity_); 

		return (data_)[index_]; 
	}
	const datatype::Time& get_time_at(int index) const{ assert(index < capacity_); return time_[index]; }
	const datatype::String& name() const { return name_; }
private:
	Base** data_;
	int capacity_;
	int index_;
	datatype::String name_;//�f�[�^�x�[�X���C�f�o�b�O�p
	datatype::Time* time_;

};

class DataPoolBase : public RootObject
{
public:
	DataPoolBase(int instance_id): createdindex_(-1) , RootObject(instance_id, "DataPoolBase"){}
	~DataPoolBase(void){}
	const int rows () const{ return this->kMaxDataPoolRows; }
	bool is_created(int index) const{ 
		assert( index < kMaxDataPoolRows && index >= 0); 
		if(index <= createdindex_) return true;
		else return false;
	}
protected:
	static const int kMaxDataPoolRows = 255;
	int createdindex_;
};

class AocsDataPoolIterator;

class AocsDataPool : public DataPoolBase//: public RootObject
{
public:
	AocsDataPool(int instance_id);
	~AocsDataPool(void){}
	// �ŐV�̒l�����̌^�Ƃ��Ď��
	template<class Producer> typename Producer::Hold get(int index) const{
		return table_[index]->get<Producer::Hold>();//copy
	}
	const datatype::IAocsData* get(int rows) const;
	const datatype::IAocsData* get(int rows,int cols) const;
	template<class T>const T& get(int rows){
		return this->table_[rows]->get<T>();
	}
	// �ŐV�̒l�����
	datatype::Time gettime(int index) const;
	const datatype::String& getname(int index) const;
	// �l���Z�b�g
	template<class Producer> void set(int index, const typename Producer::Hold& value){
		table_[index]->set<typename Producer::Hold>(this->clock_->get_time(),value);
	}
	template<class Producer> typename Producer::Hold& get_at(int index, int rows) const {
		return table_[index]->get_at<Producer::Hold>(rows);//copy
	}
	//���������ɂ̂ݎg�p�D���I����
	//IAocsData��Hold���Ă���Root�z���̃N���X�ł���Ή��ł�����
	template<class Producer> int create(Producer* producer,unsigned short capacity, const datatype::String& name = "unknown"){
		this->createdindex_++;
		this->table_[createdindex_] = new Tuple<datatype::IAocsData>(capacity,Loki::Type2Type<Producer::Hold>(),name);
		return createdindex_ ;
	}
	//���������ɂ̂ݎg�p�D���I����
	//IAocsData��Hold���Ă���Root�z���̃N���X�ł���Ή��ł�����
	template<class Datatype> int create(Loki::Type2Type<Datatype>,unsigned short capacity, const datatype::String& name = "unknown"){
		this->createdindex_++;
		this->table_[createdindex_] = new Tuple<datatype::IAocsData>(capacity,Loki::Type2Type<Datatype>(),name);
		return createdindex_ ;
	}
	//���������ɂ̂ݎg�p�D���I����
	//IAocsData��Hold���Ă���Root�z���̃N���X�ł���Ή��ł�����
	template<class Producer> int create(int id,unsigned short capacity, const datatype::String& name = "unknown"){
		this->createdindex_++;
		this->table_[createdindex_] = new Tuple<datatype::IAocsData>(capacity,Loki::Type2Type<Producer::Hold>(),name);
		return createdindex_ ;
	}
	template<class Producer> void show(int index) const{
		table_[index]->print<Producer::Hold>();
	}
	// �w�肵���C���X�^���XID�����������^�v���ւ̃|�C���^���擾�i�e�����g���p�j
	Tuple<datatype::IAocsData>* get_ptr(int index) ;
private:
	//template<class T, int i> friend class AocsDataPoolIterator;
	Tuple<datatype::IAocsData>** table_;
};

class EventDataPool : public DataPoolBase//: public RootObject
{
public:
	EventDataPool(int instance_id);
	~EventDataPool(void){}
	// �ŐV�̒l�����̌^�Ƃ��Ď��
	template<class Producer> typename Producer::Hold get(int index) const{
		return table_[index]->get<Producer::Hold>();//copy
	}
	const core::event::EventBase* get(int rows) const;
	const core::event::EventBase* get(int rows,int cols) const;
	// �ŐV�̒l�����
	datatype::Time gettime(int index) const;
	const datatype::String& getname(int index) const;
	// �l���Z�b�g
	template<class Producer> void set(int index, const typename Producer::Hold& value){
		table_[index]->set<typename Producer::Hold>(this->clock_->get_time(),value);
	}

	template<class Producer> typename Producer::Hold& get_at(int index, int rows) const {
		return table_[index]->get_at<Producer::Hold>(rows);//copy
	}

	//���������ɂ̂ݎg�p�D���I����
	//IAocsData��Hold���Ă���Root�z���̃N���X�ł���Ή��ł�����
	template<class Producer> int create(Producer* producer,unsigned short capacity, const datatype::String& name = "unknown"){
		this->createdindex_++;
		this->table_[createdindex_] = new Tuple<core::event::EventBase>(capacity,Loki::Type2Type<Producer::Hold>(),name);
		return createdindex_ ;
	}

	//���������ɂ̂ݎg�p�D���I����
	//IAocsData��Hold���Ă���Root�z���̃N���X�ł���Ή��ł�����
	template<class Datatype> int create(Loki::Type2Type<Datatype>,unsigned short capacity, const datatype::String& name = "unknown"){
		this->createdindex_++;
		this->table_[createdindex_] = new Tuple<core::event::EventBase>(capacity,Loki::Type2Type<Datatype>(),name);
		return createdindex_ ;
	}
	//���������ɂ̂ݎg�p�D���I����
	//IAocsData��Hold���Ă���Root�z���̃N���X�ł���Ή��ł�����
	template<class Producer> int create(int id,unsigned short capacity, const datatype::String& name = "unknown"){
		this->createdindex_++;
		this->table_[createdindex_] = new Tuple<core::event::EventBase>(capacity,Loki::Type2Type<Producer::Hold>(),name);
		return createdindex_ ;
	}

	template<class Producer> void show(int index) const{
		table_[index]->print<Producer::Hold>();
	}
	// �w�肵���C���X�^���XID�����������^�v���ւ̃|�C���^���擾�i�e�����g���p�j
	Tuple<core::event::EventBase>* get_ptr(int index) ;
private:
	Tuple<core::event::EventBase>** table_;
};

//���ׂĂ̗�̍ŐV�f�[�^���Ȃ߂�C�e���[�^
class AocsDataPoolIterator : public interface::Iterator {
public:
	AocsDataPoolIterator(const AocsDataPool* pool) : pool_(pool), index_(0), rows_(0) {
		focusrow_(0);
	}
	virtual void init(){
		rows_ = 0;
		focusrow_(rows_);
	}
	virtual bool end(){
		if(pool_->is_created(rows_)) return false;
		else return true;
	}
	virtual void operator ++() { 
		index_ ++;
		if(index_ >= localstreamsize_){//���̗��
			rows_++;
			focusrow_(rows_);
		}
	}
	virtual double operator()() {
		return this->localstream_[index_] ;		
	}
private:
	void focusrow_(int row){
		if(!pool_->is_created(rows_)) return;
		const datatype::IAocsData* d = pool_->get(row);
		localstream_ = d->to_stream();
		localstreamsize_ = d->stream_length();
		index_ = 0;
	}
	const AocsDataPool* pool_;
	const double* localstream_;
	int localstreamsize_;
	int index_;
	int rows_;
};


//���ׂĂ̗�̍ŐV�f�[�^���Ȃ߂�C�e���[�^
class EventDataPoolIterator : public interface::Iterator {
public:
	EventDataPoolIterator(const EventDataPool* pool) : pool_(pool), index_(0), rows_(0) {
		focusrow_(0);
	}
	virtual void init(){
		rows_ = 0;
		focusrow_(rows_);
	}
	virtual bool end(){
		if(pool_->is_created(rows_)) return false;
		else return true;
	}
	virtual void operator ++() { 
		index_ ++;
		if(index_ >= localstreamsize_){//���̗��
			rows_++;
			focusrow_(rows_);
		}
	}
	virtual double operator()() {
		return 0;//not implemented yet	
	}
private:
	void focusrow_(int row){
		if(!pool_->is_created(rows_)) return;
		const core::event::EventBase* d = pool_->get(row);
		//d->
		index_ = 0;
	}
	const EventDataPool* pool_;
	//const double* localstream_;
	int localstreamsize_;
	int index_;
	int rows_;
};

} /* End of namespace stf::core::datapool */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_datapool_Datapool_h

