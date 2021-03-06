// CometArray.cpp : A file to demonstrate the use of an
// array of classes.  Rather than open our DB and then
// read the entries one at a time into a single Comet object,
// we'll declare an array of Comets.  We'll thus open the DB
// file once BEFORE beginning the menu loop, read in all the
// Comets at once, then do menu stuff, then open the DB file
// at the end when exiting, and write all the Comets back out.
// The changes we make will therefore persist from one run
// of the program until the next.
// So, the file I/O is done in main(), not in choice-handlers,
// and therefore need to pass arguments to each handler:  the
// address of the array, and the # of entries in it.

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

/******* Our only globals are CONST variables  **************/
const string diskFileRd = "C:\\users\\ddavi\\comets_db.txt"; // Only 1 file now!
const int CA_SIZE = 10;  // # of slots in the Comet array					//++

/************* Our "Comet" class definition *****************/
class Comet
{
public:
	void putName(string newName); // Accessor-mutator function pairs
	string getName();
	void putDate(int date);
	int getDate();
	void putPeriod(int years);
	int getPeriod();

	Comet();		// Constructors. Note "overloading" of name. p.578
	Comet(string name);
	Comet(string name, int year, int period);

	bool rdDBEntry(istream& stream);  // Disk DB record rd-wrt pair
	void wrtDBEntry(ostream& stream) const;

	friend bool equalComet(const Comet& c1, const Comet& c2);
	friend bool operator ==(const Comet& c1, const Comet& c2);
	friend void operator ++(Comet& c);

private:
	void makeUC(string& s);	// A private "helper" function. ADTs p. 592

	string name;     // Possible to assign default vals HERE... See p. 587
	int yrsBetweenVisits;
	int dateOfNextVisit;
};

/****  Regular function prototypes (moved below Comet definition) ***/		//++
void viewDB(Comet C[], int size);
int add2DB(Comet C[], int size);
void updateVisitDates(Comet C[], int size);
void search4Comet(Comet C[], int size);

/*************************  Our main() ******************************/

int main()
{
	ifstream rdDB;	// Rd/wrt the SAME file, but need 1 of each stream object
	ofstream wrtDB;
	Comet CA[CA_SIZE];		// Our array of Comets							//++
	int caSize = 0;

	rdDB.open(diskFileRd);	// DB reading done one-time, before menu		//++
	while (CA[caSize].rdDBEntry(rdDB) == true)
	{
		if (++caSize >= CA_SIZE) // Got to keep within array bounds...
		{
			cout << "Array full! Skipping remaining DB entries.";
			break;
		}
	}
	rdDB.close(); // Done reading...  re-open later for writing

	char menuChoice;  // Simple menu 
	do
	{
		cout << "\n\nMenu: (V)iew DB, (N)ew entry, (U)pdate, (S)earch, e(X)it program: ";
		cin >> menuChoice;

		switch (menuChoice)
		{
		case 'X': case 'x':
			cout << "Goodbye!\n";
			wrtDB.open(diskFileRd);  // Re-open same file for writing		//++
			for (int ix = 0; ix < caSize; ix++)
				CA[ix].wrtDBEntry(wrtDB);  // Out it goes...
			wrtDB.close();
			return (0);
		case 'V': case 'v':
			viewDB(CA, caSize);												//++
			break;
		case 'N': case 'n':
			if (caSize < CA_SIZE)											//++
				caSize = add2DB(CA, caSize);  // This will increase array size!
			else
				cout << "Can't add a comet!  Array already full.";
			break;
		case 'U': case 'u':
			updateVisitDates(CA, caSize);									//++
			break;
		case 'S': case 's':	
			search4Comet(CA, caSize);										//++
			break;
		default:
			cout << "Illegal choice.  Try again. \n";
		}
	} while (true);

	return 0;
}

/**************** MUTATORS and ACCESSORS - paired ********************/

void Comet::putName(string newName)   // Pair for the "name" variable
{
	name = newName;		// MUTATOR puts new value
	makeUC(name);		// Asssure UC name, use "helper" function
}

string Comet::getName()
{
	return(name);		// ACCESSOR returns existing value
}

// Function pair for "dateOfNextVisit" private variable
void Comet::putDate(int date)
{
	dateOfNextVisit = date;
}

int Comet::getDate()
{
	return(dateOfNextVisit);
}

// Function pair for "yrsBetweenVisits" private variable
void Comet::putPeriod(int years)
{
	yrsBetweenVisits = years;
}

int Comet::getPeriod()
{
	return(yrsBetweenVisits);
}

/********** Constructors ********************************************/

Comet::Comet() : name("?"), yrsBetweenVisits(0), dateOfNextVisit(0)
{
	// Everything done in "constructor initialization" shown above
}

Comet::Comet(string s)  // This constructor handles single arg
{
	name = s;
	makeUC(name);
	yrsBetweenVisits = 0; // Defaults these 2 variable to zero
	dateOfNextVisit = 0;
}

Comet::Comet(string s, int year, int period)  // This one handles 3 args
{
	name = s;
	makeUC(name);
	yrsBetweenVisits = period;
	dateOfNextVisit = year;
}

/****** Public member functions that read and write DB entries *********/

// A member function that populates a Comet object with values
// fetched from a Database file.  If object is fetched from file,
// returns TRUE, otherwise, when none left to fetch, returns FALSE
bool Comet::rdDBEntry(istream& stream)
{
	if (stream >> name) // Evaluates TRUE if successful read of 1st field
	{
		makeUC(name);
		stream >> yrsBetweenVisits >> dateOfNextVisit; // Get other 2 fields
		return (true); // We GOT one!  Return TRUE
	}
	return (false); // Failed to get one from file.  Return FALSE
}

// A member function that writes the fields of a Comet object
// out to a Database file, tab separated, one comet per line.  Order
// of variables MUST match order in above rdDBEntry() function,
// as well as order in original Database.
void Comet::wrtDBEntry(ostream& stream) const
{
	stream << name << '\t' << yrsBetweenVisits << '\t' << dateOfNextVisit << endl;
}

/********************* Private "helper" functions ***********************/

// Function to convert all alphas in string to Upper Case.
// Call-by-ref "s" argument yields "in-place" conversion of the
// string at its location within scope of calling routine.
// Uses pointers, rather than array[index] method
void Comet::makeUC(string& s)
{
	char * cL = &s[0]; // Pointer to first char
	char * cR = &s[s.length()]; // Pointer BEYOND end of string

	for (; cL < cR; cL++) // Advance through chars
		if (isalpha(*cL))
			*cL = toupper(*cL);
}

/********* Friend functions & operator overloads ************************/

bool equalComet(const Comet& c1, const Comet& c2) // Friend function, are names equal?
{
	return (c1.name == c2.name);
}

bool operator == (const Comet& c1, const Comet& c2) // Overload == for equal names
{
	return (c1.name == c2.name);
}

void operator ++(Comet& c)  // Overload ++
{
	c.dateOfNextVisit = c.dateOfNextVisit + c.yrsBetweenVisits;
}

/**************  Menu-choice handler functions ************/

void search4Comet(Comet dbComet[], int aSize)	// (S)earch for comet in DB.
{
	string name;
	bool notFound = true;  // Assume it's NOT there...
	
	cout << "What is the comet's name? ";
	cin >> name;
	Comet search4(name);  // Construct local object w/ name only

	for (int ix = 0; ix < aSize; ix++)
	{
		// if (equalComet(dbComet[ix], search4))  // Compare w/ friend function
		if (dbComet[ix] == search4)  // Compare w/ overloaded operator ==		//**
		{
			cout << "Found! >> ";
			dbComet[ix].wrtDBEntry(cout);
			notFound = false;  // Now will skip failure msg. below
		}
	}
	if (notFound)  // Failure message
		cout << "Comet \"" << name << "\" not in DB.";
}

void viewDB(Comet dbComet[], int aSize) // The (V)iew menu choice
{
	for (int ix = 0; ix < aSize; ix++)
		dbComet[ix].wrtDBEntry(cout);
}

int add2DB(Comet dbComet[], int aSize) // The (N)ew menu choice.  Fetch data, build Comet
{
	string name;
	int period;
	int visitYear;
	char y_n;

	cout << "\nName of comet? ";
	cin >> name;
	cout << "Known orbital data (Y/N)? ";
	cin >> y_n;

	if ((y_n != 'y') && (y_n != 'Y')) {
		dbComet[aSize].putName(name);  // Use mutator to change just the name
		return(aSize + 1);
	}
	else {
		cout << "\nEnter VISIT YEAR followed by PERIOD: ";
		cin >> visitYear >> period;
		dbComet[aSize] = Comet(name, visitYear, period); // Can CALL a constructor
		return(aSize + 1);  // Array grew by one...
	}
}

void updateVisitDates(Comet dbComet[], int aSize)  // The (U)pdate menu choice.
{
	int thisYr;

	cout << "What year is it? ";
	cin >> thisYr;

	for (int ix = 0; ix < aSize; ix++)
		if (thisYr >= dbComet[ix].getDate())
			++dbComet[ix];	// Using overloaded operator ++
}
