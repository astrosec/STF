/**
 * @file   IOPort.h
 * @brief  他機器との接続を型に基づいて行うための入出力ポート．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_devicedriver_IOPort_h
#define stf_core_devicedriver_IOPort_h

#include "../../util/loki/HierarchyGenerators.h"
#include "../../datatype/Time.h"

namespace stf {
namespace core {
namespace devicedriver {

template<class T> struct InputPort;

//! データの出力を表明するポート．
/*! 
	@tparam T   出力する型．
*/	
template<class T>
struct OutputPort {
	//! コンストラクタ．ポートのポインタを初期化 //Port that asserts data output.
	OutputPort() : nextholder_(0) {}

	//! get_in_bodyframe関数から呼び出される，データの更新を行う関数．
	/*! OutputPortを継承した具象クラスは各々の更新ルーチンを実装しなければならない．本来ならこれは純粋仮想関数としておくべきだが，
	 *  OutputPortsが使用するLokiのFieldヘルパは抽象クラスを扱えない．そのため，ここではstf_assert(0)を実行する関数を実装し，
	 *  派生クラス側での未実装をコンパイル時でなく，実行時に検出する仕様としている．
	 */

	//! Function that updates data, called from get_in_bodyframe function.
//A concrete class that inherits /*! OutputPort must implement each update routine. Originally this should be a pure virtual function,
//* Loki's Field helper used by OutputPorts cannot handle abstract classes. Therefore, here we implement a function that executes stf_assert(0),
//* The specification is to detect unimplemented on the derived class side at runtime, not at compile time.
//*/
	virtual void do_compute(const datatype::Time& t){
		//util::cout << "do_compute must be implemented" << util::endl;
		stf_assert(0);
	}

	//! データの取得を行う関数． Function to get data
	virtual const T& get_value(const datatype::Time& t){ do_compute(t); return value_; }

	//! データの設定を行う関数．Function to set data
	virtual void set_value(const T& value){ value_ = value; }

	//! データの最終更新時刻を取得する関数．Function to get the last update time of data
	const datatype::Time& get_lastupdate() const{ return last_update_;}

	//! 機体座標系における取得値  Acquired value in the aircraft coordinate system
	T value_;

	//! 接続された入力ポート  Connected input port
	InputPort<T>* nextholder_;

	//! value_の最終更新時刻  time of last update of value_
	datatype::Time last_update_;
};

//! データの入力を表明するポート．Port that asserts data entry
/*! 
	@tparam T   入力する型． Type to enter
*/	
template<class T>
struct InputPort {
	//! コンストラクタ．ポートのポインタを初期化．constructor. Initialize port pointer
	InputPort() : prevholder_(0) {}

	//! 双方向のリンクリストを形成することで，出力ポートとの接続を確立する．
	//Establishes a connection with the output port by forming a bidirectional linked list
	virtual void connect_source_(OutputPort<T>* outputport) { 
		prevholder_ = outputport; 
		prevholder_->nextholder_ = this;
	}

	//! 接続された出力ポート
	//Connected output port
	OutputPort<T>* prevholder_;
};

//! 入力ポートを纏め，インターフェースを提供するクラス．
//A class that collects input ports and provides an interface
/*! 
	@tparam TList   入力ポート群．LokiのTypeListで表現する
	//Input port group. Express with Loki's TypeList
*/	
template<class TList>
class InputPorts : public Loki::GenScatterHierarchy<TList, core::devicedriver::InputPort>{
public:
	//! i番目の入力ポートに，出力ポートを持ったコンポーネントを接続する．
	//Connect a component with an output port to the i-th input port
	template<int i, class T> 
	void connect_source(T* outputport) {
		return Loki::Field<i>(*this).connect_source_(outputport); 
	}

	//! i番目の入力ポートを取得する．
	//Get the i-th input port.
	template<int i, class T>
	InputPort<T>& inputport() {
		return Loki::Field<i>(*this);
	}

	//! i番目の入力ポートに接続された出力ポートを取得する．何も接続されていないポートに対して実行した場合の動作は未定義．
	//Get the output port connected to the i-th input port. 
	//The behavior when executed for a port to which nothing is connected is undefined.
	template<int i, class T>
	OutputPort<T>& source(){
		return *(Loki::Field<i>(*this).prevholder_);
	}

	//! i番目の入力ポートに接続された出力ポートの，最終更新時刻を取得する．
	//Gets the last update time of the output port connected to the i-th input port
	template<int i>
	const datatype::Time& get_lastinput() {
		return Loki::Field<i>(*this).prevholder_->last_update_;
	}

	//! i番目の入力ポートに出力ポートが接続しているかを取得．
	//Get whether the output port is connected to the i-th input port.
	template<int i>
	bool input_isconnected() {
		if(Loki::Field<i>(*this).prevholder_ == 0) return false;
		else return true;
	}
};

//! 出力ポートを纏め，インターフェースを提供するクラス．
/*! //A class that collects output ports and provides an interface.
	@tparam TList   出力ポート群．LokiのTypeListで表現する
	//Output port group. Express with Loki's TypeList
*/	
template<class TList>
class OutputPorts : public Loki::GenScatterHierarchy<TList, OutputPort>{
public:
	//! 伝搬関数のデフォルト実装．（何もしない）
	//Default implementation of propagator. (do nothing)
	virtual void do_compute(const datatype::Time& t){}

	//! i番目の出力ポートから現在の値を伝搬無しで取得する．
	//Get the current value from the i-th output port without propagation.
	template<int i, class T>
	const T& get() const{	
		return Loki::Field<i>(*this).value_;
	}

	//! i番目の出力ポートを取得する．
	//get the i th output port
	template<int i, class T>
	OutputPort<T>& outputport() {
		return Loki::Field<i>(*this);
	}

	//! i番目の出力ポートの，最終更新時刻を取得する．
	//Get the last update time of the i-th output port
	template<int i>
	const datatype::Time& getLastOutputtime() {	
		return Loki::Field<i>(*this).get_lastupdate();
	}

	//! i番目の出力ポートの，最終更新時刻を設定する．
	//Get the last update time of the i-th output port
	template<int i>
	void setLastOutputtime(const datatype::Time& time){
		Loki::Field<i>(*this).last_update_ = time;
	}

	//! i番目の出力ポートに入力ポートが接続しているかを取得．
	//Get whether the input port is connected to the i-th output port
	template<int i>
	bool output_isconnected() {
		if(Loki::Field<i>(*this).nextholder_ == 0) return false;
		else return true;
	}
};


} /* End of namespace stf::core::component */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_IOPort_h