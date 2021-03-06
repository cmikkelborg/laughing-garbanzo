// Ch-15-Inherit.cpp : A file to demonstrate the concept
// of a "derived" class.  Vehicle is the "parent" class and
// "Truck" will be a "child" class derived from Vehicle.
// All the member variables and functions of a Vehicle are
// "inherited" by objects of the Truck class -- i.e., they
// exist in each Truck object.  A Truck is essentially an
// object of TWO types -- type "Truck" and type "Vehicle".
// The vehicle.h and vehicle.cpp files contain the interface
// and the implementation of the "parent" vehicle class.

#include "stdafx.h"
#include <iostream>
#include <string>
#include "vehicle.h"
using namespace std;

/**************** Derived Truck class ****************/
class Truck : public Vehicle  // Based upon the Vehicle class...
{
public:
	double getTowCap();		// Accessors/mutators ONLY for new private variables
	void putTowCap(double);

	Truck();
	Truck(string v, double p, int w, double t);

	void display1(char); // "Redefined" function display1() - p.853
	void discountPrice();
private:
	double towCap;  // Has a single private variable unique to trucks
};

/**************** Derived Car class ****************/
class Car : public Vehicle
{
public:
	Car(); // New child constructors.
	Car(string v, double p, int w, int c);

	int getPsgrCap(); // Accessors/mutators ONLY for new private variables.
	void putPsgrCap(int);

	void display1(char);  // redefined display1() function.
	void discountPrice();
private:
	int psgrCap;  // Passenger capacity of car.
};


/**************** TRUCK constructors, accessors ****************/
// 4-arg Truck constructor calls Vehicle 3-arg constructor, then inits. new variable
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

// This is a "redefined" version of the display1() function that was
// defined in the parent Vehicle class.  It is NOT an "overload", which
// is when functions have the same name, but then have DIFFERENT
// argument lists.  This function has the SAME argument list as the one
// declared/defined in the Vehicle class.
void Truck::display1(char vType)
{
	// This member function of the child Truck class does NOT have
	// direct access to "private" variables in the parent Vehicle class.
	// Need accessors, as seen here...
	cout << endl << vType << ": " << getVIN() << '\t' << getPrice()
		<< '\t' << getWeeks();

	// BUT, if the word "private" is changed to "protected" in the
	// parent vehicle class, then child functions DO have direct access
	// to those parental member variables!
	//cout << endl << vType << ": " << baseVIN + extVIN << '\t' << price
	//	<< '\t' << weeksOnLot;

	// The "parental" definition of the redefined function may also be
	// invoked by using the scope-resolution operator ::, as seen here.
	//Vehicle::display1(vType); // Use VEHICLE display1() function...
	cout << '\t' << towCap;
}

void Truck::discountPrice()
{
	if (getWeeks() > 5)
		putPrice(getPrice() - 800);
}


/**************** CAR constructors, accessors ****************/
Car::Car() : Vehicle(), psgrCap(2) // default - calls vehicle default and sets a default value for passenger capacity
{
}

Car::Car(string v, double p, int w, int c) : Vehicle(v, p, w), psgrCap(c)
{
}

int Car::getPsgrCap() // Accessor/mutator pair for a Cars private variables
{
	return(psgrCap);
}

void Car::putPsgrCap(int c)
{
	psgrCap = c;
}

void Car::display1(char vType)
{
	Vehicle::display1(vType); // Use VEHICLE virtual display1() function...
	cout << '\t' << psgrCap;
}

void Car::discountPrice()
{
	if (getWeeks() > 2) // modified Vehicle's virtual discountPrice() function for cars
		putPrice(getPrice() - 500); // take off 500 dollars off the price for every car that has been on the lot for 2 weeks or more
}


const int CAR_ASIZE = 4;  // Size of your Car array
const int TRUCK_ASIZE = 4;  // Size of Truck array I provided
const int V_ASIZE = CAR_ASIZE + TRUCK_ASIZE;// Size of Vehicle * array

void viewDB(Vehicle *[], int); // function to display the Vehicle * array
void sortDB(Vehicle *[], int); // function to sort the Vehicle * array
void updateWeeks(Vehicle *[], int); // function that updates the weeksOnLot of all Vehicle pointers in the Vehicle * array
void discountPrice(Vehicle *[], int); // function that calls the virtual discount function in Vehicles, that discounts cars and trucks based on how many weeks they have been on the lot
									  /****************  Our main() ****************/
int main()
{
	Truck TA[TRUCK_ASIZE];
	TA[0] = Truck("GRVBN12345", 14500, 5, 9000);  // Construct an array of trucks
	TA[1] = Truck("GRVBN54321", 17900, 1, 7000);  //    using 4-arg constructor.
	TA[2] = Truck("RGVBN54321", 15400, 0, 7000);
	TA[3] = Truck("LQVBN54321", 26999, 6, 12000);

	Car CA[CAR_ASIZE];
	CA[0] = Car("OIFJS12345", 7000, 0, 2);  // Construct an array of cars
	CA[1] = Car("PPOWV54321", 18450, 4, 4);  //    using 4-arg constructor.
	CA[2] = Car("BSDIU54321", 12200, 3, 5);
	CA[3] = Car("WLJFDK54321", 13765, 1, 4);
	// Declaring two pointers of different types, and making BOTH of
	// them point to the first Truck in the array.  We expect that when
	// using tPtr, the Truck version of display1() will be invoked, and
	// when using vPtr, the Vehicle version of display1() is invoked.

	Truck * tPtr = TA;
	Car * cPtr = CA;

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
	// and now do the same for all cars in CA[]
	for (int loopCount = CAR_ASIZE, ix = 0; loopCount > 0; loopCount--, ix++)
		VA[vehicleCount++] = &CA[ix];


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
		case 'X': case 'x': // EXIT program
			cout << "Goodbye!\n";
			return (0);
		case 'V': case 'v': // VIEW database
			viewDB(VA, vehicleCount);
			break;
		case 'U': case 'u': // UPDATE weeksOnLot
			updateWeeks(VA, vehicleCount);// Make active after handler fixed
			break;
		case 'S': case 's': // SORT database
			sortDB(VA, vehicleCount);
			break;
		case 'D': case 'd':  // Here is (D)iscount handler you will write
			discountPrice(VA, vehicleCount);
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
			if (((choice == 'w') && ((*searchPtr)->getWeeks() < (*slotWithMin)->getWeeks()))
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
void updateWeeks(Vehicle * VA[], int aSize)
{
	for (aSize--; aSize >= 0; aSize--)  // dec. aSize to convert into array index
	{
		++*VA[aSize];
	}
}

/************* Your (D)iscount handler here **************************/
void discountPrice(Vehicle *VA[], int aSize)
{
	for (aSize--; aSize >= 0; aSize--)  // dec. aSize to convert into array index
	{
		VA[aSize]->discountPrice(); // calls the virtual discountPrice() function that will call the correct modified functions for each child vehcile type
	}
}

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
