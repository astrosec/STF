/**************************************************/
/* IO Expander�ɂ��I2C�̃G�~�����[�V�����w�b�_   */
/* PRISM 2ndEM�p                                  */
/* Author:�c������                                */
/* Last updated: 07/09/11                         */
/**************************************************/
#ifndef __I2C_EMU_H__
#define __I2C_EMU_H__

#include "iodefine.h"
#include "ioexpander.h"

#define SCL_IN IOE_W_1_SCL  		//WAC1_SCL
#define SDA_IN IOE_W_1_SDA  		//WAC_1SDA
#define SCL_REL SCL_IN |= 1;        //SCL�����W�b�N�g��
#define SCL_PUL SCL_IN &= 0;        //SCL�����W�b�N�k��
#define SDA_REL SDA_IN |= 1;        //SDA�����W�b�N�g��
#define SDA_PUL SDA_IN &= 0;        //SDA�����W�b�N�k��

#define W2_SCL_IN 	IOE_W_2_SCL  	//WAC1_SCL
#define W2_SDA_IN 	IOE_W_2_SDA  	//WAC_1SDA
#define W2_SCL_REL 	W2_SCL_IN |= 1; //SCL�����W�b�N�g��
#define W2_SCL_PUL 	W2_SCL_IN &= 0; //SCL�����W�b�N�k��
#define W2_SDA_REL 	W2_SDA_IN |= 1; //SDA�����W�b�N�g��
#define W2_SDA_PUL 	W2_SDA_IN &= 0; //SDA�����W�b�N�k��

#define W3_SCL_IN 	IOE_W_3_SCL  	//WAC1_SCL
#define W3_SDA_IN 	IOE_W_3_SDA  	//WAC_1SDA
#define W3_SCL_REL 	W3_SCL_IN |= 1; //SCL�����W�b�N�g��
#define W3_SCL_PUL 	W3_SCL_IN &= 0; //SCL�����W�b�N�k��
#define W3_SDA_REL 	W3_SDA_IN |= 1; //SDA�����W�b�N�g��
#define W3_SDA_PUL 	W3_SDA_IN &= 0; //SDA�����W�b�N�k��

#define WAIT {volatile int i=30; while(i--);} //i2cCLK�����p
//#define SLAVE_ADDR 0x01;  //WAC�Ɉˑ�
//static unsigned char g_i2cbuff = 0x00;

 /* �ȉ��̊֐����ĂԂƂ��͊��荞�݂��֎~���� */
 
//�e�X�g�֐�//
void i2c_test(void);
//I2C���}�X�^�Ƃ��ď�����//
void i2c_init(void);
//�X�^�[�g�r�b�g���s//
void i2c_startbit(void);
//�X�g�b�v�r�b�g���s//
void i2c_stopbit(void);
//1byte���M//
signed int i2c_send_byte(unsigned char data);
//���M�Z�b�V����//
unsigned char i2c_write(unsigned char addr, unsigned char data);

//I2C���}�X�^�Ƃ��ď�����//
void w2_i2c_init(void);
//�X�^�[�g�r�b�g���s//
void w2_i2c_startbit(void);
//�X�g�b�v�r�b�g���s//
void w2_i2c_stopbit(void);
//1byte���M//
signed int w2_i2c_send_byte(unsigned char data);
//���M�Z�b�V����//
unsigned char w2_i2c_write(unsigned char addr, unsigned char data);

//I2C���}�X�^�Ƃ��ď�����//
void w3_i2c_init(void);
//�X�^�[�g�r�b�g���s//
void w3_i2c_startbit(void);
//�X�g�b�v�r�b�g���s//
void w3_i2c_stopbit(void);
//1byte���M//
signed int w3_i2c_send_byte(unsigned char data);
//���M�Z�b�V����//
unsigned char w3_i2c_write(unsigned char addr, unsigned char data);

#endif