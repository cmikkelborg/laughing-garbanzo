// Ch10-01-Structs.cpp : Demonstrating some characteristics
// of "struct" data structures

#include "stdafx.h"
#include <iostream>
#include <string>  // Since we're accessing "string" variables.
using namespace std;

/*  Pieces of data that logically should be thought of as
	parts of a unified data entity can be bundled into
	a user-defined data-type called a "struct".  Define
	it by using the keyword struct, give it a name, and then
	put the included basic data types within a pair of curly 
	braces, all followed by a semi-colon.
*/
struct Person {   // This struct to hold both names of a person
	string firstName;  // Each "type" included in the struct
	string lastName;   //   must be a type known to the compiler.
};

/*  The above is the DEFINITION of the data-type, "Person".  Can
	then DECLARE variables of that type.  When declaring a variable,
	can INITIALIZE it, just as you can with simple types, such as int.
	Initializing is done with an assignment operator (the equal sign)
	followed by a pair of curly braces enclosing the initial values
	of the included members, separated by commas.
*/
Person personA;  // Declaring an uninitialized Person
Person personB = { "David", "Davidson"};
Person personC = { "Matt", "Damon"};

int main()
{
    // You access the component parts of a struct with the
	// "member" operator, which is a "dot" separating the two IDs.
	cout << personB.lastName << ", " << personB.firstName << endl;
	
	// Those individual members can be treated exactly as their 
	// simple types can be treated.  Can assign new value L
	// a member.  Can concatenate added string
	// onto the end of a member.  Can assign new value to a member.
	// Can query as to whether 2 members are ==, >, <, etc.  Can
	// do math on components such as int and double.
	cin >> personA.firstName >> personA.lastName;
	cout << personA.lastName << ", " << personA.firstName << endl;

	personA.firstName = personB.firstName + personC.firstName; // Concatenating
	cout << personA.lastName << ", " << personA.firstName << endl;

	if (personB.lastName > personA.lastName)  // Comparing alphabetic order
		cout << personA.lastName << " comes before " << personB.lastName;
	else cout << personB.lastName << " comes before " << personA.lastName;
	cout << " in alphabetic order.\n";

	//  Can assign the entire contents of a struct to another one of same type.
	struct Person personD = personC;  // Declare new one, assign it a value.
	cout << personD.lastName << ", " << personD.firstName << " is person D." << endl;

	// Can then use your FIRST struct as a member of ANOTHER struct

	struct Book {  // Here we DEFINE a new struct called "Book"
		double price;
		Person author;  // Here's user-defined "Person" as part of "Book"
		string title;
	};
	// Can then DECLARE and INITIALIZE as shown earlier, with nested set
	//  of curly braces showing the values for the nested struct "Person"
	Book bookA = {4.95, {"William", "Shakespeare"}, "Macbeth"};

	// Now need two dot operators to access a member within a member
	cout << "The book " << bookA.title << " was written by "
		<< bookA.author.lastName << " and costs " << bookA.price << endl;

	return 0;
}

