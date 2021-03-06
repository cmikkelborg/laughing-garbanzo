// 04.05Notes.cpp : Defines the entry point for the console application.
// book reference struct: p550, fileIO: p313-318, functions: p346. 

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;



struct Person
{
	int last4SSN;
	string firstN, lastN, emailAddr;

};

void rdPerson(istream& rdS, Person& p1);

int main()
{
	Person per1 = { 1234, "Charles", "Mikkelborg", "cmikk@gmail.com" };
	cout << per1.firstN << " " << per1.lastN << "'s SSN is: " << per1.last4SSN << endl;

	ifstream rdStream;
	string diskFile = "\\assets\\persons.txt";
	rdStream.open(diskFile);
	if (rdStream.fail())
	{
		cout << "File open failed." << endl;
		system("pause");
		exit(1);
	}

	rdStream >> per1.last4SSN >> per1.firstN;
	cout << per1.firstN << " " << per1.lastN << "'s SSN is: " << per1.last4SSN << endl;
	rdPerson(rdStream, per1); //will read lastN from file.
	//rdPerson(cin, per1); //will ask for input for lastN.
	cout << per1.firstN << " " << per1.lastN << "'s SSN is: " << per1.last4SSN << endl;

	rdStream.close();
	system("pause");
    return 0;
}

void rdPerson(istream& rdS, Person& p1)
{
	rdS >> p1.lastN;
	return;
}
