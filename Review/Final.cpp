// 62fileInput.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream> // for cout, cin
#include <fstream>  // for file I/O
#include <string>
#include <vector>
using namespace std;


int main()
{

	int num1 = 5;
	int *p1;
	p1 = &num1;
	cout << "*p1 is: " << *p1 << endl;
	
	system("pause");
	return 0;
}

