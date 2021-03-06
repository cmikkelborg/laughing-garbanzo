//Lab01.cpp
//Author: Charles Mikkelborg, Joel Davis
//Description: Reads an input file to poplulate a structure that can be outputted to the console.
//Last modified: 04/09/2018

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

void rdPerson(istream&, Person&);
void makeUC(string& name);
void wrtPerson(Person&);

int main()
{
	// initializing an instance of Person struct to be used by the loop.
	Person per1 = {};

	// accessing asset persons.txt
	ifstream rdStream;
	string diskFile = "C:\\Users\\cmikk\\OneDrive\\School\\Q3 - Spring 2018\\Computer Science 2\\assets\\persons.txt";
	rdStream.open(diskFile);

	// check for file load error.
	if (rdStream.fail())
	{
		cout << "File open failed." << endl;
		system("pause");
		exit(1);
	}

	// loop continues to execute its functions as long as there is an integer from the stream that can be entered 
	//  into last4SSN, if not then break. 
	do
	{
		if (rdStream >> per1.last4SSN)
		{
			rdPerson(rdStream, per1);
			makeUC(per1.lastN);
			makeUC(per1.firstN);
			wrtPerson(per1);
		}
		else
			break;

	} while (true);

	system("pause");
	return 0;
}

// a file read function, that parses read data of a stream into seperate variables within an instance of Person struct.
void rdPerson(istream& rdS, Person& per)
{
	rdS >> per.firstN;
	rdS.get();
	getline(rdS, per.lastN, '\t');
	rdS >> per.emailAddr;
}

// strings passed into this function are modified to all caps.
void makeUC(string& name)
{
	string upper(name);
	for (int i = 0; i < name.length(); i++)
		upper[i] = toupper(name[i]);
	name = upper;
}

// display function, the variables of a passed instance of Person struct are displayed to the console.
void wrtPerson(Person& per1)
{
	cout << per1.lastN << ", " << per1.firstN << ":" << per1.last4SSN << ":" << per1.emailAddr << endl;
}
