// Ch07-03-ArrayDemo.cpp : Trying to help you understand the difference
// between the ADDRESSES of the "boxes" in an array, versus the CONTENTS
// of a given box.  Below is an array of 6 doubles.  Think of each double
// as being in its own box, with the ADDRESS of zero being the first box in
// line, and the address of five being the last to the right.  The
// ADDRESSES of the boxes are always ints, even if the CONTENTS of the
// boxes are something else -- doubles, in this case.

// Notice that an ADDRESS of six makes no sense, because the largest
// possible ADDRESS for this array is five
//

#include "stdafx.h"
#include <iostream>
using namespace std;


int main()
{
		// BOX ADDRESS   0    1     2    3    4     5
	double boxes[6] = { 2.3, 4.7, 8.92, 0.5, 3.2, 14.6 };

	// Re-doing here the algorithm that finds the smallest double
	// that exists within this row of boxes (i.e., this array).

	//  All of these ints are ADDRESS values that we'll fiddle with
	int	boxAddrOfLeftEnd = 0;  // The leftmost box has an ADDRESS of zero
	int boxAddrOfRightEnd = 5;  // The righmost has an ADDRESS of five
	int boxAddrOfSmallestVal;
	int box2LookIn;

	boxAddrOfSmallestVal = boxAddrOfLeftEnd;  // Make guess that smallest value is in leftmost box...

	// Now, loop thru the box ADDRESSES, from left to right.  box2LookIn will hold each ADDRESS in turn
	for (box2LookIn = boxAddrOfLeftEnd; (box2LookIn <= boxAddrOfRightEnd); box2LookIn++)
	{    // At every ADDRESS, look at the box CONTENTS (which is done with the [] notation)
		if (boxes[box2LookIn] < boxes[boxAddrOfSmallestVal])  // Does boxes[box2LookIn] contain smaller value?
			boxAddrOfSmallestVal = box2LookIn;  // If so, update the ADDRESS of the box holding smallest value
	}

	cout << "Box #" << boxAddrOfSmallestVal << " holds the smallest value\n";
	cout << "That value is " << boxes[boxAddrOfSmallestVal] << endl;

	// **************************************************************************
	// AGAIN re-doing  the algorithm that finds the smallest double
	// that exists within the array, but now with POINTERS

	//  Establish POINTERS that correspond to the box addresses above
	double * ptrToLeftEnd = &boxes[0];  // Initialize pointer to address of base element in array
	double * ptrToRightEnd = &boxes[5]; // Initialize to address of final element in array
	double * ptrToSmallestVal;
	double * ptrToScanBoxes;

	ptrToSmallestVal = ptrToLeftEnd;  // Make guess that smallest value is in leftmost box...
	
	// Now, use pointer to scan through array, looking at each element in turn.  Using the
	// ++ operator to "increment" a pointer results in the pointer now pointing at the next
	// element in the array, no matter what is stored in the array.  Here, where doubles are
	// in the array, that "increment" results in the pointer jumping ahead 8 bytes
	// in actual RAM memory address, because each double is 8 bytes in size.  Also note tha
	// comparison of pointers, in order to determine when we've scanned the whole array.
	for (ptrToScanBoxes = ptrToLeftEnd; (ptrToScanBoxes <= ptrToRightEnd); ptrToScanBoxes++)
	{    // At every address, look at the box CONTENTS (which is done with the * notation)
		if (*ptrToScanBoxes < *ptrToSmallestVal)  // Does box we're scanning contain smaller value?
			ptrToSmallestVal = ptrToScanBoxes;  // If so, update the pointer to the box holding smallest value
	}

	// To figure out which box # held smallest, can "subtract" two pointers.  Again, the
	// "subtraction" is smart enough to realize that it must account for the size of each element
	// in the array.
	cout << "Box #" << (ptrToSmallestVal - ptrToLeftEnd) << " holds the smallest value\n";
	cout << "That value is " << *ptrToSmallestVal << endl;

    return 0;
}

