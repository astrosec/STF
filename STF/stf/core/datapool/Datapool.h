/**
 * @file   Datapool.h
 * @brief  STF生成データにタイムタグを付加して格納するデータプール．
 *         データの配列を保持するTupleと，Tupleの配列を保持するデータプールによって
 *         テーブル形式のデータ構造を表現する．
 *
 A data pool that stores a time tag added to STF generated data.
  * By Tuple holding an array of data and a data pool holding an array of Tuples
  * Represents a table format data structure.
 * @author Taiga Nomi
 * @date   2011.02.16
 * @todo   EventDataPoolの運用，EventDataPoolIteratorの実装
 */
#ifndef stf_core_datapool_Datapool_h
#define stf_core_datapool_Datapool_h
#include"../../util/stfassert.h"
#include "../../RootObject.h"
#include "../../datatype/IAocsData.h"
#include "../../datatype/List.h"
#include "../../datatype/Time.h"
#include "../../datatype/String.h"
#include "../devicedriver/clock/ITimeClock.h"
#include "../../interface/Iterator.h"
#include "../../util/loki/TypeManip.h"
#include "../../util/loki/HierarchyGenerators.h"
#include "../../util/Trace.h"
#include "../event/Event.h"

namespace stf {
namespace core {
namespace event {
class EventBase;
}
namespace datapool {
//! 時刻とデータポインタのペアを一定要素数のリングバッファで保持する．
/*! データのポインタ配列を保持しており，データ追加時はBase型ではなく，キャストする型を指定する．
//A pair of time and data pointer is stored in a ring buffer with a fixed number of elements.
  It holds a pointer array of data, and when adding data, specify the type to cast, not the Base type.
	@tparam Base データの基底型
*/
template<class Base>
class Tuple
{
public:
	template <class T>
	Tuple(int capacity, Loki::Type2Type<T>, const datatype::String& name) : capacity_(capacity), index_(0), name_(name){
		stf_assert(capacity > 0);
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
		util::Trace trace(util::Trace::kDataPool, "set Tuple");
		index_ ++;
		index_ %= capacity_;
		*(static_cast<T*>(data_[index_])) = value;//copy
		time_[index_] = time;//copy
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
		stf_assert(index < capacity_); 

		return (data_)[index_]; 
	}

	const datatype::Time& get_time_at(int index) const{ stf_assert(index < capacity_); return time_[index]; }

	const datatype::String& name() const { return name_; }

private:
	int capacity_;
	int index_;
	Base** data_;
	datatype::String name_; //!< データベース名，デバッグ用 Database name, for debugging
	datatype::Time* time_; //!< data_と対応する時刻の配列  array of times corresponding to data_
};

//! Tupleを複数個保持するデータプールの基底クラス．
//Base class of data pool that holds multiple Tuples.
/*! 
*/
class DataPoolBase : public RootObject
{
public:
	DataPoolBase(): createdindex_(-1) , RootObject("DataPoolBase"){}
	~DataPoolBase(void){}
	const int rows () const{ return this->kMaxDataPoolRows; }
	bool is_created(int index) const{ 
		stf_assert( index < kMaxDataPoolRows && index >= 0); 
		if(index <= createdindex_) return true;
		else return false;
	}
protected:
	static const int kMaxDataPoolRows = 255;
	int createdindex_;
};

//イテレータの前方宣言  Forward declaration of iterator
class AocsDataPoolIterator;

//! IAocsDataのデータプール． Data pool of IAocsData.
/*! 
*/
class AocsDataPool : public DataPoolBase//: public RootObject
{
public:
	AocsDataPool();
	~AocsDataPool(void){}

	// 最新の値を元の型として取る
	//Take the latest value as the original type
	template<class Producer> typename Producer::Hold get(int index) const{
		return table_[index]->get<Producer::Hold>();//copy
	}

	const datatype::IAocsData* get(int rows) const;

	const datatype::IAocsData* get(int rows, int cols) const;

	template<class T>const T& get(int rows){
		return this->table_[rows]->get<T>();
	}

	// 最新の値を取る Take the latest value
	const datatype::Time& gettime(int index) const;

	const datatype::String& getname(int index) const;

	// 値をセット Set the value
	template<class Producer> void set(int index, const typename Producer::Hold& value){
		table_[index]->set<typename Producer::Hold>(this->clock_->get_time(), value);
	}

	template<class Producer> typename Producer::Hold& get_at(int index, int rows) const {
		return table_[index]->get_at<Producer::Hold>(rows);//copy
	}

	//初期化時にのみ使用．動的生成 Used only at initialization. Dynamic generation
	//IAocsDataをHoldしているRoot配下のクラスであれば何でも取れる
	//Any class under Root holding IAocsData can be taken
	template<class Producer> int create(Producer* producer, unsigned short capacity, const datatype::String& name = "unknown"){
		this->createdindex_++;
		this->table_[createdindex_] = new Tuple<datatype::IAocsData>(capacity, Loki::Type2Type<Producer::Hold>(), name);
		return createdindex_ ;
	}

	//初期化時にのみ使用．動的生成  Used only at initialization. Dynamic generation
	//IAocsDataをHoldしているRoot配下のクラスであれば何でも取れる Any class under Root holding IAocsData can be taken
	template<class Datatype> int create(Loki::Type2Type<Datatype>, unsigned short capacity, const datatype::String& name = "unknown"){
		this->createdindex_++;
		this->table_[createdindex_] = new Tuple<datatype::IAocsData>(capacity, Loki::Type2Type<Datatype>(), name);
		return createdindex_ ;
	}

	//初期化時にのみ使用．動的生成  Used only at initialization. Dynamic generation
	//IAocsDataをHoldしているRoot配下のクラスであれば何でも取れる  Any class under Root holding IAocsData can be taken
	template<class Producer> int create(int id, unsigned short capacity, const datatype::String& name = "unknown"){
		this->createdindex_++;
		this->table_[createdindex_] = new Tuple<datatype::IAocsData>(capacity, Loki::Type2Type<Producer::Hold>(), name);
		return createdindex_ ;
	}

	template<class Producer> void show(int index) const{
		table_[index]->print<Producer::Hold>();
	}

	// 指定したインスタンスIDが生成したタプルへのポインタを取得（テレメトリ用）
	//Get pointer to tuple generated by specified instance ID (for telemetry)
	Tuple<datatype::IAocsData>* get_ptr(int index) ;

private:
	Tuple<datatype::IAocsData>** table_;
};

//! Eventのデータプール．Data pool of Event.
/*! 
*/
class EventDataPool : public RootObject
{
public:
	typedef Loki::Tuple<TYPELIST_2( event::EventType, datatype::Time )> EventLog;

	EventDataPool() : RootObject("EventDataPool"), index_(-1)
	{
		for(int i = 0; i < kMaxEventDataCols; i++)
			Loki::Field<0>(tuple_[i]) = event::NoEvent;	
		this->eventdatapool_ = this;
	}

	~EventDataPool(void){}

	//! 最新のイベントを取得  Get the latest events
	event::EventType get() const{
		stf_assert(index_ >= 0);
		return Loki::Field<0>(tuple_[index_]);
	}

	event::EventType get(int index) const{
		stf_assert(index < kMaxEventDataCols );
		return Loki::Field<0>(tuple_[index]);
	}

	//! 最終イベント発生時刻を取得 Get last event occurrence time
	const datatype::Time& gettime() const {
		stf_assert(index_ >= 0);
		return Loki::Field<1>(tuple_[index_]);
	}

	const datatype::Time& gettime(int index) {
		stf_assert(index < kMaxEventDataCols );
		return Loki::Field<1>(tuple_[index]);
	}

	//! 指定したイベントの最終発生時刻を取得．無い場合はtimeの初期値を返却
	//Get the last occurrence time of the specified event. If it does not exist, the initial value of time is returned
	datatype::Time gettimeof(event::EventType value){
		int pt = index_;
		do{
			if(Loki::Field<0>(tuple_[pt]) == value) return Loki::Field<1>(tuple_[pt]);
			pt++;
			if(pt == kMaxEventDataCols) pt = 0;
		}while(pt != index_);
		datatype::Time t;
		return t;
	}

	//! 値をセット  Set the value
	void set(event::EventType value){
		index_ ++;
		if(index_ == kMaxEventDataCols) index_ = 0;
		Loki::Field<0>(tuple_[index_]) = value;
		Loki::Field<1>(tuple_[index_]) = this->clock_->get_time();
	}

	int rows() const { return kMaxEventDataCols; }

	int currentindex() const { return index_; }

private:
	static const int kMaxEventDataCols = 100;
	EventLog tuple_[kMaxEventDataCols];
	int index_;
};

//! AocsDataPoolの各列の最新データをなめるイテレータ．
//An iterator that licks the latest data in each column of AocsDataPool.
/*! 
*/
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
		if(index_ >= localstreamsize_){//次の列へ To next column
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

//! EventDataPoolの各列の最新データをなめるイテレータ．
//An iterator that licks the latest data in each column of EventDataPool.
/*! 
	@todo operator()の実装  Implementation of
*/
class EventDataPoolIterator : public interface::Iterator {
public:
	EventDataPoolIterator(const EventDataPool* pool) : pool_(pool) {
		startindex_ = index_ = pool_->currentindex();
	}
	virtual void init(){
		startindex_ = index_ = pool_->currentindex();
	}
	virtual bool end(){
		if(index_ == -1) return true;
		else return false;
	}
	virtual void operator ++() { 
		index_ ++;
		if(index_ == startindex_){//１周した  Made one lap
			index_ = -1;
		}
		if(index_ >= pool_->rows()){//末尾に達した  Reached the end
			index_ = 0;
		}
	}
	virtual double operator()() {
		return pool_->get(index_);
	}
private:
	const EventDataPool* pool_;
	int index_;
	int startindex_;
};

} /* End of namespace stf::core::datapool */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_datapool_Datapool_h

