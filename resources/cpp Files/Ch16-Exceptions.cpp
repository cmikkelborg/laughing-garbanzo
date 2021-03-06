// Ch16-Exceptions.cpp : This sample code is intended to
// help understand the flow-of-control and the workings
// of the C++ "Exception Handler" mechanism.  Ch 16 Savitch.

#include "stdafx.h"
#include <iostream>
#include <string>
using namespace std;

int main()
{
	try {
		// Here's your program code INSIDE a "try" block

		// Plugging away in here, and hit error...

		throw 15; // A "throw" statement followed by an integer

		// Program code that gets SKIPPED if "throw" occurs
		cout << "End of \"try\"\n";
	}
	
	// "catch" block(s) must IMMEDIATELY FOLLOW a "try" block.
	//cout << "Code here?"; // Compiler error to have other code here!

	// This "catch" block is capable of catching integers.
	catch (int myNameForInt)  // works similarly to a function argument
	{
		cout << "Caught int: " << myNameForInt << endl;
	}

	cout << "Got to end!\n";
	return 0;
}

/*  Some stuff used later in the demo...

catch (char s[])
{
cout << "Caught c-string: " << s << endl;
}
catch (ComplexE e)
{
cout << e.getE_m() << e.getE_v() << endl;
}

// Defining an error-handling class
class ComplexE {
public:
ComplexE() {};
ComplexE(string s, int i) { msg = s; value = i; }
string getE_m() { return msg; }
int getE_v() { return value; }
private:
string msg = "Default";
int value = -1;
};

void demoFunction(int i) throw (ComplexE)
{
cout << i << "+";
if (i > 0)
demoFunction(--i);
throw ComplexE("Deep in recursion! ", 26);
cout << i << "-";
}

*/

