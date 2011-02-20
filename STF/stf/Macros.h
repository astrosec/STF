/**
 * @file   Macros.h
 * @brief  STF�S�̂Ŏg�p����ȒP�ȃ}�N���֐����L�q����D
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef Macros_h
#define Macros_h


// �R�s�[�R���X�g���N�^��=���Z�q�֐��𖳌��ɂ���}�N��
// ����̓N���X�� private: �錾�̒��Ŏg���ׂ����B
// from: google C++ coding styles
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&);               \
  void operator=(const TypeName&)

#define DISALLOW_COPY_AND_ASSIGN_1(TypeName,T1) \
  TypeName(const TypeName<T1>&);                \
  void operator=(const TypeName<T1>&)

#define DISALLOW_COPY_AND_ASSIGN_2(TypeName,T1,T2) \
  TypeName(const TypeName<T1,T2>&);                \
  void operator=(const TypeName<T1,T2>&)

#define DISALLOW_COPY_AND_ASSIGN_3(TypeName,T1,T2,T3) \
  TypeName(const TypeName<T1,T2,T3>&);                \
  void operator=(const TypeName<T1,T2,T3>&)

#define DISALLOW_COPY_AND_ASSIGN_4(TypeName,T1,T2,T3,T4) \
  TypeName(const TypeName<T1,T2,T3,T4>&);                \
  void operator=(const TypeName<T1,T2,T3,T4>&)


#endif // Macros_h