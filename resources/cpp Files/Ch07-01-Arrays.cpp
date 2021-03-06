// Ch07-01-Arrays.cpp : Displaying some basic info related
// to declaring and using ARRAYS.

#include "stdafx.h"
#include <iostream>
#include <string>
#include <cctype>
using namespace std;

// Ignore this function "prototype" for now.  The function is defined
// later in the program, and there's a detailed comment down there....
void showArray(char aAddr[], int aCap);

int main()
{
	// A "const" integer is a very useful way to keep track of
	// the CAPACITY of an array (i.e., the number of elements
	// that the array can hold).
	const int ARRAYCAP = 4;

	// DECLARING an array that can hold ARRAYCAP "doubles".
	double dblArray[ARRAYCAP];

	// DECLARING and INITIALIZING an array of ARRAYCAP "chars"
	char ltrArray[ARRAYCAP] = { 'A', 'B', 'C', 'D' };

	// Each element in an array can be individually accessed
	// using its "index" position within the array.  Regardless
	// of what kind of things are stored in an array, the
	// "index" value used to access an element is always an "int".
	// Element [0] is always the first element in an array,
	// [1] the second, etc., up to [ARRAYCAP - 1], which is
	// the last.  Element [ARRAYCAP] accesses a memory location
	// that is BEYOND the end of the array, and thus garbage.
	
	// Ways of specifying the integer "index" value can differ:
	// Can give a specific CONSTANT value, such as "3" in this case
	cout << ltrArray[3] << " is ltrArray[3]\n";

	// Can use the value of an "int" VARIABLE to access an element.
	// This implies that as the value of that variable changes, different
	// elements of the array will be accessed.
	int count = 2;
	cout << ltrArray[count] << " is ltrArray[count]\n"; // Which element accessed?
	cout << ltrArray[--count] << " is ltrArray[--count]\n"; // Which one NOW?

	dblArray[3] = 4.44;  // Put a value into 4th element of other array
	dblArray[count] = dblArray[3] / 2.0; // Divide 4th element by 2.0 and save
										 // result where?  What's current value of "count"?
	cout << dblArray[1] << " is dblArray[1]\n\n";

	// "for" loop is meant to be used to access array elements in sequential order.  
	// Often see the variable "ix" used for that purpose -- shorthand for "index".
	// Start at ix = 0, then increment upward to access each element in turn. 
	//    What's in dblArray? We've only assigned values to two of the elements in 
	//    dblArray, so those two will make sense, and the others will be garbage.
	for (int ix = 0; ix < ARRAYCAP; ++ix)  // Access each element in turn...
		cout << dblArray[ix] << endl;

	// Can pass a single array element as an argument to a function
	ltrArray[2] = tolower(ltrArray[2]);

	// Can pass an entire array as an argument (works like a "call by reference").
	cout << "\nltrArray contains: ";
	showArray(ltrArray, ARRAYCAP);
	  //showArray(ltrArray, 5); // Whoa! Specified a capacity larger than reality!

	system("pause");

	const int ARRAY2CAP = 6; // Declare and initialize a larger array
	char letters[ARRAY2CAP] = { 'L','Z','M','R','A','D' };
	showArray(letters, ARRAY2CAP); // Same function can show larger array!

	// Very typical to scan through an array performing some math, such
	// as finding a min or max value, or finding the sum of values.
	int topVal = 0; // Start by assuming that element [0] is the max
	for (int ix = 0; ix < ARRAY2CAP; ix++)  // Loop through all values...
		if (letters[ix] > letters[topVal]) // If OTHER element is higher,
			topVal = ix;					//    then make IT the highest

	cout << letters[topVal] << " is the top char.\n\n";
	
	// Can have an array of any type of data, including structs
	struct Person {
		string firstName;
		string lastName;
	};

	Person people[ARRAYCAP] = { {"Fred", "Astaire"},
								{"Ginger", "Rogers"},
								{"Meryl", "Streep"},
								{"Jennifer", "Lawrence"}   };

	topVal = 0; // Start by assuming that element [0] is the max
	for (int ix = 0; ix < ARRAYCAP; ix++)  // Loop through all values...
		if (people[ix].lastName > people[topVal].lastName) // If OTHER element is higher,
			topVal = ix;									//    then make IT the highest

	cout << people[topVal].lastName << " is the top name.\n";
	return 0;
}

// An array can be passed as the argument to a function, as below.
// The identifier "aAddr" provides the ADDRESS in memory of
// the first element of the array (element [0]), and the "char"
// specification lets the compiler know the SIZE OF EACH
// INDIVIDUAL ELEMENT of the array.  The CAPACITY of the
// array is revealed by the "aCap" argument.  Without that
// argument, the function wouldn't know the possible OK
// values for the int variable "ix" that is being used to
// access the elements of the array.  The last element in
// the array is element aAddr[aCap - 1].
void showArray(char aAddr[], int aCap)
{
	for (int ix = 0; ix < aCap; ix++)
		cout << aAddr[ix] << ' ';

	cout << endl;
	return;
}

