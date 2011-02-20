/**
 * @file   GlobalObject.h
 * @brief  RTOS�Ƃ̃C���^�[�t�F�[�X�ƂȂ�C�q���A�v���P�[�V��������������I�u�W�F�N�g�Q�̊��N���X�D
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 * @todo   Singleton Pattern�̓K�p
 */
#ifndef stf_GlobalObject_h
#define stf_GlobalObject_h

#include <fstream>
#include "InstanceID.h"
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

template<class Env>
class Global{
public:
	//static Global<Env>& get_instance();//Environment���ƂɒP��̃C���X�^���X�݂̂𐶐�
	virtual const core::datapool::AocsDataPool* get_datapool() const = 0;
	virtual const core::datapool::EventDataPool* get_eventdatapool() const = 0;

	virtual const datatype::Time get_global_time() = 0;//�q����OBC�������擾
	virtual const datatype::DateTime get_global_datetime() = 0;//�q����RTC�������擾
	virtual const datatype::SatelliteModel get_satellitemodel() const = 0;//�q���̎��ʓ������f�����擾
	virtual datatype::List<core::manager::ManagerBase>* getFunctionManager() {return &(this->managers_);}

	virtual ~Global(){}//�f�X�g���N�^
	Global(){}//�R���X�g���N�^���֎~�i�V���O���g���p�^�[���j
	Global(const Global<Env>&);
	void operator=(const Global<Env>&);
	datatype::List<core::manager::ManagerBase> managers_;
};

} /* End of namespace stf */

#endif // stf_GlobalObject_h