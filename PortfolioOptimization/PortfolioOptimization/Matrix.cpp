#include "Matrix.h"
#include <stdexcept>
#include <iostream>


Matrix::Matrix(unsigned int rows, unsigned int cols)
{
	if (rows == 0 || cols == 0)
		throw std::out_of_range("Matrix can't have dimension 0");

	this->rows = rows;
	this->cols = cols;

	this->data = new double[rows * cols]();
}


Matrix::~Matrix()
{
	delete[] data;
}

Matrix::Matrix(const Matrix & m)
{
	rows = m.rows;
	cols = m.cols;
	data = new double[rows * cols];
	for (unsigned int i = 0; i < rows*cols; ++i)
		data[i] = m.data[i];
}

Matrix & Matrix::operator=(const Matrix & m)
{
	rows = m.rows;
	cols = m.cols;
	data = new double[rows * cols];
	for (unsigned int i = 0; i < rows*cols; ++i)
		data[i] = m.data[i];
	return *this;
}

Matrix Matrix::IdentityMatrix(unsigned int n)
{
	Matrix id(n, n);
	for (unsigned int i = 0; i < n; i++)
		id(i, i) = 1;
	return id;
}

Matrix Matrix::OneVector(unsigned int n)
{
	Matrix vec(n, 1); // column vector
	for (unsigned int i = 0; i < n; i++)
		vec(i, 0) = 1;
	return vec;
}

Matrix Matrix::transpose()
{
	Matrix temp(this->cols, this->rows);
	cout << "temp :" << temp << endl;
	for (unsigned int i = 0; i < temp.rows; ++i)
	{
		for (unsigned int j = 0; j < temp.cols; ++j)
		{
			temp(i, j) = (*this)(j, i);
		}
	}
	cout << "done" << endl;
	return temp;
}

double Matrix::trace()
{
	if (rows != cols)
		throw std::out_of_range("not a square matix");
	double trace = 0.0;
	for (unsigned int i = 0; i < rows; ++i)
		trace += (*this)(i, i);
	return trace;
}

double detHelper(Matrix m)
{
	double det = 0.0;
	if (m.numRows() == 2)
	{
		det = m(0, 0)*m(1, 1) - m(1, 0)*m(0, 1);
		//cout << "det( " << m << ") = " << det << endl;
		return det;
	}
	Matrix mNoRow0 = m.removeRow(0);
	for (unsigned int k = 0; k < m.numColumns(); ++k)
	{
		if (m(0, k) == 0.0) continue;
		Matrix sub = mNoRow0.removeColumn(k);
		//cout << m(0, k) << "*" << sub << endl;

		if (k%2 == 0) det += m(0, k)* detHelper(sub);
		else det -= m(0, k)* detHelper(sub);
	}
	return det;
}

double Matrix::determinant()
{
	if (rows != cols)
		throw std::out_of_range("not a square matix");
	double determinant = detHelper(*this);
	return determinant;
}

Matrix Matrix::inverse()
{
	if (rows != cols)
		throw std::out_of_range("not a square matix");
	Matrix inv = IdentityMatrix(rows);
	Matrix tmp = (*this);

	for (unsigned int i = 0; i < rows; ++i)
	{
		if (tmp(i, i) != 0)
		{
			for (unsigned int j = 0; j < rows; j++)
			{
				if (j == i) continue;
				double scale;
				if (tmp(i, i) > 0) scale = -1 * tmp(j, i) / tmp(i, i);
				else scale = tmp(j, i) / tmp(i, i);
				tmp.setRow(j, tmp.getRow(j) + scale*tmp.getRow(i));
				inv.setRow(j, inv.getRow(j) + scale*inv.getRow(i));
			}
			double scale = 1 / tmp(i, i);
			tmp.setRow(i, scale*tmp.getRow(i));
			inv.setRow(i, scale*inv.getRow(i));
		}

		//cout << "tmp" << endl;
		//cout << tmp << endl;
	}
	return inv;
}


double& Matrix::operator() (unsigned int row, unsigned int col)
{
	if (row >= rows || col >= cols)
		throw std::out_of_range("invalid index");
	return data[cols*row + col];
}

double Matrix::operator()(unsigned int row, unsigned int col) const
{
	if (row >= rows || col >= cols)
		throw std::out_of_range("invalid index");
	return data[cols*row + col];
}

unsigned int Matrix::numRows()
{
	return rows;
}

unsigned int Matrix::numColumns()
{
	return cols;
}

Matrix Matrix::removeRow(unsigned int row)
{
	Matrix subM(rows - 1, cols);
	for (unsigned int i = 0; i < row; ++i)
	{
		for (unsigned int j = 0; j < subM.cols; ++j)
		{
			subM(i, j) = (*this)(i, j);
		}
	}
	for (unsigned int i = row; i < subM.rows; ++i)
	{
		for (unsigned int j = 0; j < subM.cols; ++j)
		{
			subM(i, j) = (*this)(i+1, j);
		}
	}
	return subM;
}

Matrix Matrix::removeColumn(unsigned int column)
{
	Matrix subM(rows, cols-1);
	for (unsigned int i = 0; i < subM.rows; ++i)
	{
		for (unsigned int j = 0; j < column; ++j)
		{
			subM(i, j) = (*this)(i, j);
		}
		for (unsigned int j = column; j < subM.cols; ++j)
		{
			subM(i, j) = (*this)(i, j+1);
		}
	}
	return subM;
}

Matrix Matrix::getRow(unsigned int n)
{
	Matrix r(1, cols);
	for (unsigned int i = 0; i < cols; ++i)
		r(0, i) = (*this)(n, i);
	return r;
}

void Matrix::setRow(unsigned int n, Matrix newRow)
{
	//if (newRow.cols != this->cols)
	//throw
	for (unsigned int i = 0; i < cols; ++i)
		(*this)(n, i) = newRow(0, i);
	
}

Matrix operator* (double x, const Matrix& m)
{
	Matrix temp(m);
	for (unsigned int i = 0; i < temp.rows; ++i)
	{
		for (unsigned int j = 0; j < temp.cols; ++j)
		{
			temp(i, j) *= x;
		}
	}
	return temp;
}

Matrix operator* (const Matrix& m, double x)
{
	Matrix temp(m);
	for (unsigned int i = 0; i < temp.rows; ++i)
	{
		for (unsigned int j = 0; j < temp.cols; ++j)
		{
			temp(i, j) *= x;
		}
	}
	return temp;
}

Matrix operator* (const Matrix& lhm, const Matrix& rhm)
{
	if (lhm.cols != rhm.rows)
		throw std::out_of_range("Can't multiply matrices: dimensions dont match");
	Matrix product(lhm.rows, rhm.cols);

	for (unsigned int i = 0; i < product.rows; ++i)
	{
		for (unsigned int j = 0; j < product.cols; j++)
		{
			for (unsigned int k = 0; k < lhm.cols; ++k)
			{
				product(i, j) += lhm(i, k)*rhm(k, j);
			}
		}
	}

	return product;
}

Matrix operator+ (const Matrix& m1, const Matrix& m2)
{
	if (m1.rows != m2.rows || m1.cols != m2.cols)
		throw std::out_of_range("Can't add matrices: dimensions dont match");
	Matrix temp(m1.rows, m1.cols);
	for (unsigned int i = 0; i < temp.rows*temp.cols; ++i)
		temp.data[i] = m1.data[i] + m2.data[i];
	return temp;
}

ostream& operator<<(ostream& os, const Matrix& m)
{
	for (unsigned int i = 0; i < m.rows; ++i)
	{
		os << "[ ";
		for (unsigned int j = 0; j < m.cols-1; ++j)
		{
			os << m(i, j) << ", ";
		}
		os << m(i,m.cols-1) <<  " ]" << endl;
	}
	return os;
}