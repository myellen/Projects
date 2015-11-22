#include "MeanVariancePortfolio.h"

MeanVariancePortfolio::MeanVariancePortfolio(Matrix priceMatrix)
{
	Matrix returnMatrix(priceMatrix.numRows() - 1, priceMatrix.numColumns());
	for (unsigned int assetIndex = 0; assetIndex < returnMatrix.numColumns(); ++assetIndex)
	{
		for (unsigned int priceIndex = 0; priceIndex < returnMatrix.numRows(); ++priceIndex)
		{
			returnMatrix(priceIndex, assetIndex) = priceMatrix(priceIndex + 1, assetIndex) / priceMatrix(priceIndex, assetIndex) - 1.0;
		}
	}
	this->returnMatrix = returnMatrix;

	Matrix expectedReturns(returnMatrix.numColumns(), 1);
	for (unsigned int assetIndex = 0; assetIndex < returnMatrix.numColumns(); ++assetIndex)
	{
		for (unsigned int priceIndex = 0; priceIndex < returnMatrix.numRows(); ++priceIndex)
		{
			expectedReturns(assetIndex, 0) += returnMatrix(priceIndex, assetIndex);
		}
	}
	expectedReturns = expectedReturns * (1.0 / returnMatrix.numRows());
	this->expectedReturns = expectedReturns;

	Matrix covMatrix(priceMatrix.numColumns(), priceMatrix.numColumns());
	for (unsigned int i = 0; i < covMatrix.numRows(); ++i)
	{
		for (unsigned int j = i; j < covMatrix.numColumns(); ++j)
		{
			for (unsigned int k = 0; k < returnMatrix.numRows(); ++k)
			{
				covMatrix(i, j) += (returnMatrix(k, i) - expectedReturns(i, 0))*(returnMatrix(k, j) - expectedReturns(j, 0)) / (double)returnMatrix.numRows();
			}
			covMatrix(j, i) = covMatrix(i, j);
		}
	}
	this->covMatrix = covMatrix;
}

MeanVariancePortfolio::~MeanVariancePortfolio()
{
}

Matrix MeanVariancePortfolio::getReturnMatrix()
{
	return returnMatrix;
}

Matrix MeanVariancePortfolio::getExpectedReturns()
{
	return expectedReturns;
}

Matrix MeanVariancePortfolio::getCovarianceMatrix()
{
	return covMatrix;
}

Matrix MeanVariancePortfolio::getPortfolioWeights(double expectedReturn)
{
	Matrix covMatrixInverse = covMatrix.inverse();
	Matrix oneVector = Matrix::OneVector(covMatrix.numRows());
	Matrix oneTranspose = oneVector.transpose();

	double A = (oneTranspose * covMatrixInverse * expectedReturns)(0, 0);
	double B = (expectedReturns.transpose() * covMatrixInverse * expectedReturns)(0, 0);
	double C = (oneTranspose * covMatrixInverse * oneVector)(0, 0);
	double D = B*C - A*A;

	Matrix g = (1 / D) * (B*oneTranspose + (-1 * A)* expectedReturns.transpose())*covMatrixInverse;
	Matrix h = (1 / D) * (C*expectedReturns.transpose() + (-1 * A)*oneTranspose)*covMatrixInverse;
	//cout << A << "\t" << B << "\t" << C << "\t" << D << endl;
	//cout << g << h << endl;

	Matrix weights = g + h * expectedReturn;
	return weights;
}

Matrix MeanVariancePortfolio::getGobalMinimumVariancePortfolioWeights()
{
	Matrix covMatrixInverse = covMatrix.inverse();
	Matrix oneVector = Matrix::OneVector(covMatrix.numRows());
	Matrix oneTranspose = oneVector.transpose();

	double C = (oneTranspose * covMatrixInverse * oneVector)(0, 0);
	

	Matrix weightsGobal = (1.0 / C)*oneTranspose*covMatrixInverse;
	return weightsGobal;
}
