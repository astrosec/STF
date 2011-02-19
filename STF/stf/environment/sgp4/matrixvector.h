/**
 * @file   matrixvector.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
/* �ȈՃx�N�g���E�s�񉉎Z���C�u�����[ */
/* matrixvector.h : �w�b�_�[�t�@�C�� */
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/* ����2�s�ƍŌ�̍s�� #endif �͂��܂��Ȃ�*/
#if !defined(___MATRIXVECTOR___)
#define ___MATRIXVECTOR___

namespace sgp4 {
//�z��̗v�f���x�N�g���v�f�\�L�ŕ\��
template <class Type>
int PrintVector(const Type* x, int size)
{
	cout << "(";
	for(int i=0;i<size-1;i++) {
		cout.width(10);
		cout << x[i];
		cout << ",";
	}
	cout.width(10);
	cout << x[size-1];
	cout << ")" << endl;

	return 0;
}

//�s���\��
template <class Type>
int PrintMatrix(const Type** x, int gyou, int retsu)
{
	for (int j=0;j<gyou;j++) {
		cout << "(";
		for(int i=0;i<retsu-1;i++) {
			cout.width(10);
			cout << x[j][i];
		}
		cout.width(10);
		cout << x[j][retsu-1];
		cout << ")\n";
	}
	cout << endl;

	return 0;
}


/***************************************/
/* �x�N�g������E���Z�p�֐�                 */
/***************************************/

/* dim�����̃x�N�g����z��Ƃ��ē��I�Ɋm�ۂ��� */
/* ����: ���̊֐��ō�����x�N�g���͕K��FreeVec�֐��ŉ�@���Ȃ���΂Ȃ�Ȃ� */
double* AllocVec(int dim);

/* ���AllocVec�֐��œ��I�m�ۂ��ꂽ�x�N�g���̃�������������� */
void FreeVec(double* v);

/* �x�N�g��va[]�̒��g���x�N�g��vb[]�ɃR�s�[���� */
void CopyVec(double* va, double* vb, int dim);

/* �x�N�g��v[]�̊e�v�f��萔a�{���� */
void MultConstVec(double a, double* v, int dim);

/* 2�̃x�N�g��va[]��vb[]�̐��`�a (a*va[]+b*vb[])�����߁A���ʂ�vc[]�ɓ���� */
void LinCombVec(double a, double* va, double b,
		double* vb, double* vc, int dim);

/* �x�N�g���̑傫��(�m����)���v�Z���� */
double NormVec(double* v, int dim);

/* 2�̃x�N�g���̓��ς��v�Z���� */
double InProdVec(double* va, double* vb, int dim);


/***************************************/
/* �s�񑀍�E���Z�p�֐�                    */
/***************************************/

/* nrow�s ncol��̍s��𓮓I�Ɋm�ۂ��� */
/* (����: ���ۂɂ�1�����z��Ƃ��Ċm�ۂ��Ă���2�����z��Ɍ��������Ă���) */
/* ���̊֐��Ŋm�ۂ����s��͕K��FreeMat�֐��ŉ�����Ȃ���΂Ȃ�Ȃ� */
double** AllocMat(int nrow, int ncol);

/* ���AllocMat�֐��Ŋm�ۂ����s��̃���������� */
void FreeMat(double** m);

/* �s��ma[][]�̒��g���s��mb[][]�ɃR�s�[���� */
void CopyMat(double** ma, double** mb, int nrow, int ncol);

/* nrc�snrc��̐����s��m[][]��P�ʍs��I�ɂ��� */
void UnitMat(double** m, int nrc);

/* �s��m[][]�̊e�v�f��萔a�{�ɂ��� */
void MultConstMat(double a, double** m, int nrow, int ncol);

//[ncol,nrow]�s���[nrow,ncol]�s���
/* �s��m[][]�̓]�u�s��mt[]�����߂� */
void TransMat(double** m, double** mt, int nrow,  int ncol);

/* 2�̍s��ma[][]��mb[][]�̐��`�a (a*ma[][]+b*mb[][])�����߁A���ʂ�mc[]�ɓ���� */
void LinCombMat(double a, double** ma, double b, double** mb, 
		double** mc, int nrow, int ncol);

/* 2�̍s��ma[][]��mb[][]�̐� (ma[][]*mb[][])�����߁A���ʂ�mc[]�ɓ���� */
/* ����: ma[][]��nra�snca��Amb[][]��nca�sncb��Amc[]��nra[]�sncb��ɂȂ� */
void MultMatMat(double** ma, double** mb, double** mc, int  nra, 
		int nca, int ncb);

/* �K�E�X�E�W�����_���@��m[][]�̋t�s��minv[]�����߂� */
void InvMatGJ(double** m, double** minv, int nrc);


/***************************************/
/* �s��E�x�N�g���̉��Z�֐�                 */
/***************************************/

/* �s��m[][]�ƃx�N�g��va[]�̐ς����߁Avb[]�ɓ���� */
void MultMatVec(double** m, double* va, double* vb, int nraw, int ncol);

/* �A���ꎟ������ m[][]*vx[] = va[] ���K�E�X�̏����@�ŉ��� */
void SolvLinEqGauss(double** m, double* va, double* vx, int nrc);

}

#endif

