#ifndef stf_core_event_CommandEvent_h
#define stf_core_event_CommandEvent_h
#include "EventBase.h"

namespace stf {
namespace core {
namespace mode {
class ModeBase;
}
namespace manager {
class CommandManagerBase;
}
namespace event {
	//for test
class CommandEvent : public EventBase{
public:
	typedef manager::CommandManagerBase SubjectClass; 
	typedef mode::ModeBase Target;
	CommandEvent() : EventBase("CommandEvent"){}
	virtual ~CommandEvent(){}
	virtual int instance_id(){ return ID_COMMANDEVENT; }
private:

};

} /* End of namespace stf::core::event */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_event_CommandEvent_h
