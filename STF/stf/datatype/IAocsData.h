/**
 * @file   IAocsData.h
 * @brief  AOCS�g�p�n��̃f�[�^���ʂ̒��ۃC���^�[�t�F�[�X�D
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_datatype_IAocsData_h
#define stf_datatype_IAocsData_h

#include "../interface/ITelemetable.h"

namespace stf { 
namespace datatype {

//! AOCS�g�p�n��̃f�[�^���ʂ̒��ۃC���^�[�t�F�[�X�D
/*! */
class IAocsData : public interface::ITelemetable{
public:
	virtual void normalize() = 0;
	virtual void reset() = 0;
    virtual ~IAocsData() { }
};

} /* End of namespace stf::datatype */
} /* End of namespace stf */

#endif // stf_datatype_IAocsData_h
