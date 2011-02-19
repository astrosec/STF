/**
 * @file   Macros.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef Macros_h
#define Macros_h

//�ȒP�ȃ}�N���֐����L�q����D


// �R�s�[�R���X�g���N�^��=���Z�q�֐��𖳌��ɂ���}�N��
// ����̓N���X�� private: �錾�̒��Ŏg���ׂ����B
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&);               \
  void operator=(const TypeName&)



#endif // Macros_h