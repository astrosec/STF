/**
 * @file   matrixvector.cpp
 * @brief  NJHILS���玝���Ă����O���v�Z�֌W���W���[�����Csgp4���O��ԂŃ��b�v���Ďg�p�D
 *
 * @author 
 * @date   2011.02.16
 */

/* �ȈՃx�N�g���E�s�񉉎Z���C�u�����[ */
/* matrixvector.c : �����t�@�C�� */


#include "matrixvector.h"

namespace sgp4 {

/***************************************/
/* �x�N�g������E���Z�p�֐�                 */
/***************************************/

/* dim�����̃x�N�g����z��Ƃ��ē��I�Ɋm�ۂ��� */
/* ����: ���̊֐��ō�����x�N�g���͕K��FreeVec�֐��ŉ�@���Ȃ���΂Ȃ�Ȃ� */
double* AllocVec(int dim)
{
  double* vec;
  int i;
  vec = (double*)malloc(dim * sizeof(double)); /* ���������m�ۂ��� */

  /* ������ƃ��������m�ۂ��ꂽ�����`�F�b�N */
  if (vec == NULL) {
    fprintf(stderr,"Vector was not allocated \n");
    exit(1);
  }

  /*�S�Ă̗v�f��0�ɏ���������(�K�{�ł͂Ȃ�) */
  for (i=0;i<dim;i++)
    vec[i] = 0.0;

  return vec; /* �m�ۂ����������̐擪�A�h���X��Ԃ� */
}

/* ���AllocVec�֐��œ��I�m�ۂ��ꂽ�x�N�g���̃�������������� */
void FreeVec(double* v)
{
  free(v);
}

/* �x�N�g��va[]�̒��g���x�N�g��vb[]�ɃR�s�[���� */
void CopyVec(double* va, double* vb, int dim)
{
  int i;
  for (i=0;i<dim;i++)
    vb[i] = va[i];
}


/* �x�N�g��v[]�̊e�v�f��萔a�{���� */
void MultConstVec(double a, double* v, int dim)
{
  int i;
  for (i=0;i<dim;i++)
    v[i] *= a;
}

/* �ȉ��̃x�N�g������֐��͊e���������邱�ƁB */
/* ���`���� a*va+b*vc ���v�Z�� vc �ɓ����  */
void LinCombVec(double a, double* va, double b, double* vb, double* vc, int dim)
{
	int i;
	for (i=0;i<dim;i++)
		vc[i] = a * va[i] + b * vb[i];
}

/* �m�������v�Z */
double NormVec(double* v, int dim)
{
	int i;
	double sum = 0.0; /* �m�����̕��� */
	for (i=0;i<dim;i++)
		sum += v[i] * v[i];
	sum = sqrt(sum);
	return sum;
}

/* 2�̃x�N�g���̓��ς��v�Z */
double InProdVec(double* va, double* vb, int dim)
{
	int i;
	double sum = 0 ; /* ���� */
	for (i=0;i<dim;i++)
		sum += va[i] * vb[i];
	return sum;
}

/***************************************/
/* �s�񑀍�E���Z�p�֐�                    */
/***************************************/
/* nrow�s ncol��̍s��𓮓I�Ɋm�ۂ��� */
/* ���̊֐��Ŋm�ۂ����s��͕K��FreeMat�֐��ŉ�����Ȃ���΂Ȃ�Ȃ� */
double** AllocMat(int nrow, int ncol)
{
  double** m;
  int i;
  /* �e�s�̐擪�|�C���^��[�߂�z�� */
  m = (double**)malloc(nrow * sizeof(double*)); 

  /* ���ۂ̃f�[�^��[�߂�̈��1�����z��Ƃ��Ċm�� */
  m[0] = (double*)malloc(nrow*ncol*sizeof(double));
  /* �K�{�ł͂Ȃ����v�f��S��0.0�ɐݒ� */
  for (i=0;i<nrow*ncol;i++)
    m[0][i] = 0.0;

  /* �em[i]��i�s�ڂ̃f�[�^�̐擪�|�C���^���i�[ */
  for (i=1;i<nrow;i++)
    m[i] = &m[0][i*ncol];

  return m;
}

/* ���AllocMat�֐��Ŋm�ۂ����s��̃���������� */
void FreeMat(double** m)
{
  free(m[0]);
  free(m);
}

/* �ȉ��̍s�񉉎Z�֐��͊e������ */

/* ma[][]�̒��g��mb[][]�ɃR�s�[���� */
void CopyMat(double** ma, double** mb, int nrow, int ncol)
{
	int i, j;
	for (i=0;i<nrow;i++){
		for (j=0;j<ncol;j++)
			mb[i][j] = ma[i][j];
	}
}

/* nrc�snrc��̍s��m[][]��P�ʍs��I�ɂ��� */
void UnitMat(double** m, int nrc)
{
	int i, j;
	for (i=0;i<nrc;i++){
		for (j=0;j<nrc;j++){
			if (i==j)
				m[i][j] = 1;
			else
				m[i][j] = 0;
		}
	}
}

/* �s�� m[][] �̊e�v�f��萔a�{�ɂ��� */
void MultConstMat(double a, double** m, int nrow, int ncol)
{
	int i,j;
	for (i=0;i<nrow;i++)
		for (j=0;j<ncol;j++)
			m[i][j] *= a;
}

/*
// �s�� m[][] �̓]�u�s��mt[][]�����߂�
void TransMat2(double** m, double** mt, int nrow,  int ncol)
{
	int i,j;
	for (i=0;i<nrow;i++)
		for (j=0;j<ncol;j++)
			mt[j][i] = m[i][j];
}
*/

//[ncol,nrow]�s���[nrow,ncol]�s���
/* �s��m[][]�̓]�u�s��mt[]�����߂�*/
void TransMat(double** m, double** mt, int nrow,  int ncol)
{ 
	int i,j;
	for (i=0;i<nrow;i++){
		for (j=0;j<ncol;j++)
		 mt[i][j] = m[j][i];
	}
}

/* 2�̍s��ma[][]��mb[][]�̐��`�a (a*ma[][]+b*mb[][])�����߁A���ʂ�mc[]�ɓ���� */
void LinCombMat(double a, double** ma, double b, double** mb, double** mc, int nrow, int ncol)
{
	int i,j;
	for (i=0;i<nrow;i++)
		for (j=0;j<ncol;j++)
			mc[i][j] = a * ma[i][j] + b * mb[i][j];
}


/* 2�̍s��ma[][]��mb[][]�̐� (ma[][]*mb[][])�����߁A���ʂ�mc[]�ɓ���� */
/* ����: ma[][]��nra�snca��Amb[][]��nca�sncb��Amc[]��nra[]�sncb��ɂȂ� */

void MultMatMat(double** ma, double** mb, double** mc, int  nra, int nca, int ncb)
{
	int i,j,k;

	for (i=0;i<nra;i++){
		for (j=0;j<ncb;j++){
			mc[i][j] = 0;
			for (k=0;k<nca;k++){
				mc[i][j] += ma[i][k] * mb[k][j];
			}
		}
	}
}

/* �K�E�X�E�W�����_���@��m[][]�̋t�s��minv[]�����߂� */

 void InvMatGJ(double** m, double** minv, int nrc)
 {
 int i,j,k;
 double a,b;
 double **A;
 A=AllocMat(nrc,nrc);
 CopyMat(m,A,nrc,nrc);
 UnitMat(minv,nrc);
  for(j=0;j<nrc;j++){
  if(A[j][j]!=0){
  a=A[j][j];
  for(i=0;i<nrc;i++){
  A[j][i]/=a;
  minv[j][i]/=a;
  }
  for(i=0;i<nrc;i++){
  if(i!=j){
  b=A[i][j];
  for(k=0;k<nrc;k++){
  A[i][k]-=b*A[j][k];
  minv[i][k]-=b*minv[j][k];
  }
  }
 }
}
}
FreeMat(A);
}


/***************************************/
/* �s��E�x�N�g���̉��Z�֐�                 */
/***************************************/
/* �s��m[][]�ƃx�N�g��va[]�̐ς����߁Avb[]�ɓ���� */
void MultMatVec(double** m, double* va, double* vb, int nraw, int ncol)
{
  int i,j;

  for (i=0;i<nraw;i++) {
    vb[i] = 0.0;
    for (j=0;j<ncol;j++)
      vb[i] += m[i][j]*va[j];
  }
}

/* �ȉ��̍s��E�x�N�g�����Z�֐��͊e������ */

/* �K�E�X�̏����@�ɂ��1���A�������������� */
void SolvLinEqGauss(double** A, double* Va, double* vx, int nrc)
{
	int i,j,k;
	double temp, div, kakeru, sum;
	double *va;
	double **m;
	m = AllocMat(nrc,nrc);
	va = AllocVec(nrc);

	CopyMat(A,m,nrc,nrc);
	CopyVec(Va,va,nrc);

	for (i=0;i<nrc;i++){
		for(j=i+1;j<nrc;j++){ /* �s�{�b�g�I���i�����̐�Βl���ő�̍s����ԏ�Ɏ����Ă���j */
			if(m[i][i]*m[i][i]<m[j][i]*m[j][i]){
				temp = va[i];
				va[i] = va[j];
				va[j] = temp;
				for(k=i;k<nrc;k++){
					temp = m[i][k];
					m[i][k] = m[j][k];
					m[j][k] = temp;
				}
			}
		}
		/* i�s�ڂ�1/m[i][i]�{ */
		div = m[i][i];
		va[i] /=div;
		for(j=i;j<nrc;j++)
			m[i][j] /= div;
		/* j�s�ڂ���i�s�ڂ�m[j][i]�{������ */
		for(j=i+1;j<nrc;j++){ 
			kakeru = m[j][i];
			va[j] -= kakeru*va[i];
			for(k=i;k<nrc;k++)
				m[j][k] -= kakeru*m[i][k];
		}
	}
	/* ��ޑ���ɂ��������߂� */
	vx[nrc-1] = va[nrc-1];
	for (j=2;j<=nrc;j++){
		sum = 0;
		for(i = nrc-j+1;i<nrc;i++)
			sum += vx[i]*m[nrc-j][i];
		vx[nrc-j] = va[nrc-j] - sum;
	}

	FreeMat(m);
	FreeVec(va);
}

}
