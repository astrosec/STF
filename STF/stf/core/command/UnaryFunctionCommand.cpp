/**
 * @file   UnaryFunctionCommand.cpp
 * @brief  �P�����̃t�@���N�^�⃁���o�֐����N������R�}���h�D
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#include "UnaryFunctionCommand.h"

namespace stf {
namespace core {
namespace command {

//! �R�}���h������params�̑��v�f�ɒu��������D
template<>
void UnaryFunctorCommand<int>::init(int* params, int paramsize){
	if(paramsize >= 1)
		this->arg_ = params[0];//
}


} /* End of namespace stf::core::command */
} /* End of namespace stf::core */
} /* End of namespace stf */