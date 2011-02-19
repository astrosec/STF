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
		createComponent();
		createDataPoolConnection();
		createFunctionManager();
		createMode();
	    createCommandHotSpot();
		createTelemetryHotSpot();
		createControlHotSpot();

		createFunctorHotSpot();
		createDataUpdateHotSpot();
		createSwitchHotSpot();
		createAdditionalHotSpot();

		return returnCreatedObject();
	}
protected:
	// �f�o�C�X�h���C�o�𐶐�����t�@�N�g��
	virtual void createComponent() = 0;
	// �@�\�}�l�[�W���𐶐�����t�@�N�g��
	virtual void createFunctionManager() = 0;
	// ���[�h�𐶐�����t�@�N�g��
	virtual void createMode() = 0;
	// �e���[�h�ɂ�����Control Strategy�𐶐�����t�@�N�g��
	virtual void createControlHotSpot() = 0;
	// Command�𐶐�����t�@�N�g��
	virtual void createCommandHotSpot() = 0;
	// �e���[�h�ɂ�����Telemetry Strategy�𐶐�����t�@�N�g��
	virtual void createTelemetryHotSpot() = 0;
	// �e���[�h�ɂ�����Functor Strategy�𐶐�����t�@�N�g��
	virtual void createFunctorHotSpot() = 0;
	// �e���[�h�ɂ�����Update Strategy�𐶐�����t�@�N�g��
	virtual void createDataUpdateHotSpot() = 0;
	// �e���[�h�ɂ�����Switch Strategy�𐶐�����t�@�N�g��
	virtual void createSwitchHotSpot() = 0;
	// �e���[�h�ɂ����郆�[�U�[��`��Strategy�𐶐�����t�@�N�g��
	virtual void createAdditionalHotSpot() = 0;
	// �f�[�^�v�[���ւ̐ڑ��𐶐�����t�@�N�g��
	virtual void createDataPoolConnection() = 0;
	// �������ꂽ�I�u�W�F�N�g���AGlobal�̃|�C���^�ŕԋp
	virtual Global<Env>* returnCreatedObject() = 0;
};

} /* End of namespace stf::factory */
} /* End of namespace stf */


#endif // factory_SatelliteFactory_h