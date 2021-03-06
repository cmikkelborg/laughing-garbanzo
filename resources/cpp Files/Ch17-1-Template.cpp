// Ch17-1-Template.cpp : A file to demonstrate the concept of
// building "templates" for algorithms and data structures.
// We'll make a generic selection-sort algorithm that is
// capable of being used on different types of content.
// We'll also make a generic node for a linked list that
// is capable of containing different types of content.

#include "stdafx.h"
#include <iostream>
#include <string>
using namespace std;


/***** Here's an algorithm template **********/
/* The reserved word "template" followed by the <> brackets 
	must immediately precede the definition of the function.  The
	identifier "eventualType" present in the <> brackets is a
	local name to represent the TYPE that is eventually "passed"
	to this template when the selSort function is called.  Note
	that "eventualType" is only referenced in the parameter list
	and then at line 44, when a "temp" variable is created to
	facilitate swapping of two values in the array.  In essence,
	NONE of the algorithm's logic depends upon the "type" of
	objects in the array, which is why this algorithm is well-
	suited to implementation as a template...   
*/
template<class eventualType>
void selSort(eventualType theArray[], int arraySize)
{
	int rightSearchEdge = arraySize;
	int leftSearchEdge;
	int searcher;
	int slotWithMin;

	// Sub-array begins as ENTIRE array, and is then made smaller, slot by slot
	for (leftSearchEdge = 0; leftSearchEdge < rightSearchEdge; leftSearchEdge++)
	{
		slotWithMin = leftSearchEdge;	// Assume MIN is in 1st slot of this sub-array
		for (searcher = leftSearchEdge; searcher < rightSearchEdge; searcher++)
		{
			if (theArray[searcher] < theArray[slotWithMin])	// Find MIN value in sub-array
				slotWithMin = searcher;
		}
		eventualType temp = theArray[leftSearchEdge];    // Swap MIN into 1st slot of sub-array
		theArray[leftSearchEdge] = theArray[slotWithMin];
		theArray[slotWithMin] = temp;
	}
}

//*** Here's a template for a "class" definition *******
// This class and associated member functions implement
// a simple LIFO stack, with "pushed" items stored in
// dynamically created nodes that are then put at the
// head of a linked list. "Pop" retrieves starting at
// the head of list.

template<class T>
class slNode   // This is the CLASS definition template
{
public:
	slNode<T> * nextN; // Ptr to next node in list
	slNode() { nextN = NULL; } // Default constructor
	void push(slNode<T>*&, T); // Has member functions push/pop
	T pop(slNode<T>*&);
private:
	T content;
};

template<class T> // The member "push" FUNCTION template
void slNode<T>::push(slNode<T>*& nPtr, T newVal)
{
	slNode<T> * tempPtr = new slNode<T>;
	tempPtr->content = newVal;
	tempPtr->nextN = nPtr;
	nPtr = tempPtr;
}

template<class T> // The member "pop" FUNCTION template
T slNode<T>::pop(slNode<T>*& nPtr)
{
	T temp = nPtr->content;
	slNode<T> * tempPtr = nPtr;
	nPtr = nPtr->nextN;
	delete tempPtr;
	return temp;
}


int main()
{
	char cA[10] = "dacgibzwo"; // A c-string with 9 letters and a terminating \0
	selSort(cA, 9); // Templated "sort" function will operate on chars
	cout << cA << endl;

	int iA[9] = { 34, 14, 77, 29, 5, 43, 22, 65, 2 }; // Array of 9 ints
	selSort(iA, 9); // Templated "sort" function will operate on ints
	for (int ix = 0; ix < 9; ix++)
		cout << iA[ix] << " ";
	cout << endl;

	// Below is use of both a templated class and templated functions.  By
	// changing the "define" below from double to char, the code that follows can
	// be compiled/run with NO other changes

#define nContentType double // Can change to "char"...

	slNode<nContentType> * listHead = NULL; // Differing types of objects will be built
	nContentType temp;

	cout << "Enter 5 values, space separated: ";
	for (int ix = 0; ix < 5; ix++)
	{
		cin >> temp; // Fetch value from user -- might be either double or char!
		listHead->push(listHead, temp); // "Push" value onto stack
	}
	while (listHead != NULL)
		cout << listHead->pop(listHead) << " ";


    return 0;
}

