/**
 * @file   IEnabable.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_IEnabable_h
#define stf_core_IEnabable_h

namespace stf {
namespace core {
//CPU�ɂ��d���̃I���I�t���䂪�\�ȃR���|�[�l���g�ɑ΂���C���^�[�t�F�[�X�D
class IEnabable {
public:
    virtual void enable()  = 0;
    virtual void disable()  = 0;
	virtual bool is_enable () const = 0;
    virtual ~IEnabable() { }
};

} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_IEnabable_h
