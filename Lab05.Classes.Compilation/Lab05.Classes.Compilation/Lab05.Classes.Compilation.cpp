// Lab05.Classes.cpp
// Author: Charles Mikkelborg, Brett Turner
// Description: Reads an input file to poplulate a class object in an array that can be output to the console and a file.
//		Includes functionality to view the database, enter a new vehicle, update how many weeks a car has been the lot,
//		and search by VIN number.
// Last modified: 05/09/2018

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "ChunkVehicle.h"
using namespace std;

/**************** GLOBAL VARIABLES  ****************/
const string diskFileRd = "xvehicles_db.txt"; // database file to be called in
const int VA_SIZE = 10; // our Vehicle class array size

						/****************  REGULAR FUNCTION DECLARATIONS ****************/
void viewDB(Vehicle V[], int size); // Function used to view each member of a Vehicle array. Used for the (V)iew menu choice.
int add2DB(Vehicle V[], int size);  // Function used to add an object to the Vehicle array. Used for the the (N)ew entry menu choice.
void updateWeeksOnLot(Vehicle V[], int size);  // Function used to update each object in the Vehicle array's 'weeksOnLot' value by 1.
void search4Vehicle(Vehicle V[], int size); // Function used to search for a vehicle in the array by the letters of the vin.


int main()
{
	ifstream rdDB;  // Specifies a input stream.
	ofstream wrtDB; // Specifies a output stream.
	Vehicle VA[VA_SIZE]; // sets the Vehicle array to the global constant VA_SIZE.
	Vehicle temp;   // Temporary Vehicle used to rearrange Vehicles within the (R)earrange menu choice.
	int vaSize = 0; // Spot holder for a particular object within the array.
	int veh1, veh2; // Each specifies a specific object within the array.

					// Opens vehicle.txt and populates vehicle class objects.
					// class objects are then put into an array.
	rdDB.open(diskFileRd); // Opens the global file constant vehicle.txt
	if (rdDB.fail()) // Checks for a load error, if cannot load file, then stop program with error.
	{
		cout << "Open File Error" << endl;

		system("pause");
		exit(1);
	}

	while (rdDB >> VA[vaSize]) // Run while the input stream is still populating Vehicle array.
	{
		if (++vaSize >= VA_SIZE) // If there are a greater number of entries than the Vehicle array can hold, then stop.
		{
			cout << "Array full! Skipping remaining DB entries.";
			break;
		}
	}
	rdDB.close(); // Closes the global file constant vehicle.txt.


				  /**************** MENU ****************/
	char menuChoice; // Variable used for user entered menue choices.
	do // Infinite loop.
	{
		cout << "\n\nMenu: (V)iew DB, (N)ew entry, (U)pdate, (S)earch, (R)earrange, e(X)it program: " << endl;
		cout << "Select a menu option: ";
		cin >> menuChoice; // Asks for a menu option.

		switch (menuChoice)
		{
		case 'X': case 'x': // Writes changes made to the array to file on exit and ends the program.
			cout << "Goodbye!\n";
			/*
			wrtDB.open(diskFileRd); // Opens database file for editing.
			if (wrtDB.fail()) // Checks for a load error, if cannot load file, then stop program with error.
			{
			cout << "Open File Error";
			exit(1);
			}
			for (int ix = 0; ix < vaSize; ix++) // Rewrites database file with the changes made in the Vehcicle array.
			wrtDB << VA[ix];
			wrtDB.close(); // Closes the global file constant vehicle.txt.
			*/
			system("pause");
			return(0);

		case 'V': case 'v': // Reads and prints to the console the contents of the Vehicle array.
			viewDB(VA, vaSize);
			break;

		case 'N': case 'n': // Adds a new vehicle to the Vehicle array.
			if (vaSize < VA_SIZE) // Check to see if there is still space in the array
				vaSize = add2DB(VA, vaSize); // If there is continue with add2DB()
			else
				cout << "Can't add a vehicle! Array already full."; // If there is not space, then reject and break.
			break;

		case 'U': case 'u': // Updates the number of weeks on the lot by 1.
			updateWeeksOnLot(VA, vaSize); // Function used to update each object in the Vehicle array's 'weeksOnLot' value by 1.
			break;

		case 'S': case 's': // Search for a vehicle in the database.
			search4Vehicle(VA, vaSize); // // Function used to search for a vehicle in the array by the letters of the vin.
			break;

		case 'R': case 'r': // Rearrange two vehicles in the array.
			cout << "\nRearrange two vehicles in the database" << "\nEnter the number for the first vehicle" << endl;
			cin >> veh1; // Ask for the first vehicle
			cout << "\nEnter the number for the second vehicle" << endl;
			cin >> veh2; // Ask for the second vehicle
			if (veh1 > vaSize || veh1 <= 0 || veh2 > vaSize || veh2 <= 0) // Make sure choice is within the range of the array, if it is not then stop.
			{
				cout << "size out of range";
				break;
			}
			temp = VA[veh1 - 1]; // Here is where the two choices switch places in array
			VA[veh1 - 1] = VA[veh2 - 1];
			VA[veh2 - 1] = temp;
			break;
		default: // For when the "option" selected is not an option
			cout << "Illegal choice.  Try again. \n";
		}
	} while (true);

	return 0;
}

/**************** REGULAR FUNCTION DEFINITIONS ****************/

void viewDB(Vehicle V[], int size) // Function used to view each member of a Vehicle object for all objects in the array. Used for the (V)iew menu choice.
{
	cout << "\nVin" << '\t' << "Price" << '\t' << "Weeks On Lot" << '\t' << "Options" << endl; // A header for readability.
	for (int i = 0; i < size; i++) // For every object, print contents.
		cout << "Vehicle " << i + 1 << endl << V[i] << endl;
}

int add2DB(Vehicle dbVehicle[], int aSize) // Function used to add an object to the Vehicle array. Used for the the (N)ew entry menu choice.
{
	string bVin;  // Holder for Vehicle vin.
	double price; // Holder for Vehicle price
	char y_n;     // HOlder for user choice.

	cout << "\nEnter Vehicle VIN number: " << endl;
	cin >> bVin; // Asks for whole vin.
	cout << "Known vehicle price (Y/N)? ";
	cin >> y_n; // Asks if price is known.

	if ((y_n != 'y') && (y_n != 'Y')) { // If price is known then ask and enter it. If not proceed without a price.
		dbVehicle[aSize].wrtVin(bVin); // creates new vehicle object in the array and writes in the given vin.
		return(aSize + 1); // Make sure array size is updated to support new vehicle
	}
	else {
		cout << "\nEnter Vehicle price: " << endl;
		cin >> price;
		dbVehicle[aSize].wrtVin(bVin); // creates new vehicle object in the array and writes in the given vin.
		dbVehicle[aSize].wrtPrice(price); // Writes the variable price to the new vehicle
		return(aSize + 1); // Make sure array size is updated to support new vehicle
	}
}

void updateWeeksOnLot(Vehicle dbVehicle[], int aSize) // Function used to update each object in the Vehicle array's 'weeksOnLot' value by 1.
{
	for (int ix = 0; ix < aSize; ix++) // For each object in the array, update weeksOnLot by one.
		++dbVehicle[ix];
}

void search4Vehicle(Vehicle V[], int size)	// Function used to search for a vehicle in the array by the letters of the vin.
{
	// User can search the vehicle database by entering three uppercase letters that are in the vehicles vin.
	// If a vin with those letters is found information about that vehicle is displayed.
	string bVin;
	bool notFound = true;  // Assume it's NOT there...

	cout << "Enter the first 3 letters of the vehicle's vin: ";
	cin >> bVin; // Enter vin.

	Vehicle search4(bVin);		// Local object is created to hold array DB entries.	


	for (int i = 0; i < size; i++) // Loop until all entries read.
	{
		if (V[i] == search4)  // Check to see if entry matches the current Vehicle's vin.
		{
			cout << "Found! >> " << endl; // If found then display that array object.
			cout << V[i];
			notFound = false;  // To skip the failure msg. below.
		}
	}
	if (notFound)  // Message if vin is not found within the database.
		cout << "Vehicle \"" << bVin << "\" not in DB.";
}