/**
 * @file   IEnabable.h
 * @brief  �L�����E���������䂪�\�ȃR���|�[�l���g�ɑ΂���C���^�[�t�F�[�X�D
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_interface_IEnabable_h
#define stf_interface_IEnabable_h

namespace stf {
namespace interface {

class IEnabable {
public:
    virtual void enable()  = 0;
    virtual void disable()  = 0;
	virtual bool is_enable () const = 0;
    virtual ~IEnabable() { }
};

} /* End of namespace stf::interface */
} /* End of namespace stf */

#endif // stf_interface_IEnabable_h
