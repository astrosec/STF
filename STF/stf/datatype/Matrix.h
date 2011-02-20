/**
 * @file   Matrix.h
 * @brief  �s��v�Z���s���N���X�D
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_datatype_Matrix_h
#define stf_datatype_Matrix_h

#include <assert.h>
#include "Vector.h"
#include "StaticVector.h"
#include "IAocsData.h"

namespace stf {
namespace util {
template <class T>class Ostream;
}
}

namespace stf { 
namespace datatype {

//! �ϗv�f���̍s�񉉎Z���s���D
/*! �������̓��I�m�ۂ��s�����߁CSTF�ł̓V�X�e���������ȊO�̃^�C�~���O�ł̎g�p����������Ȃ��D�ʏ��StaticMatrix���g������ */
class Matrix {
 public:
    Matrix();
    Matrix(int rows, int cols);
    Matrix(const Matrix &rhs);
    ~Matrix();
    inline Vector &operator[](int index) const ;
    Matrix &unitize();
    Matrix trans() const ;
    Matrix inverse() const ;
    bool isSquare();
    int pivot(Matrix &m, int row) const ;
	double trace() const ;//Trace
	double det() const ; //�s��
    Matrix &operator=(const Matrix &rhs);
    Matrix &operator+=(const Matrix &rhs);
    Matrix &operator-=(const Matrix &rhs);
    Matrix &operator*=(const Matrix &rhs);
    Matrix &operator*=(double rhs);
    Matrix &operator/=(double rhs);
    bool operator==(const Matrix &rhs) const ;
    bool operator!=(const Matrix &rhs) const ;
	virtual void reset(){ for(int i = 0; i < rows_; i++) value_[i].reset(); }
	int rows() const { return rows_; }
	int cols() const { return cols_; }
private:
	friend inline const Matrix operator + (const Matrix&, const Matrix&);
	friend inline const Matrix operator - (const Matrix&, const Matrix&);
	friend inline const Matrix operator * (const Matrix&, double);
	friend inline const Matrix operator * (double, const Matrix&);
	friend inline const Matrix operator * (const Matrix&, const Matrix&);
	friend inline const Matrix operator / (const Matrix&, double);
	//friend std::ostream &operator << (std::ostream&, const Matrix&);
	friend inline const Vector operator * (const Matrix&, const Vector&);
	friend inline const Vector operator * (const Matrix&, const StaticVector<3>&);
	friend inline const Vector operator * (const Matrix&, const StaticVector<4>&);
    friend class Vector;
	template<class T>friend class stf::util::Ostream;//TBD:Vector����iostream���B�؂����C�W���o�͂��������邽�߂́u�����v�t�����h�N���X�D���܂�悭�Ȃ�������
    Vector *value_;
    int cols_;
    int rows_;
};

////////////////////////////////
//  Inline Methods for Matrix //
////////////////////////////////

inline Vector &Matrix::operator[](int index) const 
{
	assert(index >= 0 && index < rows_);
	return value_[index];
}

//�s��̉��Z
inline const Matrix operator + (const Matrix& oper1, const Matrix& oper2){
	assert(oper1.rows_ == oper2.rows_ && oper1.cols_ == oper2.cols_);
	Matrix mat = oper1;
	mat += oper2;
	return mat;
}

//�s��̌��Z
inline const Matrix operator - (const Matrix& oper1, const Matrix& oper2){
	assert(oper1.rows_ == oper2.rows_ && oper1.cols_ == oper2.cols_);
	Matrix mat = oper1;
	mat -= oper2;
	return mat;		
}

//�s��̐ώZ
inline const Matrix operator * (const Matrix& oper1, const Matrix& oper2){
	assert(oper1.cols_ == oper2.rows_);
	Matrix mat(oper1.rows_,oper2.cols_);
	for(int rows = 0;rows < mat.rows_; rows++)
	  for(int cols = 0;cols < mat.cols_; cols++)
		for(int index = 0;index < oper1.cols_; index ++)
			mat.value_[rows].value_[cols] += oper1.value_[rows].value_[index] * oper2.value_[index].value_[cols];
		  //mat[rows][cols] += oper1[rows][index] * oper2[index][cols];
	return mat;
}

//�s����E����萔�{
inline const Matrix operator * (const Matrix& oper, double factor){
	Matrix mat = oper;
	mat *= factor;
	return mat;
}

//�s���������萔�{
inline const Matrix operator * (double factor, const Matrix& oper){
	return oper * factor;
}

//�s��ƃx�N�g���̐�
inline const Matrix operator / (const Matrix& oper, double factor){
	Matrix mat = oper;
	mat /= factor;
	return mat;
}

//�s��ƃx�N�g���̐�
inline const Vector operator * (const Matrix& mat, const Vector& vec){
	assert(mat.cols_ == vec.dimension_);
	Vector temp(mat.rows_);
	for(int i = 0; i < temp.dimension_; i++)
		for(int index = 0; index < vec.dimension_; index ++)
			temp[i] += mat[i][index] * vec[index];
	return temp;
}

inline const Vector operator * (const Matrix& mat, const StaticVector<3>& vec){
	assert(mat.cols_ == 3);
	Vector temp(mat.rows_);
	for(int i = 0; i < temp.dimension(); i++)
		for(int index = 0; index < 3; index ++)
			temp[i] += mat[i][index] * vec[index];
	return temp;	
}

inline const Vector operator * (const Matrix& mat, const StaticVector<4>& vec){
	assert(mat.cols_ == 4);
	Vector temp(mat.rows_);
	for(int i = 0; i < temp.dimension(); i++)
		for(int index = 0; index < 4; index ++)
			temp[i] += mat[i][index] * vec[index];
	return temp;	
}

} /* End of namespace stf::datatype */
} /* End of namespace stf */

#endif // stf_datatype_Matrix_h