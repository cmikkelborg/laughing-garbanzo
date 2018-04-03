// 14.1-recursion.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
using namespace std;

int factorial(int n);

int main()
{
	int numb;
	cout << "What is the number you would like to factorial?" << endl;
	cin >> numb;

	cout << factorial(numb) << endl;

	system("pause");
    return 0;
}

int factorial(int n)
{

	if (n <= 1)
		return n;
	return n * factorial(n - 1);
}
