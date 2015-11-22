#pragma once
#include <string>

using namespace std;

class Matrix
{
public:
	Matrix();
	Matrix(unsigned int rows, unsigned int cols);
	~Matrix();
	Matrix(const Matrix& m);              
	Matrix& operator= (const Matrix& m);

	static Matrix IdentityMatrix(unsigned int n);
	static Matrix OneVector(unsigned int n);

	Matrix transpose();

	double trace();

	double determinant();
	Matrix inverse();

	double& operator() (unsigned int row, unsigned int col);
	double  operator() (unsigned int row, unsigned int col) const;

	friend Matrix operator* (double x, const Matrix& m);
	friend Matrix operator* (const Matrix& m, double x);

	friend Matrix operator* (const Matrix& lhm, const Matrix& rhm);

	friend Matrix operator+ (const Matrix& m1, const Matrix& m2);

	friend ostream& operator<<(ostream& os, const Matrix& m);

	unsigned int numRows();
	unsigned int numColumns();

	Matrix removeRow(unsigned int row);
	Matrix removeColumn(unsigned int column);

	Matrix getRow(unsigned int n);
	void setRow(unsigned int n, Matrix newRow);
private:
	unsigned int rows, cols;
	double* data;
};

