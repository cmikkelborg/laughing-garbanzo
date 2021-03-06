// File demonstrating some aspects of having a dynamic variable
// within a class definition.  Special care needs to be taken
// in order to use such "objects" in particular situations, such
// as assigning one object to be the value of a second object,
// or passing an object via call-by-value, which implies passing 
// a complete, independent copy the object to the function.  To
// make such actions work, we employ a "copy constructor", a
// "destructor", and an overload of the assignment operator =.
// The "Fifo" class is a toy class that helps demonstrate
// the concepts.  It is a container that stores a string in
// a dynamically allocated char[array].

#include "stdafx.h"
#include <iostream>
#include <string>
using namespace std;

class Fifo  // A FIFO storage container that holds chars
{
public:
	string getSOut();  // Retrieve a string from it

	Fifo();  // Default constructor
	Fifo(const string); // Puts a string into it

	~Fifo();   // Here's the "destructor" p. 673
	Fifo(const Fifo& original);  // The "copy constructor" p.679
	void operator =(const Fifo& rightSide); // Assignment operator p. 680

private:
	int storageSize;  // Size of the container to create
	char * stg;		// Dynamically created to be exact fit
	int next2fill;  // Which slot in the container is the next to fill
	int next2get;   // Which slot is the next to empty
};
/************* A member Accessor, of a sort  ******************/

// Member function that spits out the stored string
string Fifo::getSOut()
{
	string s = "";  // Return value will be built in "s"
	if (stg != NULL) {  // Guard against calling getSOut() when it's empty!
		while (next2get < next2fill) {  // For all chars in storage...
			s += *(stg + next2get);		// ...concatenate each in turn onto "s"
			next2get++;
		}
		delete[] stg;  // Make container empty ...
		stg = NULL;
	}
	next2get = next2fill = 0; // Show container as empty...
	return(s);
}

/***********  Constructors, Destructor *******************************/

Fifo::Fifo() { // Default constructor just makes everything empty/NULL
	next2fill = next2get = 0;
	stg = NULL;
	cout << "!"; // For debug trace
}

Fifo::Fifo(const string s) { // 1 arg. is string to be stored
	storageSize = s.length();  
	next2fill = next2get = 0;
	if (storageSize) {  // If it wasn't an empty string that we received...
		stg = new char[storageSize];		// Create the dynamic array
		while (next2fill < storageSize) { // For each char in string
			*(stg + next2fill) = s[next2fill];  // char into storage
			next2fill++;				// Advance to next slot AND next input char
		}
	}
	cout << "+"; // For debug trace
}

Fifo::~Fifo() {  // Destructor.
	if (stg != NULL)	// If there WAS dynamic storage allocated...
		delete[] stg;	//   release it to freestore
	next2fill = next2get = 0;
	stg = NULL;
	cout << "-";
}

// Copy constructor.  Works on the principle that the argument is the
// source of the copy, and the calling object is the destination.
Fifo::Fifo(const Fifo& original) { // Not changing the original
	storageSize = original.storageSize;
	if (storageSize)  // Did original HAVE any dynamic storage in use?
	{
		stg = new char[storageSize];  // If so, create a duplicate
		for (int ix = 0; ix < storageSize; ix++)
			stg[ix] = original.stg[ix];
	}
	else stg = NULL;
	next2fill = original.next2fill;
	next2get = original.next2get;
}

// Assignment operator.  This MUST be a member function, not a "friend".
// Works on principle that left side of = is the calling object, and right
// side is passed in as the argument.
void Fifo::operator =(const Fifo& rightSide) { // Not changing the right side obj
	if (stg != NULL)  // If dynamic storage in use on left side, delete it
		delete[] stg;
	storageSize = rightSide.storageSize;
	if (storageSize) // If dynamic storage in use on right side...
	{
		stg = new char[storageSize]; //    ...make independent copy.
		for (int ix = 0; ix < storageSize; ix++)
			stg[ix] = rightSide.stg[ix]; 
	}
	else stg = NULL;
	next2fill = rightSide.next2fill;
	next2get = rightSide.next2get;
}

/*********** Here's main() code and normal functions *******************/

Fifo return1(); // Prototype of regular function called by main()

// In main() we'll demo some ways that the "big 3" (p.679) work.
int main()
{
	Fifo objA = Fifo("123456");  // Constructor with 1 arg, a long string

	{ // Open a new scope.  objB has scope ONLY within here

		Fifo objB = Fifo("abc");  // Constructor w/ short string

		cout << endl << objB.getSOut() << endl; // Displays objB, and leaves it empty

		objB = objA;  // Assign the big string to the empty container!!! 
		              // Overloaded = operator causes entire copy of objA into objB

		cout << endl << objB.getSOut() << endl;

	}  // objB now OUT of scope, so destructor will be invoked upon it.

	cout << endl << objA.getSOut() << endl;

	cout << endl << return1().getSOut() << endl; // Syntax make sense?  When return1()
	                                     // returns, it effectively IS an anonymous Fifo
	                                     // object, so it has a member function getSOut().
										 // The obj is "destructed" when main() ends
	return 0;
}

// This an example of a function returning an object of Fifo class.
// For this to work, the copy constructor will make an entire independent
// copy of objC, which is returned to the caller.  The local objC instance
// WITHIN this function is constructed when the function begins, and 
// "destructed" when the function returns.
Fifo return1()
{
	Fifo objC = Fifo("987654321"); // objC has local scope in this function...
	cout << " in return() ";
	return(objC);			// ...so, destructor is invoked on objC when function returns.
}

