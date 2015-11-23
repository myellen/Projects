#include <stdio.h>
#include <iostream>
#include "Matrix.h"
#include <vector>
#include "DataCollector.h"
#include "MeanVariancePortfolio.h"
#include "BlackLittermanPortfolio.h"

using namespace std;

int main()
{
	DataCollector dc;
	vector<string> assetNames;
	Matrix priceMatrix = dc.readFromText("file", assetNames);

	cout << priceMatrix << endl;

	for (unsigned int i = 0; i < assetNames.size(); i++)
		cout << assetNames[i] << endl;

	MeanVariancePortfolio mvp(priceMatrix);

	cout << mvp.getPortfolioWeights(0.05) << endl;
	cout << mvp.getGobalMinimumVariancePortfolioWeights() << endl;

	Matrix Q = dc.readQMatrixFromText("Q.txt");
	Matrix P = dc.readPMatrixFromText("P.txt");

	BlackLittermanPortfolio blp(priceMatrix, Q, P, 0.0025);
	
	cout << blp.calcuateMeanExpectedReturns() << endl;
	cout << blp.getPortfolioWeights() << endl;
	return 0;
}
