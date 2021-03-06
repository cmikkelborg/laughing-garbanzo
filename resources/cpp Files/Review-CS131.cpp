// ReviewStruct.cpp : This demo file is intended to get folks
// back up to speed with respect to a C++ struct, and also
// with respect to the mechanics of file I/O.

#include "stdafx.h" 
#include <iostream>  // Need for console I/O
#include <fstream>  // Need for file I/O
#include <string>
using namespace std;

// Recall that a "struct" is meant to allow you to bundle
// some logically connected simple variables into a "type"
// of your own. Here's a "Person" type that has details
// of info that relate to a person.  p. 550
struct Person
{
	int last4SSN;
	string firstN;
	string lastN;
	string emailAddr;
};

void rdPerson(istream& rdS, Person& p1); // Function prototype

int main()
{
	// Recall that C++ can treat a FILE as a "stream" object, in
	// the same way it treats the CONSOLE as a stream.  To do so,
	// we must DECLARE an instance of a file stream object that 
	// is intended to handle input, as below.  The identifier
	// "rdStream" is the invented name that we will use to access
	// the content of a disk file that we'll access, using all the
	// normal tools to access a stream, such as >> and getline().
	// See p. 313 - 318
	ifstream rdStream;

	// Recall that when working with files, each file has TWO "names"
	// One is its name in the external Windows file system.  We
	// must know that name in order for Windows to find it. p. 310
	string diskFile = "C:\\users\\ddavi\\persons.txt";

	// The stream object "rdStream" has various member functions
	// that can be invoked.  .open(), .close(), etc.  p. 318 
	// rdStream is opened by using the .open() function to target 
	// the diskFile we specified earlier.
	rdStream.open(diskFile);

	// Remember to check and handle error!  p.314
	if (rdStream.fail())
	{
		cout << "dang!";// handle error
	}

	// Can simultaneously DECLARE and INITIALIZE a struct  p. 551
	Person per1 = { 1234, "Jane", "Doe", "jdoe@gmail.com" };

	// Component variables of struct are accessed with dot operator.
	cout << per1.firstN << " " << per1.lastN << " has SSN: " << per1.last4SSN << endl;

	// Can do I/O with stream objects using normal >> and << operators
	rdStream >> per1.last4SSN >> per1.firstN;

	cout << "per1 SSN is now: " << per1.last4SSN << " with first name " << per1.firstN << endl;

	// rdPerson(rdStream, per1);  // Can activate this line to read from FILE
	// rdPerson(cin, per1);  // Can instead activate THIS line to read from CONSOLE

	cout << "per1 last name is " << per1.lastN << endl;

	rdStream.close();  // Remember to .close() file when done
	return 0;
}

// Can pass a stream object to a function, as long as is done
// as call-by-reference.  Can use specific identifier "istream" as
// the argument type such that the function will work correctly with
// EITHER a file stream object or a console stream object.  p. 346
// Can also pass a struct to a function, either call-by-ref, or
// call-by-val.  Call-by-ref allows you to directly modify
// the member variables in the struct within the scope of main().
void rdPerson(istream& rdS, Person& p1)
{
	rdS >> p1.lastN; // Assigning new value to member variable of "p1"
	return;
}