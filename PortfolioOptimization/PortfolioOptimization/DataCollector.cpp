#include "DataCollector.h"
#include <iostream>
#include <functional>
#include <iomanip>
#include <fstream>
#include <sstream>


DataCollector::DataCollector()
{
}


DataCollector::~DataCollector()
{
}

void countLines(string filename, unsigned int &rows, unsigned int &columns)
{
	ifstream infile; //input file stream object
	infile.open(filename);
	if (!infile) {
		cerr << "Bad input! Can't open " << filename << endl;
		exit(1);
	}
	string line, token;
	rows = 0;
	columns = 0;
	getline(infile, line, '\n');
	stringstream ss(line);
	while (getline(ss, token, ','))
		columns++;
	rows++;
	while (getline(infile, line, '\n'))
	{
		rows++;
	}
}

void countStuff(string filename, unsigned int &numAssets, unsigned int &numDates)
{
	numAssets = 0;
	numDates = 0;

	ifstream infile; //input file stream object
	infile.open(filename);
	if (!infile) {
		cerr << "Bad input! Can't open " << filename << endl;
		exit(1);
	}

	string line;
	string token;
	getline(infile, line, '\n');
	stringstream ss(line);
	while (getline(ss, token, ' '))
		numAssets++;
	while (getline(infile, line, '\n'))
		numDates++;
}

Matrix DataCollector::readFromText(string filename, vector<string> &assetNames)
{
	//filename = "Stocks.txt";

	unsigned int numAssets, numDates;

	countStuff(filename, numAssets, numDates);

	//cout << numAssets << "\t" << numDates << endl;

	Matrix priceMatrix(numDates, numAssets);

	ifstream infile; //input file stream object
	infile.open(filename);

	if (!infile) {
		cerr << "Bad input! Can't open " << filename << endl;
		exit(1);
	}

	unsigned int i = 0;
	unsigned int j = 0;

	string line;
	string token;
	double price;
	getline(infile, line, '\n');
	stringstream ss(line);
	while (getline(ss, token, ' '))
	{
		//cout << token << "\t";
		assetNames.push_back(token);
	}
	//cout << endl;
	while (!infile.eof())
	{
		getline(infile, line, '\n');
		stringstream ss(line);
		j = 0;
		while (getline(ss, token, ','))
		{
			price = stod(token);
			priceMatrix(i, j) = price;
			j++;
			//cout << price << "\t";
		}
		//cout << endl;
		i++;
	}
	//cout << priceMatrix << endl;
	return priceMatrix;
}

Matrix DataCollector::readPMatrixFromText(string filename)
{
	unsigned int rows, columns;
	countLines(filename, rows, columns);
	ifstream infile; //input file stream object
	infile.open(filename);
	if (!infile) {
		cerr << "Bad input! Can't open " << filename << endl;
		exit(1);
	}
	Matrix P(rows, columns);
	unsigned int i = 0;
	unsigned int j = 0;
	string line;
	string token;
	while (!infile.eof())
	{
		getline(infile, line, '\n');
		stringstream ss(line);
		j = 0;
		while (getline(ss, token, ','))
		{
			P(i, j) = stod(token);
			j++;
			//cout << price << "\t";
		}
		i++;
	}
	return P;
}

Matrix DataCollector::readQMatrixFromText(string filename)
{
	unsigned int rows, columns;
	countLines(filename, rows, columns);
	ifstream infile; //input file stream object
	infile.open(filename);
	if (!infile) {
		cerr << "Bad input! Can't open " << filename << endl;
		exit(1);
	}
	Matrix Q(rows, 1);
	unsigned int i = 0;
	string line;
	while (getline(infile, line, '\n'))
	{
		Q(i++, 0) = stod(line);
	}
	return Q;
}
