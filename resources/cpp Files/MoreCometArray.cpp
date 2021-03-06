// MoreCometArray.cpp : A file to demonstrate use of a dynamic 
// array WITHIN a class.  The Comet database file now has added
// contents.  A "listSize" integer on the same line as the other
// variables indicates how many following lines of text are
// present that belong to that same Comet.  This program will
// read listSize, declare a dynamic string[] array of the 
// correct size, and input the extra lines.  To do the new
// reading task, this file also uses the overloaded << and >>
// operators, replacing the rdDBEntry and wrtDBEntry functions
// previously used.  Also built a "destructor" to delete
// dynamic arrays after use.  Removed everything else that I
// could in order to narrow the focus.

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

/******* Our only globals are CONST variables  **************/
const string diskFileRd = "C:\\users\\ddavi\\comets_db.txt";
const int CA_SIZE = 10;  // # of slots in the Comet array					

/************* Skimpy "Comet" class definition *****************/
class Comet
{
public:
	Comet();		// Constructor

	~Comet();		// Destructor											//++
	friend ostream& operator << (ostream& outS, const Comet& c);			//++
	friend istream& operator >> (istream& inS, Comet& c);					//++

private:
	string name;
	int yrsBetweenVisits;
	int dateOfNextVisit;
	int listSize = 0; // # of added lines per Comet							//++
	string * listPtr = NULL; // To point to the dynamic array				//++
};

/****  Regular function prototypes (must be below Comet definition) ***/
void viewDB(Comet C[], int size);

/*************************  Our main() ******************************/

int main()
{
	ifstream rdDB;
	ofstream wrtDB;
	Comet CA[CA_SIZE];		// Array of Comets
	int caSize = 0;

	rdDB.open(diskFileRd);
	while (rdDB >> CA[caSize]) // Loop reading entries with new operator	//++
	{
		if (++caSize >= CA_SIZE) // Keep within array bounds...
		{
			cout << "Array full! Skipping remaining DB entries.";
			break;
		}
	}
	rdDB.close(); // Done reading...  re-open later for writing

	char menuChoice;  // Simple menu 
	do
	{
		cout << "\n\nMenu: (V)iew DB, e(X)it program: ";
		cin >> menuChoice;

		switch (menuChoice)
		{
		case 'X': case 'x':			// e(X)it -- write DB out to disk!
			cout << "Goodbye!\n";
			wrtDB.open(diskFileRd);  // Re-open same file for writing
			for (int ix = 0; ix < caSize; ix++)  // Iterate through comet array
				wrtDB << CA[ix];  // Overloaded << 									//++
			wrtDB.close();
			return (0);

		case 'V': case 'v':			// (V)iew contents of DB
			viewDB(CA, caSize);	
			break;

		default:
			cout << "Illegal choice.  Try again. \n";
		}
	} while (true);

	return 0;
}
/**************  Menu-choice handler functions ************/

void viewDB(Comet C[], int aSize) // The (V)iew menu choice
{
	for (int ix = 0; ix < aSize; ix++)
		cout << C[ix];		// Using overloaded <<							//++
}

/********** Constructor & Destructor   ****************************/

Comet::Comet() : name("?"), yrsBetweenVisits(0), dateOfNextVisit(0) 
{
	listSize = 0; // # of added text lines for the Comet					//++
	listPtr = NULL; // To point to the dynamic array						//++
	cout << "+";
}

// For this destructor to work, the "listPtr" variable MUST remain
// unchanged from the moment that it received a value in the
// " new string[listSize] " statement on line 144.  If it WAS
// changed along the way, then it no longer points at a piece of
// freestore memory that is recognizable by the system runtime
// functions, and the " delete[] " will fail, and likely crash
// the program.
Comet::~Comet()  // A destructor, to free up dynamic memory. See p.672		//++
{
	if (listPtr != NULL)	// ONLY call delete [] if listPtr is...
		delete[] listPtr;	//  ... pointing at real content!!
	listPtr = NULL;			// Reset things to empty
	listSize = 0;
	cout << "-";
}

/******************  Overloaded operators ***************/

// When overloading >> and <<, the functions HAVE to return stream
// objects, NOT the boolean that we had been using.  Rewrote this, then,
// to attempt to read a new Comet entry from file.  If c.name is read,
// then I assume the rest of the variables will ALSO be read.  If c.name
// is NOT read, no further reading is done, and in EITHER case, a
// stream object "inS" is the return value.
istream& operator >> (istream& inS, Comet& c)    // Overload >>				//++
{
	c.name[0] = '?'; // Put known value into first char...
	inS >> c.name;   //   ... then fetch "name" from input stream
	if (c.name[0] != '?') // If content DID arrive, it overwrote "?"!
	{
		inS >> c.yrsBetweenVisits >> c.dateOfNextVisit >> c.listSize;
		inS.get();  // Gobble up the '\n' at end of line..

		if (c.listSize > 0) // Added lines of text?
		{
			c.listPtr = new string[c.listSize];  // Create dynamic array of correct size
			string * sPtr = c.listPtr;  // PRESERVE value of listPtr for later use
			for (int ix = 0; ix < c.listSize; ix++)  // For each extra line of text...
			{
				getline(inS, *sPtr); // Fetch the line, and...
				sPtr++;				//   ...advance pointer to next row of storage in string[]
			}
		}
	}
	return(inS);
}

// Again, this function MUST return a stream object.
ostream& operator << (ostream& outS, const Comet& c)	// Overload of <<	//++
{
	outS << c.name << '\t' << c.yrsBetweenVisits << '\t' << c.dateOfNextVisit << '\t' << c.listSize << endl;

	if (c.listSize > 0)  // Is there list of chemicals?
	{
		string * sPtr = c.listPtr;  // Init. a ptr to scan through the dynamic array
		for (int ix = 0; ix < c.listSize; ix++) // For each line of text...
		{
			outS << *sPtr << endl;				//   send it to stream, along with '\n'
			sPtr++;								//      and advance to next row of string[]
		}
	}
	return(outS);
}
