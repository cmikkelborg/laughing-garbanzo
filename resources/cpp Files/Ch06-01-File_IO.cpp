// Ch06-01-File_IO.  A console application to demonstrate opening a file on
// disk, and doing data I/O to the file.  We will be using "member functions".
//  Just as it is possible to have variables that are "members" of a struct, it's
//  possible to have FUNCTIONS (as well as variables) that are "members" of an "object".

#include "stdafx.h"
#include <iostream> // for cout, cin
#include <fstream>  // for file I/O
#include <string>
using namespace std;

// Specify a file name in a WRITABLE location on C:.  Need "\\" to produce "\"
// This is the EXTERNAL name of the file, the name that is visible in the
// Windows folder after the program is done executing.
string fileName = "C:\\users\\ddavi\\outFile.txt";

int main()
{
	string s1;

	// Declare an "object" of type "ofstream" -- an "output file stream"
	// This is a name that will be used INTERNAL to our program when we
	// do function calls to read or write a file.  This "object" has
	// "member functions" as well as "member variables".
	ofstream outFile;

	// Open the file.  Here we "attach" the internal variable to the external file
	//   using the member function ".open()"
	outFile.open(fileName);  // to create new file, or overwrite existing file
	// outFile.open(fileName, ios::app);  // to append to existing file

	if (outFile.fail())  // Always test for success, using member function ".fail()"
	{
		cout << "Failed open for output: " << fileName << endl;
		system("pause");
		exit(1);  // A function that immediately exits the program. (1) indicates error
	}

	cout << "Enter words (q to quit): ";
	while (cin >> s1)   // Get words of input from console
	{
		if (s1 == "q")  // Our "sentinel" ?
			break;
		else
		{
			//outFile << s1;  // If no "endl", all words will run together in file
			outFile << s1 << endl; // Write words to the file using << operator, as usual
		}
	}
	outFile.close();  // Close the file.

	system("pause");

	// Now, an example of opening a file to READ it.
	ifstream inFile;   // "ifstream" is an "object" for INPUT of a file's contents

	inFile.open(fileName); // Use same "member" functions as above 
	if (inFile.fail())  // Test for success...
	{
		cout << "Failed open for input: " << fileName << endl;
		system("pause");
		exit(1);
	}

	// Get words from file using extraction operator
	while (inFile >> s1)
		cout << s1 << " ";   // Output to console
		
	inFile.close();  // Close the file.

	system("pause");
	return 0;
}
