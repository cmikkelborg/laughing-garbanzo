// Ch-15-Polymorphism.cpp : A file to demonstrate the concept
// of a "derived" class that exhibits "polymorphism".
// It is very similar to your menu-code for vehicles, but all
// of the file I/O in your prior Vehicle programs has been
// removed, as well as the handlers for (N)ew, (R)earrange,
// and (S)earch.  We'll work with static arrays of vehicles
// of various kinds that get declared within main().
// The vehicle.h and vehicle.cpp files contain the interface
// and the implementation of the "parent" vehicle class.

#include "stdafx.h"
#include <iostream>
#include <string>
#include "vehicle.h"
using namespace std;

/************* Derived Truck class ********************************/
class Truck : public Vehicle  // Based upon the Vehicle class...
{
public:
	double getTowCap();		// Accessors/mutators ONLY for new private variables
	void putTowCap(double);

	Truck();
	Truck(string v, double p, int w, double t);

	void display1(char); // Will become our "virtual" function

private:
	double towCap;  // Has 1 private variable unique to trucks
};

/************* TRUCK constructors, accessors ****************************/

// 4-arg constructor calls Vehicle 3-arg constructor, and then inits. new variable
// See p. 845 regarding this syntax, which MUST be used in derived class
Truck::Truck(string v, double p, int w, double tc) : Vehicle(v, p, w), towCap(tc)
{
}

Truck::Truck() : Vehicle(), towCap(0.0)  // Default -- calls Vehicle default
{
}

double Truck::getTowCap() // Accessor/mutator pair for new private variable
{
	return(towCap);
}
void Truck::putTowCap(double t)
{
	towCap = t;
}

void Truck::display1(char vType)
{
	// The "parental" definition of the function is being invoked here,
	// making use of the scope resolution operator ::  
	Vehicle::display1(vType);
	cout << '\t' << towCap << endl;
}


/*****  ALL YOUR CAR-CLASS STUFF SHOULD BE ABOVE HERE***************/


/***************COPY/PASTE EVERYTHING FROM HERE DOWN ****************/

/******* Only globals are our CONST values  ***********************/
const int CAR_ASIZE = 4;  // Size of your Car array
const int TRUCK_ASIZE = 4;  // Size of Truck array I provided
const int V_ASIZE = CAR_ASIZE + TRUCK_ASIZE;// Size of Vehicle * array

/*******  Regular function prototypes -- menu-choice handlers ********/
// Placed below class definitions to resolve forward references
void viewDB(Vehicle *[], int);
void sortDB(Vehicle *[], int);
//void updateWeeks(Vehicle *[], int); // Make active after you fix the handler...

/*************************  Our main() ******************************/

int main()
{
	Truck TA[TRUCK_ASIZE];
	TA[0] = Truck("GRVBN12345", 14500, 3, 9000);  // Construct an array of trucks
	TA[1] = Truck("GRVBN54321", 17900, 1, 7000);  //    using 4-arg constructor.
	TA[2] = Truck("RGVBN54321", 15400, 0, 7000);
	TA[3] = Truck("LQVBN54321", 26999, 2, 12000);

	// Declaring two pointers of different types, and making BOTH of
	// them point to the first Truck in the array.  We expect that when
	// using tPtr, the Truck version of display1() will be invoked, and
	// when using vPtr, the Vehicle version of display1() is invoked.
	Truck * tPtr = TA;
	Vehicle * vPtr = TA;
	tPtr->display1('T');
	vPtr->display1('V');

	// BUT, if the display1() function is declared as "virtual" on
	// line 32 of vehicle.h, the above code works differently!  At
	// COMPILE-time a lookup table is built, and at RUN-time the system
	// examines WHAT TYPE of object is being pointed to by vPtr and
	// uses the lookup table to invoke the version of display1()
	// that is appropriate for that specific object type.  BOTH lines 
	// above will display Truck content, including the towCap.  This is
	// "late binding" -- i.e., binding the appropriate function to
	// the given type of object at runtime.  Also known as
	// "polymorphism"  p.863

	/* The array below is what I will use to work with my ENTIRE inventory
	of vehicles.  It is an array of POINTERS, with each pointer set to
	point at an object in one of the OTHER two arrays.  */

	Vehicle * VA[V_ASIZE];  // Enough room for ALL vehicles of ALL types
	int  vehicleCount = 0;  // How many vehicles of ALL types are in inventory

	// Loop to init. pointers in VA[] to point to trucks in TA[]
	for (int loopCount = TRUCK_ASIZE, ix = 0; loopCount > 0; loopCount--, ix++)
		VA[vehicleCount++] = &TA[ix];

	// Your array of cars should go here, and then be followed by code that
	// completes the initialization of the Vehicle * VA[] array.  VA[] will
	// then contain some pointers to Cars, and some to Trucks.

	char menuChoice;  // Simple menu, easy to copy/paste for your lab 
	do
	{
		cout << "\n\nMenu: (V)iew DB, (U)pdate, (S)ort, (D)iscount, e(X)it program: ";
		cin >> menuChoice;

		switch (menuChoice)
		{
		case 'X': case 'x':
			cout << "Goodbye!\n";
			return (0);
		case 'V': case 'v':
			viewDB(VA, vehicleCount);
			break;
		case 'U': case 'u':
			//updateWeeks(Vehicle * VA[], int aSize);// Make active after handler fixed
			break;
		case 'S': case 's':
			sortDB(VA, vehicleCount);
			break;
		case 'D': case 'd':  // Here is (D)iscount handler you will write
			break;
		default:
			cout << "Illegal choice.  Try again. \n";
		}
	} while (true);

	return 0;
}

/**************  Menu-choice handler functions ************/

void viewDB(Vehicle * VA[], int aSize) // (V)iew handles only parent Vehicle objects
{
	for (aSize--; aSize >= 0; aSize--)  // dec. aSize to convert into array index
		VA[aSize]->display1('P');  // Call the display1() function that is a member
	                               // of the object being pointed to by VA[aSize]
}

// Here's the implementation of the (S)ort menu choice.  It sorts the POINTERS in
// the VA[] array, rather than sorting actual contents of Truck[] and Car[] arrays.
// This lets us view the entire inventory in sorted order.
void sortDB(Vehicle * VA[], int aSize)	// Choice to (S)ort Vehicles in DB.
{
	char choice;
	cout << "Sort by (W)eeks or (P)rice.  Enter choice: ";
	cin >> choice;
	choice = (choice == 'w' || choice == 'W') ? 'w' : 'p'; // The "ternary" operator of C++

	// This is a "selection sort" as per p. 418 Savitch
	Vehicle * * leftSearchEdge = VA;
	Vehicle * * rightSearchEdge = &VA[aSize - 1];
	Vehicle * * searchPtr;
	Vehicle * * slotWithMin;
	for (; leftSearchEdge < rightSearchEdge; leftSearchEdge++)
	{
		slotWithMin = leftSearchEdge;	// Assume MIN is in 1st slot of this sub-array
		for (searchPtr = leftSearchEdge + 1; searchPtr <= rightSearchEdge; searchPtr++)
		{
			if (   ((choice == 'w') && ((*searchPtr)->getWeeks() < (*slotWithMin)->getWeeks()))
				|| ((choice == 'p') && ((*searchPtr)->getPrice() < (*slotWithMin)->getPrice())))
				slotWithMin = searchPtr;
		}
		if (slotWithMin != leftSearchEdge) {
			Vehicle * temp = *leftSearchEdge;
			*leftSearchEdge = *slotWithMin;
			*slotWithMin = temp;
		}
	}
}
/************* Your (D)iscount handler here **************************/


/*  Below is OLD menu-handler function.  It worked fine when it
    was passed an array of Trucks.  Now, however, it will be
	passed an array of POINTERS to Vehicles.  It must be revised
	to work correctly in that circumstance:  revise the argument types,
	and also revise the logic of the algorithm.  The (V)iew handler above
	has already been revised...	*/
/*
void updateWeeks(Truck TA[], int aSize)  // The (U)pdate menu choice.
{
	for (--aSize; aSize >= 0; aSize--)
		++TA[aSize];  // Using overloaded ++ operator to inc. weeksOnLot
}
*/
