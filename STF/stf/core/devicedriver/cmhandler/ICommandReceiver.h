/**
 * @file   ICommandReceiver.h
 * @brief  ��M�@����R�}���h���󂯎��C������ԋp����f�o�C�X�̒��ۃC���^�[�t�F�[�X�D
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_devicedriver_cmhandler_ICommandReceiver_h
#define stf_core_devicedriver_cmhandler_ICommandReceiver_h

namespace stf {
namespace datatype {
class String;
}
namespace core {
namespace command {
class Command;
}
namespace devicedriver {
namespace cmhandler {

//! ��M�@����R�}���h���󂯎��C������ԋp����f�o�C�X�̒��ۃC���^�[�t�F�[�X�D
/*! 
*/
class ICommandReceiver {
public:
	//! �O���ʐM�@����R�}���h���󂯎��
    virtual void receive_command() = 0;
	//! �O���ʐM�@�ɃR�}���h�̉����𑗐M����D
	virtual void send_packet(const datatype::String& msg) = 0;
	//! �O���ʐM�@�ɃR�}���h�̉����𑗐M����D
	virtual void send_packet(int msg) = 0;
	//! �R�}���h���R�}���h�}�l�[�W�����ێ�����R�}���h���X�g�ɑ}������
	virtual void add_command(command::Command*) = 0;
    virtual ~ICommandReceiver() { }
};


} /* End of namespace stf::core::devicedriver::cmhandler */
} /* End of namespace stf::core::devicedriver */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_cmhandler_ICommandReceiver_h
