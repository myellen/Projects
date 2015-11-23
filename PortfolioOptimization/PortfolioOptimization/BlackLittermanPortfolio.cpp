#include "BlackLittermanPortfolio.h"



BlackLittermanPortfolio::BlackLittermanPortfolio(Matrix priceMatrix, Matrix Q, Matrix P, double tau)
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

	this->P = P;
	this->Q = Q;
	Matrix Omega = this->P * covMatrix * this->P.transpose();
	this->Omega = Omega;

	this->riskAversion = 1;
	this->tau = tau;
	this->Pi = riskAversion * this->covMatrix * this->getGobalMinimumVariancePortfolioWeights().transpose();
}


BlackLittermanPortfolio::~BlackLittermanPortfolio()
{
}

Matrix BlackLittermanPortfolio::getPortfolioWeights()
{
	Matrix weights = covMatrix.inverse()*calcuateMeanExpectedReturns() * (1.0/riskAversion);
	return weights;
}
Matrix BlackLittermanPortfolio::getGobalMinimumVariancePortfolioWeights()
{
	
	Matrix covMatrixInverse = covMatrix.inverse();
	Matrix oneVector = Matrix::OneVector(covMatrix.numRows());
	Matrix oneTranspose = oneVector.transpose();

	double C = (oneTranspose * covMatrixInverse * oneVector)(0, 0);

	Matrix weightsGobal = (1.0 / C)*oneTranspose*covMatrixInverse;
	return weightsGobal;
	
}

Matrix BlackLittermanPortfolio::calcuateMeanExpectedReturns()
{
	Matrix lhm = (tau*covMatrix).inverse() + P.transpose()*Omega.inverse()*P;
	Matrix rhm = (tau*covMatrix).inverse()*Pi + P.transpose()*Omega.inverse()*Q;
	
	Matrix meanExpReturns = lhm.inverse()*rhm;
	
	return meanExpReturns;
}
