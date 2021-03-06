// Lab04.cpp
// Author: Charles Mikkelborg, Brett Turner
// Description: Reads an input file to poplulate a class object in an array that can be output to the console and a file.
//		Includes functionality to view the database, enter a new vehicle, update how many weeks a car has been the lot,
//		and search by VIN number.
// Last modified: 05/03/2018

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

/******* Our only globals are CONST variables  **************/
const string diskFileRd = "xvehicles_db.txt"; // database file to be called in
const int VA_SIZE = 10; // our Vehicle class array size


						/****************  Member functions  *****************/
class Vehicle
{
public:
	/* Mutator and Accessor declarations */
	void wrtVin(string wVin);
	void wrtPrice(double wPrice);
	void vinBreaker(string& wVin);

	/* Constructor declarations */
	Vehicle();
	Vehicle(string vin);

	/* Destructor declarations */
	~Vehicle();

	friend ostream& operator << (ostream& outS, const Vehicle& v);
	friend istream& operator >> (istream& inS, Vehicle& v);

	/* Helper functions */
	friend void operator ++(Vehicle& v);
	friend bool operator ==(const Vehicle& v1, const Vehicle& v2);

	/* Copy and Rearrange*/
	Vehicle(const Vehicle& original); //Copy Constructor
	void operator =(const Vehicle& rightSide); //Assignment Operator

private:
	void makeUC(string& s);	// A private make uppercase function
	string v1 = "";
	string vin;
	string v3 = "";
	double price;
	int weeksOnLot;
	int listSize = 0;
	string * listPtr = NULL;
};

/****************  Regular functions  ***************/
void viewDB(Vehicle V[], int size);
int add2DB(Vehicle V[], int size);
void updateWeeksOnLot(Vehicle V[], int size);
void search4Vehicle(Vehicle V[], int size);


int main()
{
	ifstream rdDB;
	ofstream wrtDB;
	Vehicle VA[VA_SIZE];
	Vehicle temp;
	int vaSize = 0;
	int veh1, veh2;

	// Opens vehicle.txt and populates vehicle class objects.
	// class objects are then put into an array.
	rdDB.open(diskFileRd);
	if (rdDB.fail())
	{
		cout << "Open File Error";
		exit(1);
	}

	while (rdDB >> VA[vaSize])
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
		cout << "\n\nMenu: (V)iew DB, (N)ew entry, (U)pdate, (S)earch, (R)earrange, e(X)it program: ";
		cin >> menuChoice;

		switch (menuChoice)
		{
		case 'X': case 'x':
			// writes changes made to the array to file on exit.
			cout << "Goodbye!\n";
			/*
			wrtDB.open(diskFileRd); // opens database file for editing
			if (wrtDB.fail()) // check for file load error
			{
			cout << "Open File Error";
			exit(1);
			}
			for (int ix = 0; ix < vaSize; ix++) // rewrites database file with changes made in our Vehcicle array
			wrtDB << VA[ix];
			wrtDB.close();
			*/
			system("pause");
			return(0);
		case 'V': case 'v':
			viewDB(VA, vaSize); // reads and prints to the console the contents of Vehicle array
			break;
		case 'N': case 'n':
			// add new vehicle
			if (vaSize < VA_SIZE) // check to see if there is still space in the array
				vaSize = add2DB(VA, vaSize); // if there is continue with add2DB()
			else
				cout << "Can't add a vehicle! Array already full."; // if not reject.
			break;
		case 'U': case 'u':
			updateWeeksOnLot(VA, vaSize); // updates each object's weeksOnLot in array by 1
			break;
		case 'S': case 's':
			search4Vehicle(VA, vaSize); // search for a vehicle in array based on the letters of the vin
			break;
		case 'R': case 'r': // rearrange two vehicles in the data base
			cout << "\nRearrange two vehicles in the database" << "\nEnter the number for the first vehicle" << endl;
			cin >> veh1;
			cout << "\nEnter the number for the second vehicle" << endl;
			cin >> veh2;
			if (veh1 > vaSize || veh1 <= 0 || veh2 > vaSize || veh2 <= 0) // make sure choice is within the range of the array
			{
				cout << "size out of range";
				break;
			}
			temp = VA[veh1 - 1]; // this is where the two choices switch places in array
			VA[veh1 - 1] = VA[veh2 - 1];
			VA[veh2 - 1] = temp;
			break;
		default:
			cout << "Illegal choice.  Try again. \n";
		}
	} while (true);

	return 0;
}

/************* "Friend" functions and operator overload ***************/
void operator ++(Vehicle& v) // Operator overload function to update "weeksOnLot" by one.
{
	v.weeksOnLot = v.weeksOnLot++;
}


bool operator==(const Vehicle & v1, const Vehicle & v2) // Operator overload function to compare two vins.
{
	return (v1.vin == v2.vin);
}

void Vehicle::operator =(const Vehicle& rightSide) //Assignment Operator
{
	if (listPtr != NULL)  // If dynamic storage in use on left side, delete it
		delete[] listPtr;

	listSize = rightSide.listSize;
	listPtr = new string[listSize]; //    ...make independent copy.
	v1 = rightSide.v1;              // all veriable need to by copied to be an exact copy
	vin = rightSide.vin;
	v3 = rightSide.v3;
	price = rightSide.price;
	weeksOnLot = rightSide.weeksOnLot;
	listSize = rightSide.listSize;
	for (int ix = 0; ix < listSize; ix++) // make a seperate copy of the dynamic storage
		listPtr[ix] = rightSide.listPtr[ix];

}

/**********************************************************************/
// Here are paired MUTATOR and ACCESSOR functions for private Vehicle variables

void Vehicle::wrtVin(string wVin)		// Mutator to change private variable "vin"
{
	makeUC(wVin);		// Assure UC vin through "helper" function
	vinBreaker(wVin);   // break the vin into the three private variables v1, vin, and v3
}

void Vehicle::wrtPrice(double wPrice)		// Mutator to change private variable "price"
{
	price = wPrice;
}


void Vehicle::vinBreaker(string& wVin) // Mutator to break down a given vin number into 3 parts
{
	v1 = wVin.substr(0, 1);
	v3 = wVin.substr(4, 5);
	vin = wVin.substr(1, 3);

}

/**********************************************************************/
// Here are CONSTRUCTOR definitions

Vehicle::Vehicle() : v1(""), vin("?"), v3(""), price(0.00), weeksOnLot(0), listSize(0) // Default constructor
{
	listSize = 0;
	listPtr = NULL;
}

Vehicle::Vehicle(string s) // Constructor with vin field for the add2DB()
{
	makeUC(s);	// UC vin through "helper" function
	v1 = "";
	vin = s;
	v3 = "";
	price = 0.00;
	weeksOnLot = 0;
	listSize = 0;
}


Vehicle::Vehicle(const Vehicle &original) //Copy Constructor
{
	listSize = original.listSize;

	listPtr = new string[listSize];  // If so, create a duplicate
	for (int ix = 0; ix < listSize; ix++)
		listPtr[ix] = original.listPtr[ix];
}


/**********************************************************************/
// Here are DESTRUCTOR definitions

Vehicle::~Vehicle()
{
	if (listPtr != NULL) // if object is not NULL delete and set pointer and size to default state
		delete[] listPtr;
	listPtr = NULL;
	listSize = 0;
}

/********************* Private "helper" functions ***********************/
// Function to convert all letters in string to Upper Case.

void Vehicle::makeUC(string& s) // class function to make characters upper case
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
	cout << "\nVin" << '\t' << "Price" << '\t' << "Weeks On Lot" << '\t' << "Options" << endl; // a header for readability
	for (int i = 0; i < size; i++) //for every object, print contents
		cout << "Vehicle " << i + 1 << endl << V[i] << endl;
}


// Lets the user input a vehicle to be added to the database

int add2DB(Vehicle dbVehicle[], int aSize) // The (N)ew menu choice.  Fetch data, build Vehicle, add to array
{
	string bVin;
	double price;
	char y_n;

	cout << "\nEnter Vehicle VIN number: " << endl;
	cin >> bVin;
	cout << "Known vehicle price (Y/N)? ";
	cin >> y_n;

	if ((y_n != 'y') && (y_n != 'Y')) { // if 'y' or 'Y' are entered then ask for price
		dbVehicle[aSize].wrtVin(bVin); // creates new vehicle with given "vin"
		return(aSize + 1); // make sure array size is updated to support new vehicle
	}
	else {
		cout << "\nEnter Vehicle price: " << endl;
		cin >> price;
		dbVehicle[aSize].wrtVin(bVin); // writes new "vin" to new vehicle
		dbVehicle[aSize].wrtPrice(price); // writes ne "price" to new vehicle
		return(aSize + 1); // make sure array size is updated to support new vehicle
	}
}

// Increments the number of weeks a vehicle has been on the lot by 1, writes the updated database to a new file

void updateWeeksOnLot(Vehicle dbVehicle[], int aSize) // Mutator that updates weeksOnLot for all objects in an array by 1
{
	for (int ix = 0; ix < aSize; ix++)
		++dbVehicle[ix];
}

// User can search the vehicle database by entering three uppercase letters that are in the vehicles vin
// If a vin with those letters is found information about that vehicle is displayed
void search4Vehicle(Vehicle V[], int size)	// Choice to (S)earch for vehicle in DB.
{
	string bVin;
	bool notFound = true;  // Assume it's NOT there...

	cout << "Enter the first 3 letters of the vehicle's vin: ";
	cin >> bVin;

	Vehicle search4(bVin);		// Local object to hold disk DB entries			


	for (int i = 0; i < size; i++)
	{
		if (V[i] == search4) // Loop until all entries read
		{
			cout << "Found! >> " << endl; // if found then display that array object
			cout << V[i];
			notFound = false;  // Now will skip failure msg. below
		}
	}
	if (notFound)  // Failure message
		cout << "Vehicle \"" << bVin << "\" not in DB.";
}

// overloaded << operator to read an objects variables and sends them to an output stream
ostream& operator << (ostream& outS, const Vehicle& v)
{
	outS << v.v1 + v.vin + v.v3 << '\t' << v.price << '\t' << v.weeksOnLot << '\t' << v.listSize << endl;
	if (v.listSize > 0) // make sure there is additional lines to retrieve
	{
		string * sPtr = v.listPtr;
		for (int ix = 0; ix < v.listSize; ix++) // grab next lines equal to the value of listSize
		{
			outS << *sPtr << endl;
			sPtr++;
		}

	}
	return(outS); // return the stream for output use
}

// overloaded >> operator to write variables to an object from a stream of input
istream& operator >> (istream& inS, Vehicle& v)
{
	string bVin;
	v.vin[0] = '?';
	inS >> v.vin;
	if (v.vin[0] != '?') // check to see if there is something to input into vin, if there is than continue to fill object, if not stop.
	{
		v.vinBreaker(v.vin);
		inS >> v.price >> v.weeksOnLot >> v.listSize;
		inS.get();
		if (v.listSize > 0)
		{
			v.listPtr = new string[v.listSize];
			string * sPtr = v.listPtr;
			for (int ix = 0; ix < v.listSize; ix++)
			{
				getline(inS, *sPtr);
				sPtr++;
			}
		}
	}
	return(inS); // return the stream for input use
}
