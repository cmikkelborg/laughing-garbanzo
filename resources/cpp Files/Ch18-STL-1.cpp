// Ch18-STL-1.cpp : Demonstrating some characteristics of
// "vectors", one of the "sequential container templates"
// that exist within the C++ Standard Template Library.
// vectors are chosen for this demo because of their
// versatility -- they can be accessed both iteratively
// (i.e., by advancing an "iterator" (which is like a
// pointer) along the sequence) and randomly, using
// the bracket [index] method.  See p 977.
// The "vector" class supports many member functions,
// (see p. 977, 978), including several that are NOT
// mentioned in Savitch, such as
//   .back() references the final element in the vector
//   .pop_back() to remove final element
//   .emplace() to construct and insert a new element
//
// google "member functions C++ vector" to see a full
// list

#include "stdafx.h"
#include <iostream>
#include <vector>  // Each STL container requires its own #include
using namespace std;

// Here is a function we can use to display vector's contents
// repeatedly.  All "sequential containers" have a member function
// .size() that reveals how many elements are in the container.
// .size() returns an "unsigned int" rather than our usual "int",
// so the "i" variable has been declared as "unsigned int" in 
// order to avoid having the compiler issue a warning...

void displayIntVector(vector<int>& v)
{
	cout << "\nSize of vector is " << v.size() << endl;
	for (int i = 0; i < v.size(); i++)
		cout << v[i] << " ";  // Using bracket[ix] to see contents!
	cout << endl << endl;
}

int main()
{
	// Here's a declaration and initialization of a vector named v1 that can
	// hold ints, and starts off with 3 of them.
	vector <int> v1 = { 23, 47, 162 };

	displayIntVector(v1);  // Call our function above

	// The index value used to access an element must be
	// within the range of the vector's current size!
	// Try to compile/run the following line -- problem!
	// cout << v1[4];  // Index too high!  Not valid!

	// To make a LIFO "stack" simple to implement, two 
	// member functions are available to "push" onto the
	// back and "pop" off of the back of the vector
	int num1 = 1;
	v1.push_back(num1); // Can "push" integers onto v1....
	v1.push_back(2);    //   int constant, or int variable...
	displayIntVector(v1);

	// bracket[index] method can access elements in the vector
	num1 = v1[v1.size() - 1];
	cout << num1 << " is at back, " << v1[0] << " is at front\n";

	v1.pop_back();      // Removes the backmost element
	displayIntVector(v1);  //  See that v1 has now shrunk

	// There's an .erase() function and an .insert() function that
	// can remove and add elements at ANY location in the vector.
	// BUT, they must be passed an iterator indicating where to make
	// the change, and the iterator must be derived by using either
	// the .begin() function (which references the first element) or
	// the .end() function, which is a sentinel value just beyond 
	// the current size of the vector.
	// Remove the first element:
	v1.erase(v1.begin());
	displayIntVector(v1);

	// Add an element at the end (which is what .push_back() also does)
	v1.insert(v1.end(), 99);
	displayIntVector(v1);

	// As with pointers, can add/subtract to an iterator, which
	// makes it reference other elements in the vector.
	// Add an element at 2nd position, then erase 2nd from rear
	v1.insert(v1.begin() + 1, 88);
	v1.erase(v1.end() - 2);
	displayIntVector(v1);

	system("pause");
	return 0;
}
/*
// Here's an ALTERNATE "display" function that uses an
// "iterator" to access each vector element.  Each STL
// container defines an "iterator" type, which is conceptually
// equivalent to a pointer.  The standard "*" and "&" operators
// that we use to establish pointers to arrays will NOT work
// with STL containers.    int * localPtr = &v[0];  is what
// we might use to establish a pointer to the first int in
// an array of ints.  WON'T work with STL containers...
// Must use "iterator" type, and must then use member
// functions .begin(), .end() to initialize the iterator.
// BUT, once initialized, normal pointer math and operations
// are supported     ++   --   *  ==   !=
void displayIntVector(vector<int>& v)
{
	cout << "\nSize of vector is " << v.size() << endl;
	vector<int>::iterator localPtr; // Syntax of specifying "type" of iterator
	localPtr = v.begin(); // Initialize to first element in vector
	for (; localPtr != v.end(); localPtr++)
		cout << *localPtr << " ";  // using pointer syntax
	cout << endl << endl;
}
// Here's a display function that uses a REVERSE iterator
// to "advance" from the back to the front using the ++.
// It will display contents in reverse order.
void rdisplayIntVector(vector<int>& v)
{
	cout << "\nSize of vector is " << v.size() << endl;
	vector<int>::reverse_iterator localPtr; // Specifying "reverse" type
	localPtr = v.rbegin(); // Initializes to LAST element in vector
	for (; localPtr != v.rend(); localPtr++)
		cout << *localPtr << " ";  // using pointer syntax
	cout << endl << endl;
}

// Stuff to do with generic algorithms in the STL - discuss next class
#include <algorithm>
reverse(v1.begin(), v1.end());
displayIntVector(v1);
random_shuffle(v1.begin(), v1.end());
displayIntVector(v1);

*/


