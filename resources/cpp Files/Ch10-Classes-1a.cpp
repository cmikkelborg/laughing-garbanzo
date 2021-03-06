// Ch-10-Classes-1.cpp : A file to demonstrate some first concepts
// related to defining a "class" and then declaring/defining/using
// "objects" belonging to that class.

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;


struct Person  // struct used in first lab
{
	string last4SSN;
	string firstN;
	string lastN;
	string emailAddr;
};
void wrtPerson(ostream& wrtS, Person& p1);
void rdPerson(istream& rdS, Person& p1);


int main()
{
	Person per1 = { "1234", "Jane", "Doe", "jdoe@gmail.com" };
	wrtPerson(cout, per1);

	ifstream rdStream;
	string diskFile = "C:\\users\\ddavi\\persons.txt";
	rdStream.open(diskFile); // Not checking for failure, but YOU better!

		for (int ix = 0; ix < 5; ix++)
		{
			rdPerson(rdStream, per1);
			wrtPerson(cout, per1);
		}
	
	rdStream.close();  //.close() file when done
	return 0;
}


void wrtPerson(ostream& wrtS, Person& p1)
{
	wrtS << p1.last4SSN << '\t' << p1.lastN << ", " << p1.firstN
		<< '\t' << p1.emailAddr << endl;
}

void rdPerson(istream& rdS, Person& p1)
{
	char c;

	rdS >> p1.last4SSN >> p1.firstN;
	rdS.get(c); // Pull leading tab character from stream
	getline(rdS, p1.lastN, '\t'); // Grabs multi-word name
	rdS >> p1.emailAddr;  // Grabs rest of line
}
