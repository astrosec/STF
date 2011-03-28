/**************************************************/
/* IO Expander�ɂ��I2C�̃G�~�����[�V�����R�[�h   */
/* PRISM 2ndEM�p                                  */
/* Author:�c������                                */
/* Last updated: 07/09/11                         */
/**************************************************/
#include "ioexpander.h"
#include "i2c_emu.h"

#define	FALSE	0
#define TRUE	1

/******************************/
// �e�X�g�֐�                 //
/******************************/

void i2c_test(void)
{
	/*i2c������*/
	i2c_init();

	i2c_write( 0x11, 0x11);//��΂��A�G���[�o��
}

/*******************************/
// I2C���}�X�^�Ƃ��ď�����     //
// ��������̊֐��Ƃ��Ԃ��Ă�H//
/*******************************/

void i2c_init(void)
{
	 SCL_REL;
	 SDA_REL;
}

void w2_i2c_init(void)
{
	 W2_SCL_REL;
	 W2_SDA_REL;
}

void w3_i2c_init(void)
{
	 W3_SCL_REL;
	 W3_SDA_REL;
}

/***************************************************/
// �X�^�[�g�r�b�g���s�֐�                          //
// SCL�̓n�C�̏�Ԃ�SDA�����[�ɂ��邱�ƂŎ���      //
// SDA�܂���SCL�����łɃ��[�Ȃ�Α��̃}�X�^���g�p��//
/***************************************************/

void i2c_startbit(void)
{
	WAIT;
	//SCL��SDA���Е��ł����[�Ȃ�if����//
	if(!SCL_IN || !SDA_IN){    
	//�ȉ�SCL�����[�ɂ��Ă���SDA���n�C��//
		if(SCL_IN){
			SCL_PUL;           //���W�b�N�k��
			WAIT;
		}
		if(!SDA_IN){
			SDA_REL;           //���W�b�N�g��
			WAIT;
		}
		SCL_REL;               //���W�b�N�g��
		WAIT;
	}
	//�����Ƃ����W�b�N�g�ɂȂ�����ȉ��̏���//
	SDA_PUL;                   //���W�b�N�k��
	WAIT;
	SCL_PUL;                   //���W�b�N�k��
	WAIT;
	/* SCL = SDA = L */
}

void w2_i2c_startbit(void)
{
	WAIT;
	//SCL��SDA���Е��ł����[�Ȃ�if����//
	if(!W2_SCL_IN || !W2_SDA_IN){    
	//�ȉ�SCL�����[�ɂ��Ă���SDA���n�C��//
		if(W2_SCL_IN){
			W2_SCL_PUL;           //���W�b�N�k��
			WAIT;
		}
		if(!W2_SDA_IN){
			W2_SDA_REL;           //���W�b�N�g��
			WAIT;
		}
		W2_SCL_REL;               //���W�b�N�g��
		WAIT;
	}
	//�����Ƃ����W�b�N�g�ɂȂ�����ȉ��̏���//
	W2_SDA_PUL;                   //���W�b�N�k��
	WAIT;
	W2_SCL_PUL;                   //���W�b�N�k��
	WAIT;
	/* SCL = SDA = L */
}

void w3_i2c_startbit(void)
{
	WAIT;
	//SCL��SDA���Е��ł����[�Ȃ�if����//
	if(!W3_SCL_IN || !W3_SDA_IN){    
	//�ȉ�SCL�����[�ɂ��Ă���SDA���n�C��//
		if(W3_SCL_IN){
			W3_SCL_PUL;           //���W�b�N�k��
			WAIT;
		}
		if(!W3_SDA_IN){
			W3_SDA_REL;           //���W�b�N�g��
			WAIT;
		}
		W3_SCL_REL;               //���W�b�N�g��
		WAIT;
	}
	//�����Ƃ����W�b�N�g�ɂȂ�����ȉ��̏���//
	W3_SDA_PUL;                   //���W�b�N�k��
	WAIT;
	W3_SCL_PUL;                   //���W�b�N�k��
	WAIT;
	/* SCL = SDA = L */
}

/********************************************************/
// �X�g�b�v�r�b�g���s�֐�                               //
// �}�X�^��SCL�����[�̏�Ԃ�SDA���n�C�ɂ��ASCL���n�C�ɁB//
// ���̏��SDA���n�C�ɂ���ƃX�g�b�v�R���f�B�V�����B���B//
/********************************************************/

void i2c_stopbit(void)
{
	/* assume SCL = SDA =L*/
	WAIT;
	SCL_REL;
	WAIT;
	SDA_REL;
	WAIT;
	/* SCL = SDA = H */
}

void w2_i2c_stopbit(void)
{
	/* assume SCL = SDA =L*/
	WAIT;
	W2_SCL_REL;
	WAIT;
	W2_SDA_REL;
	WAIT;
	/* SCL = SDA = H */
}

void w3_i2c_stopbit(void)
{
	/* assume SCL = SDA =L*/
	WAIT;
	W3_SCL_REL;
	WAIT;
	W3_SDA_REL;
	WAIT;
	/* SCL = SDA = H */
}

/************************************************************/
// 1byte���M�֐�                                    �@      //
// �X���[�u��SCL�����[�Ɉ����ăE�F�C�g����������ԂŁA      //
// �A�h���X��8�r�b�g�ڂŎw�肳�ꂽ�]�������ŒʐM����������B//
// ���������������SCL�����[�ɂЂ��̂���߂�B              //
// ����ɂ��SCL�̓}�X�^������ł���悤�ɂȂ�A            //
// �}�X�^�����SCL�Ńf�[�^�]�����s����悤�ɂȂ�B          //
// �ʐM�͕K��SCL�����[�̂Ƃ���SDA���ω�����B               //
// data���ŏ�ʃr�b�g���珇��SDA�ɏ悹�A                    //
// SCL��8�N���b�N�ɂ�著�M�B                               //
// 9�N���b�N�ڂ�ACK�r�b�g����荞�ށB                       //
// input data                                               //
// output ack                                               //
/************************************************************/

signed int i2c_send_byte(unsigned char data)
{
	/* assume SCL = SDA = L */
	signed int ack;
	volatile int i;
	for(i = 0; i<8; i++){
		if(data & 0x80){  //��ʂ���1bit�Â�SDA�ɂ̂��ē]��
			SDA_REL;
		}
		else{
			SDA_PUL;
		}
			WAIT;
			WAIT;
			SCL_REL; //SCL���g�̏�Ԃ�SDA��ύX�����start��stop�ƂȂ�
			WAIT;
			WAIT;
		if(i != 7){
			data <<= 1;
		}
		SCL_PUL;
	}
	WAIT;
	WAIT;
	SDA_REL;
	SCL_REL;
	WAIT;
	WAIT;
	WAIT;
	/* while(SCL_IN == 0);*/ /* �X���[�u�ɂ��N���b�N�Ђ��̂΂� */
	ack = SDA_IN;
	WAIT;
	WAIT;
	WAIT;
	WAIT;
	SCL_PUL;
	SDA_PUL;               //���������ɂ��Ȃ��ƃ_������
	/* SCL = SDA = L */
	return ack;
}

signed int w2_i2c_send_byte(unsigned char data)
{
	/* assume SCL = SDA = L */
	signed int ack;
	volatile int i;
	for(i = 0; i<8; i++){
		if(data & 0x80){  //��ʂ���1bit�Â�SDA�ɂ̂��ē]��
			W2_SDA_REL;
		}
		else{
			W2_SDA_PUL;
		}
			WAIT;
			WAIT;
			W2_SCL_REL; //SCL���g�̏�Ԃ�SDA��ύX�����start��stop�ƂȂ�
			WAIT;
			WAIT;
		if(i != 7){
			data <<= 1;
		}
		W2_SCL_PUL;
	}
	WAIT;
	WAIT;
	W2_SDA_REL;
	W2_SCL_REL;
	WAIT;
	WAIT;
	WAIT;
	/* while(SCL_IN == 0);*/ /* �X���[�u�ɂ��N���b�N�Ђ��̂΂� */
	ack = W2_SDA_IN;
	WAIT;
	WAIT;
	WAIT;
	WAIT;
	W2_SCL_PUL;
	W2_SDA_PUL;               //���������ɂ��Ȃ��ƃ_������
	/* SCL = SDA = L */
	return ack;
}

signed int w3_i2c_send_byte(unsigned char data)
{
	/* assume SCL = SDA = L */
	signed int ack;
	volatile int i;
	for(i = 0; i<8; i++){
		if(data & 0x80){  //��ʂ���1bit�Â�SDA�ɂ̂��ē]��
			W3_SDA_REL;
		}
		else{
			W3_SDA_PUL;
		}
			WAIT;
			WAIT;
			W3_SCL_REL; //SCL���g�̏�Ԃ�SDA��ύX�����start��stop�ƂȂ�
			WAIT;
			WAIT;
		if(i != 7){
			data <<= 1;
		}
		W3_SCL_PUL;
	}
	WAIT;
	WAIT;
	W3_SDA_REL;
	W3_SCL_REL;
	WAIT;
	WAIT;
	WAIT;
	/* while(SCL_IN == 0);*/ /* �X���[�u�ɂ��N���b�N�Ђ��̂΂� */
	ack = W3_SDA_IN;
	WAIT;
	WAIT;
	WAIT;
	WAIT;
	W3_SCL_PUL;
	W3_SDA_PUL;               //���������ɂ��Ȃ��ƃ_������
	/* SCL = SDA = L */
	return ack;
}

/****************************************************/
// 1byte���M�Z�b�V�����֐�                          //
// addr�Ŏw�肳�ꂽ�X���[�u�A�h���X��               //
// data�Ɋi�[���ꂽ�f�[�^�𑗐M����B   //
// �r����NACK���Ԃ����Ƒ��M�����f����FALSE���A��B//
// �O���startbit��stopbit��z�u���邱�Ƃɒ��ӁB    //
// input addr data                                  //
// output T or F                                    //
/****************************************************/

unsigned char i2c_write(unsigned char addr, unsigned char data){ //����*data������

	i2c_startbit();

	if(i2c_send_byte(0x42) != 0){   //slave address
	//	return FALSE;
	}
	if(i2c_send_byte(addr) != 0){   //nack�Ȃ�false
	//	return FALSE;
	}
		if(i2c_send_byte(data) !=0){   //nack�Ȃ�false
		//	return FALSE;
		}
	
	i2c_stopbit();	
		
	return TRUE;
}

unsigned char w2_i2c_write(unsigned char addr, unsigned char data){ //����*data������

	w2_i2c_startbit();

	if(w2_i2c_send_byte(0x42) != 0){   //slave address
	//	return FALSE;
	}
	if(w2_i2c_send_byte(addr) != 0){   //nack�Ȃ�false
	//	return FALSE;
	}
	if(w2_i2c_send_byte(data) !=0){   //nack�Ȃ�false
	//	return FALSE;
	}
	
	w2_i2c_stopbit();	
		
	return TRUE;
}

unsigned char w3_i2c_write(unsigned char addr, unsigned char data){ //����*data������

	w3_i2c_startbit();

	if(w3_i2c_send_byte(0x42) != 0){   //slave address
	//	return FALSE;
	}
	if(w3_i2c_send_byte(addr) != 0){   //nack�Ȃ�false
	//	return FALSE;
	}
	if(w3_i2c_send_byte(data) !=0){   //nack�Ȃ�false
	//	return FALSE;
	}
	
	w3_i2c_stopbit();	
		
	return TRUE;
}