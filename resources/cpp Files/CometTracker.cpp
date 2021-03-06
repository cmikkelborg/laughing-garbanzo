// CometTracker.cpp : A file to demonstrate aspects of
// OOP -- mutators, accessors, constructors, default
// constructor, and overloaded function names..

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

/****************  Regular function prototypes ****************/
void viewDB();
void add2DB();
void updateVisitDates();

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
	string name;     // Possible to assign default vals HERE... See p. 587
	int yrsBetweenVisits;
	int dateOfNextVisit;
};

/*************************  Our main() ******************************/

int main()
{
	char menuChoice;  // Simple menu, easy to copy/paste for your lab
	do
	{
		cout << "\n\nMenu: (V)iew DB, (N)ew entry, (U)pdate, e(X)it program: ";
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
			cout << "Not yet implemented.  Choose another. \n";
			//updateVisitDates(); // Just un-comment, if you want
			break;
		default:
			cout << "Illegal choice.  Try again. \n";
		}
	} while (true);

    return 0;
}

/**********************************************************************/
// Here are paired MUTATOR and ACCESSOR for "name" private variable
void Comet::putName(string newName) 
{
	name = newName;		// MUTATOR puts new value
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
	yrsBetweenVisits = 0; // Defaults these 2 variable to zero
	dateOfNextVisit = 0;
}

Comet::Comet(string s, int year, int period)  // This one handles 3 args
{
	name = s;
	yrsBetweenVisits = period;
	dateOfNextVisit = year;
}

/****** Our member functions that read and write DB entries ******************/

// A member function that populates a Comet object with values
// fetched from a Database file.  If object is fetched from file,
// returns TRUE, otherwise, when none left to fetch, returns FALSE
bool Comet::rdDBEntry(istream& stream)
{
	if (stream >> name) // Evaluates TRUE if successful read of 1st field
	{
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


/**************  Regular functions, one to handle each menu choice ************/

void viewDB() // The (V)iew menu choice
{
	ifstream rdDB;
	Comet aComet;  // Default constructor -- NO PARENTHESES!! p.586
	// aComet.wrtDBEntry(cout);
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

/**************************************************************/

//   A demo function that reads DB, 1 comet at a time, changes 1 field of each 
//   comet, writes DB to 2nd file.  This implements the (U) menu choice.
//   It's similar to the ageInventory() function you must write.

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

