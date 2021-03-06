// Ch18-STL-2.cpp : Demonstrating the "map" container within the STL.
// See Display 18.13 in Savitch.  Map contains linked pairs of content,
// where the first item in the pair is the "key" and the second item
// is the associated value.  The "key" is used to specify which
// element in the map is to be accessed.

#include "stdafx.h"
#include <iostream>
#include <string>
#include <map>   // Include the necessary header...
#include <utility>
using namespace std;

int main()
{	// Our map will have state names as "key" values, with the
	// associated populations as the corresponding data.
	// Note syntax of type declaration, with <> brackets showing
	// the types of the two parts of the pair -- string for state
	// name (the key), and int for population.  We initialize
	// in random order, but when building the map, STL puts the states
	// in ascending order by "key"  i.e., in alpha order
	// by state name.
	map<string, int> statePops = {
		{ "Washington", 7288000 },
		{ "California", 39250017 },
		{ "Alabama", 4863300 },
		{ "New York", 19745289}
	};

	// Bracket[key] syntax is used to refer to the int value paired
	// with each state name.  Here, we print the pop of Alabama.
	cout << statePops["Alabama"] << endl;

	// Here, we assign a pop to Nevada, which was NOT in the map!
	//  Goes ahead and puts pair into the map, in correct alpha order.
	statePops["Nevada"] = 2940058;

	// See discussion in Savitch about "pair<T1 T2>" class, on the page
	// before display 18.13.  Basically, to use some of the map member
	// functions (such as .insert()), it's necessary to create an object
	// of type "pair<string,int>"  (which matches the type of objects
	// we built the map out of).  Here, we declare such an object, and
	// we then prompt the user to give us a new pair for the map,
	// putting the name into ".first" and the pop into ".second", which
	// are two public variables in the "pair" class.
	pair<string, int> aState;
	cout << "Enter state and pop: ";
	cin >> aState.first >> aState.second;

	// See the description of the .insert() function for map, in
	// display 18.13.  .insert() returns a value of type "pair<iterator, bool>"
	// In our case, the "iterator" is a "map<string, int>::iterator", so the
	// declaration of the object needed to hold the result is thus:
	pair<map<string, int>::iterator, bool> inResult;
	inResult = statePops.insert(aState);
	if (inResult.second) // Test the bool -- success doing insertion?
		cout << inResult.first->second << endl; // Yep.  Print out the pop.

	// Here we declare an iterator that will work with our map.  The
	// .begin() function has a return value of "iterator".  We'll use the
	// iterator to print the map content.
	map<string, int>::iterator iter;
	for (iter = statePops.begin(); iter != statePops.end(); iter++)
		cout << iter->first << ": " << iter->second << endl;

	// .size() tells # entries in map.  
	cout << endl << statePops.size() << " " << "entries in map\n";

	// Use reverse_iterator type to print the map content in reverse order.
	map<string, int>::reverse_iterator riter;
	for (riter = statePops.rbegin(); riter != statePops.rend(); riter++)
		cout << riter->first << ": " << riter->second << endl;

    return 0;
}

