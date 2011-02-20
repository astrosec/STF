/**
 * @file   SatelliteFactory.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef factory_SatelliteFactory_h
#define factory_SatelliteFactory_h

#include "../GlobalObject.h"

namespace stf {
namespace factory {

template<class Env>
class SatelliteFactory {
public:
	SatelliteFactory(){}
	virtual ~SatelliteFactory(){}
	Global<Env>* create(){
		create_component();
		create_datapool();
		create_funcmanager();
		create_mode();
	    create_command();
		create_telemetry();
		create_controller();

		create_functor();
		create_dataupdates();
		create_switches();
		create_additional_hotspot();

		return return_created_object();
	}
protected:
	// �f�o�C�X�h���C�o�𐶐�����t�@�N�g��
	virtual void create_component() = 0;
	// �@�\�}�l�[�W���𐶐�����t�@�N�g��
	virtual void create_funcmanager() = 0;
	// ���[�h�𐶐�����t�@�N�g��
	virtual void create_mode() = 0;
	// �e���[�h�ɂ�����Control Strategy�𐶐�����t�@�N�g��
	virtual void create_controller() = 0;
	// Command�𐶐�����t�@�N�g��
	virtual void create_command() = 0;
	// �e���[�h�ɂ�����Telemetry Strategy�𐶐�����t�@�N�g��
	virtual void create_telemetry() = 0;
	// �e���[�h�ɂ�����Functor Strategy�𐶐�����t�@�N�g��
	virtual void create_functor() = 0;
	// �e���[�h�ɂ�����Update Strategy�𐶐�����t�@�N�g��
	virtual void create_dataupdates() = 0;
	// �e���[�h�ɂ�����Switch Strategy�𐶐�����t�@�N�g��
	virtual void create_switches() = 0;
	// �e���[�h�ɂ����郆�[�U�[��`��Strategy�𐶐�����t�@�N�g��
	virtual void create_additional_hotspot() = 0;
	// �f�[�^�v�[���ւ̐ڑ��𐶐�����t�@�N�g��
	virtual void create_datapool() = 0;
	// �������ꂽ�I�u�W�F�N�g���AGlobal�̃|�C���^�ŕԋp
	virtual Global<Env>* return_created_object() = 0;
};

} /* End of namespace stf::factory */
} /* End of namespace stf */


#endif // factory_SatelliteFactory_h