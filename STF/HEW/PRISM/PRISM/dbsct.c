/***********************************************************************/
/*                                                                     */
/*  FILE        :dbsct.c                                               */
/*  DATE        :Tue, Mar 22, 2011                                     */
/*  DESCRIPTION :Setting of B,R Section                                */
/*  CPU TYPE    :SH7045F                                               */
/*                                                                     */
/*  This file is generated by Renesas Project Generator (Ver.4.18).    */
/*  NOTE:THIS IS A TYPICAL EXAMPLE.                                    */
/***********************************************************************/
                  


#include "typedefine.h"

#pragma section $DSEC
static const struct {
    _UBYTE *rom_s;       /* �������f�[�^�Z�N�V������ROM ��̐擪�A�h���X */
    _UBYTE *rom_e;       /* �������f�[�^�Z�N�V������ROM ��̍ŏI�A�h���X */
    _UBYTE *ram_s;       /* �������f�[�^�Z�N�V������RAM ��̐擪�A�h���X */
}   DTBL[] = {
    { __sectop("D"), __secend("D"), __sectop("R") }
};
#pragma section $BSEC
static const struct {
    _UBYTE *b_s;         /* ���������f�[�^�Z�N�V�����̐擪�A�h���X */
    _UBYTE *b_e;         /* ���������f�[�^�Z�N�V�����̍ŏI�A�h���X */
}   BTBL[] = {
    { __sectop("B"), __secend("B") }
};