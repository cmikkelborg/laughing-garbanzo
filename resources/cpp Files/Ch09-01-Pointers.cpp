// Ch9-01-Pointers.cpp : This file is intended to help understand the concept
// of a "pointer".  Most of the TYPES of variables we've used are designed
// to represent real-world kinds of data that we need to work with -- 
// "char" for letter/digits, "double" for floating point numbers, etc.  The
// pointer is NOT a type that corresponds with any real-world data, but
// rather is a thing that was invented purely to help manipulate
// data within computer programs.  It basically exists in order to
// work with arrays (which we will do), and linked lists (which are studied in
// CS 132).

#include "stdafx.h"
#include <iostream>
using namespace std;

int main()
{
	// When we declare and initialize a "normal" variable, the compiler places
	// the specified value into a location in memory that is the correct size
	// to handle that type of value. So below, two doubles are declared.  The
	// compiler establishes an 8-byte storage location for each (because 8 bytes
	// are needed to store a double), puts the values (5.6 and 8.9) into the
	// locations, and associates the names "num1" and "num2" with those locations.
	double num1 = 5.6, num2 = 8.9;

	// A "pointer" is a type of variable that holds the MEMORY ADDRESS of
	// some traditional variable.  You must tell the compiler what TYPE of
	// traditional variable the pointer will point to.  The asterisk * symbol
	// is used to indicate that you want to declare a POINTER, rather than
	// a traditional variable.  Here, we tell the compiler that we want to
	// have a variable named "dPtr" that is able to hold the ADDRESS of a
	// traditional "double" variable (such as the two we declared above!)
	double * dPtr;

	// So, how do we determine the ADDRESS of a traditional variable?  There
	// is the & operator.   When placed in front of the name of a
	// traditional variable, that operator gives the ADDRESS in memory of that
	// specific variable.  That ADDRESS, then, can be assigned as the value
	// of a pointer.  Here, we determine the ADDRESS of num1, and assign that
	// ADDRESS as the value of the dPtr pointer.
	dPtr = &num1;
	cout << "The value of num1 is " << num1 << " and its ADDRESS is " << dPtr << endl;

	// Once there is a pointer that is declared and initialized, it can then
	// be used to access the variable that it is pointing to.  This is also done 
	// with the asterisk * operator.  Putting an asterisk in front of a pointer
	// means "access what it is pointing to".  In essence, a variable's value
	// can now be accessed in two different ways -- either by its normal variable
	// name, or indirectly, by using the pointer that points to it.
	cout << "num1 is " << num1 << " and *dPtr is ALSO " << *dPtr << endl;

	// An assignment of a new value to the variable can be done via the *dPtr
	// access.  *dPtr basically can be placed anywhere in a statement that 
	// a traditional double variable could have beend placed.
	*dPtr = *dPtr + 4.0;
	cout << "After *dPtr = *dPtr + 4.0, num1 is " << num1 << endl;

	// So, why bother!?!  What good is it to set up two different ways of
	// accessing the same variable?  Turns out to be of little use when
	// accessing a single variable (such as num1), but very useful when
	// accessing the elements in an array.  Here we declare an array
	// that can hold 4 doubles.
	double dA[4] = { 1.1, 2.2, 3.3, 4.4 };

	// We can make dPtr point to the first element in the array.
	dPtr = &dA[0];
	cout << "First element in dA is " << *dPtr << endl;

	// We can then use a limited group of math operations (add, subtract,
	// compare) to change and work with the value of dPtr, which then lets us 
	// access other doubles in the array.  If we add 1 to dPtr, it makes
	// dPtr able to access the next element in the array, for example.  
	// Adding 1 to a pointer works the same as adding 1 to an [ix] index value
	// See p.528 Savitch, "Pointer Arithmetic"
	cout << "Second element in dA is " << *(dPtr + 1) << endl;

	// Below, we'll declare a second pointer and initialize it to point to
	// the LAST element in the array.  We can then easily scan through
	// the array by incrementing dPtr until such time as dPtr reaches dPtr2
	double * dPtr2 = &dA[3];  // dPtr2 points at LAST element in array
	for (; dPtr <= dPtr2; dPtr++)
		cout << *dPtr << "  ";  // Output "what's pointed to", which is the
								// double stored in that element of the array

	// There's another thing that can be done with pointers and arrays.
	// It is ALWAYS necessary to specify the SIZE and TYPE of an array at the
	// time the array is declared (and that size/type can then never be changed). 
	// BUT arrays don't always have to be declared at the time you compile
	// your program.  You can have a DYNAMIC array that is declared into
	// existence while the program is running, and the size of that
	// array can be established just before it is declared.  See p. 522 Savitch
	cout << "\nArray size? (6 or larger!) ";  // Let user choose the size...
	int size;
	cin >> size;
	double * dNewArr;			// Declare a pointer variable, and then init it
	dNewArr = new double[size];  // to access a NEW array we bring into existence!
	double * dPtr3;  // Init. another pointer we'll use in a moment...

	// Now going to copy elements from our original array into the new one
	dPtr = &dA[0];  // Re-set dPtr to base of original static array
	dPtr3 = dNewArr; // Set up dPtr3 to base of new dynamic array
	for ( ; dPtr <= dPtr2; dPtr++, dPtr3++) // For each element in original array
		*dPtr3 = *dPtr;                     //   copy it into new array

	*dPtr3++ = num1;  // Tack a couple more values onto end of new array
	*dPtr3++ = num2;

	// Now let's look at what's in the new array.  Scan again, starting at base...
	for (dPtr = dNewArr; dPtr < dPtr3; dPtr++)
		cout << *dPtr << "  ";
	cout << endl;

	delete[] dNewArr; // Got to manually delete dynamic arrays...

	system("pause");
	return 0;
}

