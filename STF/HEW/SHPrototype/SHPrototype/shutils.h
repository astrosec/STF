/****************************************************************
sh_7045.h
Copyright (c) Kosaka Lab CS TNCT

���̃C���N���[�h�t�@�C����H8/3048�p�t�@�C�������~���ɂ���
2003�N�x�������R���N�C�i�R����̋��͂ł܂Ƃ߂����̂ł���B
28 Jun 2006 h8-01.h  ���� chkgetSCI1�̃^�C�~���O�C��
 4 Dec 2003 h8-01.h  ����C�R���C�i�R

�y�P�zSCI ch1 �֌W
void initSCI1()
 SCI-ch1�̏������@38400baud, Ascnc, 8bit , NoParity, stop1

short int getCharSCI1()
 SCI-ch1����1byte���̓R�[�h�B�G���[�������-2���߂�B
short int chkgetCharSCI1()
 SCI-ch1���������C��M�f�[�^�������1byte���̓R�[�h���߂�B
 �Ȃ����-1���C���s�����-2���߂�B
short int getIntSCI1(char prompt[])
 SCI-ch1����v�����v�g�t�ŁCshort int�̒l���󂯎��B
 ������10�i���܂���16�i�����󂯕t����B16�i����0x�Ŏn�܂�

void putCharSCI1(char c)
 SCI-ch1��1�o�C�g�o�͂���B
void putStringSCI1(char *str)
 SCI-ch1�ɕ�������o�͂���B
void SCI1_printf(char *format,...)
  �֐�printf��SCI��
  �y�ʉ��̂��߃G���[�����͂Ȃ��̂Ō����w��̏ꍇ�͒���
  �Ή�����
  %d   : [int] integer with sign. '%d','%4d','%-4d', and '%04d' are available
  %ld  : explicit [long int]  '%ld','%9ld','%-9ld', and '%09ld' are available
  %u   : [unsigbed int] unsigned integer.
            '%u','%4u','%-4u', and '%04u' are available
  %lu  : explicit [unsigned long int]
            '%lu','%9lu','%-9lu', and '%09lu' are available
  %x   : [unsigned int] in Hex  '%x','%4x','%-4x', and '%04x' are available
  %lx  : explicit [unsigned long int] in Hex  
            '%lx','%8lx','%-8lx', and '%08lx' are available
  %o   : [unsigned int] in Oct  '%o','%4o','%-4o', and '%04o' are available
  %lo  : explicit [unsigned long int] in Oct  
            '%lo','%8lo','%-8lo', and '%08lo' are available
  %b   : [unsigned int] in Bin  '%b','%8b','%-8b', and '%08b' are available
  %lb  : explicit [unsigned long int] in Bin  
            '%lb','%8lb','%-8lb', and '%08lb' are available
  %c   : char
  %s   : string %20s %-20s are available

�y�Q�z�}�U�[�{�[�h�֌W
void initLed()
 LED�̏�����
void turnOnLed(short int number)
 LED�̓_���@number��LED�ԍ���0�܂���1���w�肷��
void turnOffLed(short int number)
 LED�̏����@number��LED�ԍ���0�܂���1���w�肷��

void initPushSW(void)
 �����{�^���X�C�b�`�̏�����
short int getPushSW(void)
 �����{�^���X�C�b�`�̎擾�B
 �����{�^���X�C�b�`�̏󋵂͑�0�Ƒ�2�r�b�g�Ɍ����B
short int checkPushSW(short int number)
 push sw 0,1�̏�Ԃ𒲂ׂ�@number:0 or 1
 ������Ă�����1�A�����łȂ�������0��Ԃ�

void init4BitSW(void)
 4�r�b�g�X�C�b�`�̏�����
short int get4BitSW(void)
 4�r�b�g�X�C�b�`�̎擾�@�������|�[�g��ǂݍ��݁C�r�b�g���]�̂݁B
 4�r�b�g�X�C�b�`�̏󋵂͑�0-��3�r�b�g�Ɍ����B
short int check4BitSW(short int number)
 4bitsw 0,1,2,3�̏�Ԃ𒲂ׂ�@number:0,1,2,or 3
 ON�Ȃ�1�A�����łȂ�������0��Ԃ�

�y�R�z�^�C�~���O���荞��
void initCMTInt(unsigned long int period,int ch,int intLebel)
 �R���y�A�}�b�`�^�C�}�ɂ��^�C�}���荞�݂̏����� 
 ���荞�݊Ԋu�͈���peiod�ŒP�ʂ̓�sec�ł��� 
 0<period<1170104 �Ȃ̂ōŒ�1.170104sec�܂ŉ\ 
 �`�����l�����Q����̂ł�ch��0,1�̂ǂ��炩��I�� 
 ���荞�݃��x��intLebel��1�`15�ɂ��� 
void startCMT0(void)
 �R���y�A�}�b�`�^�C�}0�X�^�[�g
void stopCMT0(void)
 �R���y�A�}�b�`�^�C�}0�X�g�b�v
void clearCMFlag0(void)
 �R���y�A�}�b�`�t���b�O0�N���A (���荞�݃��[�`�����ŌĂяo������)
void startCMT1(void)
 �R���y�A�}�b�`�^�C�}1�X�^�[�g
void stopCMT1(void)
 �R���y�A�}�b�`�^�C�}1�X�g�b�v
void clearCMFlag1(void)
 �R���y�A�}�b�`�t���b�O1�N���A (���荞�݃��[�`�����ŌĂяo������)

****************************************************************/
#include"7040S.h"
#include<stdarg.h>
void setIntMask(int mask);
int getIntMask(void);

/* ------------------------------------------------- */
/* SCI1 INITIALIZATION fixed baud at 38400           */
/* ------------------------------------------------- */
void initSCI1()
{
	int i;
	PFC.PACRL2.BIT.PA4MD = 1;/* 0:PA4, 1:TXD1 */
	PFC.PACRL2.BIT.PA3MD = 1;/* 0:PA3, 1:RXD1 */
	SCI1.SCR.BYTE = 0;       /* clear all flags */
	SCI1.SCR.BYTE = 0;       /* clear all flags */
	                  /* 2400-38400baud are available at n=0(cks1=0,cks2=0) */
	SCI1.SMR.BYTE = 0;       /* Ascnc, 8bit , NoParity, stop1, 1/1 */
	SCI1.BRR = 22;	         /* 38400baud (CPU=28.6MHz) */
	for(i=0;i<1000000;i++);      /* wait more than 1bit time */
	SCI1.SCR.BYTE = 0x30;    /* scr = 0011 0000 (TE=1,RE=1) */
	return;
}

/* ------------------------------------------------- */
/* GET BYTE FROM SCI1 */
/* ------------------------------------------------- */
short int getCharSCI1()
/* return value 0x00-0xFF:received data */
/*              -2(0xFFFE):error */
{
	short int flags,recdata;
	do {
		flags = SCI1.SSR.BYTE;
		if (flags&0x38) {/* error */
			SCI1.SSR.BIT.RDRF = 0;
			SCI1.SSR.BIT.ORER = 0;
			SCI1.SSR.BIT.FER = 0;
			SCI1.SSR.BIT.PER = 0;
			return -2;
		}
		if (flags&0x40) {/* normally received one data */
			SCI1.SSR.BIT.RDRF = 0;
			recdata=SCI1.RDR;
			return recdata;
		}
	} while (1);
}

/* ------------------------------------------------- */
/* CHECK SCI BUFFER AND GET DATA */
/* ------------------------------------------------- */
short int chkgetCharSCI1()
/* return value -1(0xFFFF):no received data  */
/*              0x00-0xFF:received data */
/*              -2(0xFFFE):error */
{
	short int flags,recdata;
	flags = SCI1.SSR.BYTE;
	if (flags&0x38) {/* error */
		SCI1.SSR.BIT.RDRF = 0;
		SCI1.SSR.BIT.ORER = 0;
		SCI1.SSR.BIT.FER = 0;
		SCI1.SSR.BIT.PER = 0;
		return -2;
	}
	if (flags&0x40) {/* normally received one data */
		recdata=SCI1.RDR;
		SCI1.SSR.BIT.RDRF = 0;
		return recdata;
	} else {
		return -1;
	}
}

void putStringSCI1(char *str);

/*SCI1��蕶�������[return]���I�[�����C'\n'�͎擾����Ȃ�*/
/*^H�Ńo�b�N�X�y�C�X*/
int getStringSCI1(char *buff,int max)
{
	int i,ch;
	for (i=0;i<max-1;i++) {
		ch=getCharSCI1(); /*1�����擾*/
		*buff=(char)ch; /*1�����擾*/
		if (*buff=='\r'||ch<0) {
			*buff=0;
			return i+1;
		}
		if (*buff==0x8) {
			buff-=2;
			i-=2;
		}
		if (*buff!='\n') buff++;
		else i--;
	}
	*buff=0;
	return i+1;
}

/*SCI1�փv�����v�g��\�����āCSCI1��萮���l�����*/
int getIntSCI1(char prompt[])
/*getting integer from serial port*/
/* format 123[ret] */
/*        -123[ret] */
/*        0x1a[ret] */
/*        -0x100[ret] */
{
	int x=0,y,m=0,n=0,v=0,i=0;
	char buff[16];
	putStringSCI1(prompt);
	getStringSCI1(buff,16);
	y=buff[i];
	while(y!=0){
		if(y=='-') m=1;
		if('a'<=y&&y<='z') y=y-'a'+'A';
		if(y=='0') n=1;

		if(v==1){
			if('0'<=y&&y<='9'){
				y=y-'0';
			}
			else if('A'<=y&&y<='F'){
				y=y-'A'+10;
			}
			x=16*x+y;
		}

		if(n==1&&y=='X'){
			v=1;
		}
				
		if(v==0&&'0'<=y&&y<='9'){
			y=y-'0';
			x=10*x+y;
		}

		y=buff[++i];
	}
	if(m==1) x=-x;
	return x;
}

/* ------------------------------------------------- */
/* PUT BYTE TO SCI1 */
/* ------------------------------------------------- */
void putCharSCI1(char c)
{
	unsigned char tmp;
	if (c=='\n') putCharSCI1('\r');
	do{
		tmp = SCI1.SSR.BYTE;
	} while((tmp & 0x80)==0);
	SCI1.TDR = c;
	SCI1.SSR.BIT.TDRE = 0;
	return;
}

void putStringSCI1(char *str)
{
	while(*str){
		putCharSCI1(*str);
		str++;
	}
}

const char hexstring[]="0123456789abcdef0123456789ABCDEF";
#define MAXDIGIT 34
void SCI1_printf(char *format,...)
{
	va_list arg_ptr;
	char buf[MAXDIGIT];
	unsigned char flag=0;  /*%d:bit2 l:bit1 %:bit0 */
	unsigned char digit=0; /* ���� */
	unsigned char minus=0;
	char fill,format1;
	unsigned char radix; /*N�i�*/
	char sign;
	char *ptr; /*�o�͕����|�C���^*/
	unsigned char cntr; /*�o�͕������J�E���^*/
	unsigned char shift; /*16�i�V�t�g 0 or 6*/
	unsigned char i;
	unsigned long int value;
	va_start(arg_ptr,format);
	while (*format) {
		format1=*format;
		if (flag==0) {
			if (format1=='%') {
				flag=1;
				digit=0;
				fill=' ';
				minus=0;
				radix=0;
				ptr=&buf[MAXDIGIT-1];
				*ptr--='\0';
				cntr=0;
				shift=0;
				sign='+';
			} else {
				putCharSCI1(format1);
			}
		} else {
			if (format1=='l') {
				flag|=2;
			} else if ('0'<=(format1)&&(format1)<='9') {
				if (digit==0 && format1=='0') {
					fill='0';
				} else {
					digit=digit*10+((format1)-'0');
					if (MAXDIGIT-2<digit) digit=MAXDIGIT-2;
				}
			} else if (format1=='-') {
				minus=1;
			} else if (format1=='d') {
				flag|=4;
				radix=10;
			} else if (format1=='u') {
				radix=10;
			} else if (format1=='x') {
				radix=16;
			} else if (format1=='X') {
				radix=16;shift=16;
			} else if (format1=='o') {
				radix=8;
			} else if (format1=='b') {
				radix=2;
			} else if (format1=='p') {
				radix=16;shift=16;digit=8;fill='0';flag|=2;
			} else if (format1=='c') {
				putCharSCI1((unsigned char)(va_arg(arg_ptr,int)));
				flag=0;
			} else if (format1=='s') {
				if (digit) {
					cntr=0;ptr=va_arg(arg_ptr,char *);
					while (ptr[cntr]) cntr++; /*cntr�͕�����*/
					if (!minus) for (i=cntr;i<digit;i++) putCharSCI1(' ');
					putStringSCI1(ptr);
					if (minus) for (i=cntr;i<digit;i++) putCharSCI1(' ');
				} else {
					putStringSCI1(va_arg(arg_ptr,char *));
				}
				flag=0;
			} else {
				putCharSCI1(format1);
				flag=0;
			}
			if (radix) {
				switch (flag&6) {
				case 0: /* unsig int */
					value=(unsigned int)va_arg(arg_ptr,int);
					break;
				case 2: /* unsig long int */
					value=va_arg(arg_ptr,long int);
					break;
				case 4: /* sig int */
					value=(long int)va_arg(arg_ptr,int);
					if ((long int)value<0) {
						value=-(long int)value;
						sign='-';
					}
					break;
				case 6: /* sig long int */
					value=va_arg(arg_ptr,long int);
					if ((long int)value<0) {
						value=-(long int)value;
						sign='-';
					}
					break;
				default:
					break;
				}
				while (value) {
					*ptr--=hexstring[value%radix+shift];
					cntr++;
					value/=radix;
				}
				if (cntr==0) {
					*ptr--='0';
					cntr++;
				}
				if (fill==' ') {
					if (sign=='-') {
						*ptr--='-';
						cntr++;
					}
					if (!minus) for (i=cntr;i<digit;i++) putCharSCI1(' ');
					putStringSCI1(++ptr);
					if (minus) for (i=cntr;i<digit;i++) putCharSCI1(' ');
				} else {
					for (;cntr<digit-1;cntr++) *ptr--='0';
					if (sign!='-'&&cntr<digit) *ptr--='0';
					else if (sign=='-') *ptr--='-';
					putStringSCI1(++ptr);
				}
				flag=0;
			}
		}
		format++;
	}
}

/* ------------------------------------------------- */
/*                 LED INITIALIZATION                */
/* ------------------------------------------------- */
/*LED��bit���Ȃ킿�|�[�gE��bit9,bit11�iPE��H��bit1,bit3�j���o�͂ɐݒ�*/
/*void initLed(void)
{
	PFC.PEIOR.BYTE.H |= 0x0a;
}*/
#define initLed() (PFC.PEIOR.BYTE.H |= 0x0a)

/* ------------------------------------------------- */
/* LET LED ON */
/* ------------------------------------------------- */
/*number��0�܂���1*/
void turnOnLed(short int number)
{	
	static unsigned char mask[]={0x2,0x8};
	PE.DR.BYTE.H |= mask[number];
}

/* ------------------------------------------------- */
/* LET LED OFF */
/* ------------------------------------------------- */
/*number��0�܂���1*/
void turnOffLed(short int number)
{
	static unsigned char mask[]={0xfd,0xf7};
	PE.DR.BYTE.H &= mask[number];
}

/* ------------------------------------------------- */
/*              PUSH SW INITIALIZATION               */
/* ------------------------------------------------- */
/*PushSW��PE��bit13,15�Ɋ��蓖�Ă��Ă���*/
/*PushSW�̃|�[�g����͂ɐݒ�*/
/*void initPushSW(void)
{
	PFC.PEIOR.BYTE.H &= 0x5f;
}*/
#define initPushSW() (PFC.PEIOR.BYTE.H &= 0x5f)

/* Pushsw�̏�Ԃ����̂܂ܕԂ� */
short int getPushSW(void)
{
	return ((PE.DR.BYTE.H>>5)&0x5);
}

short int checkPushSW(short int number)
/*Pushsw 0,1�̏�Ԃ𒲂ׂ�@number:0,or 1*/
/*ON�Ȃ�1�A�����łȂ�������0��Ԃ�*/
{
	short int ret;
	static const unsigned char mask[]={0x20,0x80};
	if (PE.DR.BYTE.H&mask[number&1]) ret=1;
	else ret=0;
	return ret;
}

/* ------------------------------------------------- */
/*              4 BIT SW INITIALIZATION              */
/* ------------------------------------------------- */
/*4BitSW��PB��bit2,3,4,5�Ɋ��蓖�Ă��Ă���*/
/*4bitSW�̃|�[�g����͂ɐݒ�*/
/*void init4BitSW(void)
{
	PFC.PBIOR.BYTE.L &= 0xc3;
}*/
#define init4BitSW() (PFC.PBIOR.BYTE.L &= 0xc3)

/* 4bitsw�̏�Ԃ����̂܂ܕԂ� */
short int get4BitSW(void)
{
	return ((PB.DR.BYTE.L>>2)&0xf);
}

short int check4BitSW(short int number)
/*4bitsw 0,1,2,3�̏�Ԃ𒲂ׂ�@number:0,1,2,or 4*/
/*ON�Ȃ�1�A�����łȂ�������0��Ԃ�*/
{
	short int ret;
	static const unsigned char mask[]={4,8,0x10,0x20};
	if (PB.DR.BYTE.L&mask[number&3]) ret=1;
	else ret=0;
	return ret;
}

/* ------------------------------------------------- */
/*         COMPARE MATCH TIMER INITIALIZATION        */
/* ------------------------------------------------- */
/* �R���y�A�}�b�`�^�C�}�ɂ��^�C�}���荞�݂̏����� */
/* ���荞�݊Ԋu�͈���peiod�ŒP�ʂ̓�sec�ł��� */
/* 0<period<1170104 �Ȃ̂ōŒ�1.170104sec�܂ŉ\ */
/* �`�����l�����Q����̂ł�ch��0,1�̂ǂ��炩��I�� */
/* ���荞�݃��x��intLebel��1�`15�ɂ��� */
void initCMTInt(unsigned long int period,int ch,int intLebel)
{
	/* �ӁF28.636MHz */
//	double dblcmcor;
	unsigned long int cmcor;
	unsigned char cks;
	if (period<16000) {
//		dblcmcor=(double)period*(28.636/8.);
		cmcor=period*28636/8000;
		cks=0; /* ��/8 */
	} else if (period<64000) {
//		dblcmcor=(double)period*(28.636/32.);
		cmcor=period*7159/8000;
		cks=1; /* ��/32 */
	} else if (period<256000) {
//		dblcmcor=(double)period*(28.636/128.);
		cmcor=period/4*7159/8000;
		cks=2; /* ��/128 */
	} else {
//		dblcmcor=(double)period*(28.636/512.);
		cmcor=period/16*7159/8000;
		cks=3; /* ��/512 */
	}
	if (ch==0) {
//		CMT0.CMCOR=(unsigned short int)(dblcmcor+0.5);
		CMT.CMSTR.BIT.STR0=0; /* �R���y�A�}�b�`�^�C�}0�X�g�b�v */
		CMT0.CMCOR=cmcor-1;
		CMT0.CMCSR.BIT.CKS=cks; /* �ӂ̐ݒ� */
		CMT0.CMCSR.BIT.CMIE=1; /* ���荞�݉ݒ� */
		INTC.IPRG.BIT._CMT0=intLebel; /* ���荞�݃R���g���[���̊��荞�݃��x�� */
	} else {
//		CMT1.CMCOR=(unsigned short int)(dblcmcor+0.5);
		CMT.CMSTR.BIT.STR1=0; /* �R���y�A�}�b�`�^�C�}1�X�g�b�v*/
		CMT1.CMCOR=cmcor-1;
		CMT1.CMCSR.BIT.CKS=cks; /* �ӂ̐ݒ� */
		CMT1.CMCSR.BIT.CMIE=1; /* ���荞�݉ݒ� */
		INTC.IPRG.BIT._CMT1=intLebel; /* ���荞�݃R���g���[���̊��荞�݃��x�� */
	}
}

#define startCMT0()      (CMT.CMSTR.BIT.STR0=1) /* �R���y�A�}�b�`�^�C�}0�X�^�[�g */
#define stopCMT0()       (CMT.CMSTR.BIT.STR0=0) /* �R���y�A�}�b�`�^�C�}0�X�g�b�v */
#define clearCMFlag0()  (CMT0.CMCSR.BIT.CMF=0) /* �R���y�A�}�b�`�t���b�O0�N���A */
#define startCMT1()      (CMT.CMSTR.BIT.STR1=1) /* �R���y�A�}�b�`�^�C�}1�X�^�[�g */
#define stopCMT1()       (CMT.CMSTR.BIT.STR1=0) /* �R���y�A�}�b�`�^�C�}1�X�g�b�v*/
#define clearCMFlag1()  (CMT1.CMCSR.BIT.CMF=0) /* �R���y�A�}�b�`�t���b�O1�N���A */
