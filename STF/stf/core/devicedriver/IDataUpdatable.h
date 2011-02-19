#ifndef stf_core_devicedriver_IDataUpdatable_h
#define stf_core_devicedriver_IDataUpdatable_h


namespace stf {
namespace core {
namespace devicedriver {

/// �����I�Ƀf�[�^���擾�C���M����R���|�[�l���g�ɑ΂���C���^�[�t�F�[�X
class IDataUpdatable {
public:
	virtual void doUpdate()  = 0;
	virtual ~IDataUpdatable() { }
};

} /* End of namespace stf::core::component */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_IDataUpdatable_h
