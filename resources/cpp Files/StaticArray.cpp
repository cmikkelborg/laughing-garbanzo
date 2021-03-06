// File demonstrating some aspects of use of arrays with classes.
// You can have an array containing objects of a class, and can
// have a class that has an array as a member component.  The
// syntax of working with things can be tricky...

#include "stdafx.h"
#include <iostream>
#include <string>
using namespace std;

const int A1_SIZE = 5;  // The size of array of objects
const int A2_SIZE = 20; // An size of array WITHIN each object

// C++ allows user to define an identifier as a substitute for arbitrary content
// Here, each time I want to see certain array contents, I'll SEE_1ST_LAST.  Eliminates
// some clutter from the demo main() routine below.  Not a great practice in real
// life, though!  Just want you to know it exists.
#define SEE_1ST_LAST cout << endl << holders[0].seeS() << endl << holders[A1_SIZE - 1].seeS() << endl;

class Holder  // A container that holds a c-string char[]
{
public:
	void loadS(string);		// Put string into storage
	char * seeS();			// Provide ptr to private storage[]
	Holder();  // Default constructor
private:
	char storage[A2_SIZE];
	int next2fill;  // Which slot in storage is the next to fill
};

Holder::Holder() { // Default constructor makes "?" c-string
	storage[0] = '?';
	storage[1] = '\0';
	next2fill = 1;  // Set to append...
	cout << "+"; // For debug trace
}

void demoFunc(Holder [], int); // Prototype.  Ignore for now...

int main()
{
	Holder holders[A1_SIZE];  // Declare object array.  Default constructor acts on each

	// Each element of the array is a "Holder" object, so each one has "member functions"
	// that are accessed using the dot operator.  Here, the .seeS() function is invoked
	// upon the "0th" element in the array.  A char * to a c-string is the return value.
	cout << holders[0].seeS() << endl;

	//holders[0] = { {'a','b','c'}, 3, 0 };  // Can't "initialize" an object - compiler error!

	string sTemplate = "0_content";
	holders[0].loadS(sTemplate);  // Use member function to load a string

	// As with all arrays, instead of using a hardcoded index (like the [0] that was
	// used above), you can use an integer variable to do the indexing.
	for (int ix = 1; ix < A1_SIZE; ix++)  // Loop to load the rest of holders[]
	{
		++sTemplate[0];  // The ASCII digit at the front of sTemplate will increment
		holders[ix].loadS(sTemplate);
	}
	SEE_1ST_LAST

	sTemplate[0] = 'A'; // Our template now starts with alpha A

	// An array's NAME is semantically identical to a POINTER to the 0th element of
	// the array (i.e., it is a pointer to the TYPE of elements in the array, and more
	// specifically to the element found at the 0th location in the array).
	// Below, the base type is "Holder", so "holders" is a pointer to the Holder object
	// found at the base of the array.   &holders[0] and holders are the same thing!
	for (Holder * hP = holders; hP < &holders[A1_SIZE]; )
	{
		// hP points to objects of Holder type.  Each object has members.  The
		// next line means "access what hP is pointing to (i.e., a Holder object)
		// and then invoke that object's member function .loadS()"
		(*hP).loadS(sTemplate); 

		// There's a less clunky syntax available in C++ to achieve the above,
		// the -> operator.  Below is a statement that has the same effect as
		// the statement above.  It means "look at the object that hP is pointing
		// to and invoke the member function .loadS() "
		hP->loadS(sTemplate);    

		hP++;  // Incrementing the pointer moves it in chunks of Holder type
		// hp = hp + 1; // Identical meaning to line above

		++sTemplate[0];  // The ASCII letter at front of sTemplate will increment
	}
	SEE_1ST_LAST

	demoFunc(holders, A1_SIZE); // Demo passing an array to a function.  See function below.
	SEE_1ST_LAST

	holders[A1_SIZE - 1] = holders[2];  // Demo ASSIGNMENT of one element to other spot
	SEE_1ST_LAST

	return 0;
}

// Example of passing an array of objects to a function.  What actually gets passed
// is the POINTER to the base of the array.  Must also let your function know the
// size of the array, if you're going to access all elements via a loop
void demoFunc(Holder h[], int h_size)
{
	h[0].loadS("New 0 content's much too large"); // Will get truncated in loadS()...
	return;
}

// Member function to let us access the storage.  Returns a pointer
// to the storage[] array.
char * Holder::seeS() {
	//return(storage);    // These two lines have identical meaning
	return(&storage[0]);
}

// Member function to put a string into storage
void Holder::loadS(string s) { // 1 arg. is string to be stored
	int sLen = s.length();
	next2fill = 0;
	while (next2fill < (A2_SIZE - 1)  // Don't overflow our buffer!
		&& next2fill < sLen) // AND don't exceed string length!
	{
		storage[next2fill] = s[next2fill];
		next2fill++;
	}
	storage[next2fill] = '\0';		// This statement and next...
	*(storage + next2fill) = '\0';	//   ...have identical meaning!

	//cout << "l"; // For debug trace
}
