// Lab02.cpp
// Author: Charles Mikkelborg, Brett Turner
// Description: Reads an input file to poplulate a class object that can be output to the console and a file.
//		Includes functionality to view the database, enter a new vehicle, update how many weeks a car has been the lot,
//		and search by VIN number.
// Last modified: 04/18/2018

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

/****************  Regular functions  ***************/
void viewDB();
void add2DB();
void updateWeeksOnLot();
void search4Vehicle();
bool checkUpperAlpha(string &s);

const string diskFileRd = "vehicles.txt";
const string diskFileWrt = "aged_vehicles.txt";

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
	Vehicle(string vin, double price);

	bool rdDBEntry(istream& stream);  // Disk DB record rd-wrt pair
	void wrtDBEntry(ostream& stream);
private:
	void makeUC(string& s);	// A private make uppercase function
	string v1 = "A";
	string vin;
	string v3 = "Z";
	double price;
	int weeksOnLot;
};

int main()
{
	/* Set a fixed double decimal amount to 2 places */
	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(2);

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
			return (0);
		case 'V': case 'v':
			viewDB();
			break;
		case 'N': case 'n':
			add2DB();
			break;
		case 'U': case 'u':
			updateWeeksOnLot();
			break;
		case 'S': case 's':
			search4Vehicle();
			break;
		default:
			cout << "Illegal choice.  Try again. \n";
		}
	} while (true);

	return 0;
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
	string tv1(wVin, 0, 1);
	string tvin(wVin, 1, 3);
	string tv3(wVin, 4, 5);
	v1 = tv1;
	vin = tvin;
	v3 = tv3;
}

string Vehicle::wholeVin()
{
	string wholeVin;
	wholeVin.append(v1);
	wholeVin.append(vin);
	wholeVin.append(v3);
	return string(wholeVin);
}

/**********************************************************************/
// Here are CONSTRUCTOR definitions

Vehicle::Vehicle() : vin("?"), price(0.00), weeksOnLot(0) // Default constructor
{

}

Vehicle::Vehicle(string s) // Constructor with vin field
{
	string wVin;
	makeUC(s);	// UC vin through "helper" function
	wVin = s;
	vinBreaker(wVin);
	price = 0.00;
	weeksOnLot = 0;
}

Vehicle::Vehicle(string s, double p) // Constructor with vin and price fields
{
	string wVin;
	makeUC(s);	// UC vin through "helper" function
	wVin = s;
	vinBreaker(wVin);
	price = p;
	weeksOnLot = 0;
}

/****** Our member functions that read and write DB entries ******************/

// A member function that populates a Vehicle object with values
// fetched from a Database file.  If object is fetched from file,
// returns TRUE, otherwise, when none left to fetch, returns FALSE
bool Vehicle::rdDBEntry(istream& stream)
{
	if (stream >> vin) // Evaluates TRUE if successful read of 1st field
	{
		string wVin;
		makeUC(vin);
		wVin = vin;
		vinBreaker(wVin);
		stream >> price >> weeksOnLot; // Get other 2 fields
		return (true);
	}
	return (false);
}

// A member function that writes the fields of a Vehicle object
// out to the console or a Database file, tab separated, one vehicle per line.
void Vehicle::wrtDBEntry(ostream& stream)
{
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
void viewDB() // The (V)iew menu choice
{
	ifstream rdDB;
	Vehicle aVehicle;  // Default constructor
	rdDB.open(diskFileRd);
	if (rdDB.fail())
	{
		cout << "Open File Error";
		system("pause");
		exit(1);
	}
	while (aVehicle.rdDBEntry(rdDB) == true) // Loop until all entries read
		aVehicle.wrtDBEntry(cout);

	rdDB.close();
}

// Lets the user input a vehicle to be added to the database
void add2DB() // The (N)ew menu choice.  Fetch data, build Vehicle, APPEND to DB file
{
	string vin;
	double price;
	char y_n;

	ofstream wrtDB;
	wrtDB.open(diskFileRd, ios::app); // Open DB file for WRITE/APPEND

									  /* Assures that output is a fixed decimal of 2 places */
	wrtDB.setf(ios::fixed);
	wrtDB.setf(ios::showpoint);
	wrtDB.precision(2);

	cout << "\nEnter Vehicle VIN number: " << endl;
	cin >> vin;
	cout << "Known vehicle price (Y/N)? ";
	cin >> y_n;

	if ((y_n != 'y') && (y_n != 'Y')) { // if 'y' or 'Y' are entered then ask for price
		Vehicle newVehicle(vin);  // Constructor with 1 arg
		newVehicle.wrtDBEntry(wrtDB);
	}
	else {
		cout << "\nEnter Vehicle price: " << endl;
		cin >> price;

		Vehicle newVehicle(vin, price);  // Constructor with 2 args
		newVehicle.wrtDBEntry(wrtDB);
	}

	wrtDB.close();
}

// Increments the number of weeks a vehicle has been on the lot by 1, writes the updated database to a new file
void updateWeeksOnLot()
{
	int weeks;
	Vehicle aVehicle;  // A single local "vehicle" object

	ifstream rdDB;  // Open two files, one to read, other to write
	ofstream wrtDB;
	rdDB.open(diskFileRd);

	if (rdDB.fail())
	{
		cout << "Open File Error";
		exit(1);
	}

	wrtDB.open(diskFileWrt);

	while (aVehicle.rdDBEntry(rdDB) == true) // Loop until all entries read
	{
		{

			weeks = aVehicle.rdWeeksOnLot();
			weeks++;
			aVehicle.wrtWeeksOnLot(weeks);
		}

		aVehicle.wrtDBEntry(wrtDB);
	}
	rdDB.close();
	wrtDB.close();
}

// User can search the vehicle database by entering three uppercase letters that are in the vehicles vin
// If a vin with those letters is found information about that vehicle is displayed
void search4Vehicle()	// Choice to (S)earch for vehicle in DB.
{
	string vin;
	bool notFound = true;  // Assume it's NOT there...
	ifstream rdDB;
	Vehicle dbVehicle;		// Local object to hold disk DB entries
	cout << "Enter the first 3 capital letters of the vehicle's vin ";
	cin >> vin;
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
			if (dbVehicle.rdVin().find(vin) != string::npos)  // Use "accessors" to see vins and check for a match
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