// Ch-10-Classes-1.cpp : A file to demonstrate some first concepts
// related to defining a "class" and then declaring/defining/using
// "objects" belonging to that class.  Starts with our "struct"
// based lab project and shows how it transforms to a "class"-based
// implementation.  See lengthy comment at bottom of file.

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Person  // struct from line 116 now converted to class
{
public:
	void wrtPerson(ostream& wrtS);
	void rdPerson(istream& rdS);
	void putSSN(string SSN);  // A "mutator" function
	string getSSN();  // An "accessor" function
private:
	string last4SSN;
	string firstN;
	string lastN;
	string emailAddr;
};

int main()
{
	Person per1;  // Declares an "object", but fails to initialize
				  //per1.last4SSN = "8888"; // Not possible, once last4SSN is private!
	per1.putSSN("8888");  // Must update with "mutator", instead
	cout << "SSN = " << per1.getSSN() << endl;  // and fetch with "accessor"
	per1.wrtPerson(cout);

	ifstream rdStream;
	string diskFile = "C:\\users\\ddavi\\persons.txt";
	rdStream.open(diskFile); // Didn't check for failure, but YOU better!

	for (int ix = 0; ix < 5; ix++)
	{
		per1.rdPerson(rdStream);
		per1.wrtPerson(cout);
	}

	rdStream.close();  //.close() file when done
	return 0;
}

void Person::putSSN(string SSN)  // New "mutator" function
{
	last4SSN = SSN;
}

string Person::getSSN()  // New "accessor" function
{
	return(last4SSN);
}

void Person::wrtPerson(ostream& wrtS)
{
	wrtS << last4SSN << '\t' << lastN << ", " << firstN
		<< '\t' << emailAddr << endl;
}

void Person::rdPerson(istream& rdS)
{
	char c;

	rdS >> last4SSN >> firstN;
	rdS.get(c); // Pull leading tab character from stream
	getline(rdS, lastN, '\t'); // Grab multi-word name
	rdS >> emailAddr;  // Grab rest of line
}

/* In the large commented-out section below is the
"struct"-based version of the first lab.  In the
sequence of steps outlined below, that code is
transformed into the "class"-based version shown above.
Note that the code compiles and runs just fine at
various midway checkpoints: i.e., after steps 1, 3, 4,
5, 7.

1. Change single word "struct" to "class" and also
add the "public:" designator within the class
2. Move the 2 function prototypes -- rdPerson() and
wrtPerson() -- into the class as public members.
They're now member functions of the class.
3. Add "Person::" scope-resolution operator to
the function definitions, and also add the
"per1." phrase prior to calling rdPerson and
wrtPerson.  Now calling them as member functions.
4. Within rdPerson and wrtPerson, remove the "p1."
designators to access struct member variables,
because functions already KNOW which object to
access, given that each is called as a member
of a specific object.
5. Then remove the call-by-ref arguments for "p1"
from both the prototypes and the definitions of
rdPerson() and wrtPerson().  These are now
superfluous, because the function KNOWS which
object to work on...
6. Add the "private:" designation into the class
definition, separating the public functions from the
private variables.  Encapsulation and data-hiding!
7. Step (6) breaks the initialization of our per1 Person,
(in line 129 below) as the member variables are no
longer accessible.  Delete the initialization.
8. Add a "mutator" function putSSN()  and "accessor"
functions that are members of the class, and thus able
to get at the private variables, and that can be used to
update (i.e., to "mutate") the content of the private
variable last4SSN.
*/

/*
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
*/