/**
 * @file   debuglogger.h
 * @brief  �e�����n���h���̃f�o�b�O�p�N���X�D
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_devicedriver_tmhandler_DebugLogger_h
#define stf_core_devicedriver_tmhandler_DebugLogger_h

#include <fstream>

//#include <interface/ITelemetryStoragable.h>
#include "../../../datatype/String.h"
#include "ITelemetryStoragable.h"

namespace stf {
namespace core {
namespace devicedriver {
namespace tmhandler {

//! �e�����n���h���̃f�o�b�O�p�N���X�D
/*! 
	�e�����g�������L�X�g���[�W�ɕۑ�������C���M�@�ɑ��o��������
	�w�肳�ꂽ�t�@�C���֏����o���f�o�b�O�p�̃e�����g���n���h���D
*/
class DebugLogger : virtual public ITelemetryStoragable{
public:
    DebugLogger(const std::string &filename, bool console_out);
    DebugLogger();
    virtual ~DebugLogger();
    void logging(int value, int address);
    virtual void logging(double value, int address);
    virtual void logging(datatype::String value, int address);
    virtual ITelemetryStoragable &operator <<(int value);
    virtual ITelemetryStoragable &operator <<(double value);
    ITelemetryStoragable &operator <<(const char* value);
    virtual ITelemetryStoragable &endl();
 private:
    std::ofstream *ofs_;
    bool console_out_;
};
} /* End of namespace stf::core::devicedriver::tmhandler */
} /* End of namespace stf::core::devicedriver */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_tmhandler_DebugLogger_h
