#include "stdafx.h"
#include <iostream>
#include <string>
using namespace std;

/*  This code tests both "class" concepts and "linked list"
	concepts.  A Person "class" is defined, and it includes a
	public member variable that is a pointer to another Person.
	I provide a 2-arg constructor that populates all member
	variables, and I then use that constructor at the start of
	main() to make a linked list of 2 Persons, which are arranged
	in order of birth (lowest to highest) within the list.  I also
	provide code to partially implement the "(V)iew" menu choice. 
	DON'T WORRY ABOUT UPPER- LOWER-CASE of names.  When I test
	your code I'll type accurately. */ 

class Person { 
public:
	Person * nextP = NULL; // The PTR to the next Person
	Person();  // Default constructor
	Person(string, int);  // 2-arg constructor
	string getName();  // Accessor
	// void virtual show1(); // Task 3.  Write this function
protected:
	string name = "-";
	int birthYr = 0;
};

Person::Person() {}

Person::Person(string n, int yr) { name = n; birthYr = yr; }

string Person::getName() { return name; }

/****** Put Task 1, 2, 3 code ABOVE here, with other "Person" stuff *****/

/*	Task 1: Write an accessor that returns a Person's birth year. 3 pts.

	Task 2: Write a mutator that changes birth year.  3 pts.

	Task 3: Write a virtual member-function named "show1()" for the Person 
	class that displays birth year followed by name, tab separated, on a
	single line.  Display to cout. 5 pts.

	Task 4: Modify the (V)iew handler to use the "show1()" function
	written in Task 3. 3 pts.

	Task 5: For full credit (6 pts) write a "(C)hange" handler that
	prompts the user for the name of which person to change and for
	the new birth year. It then should update the year for that person.
	Don't bother to preserve sorted order!!  For partial credit (3 pts), 
	use the year mutator to change the year of the 1st person in the
	list to 1935.

	Task 6: Write a "(R)emove" handler. For full credit (8 pts), prompt the
	user for the person's name, find that person, and remove it from the
	list (while keeping the list useable, of course!). Remember to return 
	memory to the freestore...  For partial credit (4 pts), remove the
	person at the head of the list (i.e., SKIP prompting/scanning), or
	for 5 pts, remove the 2nd node from the list.

	Task 7. Define a class called "Musician" that is a "child" of
	the Person class.  It has a private string variable named
	"instrument" and BOTH a default constructor (that does nothing)
	AND a 3-arg constructor, which initializes "instrument" as well
	as the inherited birthYr and name variables present within its
	underlying parent Person object.  Use the 3-arg constructor to
	make "Marsalis" the 3rd object in the list -- see the code below
	that currently is commented-out...  10 pts.  Liberal partial 
	credit awarded for efforts that don't get the entire task completed
	but that have good syntax (i.e., no warnings/errors during compile)

	Task 8. Within the Musician class, "over-ride" the virtual "show1()"
	Person function with a member function that displays year, name, and
	instrument on a single line, tab separated.  6 pts if done by
	incorporating a call of the "show1()" function found in the parent
	Person class, 4 pts if done in another manner.

	Task 9.  Write an "(A)dd" handler.  Prompt the user
	for the necessary data, construct a "new" object, and then
	insert that object into the list in correct birth-year order. (I'll
	make sure I test your (C)hange handler AFTER this handler -- you
	should do the same.)

		Prompt/construct a Musician and insert by birth order = 10 pts
		Prompt/construct a Musician and insert in 2nd slot of list = 8 pts
		Prompt/construct a Musician and insert at head of list = 7 pts

			Deduct 1 from above if NO prompts, but object created by call of
			  constructor with "hard-coded" data you invent (like Marsalis) 

			Deduct 1 from above if PERSON is constructed/inserted instead of
			  Musician (so you can get partial credit even if Task 7 is skipped)

	Task 10. Write an exception handler that handles the "default" case within
	the switch statement.  It should cause the program to exit and issue
	some kind of message about the user choosing an invalid menu option. 6 pts.

*/
/****** Task 7, 8 Musician definition/functions go BELOW here ********/



/*********  Musician stuff goes ABOVE here ***************/

int main()
{
	// Here's the Person list being built.  "firstP" is the 
	// pointer to the head of the list.  I then made Fonda's
	// nextP point to a SECOND newly created node.
	Person * firstP = new Person("Fonda", 1937);
	firstP->nextP = new Person("Winfrey", 1954);

	// For Task 7, when 3-arg constructor is ready, un-comment the following
	//   line, which will then add a Musician as the 3rd node in the list.
	//(firstP->nextP)->nextP = new Musician("Marsalis", 1961, "trumpet");
	
	Person * movingPtr;  // Pointer used in (V)iew to scan through the list
	char menuChoice;

	while (true) {
		cout << "\n(V)iew, (A)dd, (C)hange, (R)emove, e(X)it: ";
		cin >> menuChoice;

		switch (menuChoice) {

		case 'V': case 'v':            // View the list
			movingPtr = firstP; // Start at head of list...
			cout << endl;
			while (movingPtr != NULL) {
				// Task 4.  Comment out the following line and replace
				//   with statement that uses your "show1" function.
				cout << movingPtr->getName() << endl;

				movingPtr = (*movingPtr).nextP; // Move on to next list node...
			}
			break;

		case 'A': case 'a':  // Add a new person/musician
			break;

		case 'C': case 'c':  // Change the year of birth
			break;

		case 'R': case 'r': // Remove person
			break;

		case 'X': case 'x':  // Exit the program
			cout << endl;
			return 0;
		default:
			cout << "Invalid choice! Choose again.";
			break;
		}
	}

    return 0;
}

