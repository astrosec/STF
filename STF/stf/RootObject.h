/**
 * @file   RootObject.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef RootObject_h
#define RootObject_h

#include "InstanceID.h"
#include "datatype/String.h"
#include "Macros.h"

namespace stf {
namespace datatype {
class Time;
class IAocsData;
}
namespace core {
namespace event {
class EventBase;
}
namespace devicedriver {
namespace clock {
class ITimeClock;
}
}
namespace datapool {
class AocsDataPool;
class EventDataPool;
}
}
// ���l�^���������S�N���X�̊�{�ƂȂ�N���X�D
// string�^�Ŗ��O��ێ����Ă��邪�C�ŏI�I�ɂ̓T�C�Y�̖��ʂȂ̂ō폜�H
class RootObject {
public:
	RootObject(int instance_id, const datatype::String& name);
	int instance_id() const{ return instance_id_; }
	virtual ~RootObject(){}
	virtual int get_datapoolKey() const;
protected:
    int oid_;
	int instance_id_;
	datatype::String name_;
    static int last_oid_;
	static core::devicedriver::clock::ITimeClock* clock_;
	//�ϑ��l���i�[�����f�[�^�x�[�X�C���f�b�N�X�D
	int datapool_hold_index_;
	core::datapool::AocsDataPool* datapool_;
private:
    RootObject();
	DISALLOW_COPY_AND_ASSIGN(RootObject);
};

} /* End of namespace stf */

#endif // RootObject_h
