// Lab02.cpp
// Author: Charles Mikkelborg, Brett Turner
// Description: Reads an input file to poplulate a class object that can be output to the console and a file.
//		Includes functionality to view the database, enter a new vehicle, update how many weeks a car has been the lot,
//		and search by VIN number.
// Last modified: 04/18/2018
/*
Part 1.  Augment your code to incorporate three new things. 
FIRST, change your internal representation of a VIN to be represented by three separate strings -- 
a 1-char string that is the leading digit, a 3-char string that is the LETTERS, and a third string to hold the trailing digits.  
You'll need to update your constructors, accessors, mutators (including the 2 functions that read/write disk) to make things work transparently for non-class functions that use your Vehicle class.  
The disk file format should remain unchanged.  SECOND, write a friend function that compares two Vehicle objects for equality, with equality defined as the alpha letters of the VIN being equal.  
Use that friend function in your (S)earch menu option.  THIRD, write code that overloads the ++ operator, such that it performs the incrementing of weeksOnLot for a given object.  
Use the new operator in your (U)pdate menu option.

Part 2.  Modify your code to make use of an array of vehicle objects.  
In this way you can read the entire disk DB into memory once, at the onset of main(), do all manipulations [search, update ages, add vehicle, view] with reference to the array, 
and then write the array back TO THE SAME DB FILE when exiting the program.  
Most of the menu-handler functions must then be modified to accept two arguments (the name/size of the array), and to remove the file-handling they've thus far been doing, 
and to act upon the array-member objects, rather than upon a locally-declared Vehicle object.  One of them (the "add new vehicle") must modify the "fullness" of the array.
*/

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

/******* Our only globals are CONST variables  **************/
const string diskFileRd = "vehicles.txt";
const int VA_SIZE = 10;


/****************  Member functions  *****************/
class Vehicle
{
public:
	/* Mutator and Accessor declarations */
	string rdVin();
	void wrtVin(string wVin);
	double rdPrice();
	void wrtPrice(double wPrice);
	int rdWeeksOnLot();
	void wrtWeeksOnLot(int wWol);
	void vinBreaker(string wVin);
	string wholeVin();

	/* Constructor declarations */
	Vehicle();
	Vehicle(string vin);
	Vehicle(string a, string s, string d, double p);

	bool rdDBEntry(istream& stream);  // Disk DB record rd-wrt pair
	void wrtDBEntry(ostream& stream);

	friend bool equalVins(const Vehicle& vin1, const Vehicle& vin2);
	friend void operator ++(Vehicle& v);

private:
	void makeUC(string& s);	// A private make uppercase function
	string v1 = "";
	string vin;
	string v3 = "";
	double price;
	int weeksOnLot;
};

/****************  Regular functions  ***************/
void viewDB(Vehicle V[], int size);
int add2DB(Vehicle V[], int size);
void updateWeeksOnLot(Vehicle V[], int size);
void search4Vehicle(Vehicle V[], int size);
bool checkUpperAlpha(string &s);

int main()
{
	ifstream rdDB;
	ofstream wrtDB;
	Vehicle VA[VA_SIZE];
	int vaSize = 0;

	rdDB.open(diskFileRd);
	while (VA[vaSize].rdDBEntry(rdDB) == true)
	{
		if (++vaSize >= VA_SIZE)
		{
			cout << "Array full! Skipping remaining DB entries.";
			break;
		}
	}
	rdDB.close();
	/* Menu */
	char menuChoice;
	do
	{
		cout << "\n\nMenu: (V)iew DB, (N)ew entry, (U)pdate, (S)earch, e(X)it program: ";
		cin >> menuChoice;

		switch (menuChoice)
		{
		case 'X': case 'x':
			cout << "Goodbye!\n";
			wrtDB.open(diskFileRd);
			for (int ix = 0; ix < vaSize; ix++)
				VA[ix].wrtDBEntry(wrtDB);
			wrtDB.close();
			return(0);
		case 'V': case 'v':
			viewDB(VA, vaSize);
			break;
		case 'N': case 'n':
			if (vaSize < VA_SIZE)
				vaSize = add2DB(VA, vaSize);
			else
				cout << "Can't add a vehicle! Array already full.";
			break;
		case 'U': case 'u':
			updateWeeksOnLot(VA, vaSize);
			break;
		case 'S': case 's':
			search4Vehicle(VA, vaSize);
			break;
		default:
			cout << "Illegal choice.  Try again. \n";
		}
	} while (true);

	return 0;
}

/************* "Friend" functions and operator overload ***************/
bool equalVins(const Vehicle& vin1, const Vehicle& vin2)
{
	return (vin1.vin == vin2.vin);
}

void operator ++(Vehicle& v)
{
	v.weeksOnLot = v.weeksOnLot++;
}

/**********************************************************************/
// Here are paired MUTATOR and ACCESSOR functions for private Vehicle variables

string Vehicle::rdVin()		// Accessor to read private variable "vin"
{
	return string(wholeVin());
}

void Vehicle::wrtVin(string wVin)		// Mutator to change private variable "vin"
{
	makeUC(wVin);		// Assure UC vin through "helper" function
	vinBreaker(wVin);
}

double Vehicle::rdPrice()		// Accessor to read private variable "price"
{
	return double(price);
}

void Vehicle::wrtPrice(double wPrice)		// Mutator to change private variable "price"
{
	price = wPrice;
}

int Vehicle::rdWeeksOnLot()		// Accessor to read private variable "weeksOnLot"
{
	return(weeksOnLot);
}

void Vehicle::wrtWeeksOnLot(int wWol)		// Mutator to change private variable "weeksOnLot"
{
	weeksOnLot = wWol;
}

void Vehicle::vinBreaker(string wVin)
{
	v1 = wVin.substr (0);
	vin = wVin.substr (1, 3);
	v3 = wVin.substr (4, 8);
}

string Vehicle::wholeVin()
{
	string wholeVin;
	wholeVin.replace(0, 0, v1);
	wholeVin.replace(1, 3, vin);
	wholeVin.replace(4, 8, v3);
	return wholeVin;
}

/**********************************************************************/
// Here are CONSTRUCTOR definitions

Vehicle::Vehicle() : vin("?"), price(0.00), weeksOnLot(0) // Default constructor
{

}

Vehicle::Vehicle(string s) // Constructor with vin field
{
	makeUC(s);	// UC vin through "helper" function
	vin = s;
	price = 0.00;
	weeksOnLot = 0;
}

Vehicle::Vehicle(string a, string s,  string d, double p) // Constructor with vin and price fields
{
	makeUC(s);	// UC vin through "helper" function
	v1 = a;
	vin = s;
	v3 = d;
	price = p;
	weeksOnLot = 0;
}

/****** Our member functions that read and write DB entries ******************/

// A member function that populates a Vehicle object with values
// fetched from a Database file.  If object is fetched from file,
// returns TRUE, otherwise, when none left to fetch, returns FALSE
bool Vehicle::rdDBEntry(istream& stream)
{
	/* Set a fixed double decimal amount to 2 places */
	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(2);

	if (stream >> vin) // Evaluates TRUE if successful read of 1st field
	{
		makeUC(vin);
		vinBreaker(vin);
		stream >> price >> weeksOnLot; // Get other 2 fields
		return (true);
	}
	return (false);
}

// A member function that writes the fields of a Vehicle object
// out to the console or a Database file, tab separated, one vehicle per line.
void Vehicle::wrtDBEntry(ostream& stream)
{
	/* Set a fixed double decimal amount to 2 places */
	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(2);

	stream << wholeVin() << '\t' << price << '\t' << weeksOnLot << endl;
}

/********************* Private "helper" functions ***********************/

// Function to convert all letters in string to Upper Case.
void Vehicle::makeUC(string& s)
{
	char * cL = &s[0]; // Pointer to first char
	char * cR = &s[s.length()]; // Pointer BEYOND end of string

	for (; cL < cR; cL++) // Examine each char, in turn
		if (isalpha(*cL))
			*cL = toupper(*cL);
}

/**************  Regular functions, one to handle each menu choice ************/

// Displays a list of vehicles that are in the database
void viewDB(Vehicle V[], int size) // The (V)iew menu choice
{
	ifstream rdDB;
	Vehicle aVehicle;  // Default constructor
	rdDB.open(diskFileRd);
	if (rdDB.fail())
	{
		cout << "Open File Error";
		exit(1);
	}
	while (aVehicle.rdDBEntry(rdDB) == true) // Loop until all entries read
		aVehicle.wrtDBEntry(cout);

	rdDB.close();
}

// Lets the user input a vehicle to be added to the database
int add2DB(Vehicle dbVehicle[], int aSize) // The (N)ew menu choice.  Fetch data, build Vehicle, APPEND to DB file
{
	string vin;
	string v1;
	string v3;
	double price;
	char y_n;

	cout << "\nEnter Vehicle VIN number: " << endl;
	cin >> vin;
	cout << "Known vehicle price (Y/N)? ";
	cin >> y_n;

	if ((y_n != 'y') && (y_n != 'Y')) { // if 'y' or 'Y' are entered then ask for price
		dbVehicle[aSize].wrtVin(vin);
		return(aSize + 1);
	}
	else {
		cout << "\nEnter Vehicle price: " << endl;
		cin >> price;
		dbVehicle[aSize] = Vehicle(v1, vin, v3, price);
		return(aSize + 1);
	}
}

// Increments the number of weeks a vehicle has been on the lot by 1, writes the updated database to a new file
void updateWeeksOnLot(Vehicle V[], int size)
{

	Vehicle aVehicle;  // A single local "vehicle" object

	//while (aVehicle.rdDBEntry(rdDB) == true) // Loop until all entries read
	{

			//aVehicle.rdWeeksOnLot();
			//++aVehicle;						// Using the overloaded operator
			//aVehicle.wrtDBEntry(wrtDB);
	}
}

// User can search the vehicle database by entering three uppercase letters that are in the vehicles vin
// If a vin with those letters is found information about that vehicle is displayed
void search4Vehicle(Vehicle V[], int size)	// Choice to (S)earch for vehicle in DB.
{
	string vin;
	bool notFound = true;  // Assume it's NOT there...
	ifstream rdDB;
	Vehicle dbVehicle;		// Local object to hold disk DB entries			
	cout << "Enter the first 3 capital letters of the vehicle's vin: ";
	cin >> vin;
	Vehicle search4(vin);		// Local object to hold disk DB entries			


	if ((vin.length() == 3) && (checkUpperAlpha(vin)))
	{
		rdDB.open(diskFileRd);

		if (rdDB.fail())
		{
			cout << "Open File Error";
			exit(1);
		}

		while (dbVehicle.rdDBEntry(rdDB) == true) // Loop until all entries read
		{

			if (equalVins(search4, dbVehicle))  // Use "accessors" to see vins and check for a match
			{
				cout << "Found! >> ";
				dbVehicle.wrtDBEntry(cout);
				notFound = false;  // Now will skip failure msg. below
			}
		}
		if (notFound)  // Failure message
			cout << "Vehicle \"" << vin << "\" not in DB.";

		rdDB.close();
	}
	else
	{
		cout << "Three capital letters not entered.";
	}
}

// Checks if a string consists of entirely uppercase alpha characters
bool checkUpperAlpha(string &s)
{
	int i = 0;
	char * cL = &s[0];
	char * cR = &s[s.length()];

	for (; cL < cR; cL++)
		if (!isalpha(*cL) || (!isupper(*cL)))
			i++;
	if (i >= 1)
		return false;
	else
		return true;
}
