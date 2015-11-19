#include <stdio.h>
#include <iostream>
#include "Matrix.h"

using namespace std;

int main()
{
	/*
	cout << "Hello World!" << endl;
	
	Matrix test(4, 4);
	test(1, 2) = 106.15;
	test(1, 2) *= .5;
	test(0, 0) = 8;
	
	cout << test(1, 2) << endl;
	cout << test << endl;
	Matrix test2 = (test*.5);
	cout << test2 << endl;
	cout << test + test2 << endl;

	Matrix test3 = test2.transpose();
	//Matrix test3(test2.transpose());
	cout << test3 << endl;
	cout << test3.trace() << endl;
	cout << test3.removeColumn(1) << endl;
	cout << test3.removeRow(1) << endl;
	*/

	Matrix detTest(4, 4);
	detTest(0, 0) = 3;
	detTest(0, 1) = 0;
	detTest(0, 2) = 2;
	detTest(0, 3) = -1;
	detTest(1, 0) = 1;
	detTest(1, 1) = 2;
	detTest(1, 2) = 0;
	detTest(1, 3) = -2;
	detTest(2, 0) = 4;
	detTest(2, 1) = 0;
	detTest(2, 2) = 6;
	detTest(2, 3) = -3;
	detTest(3, 0) = 5;
	detTest(3, 1) = 0;
	detTest(3, 2) = 2;
	detTest(3, 3) = 0;

	cout << detTest << endl;
	cout << "det :" << detTest.determinant() << endl;

	//detTest.setRow(2, 2*detTest.getRow(0) + detTest.getRow(2));
	//cout << detTest << endl;
	/*
	Matrix lhm(2, 3);

	lhm(0, 0) = 1;
	lhm(0, 1) = 2;
	lhm(0, 2) = -3;
	lhm(1, 0) = 4;
	lhm(1, 1) = -1;
	lhm(1, 2) = 2;
	cout << lhm << endl;

	Matrix rhm(3, 2);
	rhm(0, 0) = 1;
	rhm(0, 1) = 2;
	rhm(1, 0) = -3;
	rhm(1, 1) = -1;
	rhm(2, 0) = -2;
	rhm(2, 1) = 0;
	cout << rhm << endl;

	cout << lhm*rhm << endl;
	*/
	//cout << detTest*Matrix::IdentityMatrix(4) << endl;
	Matrix inverse = detTest.inverse();
	cout << inverse << endl;
	cout << detTest * inverse << endl;
	return 0;
}
