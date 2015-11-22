#pragma once
#include "Matrix.h"
class MeanVariancePortfolio
{
public:
	MeanVariancePortfolio(Matrix priceMatrix);
	~MeanVariancePortfolio();

	Matrix getReturnMatrix();
	Matrix getExpectedReturns();
	Matrix getCovarianceMatrix();

	Matrix getPortfolioWeights(double expectedReturn); // returns row vector
	Matrix getGobalMinimumVariancePortfolioWeights(); // returns row vector

private:
	Matrix returnMatrix;
	Matrix expectedReturns;
	Matrix covMatrix;
};

