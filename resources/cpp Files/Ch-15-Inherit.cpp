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

/************* Derived Truck class ********************************/
class Truck : public Vehicle  // Based upon the Vehicle class...
{
public:
	double getTowCap();		// Accessors/mutators ONLY for new private variables
	void putTowCap(double);

	Truck();
	Truck(string v, double p, int w, double t);

	void display1(char); // "Redefined" function display1() - p.853

private:
	double towCap;  // Has a single private variable unique to trucks
};

/*************************  Our main() ******************************/
int main()
{
	// Construct one each of our two class types.  The truck constructors
	// invoke the parent Vehicle constructors.
	Vehicle v1("VHICL12345", 14500, 0);
	Truck t1("TRUCK54321", 17900, 2, 7000); // Extra private variable

	// The mutators/accessors of the parent class exist for each child object
	cout << v1.getVIN() << " is VIN of v1\n"; // Using own class accessor
	cout << t1.getVIN() << " is VIN of t1\n\n"; // Using parent accessor

	// Child object invoking accessor of its OWN class -- all is fine.  
	cout << t1.getTowCap() << " is towing cap of t1\n\n";

	// Parent object CAN'T invoke accessor of child class!  Compiler error.
	// cout << v1.getTowCap(); // Won't compile...

	// Can assign a child object as the value of a parent object, but the parent
	// doesn't HAVE a "towCap", so that value is lost.  "Slicing problem" p.871
	Vehicle v2; // Construct a new default Vehicle... 
	v2 = t1;    //   ... and assign it the value of a child Truck object
	cout << v2.getVIN() << " is VIN of v2 (assigned from t1)\n\n";

	// Can NOT assign parent object to child object.  Compiler error
	// t1 = v1; // Won't compile

	// Overloaded ++ operator of the parent Vehicle class can be invoked on Truck
	cout << t1.getWeeks() << " weeks for t1 before ++, ";
	++t1; 
	cout << t1.getWeeks() << " weeks after ++\n\n";

	if (v2 == t1) // Ditto, overloaded parental == operator works on both Trucks and Vehicles
		cout << "== operator found v2 equal to t1\n";
	else cout << "== operator found v2 UNequal to t1\n";

	// Can have a member function in the parent class that is "redefined" to do
	// something different in the child class. p. 853.
	v1.display1('V');  // Uses display1() definition in Vehicle, because v1 is Vehicle object
	t1.display1('T');  // Uses display1() in Truck, because t1 is Truck object

	// In essence, a "Truck" object is BOTH an object of type Truck AND
	// an object of type Vehicle.  So, it is possible to define two different
	// pointers, as below, and BOTH of the pointers are willing to point to
	// a "Truck" object.
	Vehicle * vPtr = &t1;
	Truck * tPtr = &t1;

	tPtr->display1('T'); // Behaves as expected, uses "Truck" version of display1() function.
	vPtr->display1('V'); // But HERE, the use of vPtr indicates to compiler that we're treating
	                     // t1 as a "Vehicle" rather than as a "Truck", so "Vehicle" version of
	                     // of display1() function is invoked.
	
	// In contrast, a "Vehicle" object is NOT an object of type Vehicle and type Truck.
	// Attempting to make  Truck pointer point to a Vehicle causes a compiler error.
	//tPtr = &v1;

	cout << endl;
	return 0;
}

/************* TRUCK constructors, accessors ****************************/

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
	cout << '\t' << towCap << endl;
}