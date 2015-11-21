#pragma once
#include <string>
#include <vector>
#include "Matrix.h"

using namespace std;

class DataCollector
{
public:
	DataCollector();
	~DataCollector();

	Matrix readFromText(string filename, vector<string> &assetNames);
};

