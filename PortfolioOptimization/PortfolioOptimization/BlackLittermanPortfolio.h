#pragma once
#include "Matrix.h"

class BlackLittermanPortfolio
{
public:
	BlackLittermanPortfolio(Matrix priceMatrix, Matrix Q, Matrix P, double tau);
	~BlackLittermanPortfolio();

	Matrix getPortfolioWeights(); // returns row vector
	Matrix getGobalMinimumVariancePortfolioWeights();

	Matrix calcuateMeanExpectedReturns();
private:
	double riskAversion;
	double tau;

	Matrix returnMatrix;
	Matrix expectedReturns;
	Matrix covMatrix;

	Matrix Q;
	Matrix P;
	Matrix Pi;
	Matrix Omega;
};

