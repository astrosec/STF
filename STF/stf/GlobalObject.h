/**
 * @file   GlobalObject.h
 * @brief  RTOSとのインターフェースとなる，衛星アプリケーションが生成するオブジェクト群の基底クラス．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_GlobalObject_h
#define stf_GlobalObject_h

#include <fstream>
#include "datatype/List.h"
#include "datatype/Time.h"
#include "datatype/DateTime.h"
#include "datatype/SatelliteModel.h"

namespace stf {
namespace core {
namespace datapool {
class AocsDataPool;
class EventDataPool;
}
namespace manager {
class ManagerBase;
}
}
}

namespace stf {

using namespace core;

//! RTOSとのインターフェースとなる，衛星アプリケーションが生成するオブジェクト群の基底クラス．
//Base class for objects that satellite applications generate that interface with
/*! 
	@tparam Env アプリケーションの環境クラス． Environment class of application.
*/
template<class Env>
class Global{
public:
	typedef Env Environment;//!< 環境クラス．Environmental class

	//! Aocsデータプールのハンドラを取得． Get datapool handler
	virtual const core::datapool::AocsDataPool* get_datapool() const = 0;

	//! Eventデータプールのハンドラを取得．Get datapool handler
	virtual const core::datapool::EventDataPool* get_eventdatapool() const = 0;

	//! 衛星のOBC時刻を取得 Get satellite OBC time
	virtual const datatype::Time get_global_time() = 0;

	//! 衛星のRTC時刻を取得 Get satellite RTC time
	virtual const datatype::DateTime get_global_datetime() = 0;

	//! 衛星の質量特性モデルを取得 Acquires satellite mass characteristics model
	virtual const datatype::SatelliteModel get_satellitemodel() const = 0;

	//! 衛星の機能マネージャをリスト形式で取得 Get satellite feature manager in list format
	virtual datatype::List<core::manager::ManagerBase>* get_function_manager() {return &(this->managers_);}

	//! 衛星の機能マネージャを追加 Added satellite function manager
	void add_function_manager(core::manager::ManagerBase* manager){ this->managers_.add(*manager); }

	virtual ~Global(){}//デストラクタ Destructor

protected:
	Global(){}
	datatype::List<core::manager::ManagerBase> managers_;

private:
	Global(const Global<Env>&);
	void operator=(const Global<Env>&);
};

} /* End of namespace stf */

#endif // stf_GlobalObject_h