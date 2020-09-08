/**
 * @file   Trace.h
 * @brief  STFの内部状態を外部ファイルに書き出すためのトレースオブジェクト．
 //A trace object for writing the internal state of STF to an external file.
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_util_Trace_h
#define stf_util_Trace_h

#include "Cout.h"
#include "../datatype/String.h"

namespace stf { 
namespace util {

//! 標準出力のラッパ．Standard output wrapper.
/*! 
	STFの内部状態を外部ファイルに書き出すためのトレースオブジェクト．
    種別ごとにデバッグ出力のオン・オフが選択できる．
    デフォルトでは全てのログ出力が無効化されているので，main関数などで
    必要なデバッグログに対応するTraceIdをenable関数で有効化する．
    出力先はOstream::clogの定義に依存する．

	使用側は必要な関数スコープでTraceオブジェクトをインスタンス化し，
	さらに途中で重要なイベントがあれば追加で記録する．
	スコープを抜けるとともにデストラクタが呼ばれ，スコープでの記録が完了する．

	デバッグ無効時の動作速度を優先した実装となっているが，
	単純で多数回呼び出される関数に埋め込むとコンストラクタ・デストラクタ呼び出しに起因するパフォーマンス低下を招く恐れがある．
	

A trace object for writing the internal state of STF to an external file.
     Debug output can be turned on/off for each type.
     By default, all log output is disabled, so in main function etc.
     Enable the TraceId corresponding to the required debug log with the enable function.
     The output destination depends on the definition of Ostream::clog.

The consumer instantiates a Trace object with the required function scope,
If there are any important events on the way, they will be recorded additionally.
When leaving the scope, the destructor is called and the recording in the scope is completed.

Although it is implemented with priority on the operation speed when debugging is disabled,
If you embed it in a simple function that is called many times, there is a risk of performance degradation due to the constructor/destructor call.

　	@code
	ModeManager::run(){
		util::Trace trace(util::Trace::kManager, "run ModeManager");
		...
		trace.debug("some more information");
		...
	}
	@endcode

	@code
	int main(void){
		stf::util::Trace::enable(stf::util::Trace::kManager); //機能マネージャに関するトレースログを有効化 Enable trace log for Feature Manager
		stf::util::Trace::enable(stf::util::Trace::kControlBlock); //姿勢制御ブロックに関するトレースログを有効化 Enable trace log for attitude control block
		//それ以外のログは取らない No other logs are taken
	}
	@endcode
*/
class Trace {
public:
	//! トレースログの種類を識別するための列挙体．Enumeration for identifying the type of trace log
	enum TraceId{
		kManager = 0,//!< 機能マネージャ Function manager
		kControlBlock = 1,//!< 姿勢制御ブロック Attitude control block
		kCommand = 2,//!< コマンド処理 Command processing
		kDataPool = 3,//!< データプール書き込み Data pool write
		kEvent = 4,//!< イベント  Event
	};

	//! コンストラクタ．constructor
	/*!
		@param id   記録するトレースの種類． The type of trace to record.
		@param name トレースの名前．（関数名など）The name of the trace. (Function name, etc.)
	*/
	Trace(TraceId id, const char* name) : function_name_(name), id_(-1){
		if(this->active_table_[id]){
			id_ = id;
			util::clog << id_ 
				<< ", begin, " 
				<< name 
				<< util::endl;
		}
	}

	//! コンストラクタ．
	/*!
		@param id   記録するトレースの種類．
		@param name トレースの名前．（関数名など）
	*/
	Trace(TraceId id, const datatype::String& name) : function_name_(0), id_(-1){
		if(this->active_table_[id]){
			id_ = id;
			function_name_ = name.to_char();
			util::clog << id_ << ", begin, " << name << util::endl;
		}
	}

	~Trace() {
		if(id_ != -1){
			util::clog << id_ << ", end, " << function_name_ << util::endl;
		}
	}

	//! 関数内部で生じたイベントのログ．
	//Log of events that occurred inside the function.
	/*!
		@param message 追加で記録する処理の名称．
		@param message Name of the process to record additionally
	*/
	template<typename T>
	void debug(T message){
		if(id_ != -1){
			util::clog << id_ << ", do, " << message << util::endl;
		}
	}
		
	//! 関数内部で生じたイベントのログ．
	//Log of events that occurred inside the function
	/*!
		@param message 追加で記録する処理の名称．
		//@param message Name of the process to record additionally.
	*/
	void debug(const datatype::String& message){
		if(id_ != -1){
			util::clog << id_ << ", do, " << message.to_char() << util::endl;
		}
	}

	//! トレースフラグの有効化．この関数で明示的に有効化しないフラグはすべて無効．
	//Enable trace flag. All flags that are not explicitly enabled by this function are invalid. ．
	/*!
		@param id 有効化するトレースの種別．
		//The type of trace to activate. ．
	*/
	static void enable(TraceId id){
		active_table_[id] = true;
	}
private:
	static bool active_table_[5];
	int id_;
	const char* function_name_;
};



} /* End of namespace stf::util */
} /* End of namespace stf */

#endif // stf_util_Trace_h
