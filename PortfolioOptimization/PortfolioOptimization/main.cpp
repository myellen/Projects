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
	string filename;
	double expectedReturn;

	cout << "Enter stock data file name for Mean Variance and Black Litterman portfolio calculations (e.g. Stocks.txt): " << endl;
	cin >> filename;

	cout << "Enter expected return for Mean Variance Portfolio (e.g. 0.05): " << endl;
	cin >> expectedReturn;

	Matrix priceMatrix = dc.readFromText(filename, assetNames);

	//cout << priceMatrix << endl;

	MeanVariancePortfolio mvp(priceMatrix);

	cout << "Assets:\t\t";
	for (unsigned int i = 0; i < assetNames.size(); i++)
		cout << assetNames[i] << "\t";
	cout << endl;

	cout << "E[r] weights:\t";
	Matrix expectedReturnWeights = mvp.getPortfolioWeights(expectedReturn);
	for (unsigned int i = 0; i < assetNames.size(); i++)
		cout << expectedReturnWeights(0,i) << "\t";
	cout << endl;

	cout << "global minimum weights:\t";
	Matrix globalMVPWeights = mvp.getGobalMinimumVariancePortfolioWeights();
	for (unsigned int i = 0; i < assetNames.size(); i++)
		cout << globalMVPWeights(0, i) << "\t";
	cout << endl << endl;

	cout << "Enter file name for Q matrix (e.g. Q.txt): ";
	cin >> filename;
	Matrix Q = dc.readQMatrixFromText(filename);

	cout << "Enter file name for P matrix (e.g. P.txt): ";
	cin >> filename;
	Matrix P = dc.readPMatrixFromText(filename);

	double riskAversion, tau;
	cout << "Enter Tau value (e.g. 0.025): ";
	cin >> tau;

	cout << "Enter risk aversion coefficient (e.g. 15): ";
	cin >> riskAversion;
	BlackLittermanPortfolio blp(priceMatrix, Q, P, 0.0025, riskAversion);
	
	cout << "Black Litterman Portfolio Weights: " << endl;
	for (unsigned int i = 0; i < assetNames.size(); i++)
		cout << assetNames[i] << "\t";
	cout << endl;

	Matrix blpWeights = blp.getPortfolioWeights();
	for (unsigned int i = 0; i < assetNames.size(); i++)
		cout << blpWeights(i, 0) << "\t";
	cout << endl;
	return 0;
}
