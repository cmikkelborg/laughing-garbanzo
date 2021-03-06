// CometSearch.cpp : A file to demonstrate aspects of use
// of classes.  To support a new "(S)earch" menu function,
// I chose to make all comet names upper-case within
// the private member variable.  This makes it easier for
// me to implement a search, given that I need to compare
// the stored name to the name specified by the user.  To
// support this, I wrote a "private member" function (p.570)
// named makeUC(), which does the conversion.  I then needed
// to call that function at ALL places where a new value
// was being assigned to the comet's name -- that includes
// constructors, mutators, and our file-read function.
// Also demonstrates some use of accessor/mutator functions.
// Can't compare names of Comets without accessing the
// stored (and private) name variable...

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

/****************  Regular function prototypes ****************/
void viewDB();
void add2DB();
void updateVisitDates();
void search4Comet();														//++

/******* Our only globals are CONST variables of file names *******/
const string diskFileRd = "C:\\users\\ddavi\\comets_r.txt";
const string diskFileWrt = "C:\\users\\ddavi\\comets_w.txt";

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
	void wrtDBEntry(ostream& stream);
private:
	void makeUC(string& s);	// A private "helper" function.  p. 570			//++

	string name;  
	int yrsBetweenVisits;
	int dateOfNextVisit;
};

/*************************  Our main() ******************************/

int main()
{
	char menuChoice;  // Simple menu, easy to copy/paste for your lab 
	do
	{
		cout << "\n\nMenu: (V)iew DB, (N)ew entry, (U)pdate, (S)earch, e(X)it program: ";
		cin >> menuChoice;

		switch (menuChoice)
		{
		case 'X': case 'x':
			cout << "Goodbye!\n";
			return (0);
		case 'V': case 'v':
			viewDB();
			break;
		case 'N': case 'n':
			add2DB();
			break;
		case 'U': case 'u':
			updateVisitDates();
			break;
		case 'S': case 's':													//++
			search4Comet();
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
	makeUC(name);		// Asssure UC name, use "helper" function			//++
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

Comet::Comet() : name("?"), yrsBetweenVisits(0), dateOfNextVisit(0) // Default constructor has NO args
{
	// Line above shows "constructor initialization" as shown on p.582
	// It's equivalent to the three commented-out lines below.
	// name = "?";
	// yrsBetweenVisits = 0;
	// dateOfNextVisit = 0;
}

Comet::Comet(string s)  // This constructor handles single arg
{
	name = s;
	makeUC(name);															//++
	yrsBetweenVisits = 0; // Defaults these 2 variable to zero
	dateOfNextVisit = 0;
}

Comet::Comet(string s, int year, int period)  // This one handles 3 args
{
	name = s; 
	makeUC(name);															//++
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
		makeUC(name);														//++
		stream >> yrsBetweenVisits >> dateOfNextVisit; // Get other 2 fields
		return (true); // We GOT one!  Return TRUE
	}
	return (false); // Failed to get one from file.  Return FALSE
}

// A member function that writes the fields of a Comet object
// out to a Database file, tab separated, one comet per line.  Order
// of variables MUST match order in above rdDBEntry() function,
// as well as order in original Database.
void Comet::wrtDBEntry(ostream& stream)
{
	stream << name << '\t' << yrsBetweenVisits << '\t' << dateOfNextVisit << endl;
}

/********************* Private "helper" functions ***********************/

// Function to convert all alphas in string to Upper Case.
// Call-by-ref "s" argument yields "in-place" conversion of the
// string at its location within scope of calling routine.
// Uses pointers, rather than array[index] method
void Comet::makeUC(string& s)												//++
{
	char * cL = &s[0]; // Pointer to first char
	char * cR = &s[s.length()]; // Pointer BEYOND end of string

	for (; cL < cR; cL++) // Examine each char, in turn
		if (isalpha(*cL))
			*cL = toupper(*cL);
}

/**************  Menu-choice handler functions ************/

void search4Comet()	// Choice to (S)earch for comet in DB.					//++
{
	string name;
	bool notFound = true;  // Assume it's NOT there...
	ifstream rdDB;
	Comet dbComet;  // Local object to hold disk DB entries
	
	cout << "What is the comet's name? ";
	cin >> name;
	Comet search4(name);  // Construct 2nd local object w/ name only

	rdDB.open(diskFileRd);
	while (dbComet.rdDBEntry(rdDB) == true) // Loop until all entries read
	{
		if (dbComet.getName() == search4.getName())  // Use "accessors" to see names
		{
			cout << "Found! >> ";
			dbComet.wrtDBEntry(cout);
			notFound = false;  // Now will skip failure msg. below
		}
	}
	if (notFound)  // Failure message
		cout << "Comet \"" << name << "\" not in DB.";

	rdDB.close();
}

void viewDB() // The (V)iew menu choice
{
	ifstream rdDB;
	Comet aComet;  // Default constructor -- NO PARENTHESES!! p.586
	// aComet.wrtDBEntry(cout); // Debug: see that the defaults were used...
	rdDB.open(diskFileRd);
	while (aComet.rdDBEntry(rdDB) == true) // Loop until all entries read
		aComet.wrtDBEntry(cout);

	rdDB.close();
}

void add2DB() // The (N)ew menu choice.  Fetch data, build Comet, APPEND to DB file
{
	string name;
	int period;
	int visitYear;
	char y_n;

	ofstream wrtDB;
	wrtDB.open(diskFileRd, ios::app); // Open DB file for WRITE/APPEND p. 321

	cout << "\nName of comet? ";
	cin >> name;
	cout << "Known orbital data (Y/N)? ";
	cin >> y_n;

	if ((y_n != 'y') && (y_n != 'Y')) { // See top p. 345 re: this logic
		Comet newComet(name);  // Constructor with 1 arg
		newComet.wrtDBEntry(wrtDB);
	}
	else {
		cout << "\nEnter VISIT YEAR followed by PERIOD: ";
		cin >> visitYear >> period;
		Comet newComet(name, visitYear, period);  // Constructor with 3 args
		newComet.wrtDBEntry(wrtDB);
	}

	wrtDB.close();
}

//  The (U)pdate menu choice.  Cycles DB entries through a local Comet
//  object, updating nextVisitDate if necessary.  Writes to 2nd file.
void updateVisitDates()  // The (U)pdate menu choice.
{
	int thisYr, nextVisit;
	Comet aComet;  // A single local "comet" object we'll shuffle them through

	ifstream rdDB;  // Got to open TWO files, one to read, other to write
	ofstream wrtDB;
	rdDB.open(diskFileRd); // Again, YOU should check for file-open errors
	wrtDB.open(diskFileWrt);

	cout << "What year is it? ";
	cin >> thisYr;

	while (aComet.rdDBEntry(rdDB) == true) // Loop until all entries read
	{
		// If the year that a comet visits is NOW, or IN THE PAST, then
		// the comet's PERIOD needs to be added to the DATE of last visit,
		// and the result "put" back into the comet object.

		if (thisYr >= aComet.getDate())
		{
			nextVisit = aComet.getPeriod() + aComet.getDate();
			aComet.putDate(nextVisit);
		}
		// aComet.wrtDBEntry(cout); // Just for debug
		aComet.wrtDBEntry(wrtDB);
	}

	rdDB.close();
	wrtDB.close();
}
