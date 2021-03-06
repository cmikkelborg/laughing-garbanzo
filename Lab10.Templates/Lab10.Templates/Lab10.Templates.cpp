// Lab010.Templates.cpp
// Author: Charles Mikkelborg
// Description: Reads an input file to poplulate a list of nodes and sorts them based on their value. 
//		Each node has a pointer to the next, so each new node has to be inserted without losing a pointer 
//      to any other node. After all nodes are entered and sorted, then print the list. This is a modified 
//      version of lab07, that uses a template structure and function to accept files of different data 
//      types and sort them in the same way, with minimal changes to the main code. In this version,
//      line 83 and 86 are the only lines that have to be changed to sort either integers or characters.
// Last modified: 06/06/2018

#include "stdafx.h"
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

const string fileIntRd = "unsorted127.txt"; // integer file
const string fileAlphaRd = "unsortedalphas.txt"; // alpha file

// STRUCTURES //

// The original assignment called only for a template function so there was a need to
// have a seperate structure for both ints and chars. I have left these here, so that
// the original assignment is preserved. They can be un-commented and can be used by 
// making appropriate changes within main.

struct iNode { // Node for storing integers
	int value; // placeholder for data from file
	struct iNode * nextNode; // pointer to point to other Nodes
};
struct aNode { // Node for storing chars
	char value;
	struct aNode * nextNode;
};

/*
// A template structure, although not called for, made changing between data
// types a bit more simple within the main code.
template<class T>
struct Node { // template Node for storing any desired data type
	T value;
	Node<T> * nextNode;
};
*/

// ***** TEMPLATE FUNCTIOIN ***** //
template<class NODETYPE>
NODETYPE * sortNode(NODETYPE * listHead, NODETYPE * createdNode) { // This function sorts Nodes by the size of its content, 
																   // and is configurable for different data types
	if (listHead == nullptr) { // check to see if there is any list
		listHead = createdNode; // if not, then make the new Node the head of list
		listHead->nextNode = nullptr; // and also make it the end of list
	}
	else if (listHead->value > createdNode->value) { // else check to see if the value of the new Node is the smallest value so far
		createdNode->nextNode = listHead; // if so set new Nodes's pointer to point to old head of list
		listHead = createdNode; // and set new Node as the new list head
	}
	else { // lastly, if its value is not less than list head continue to place it correctly in list
		bool inserted = false; // boolean to evaluate if Node has been placed anywhere in list
		NODETYPE * movingPtr; // create new pointer of same type as the input pointers
		movingPtr = listHead; // establish a pointer to move through list, starting at the beginning of list
		while (!inserted) { // run while new Node is not yet inserted anywhere in list
			if (movingPtr->nextNode == NULL) { // first check to see if movingptr is at the end of the list
				movingPtr->nextNode = createdNode; // if it is at the end of list, add new Node to end of list
				createdNode->nextNode = NULL; // and set new Node's pointer to be the new end of list
				inserted = true; // new Node is now inserted
			}
			else if ((movingPtr->nextNode)->value >= createdNode->value) { // else if the moving pointer is not at end of list, check to see if
																		   // the value of what moving pointer is pointing too is greater than
																		   // the value of the new Node 
				createdNode->nextNode = movingPtr->nextNode; // if it is, put new Node between moving pointer and what it is currently pointing to.
				movingPtr->nextNode = createdNode;           // by first setting new Node's pointer to the same as moving pointer's pointer, and then
				inserted = true;                             // setting moving pointer's pointer to point to new Node, and show new Node as sorted.
			}
			else
				movingPtr = movingPtr->nextNode; // else move moving pointer forward by one in the list.
		}
	}
	return(listHead); // when finished return the list head pointer of the newly modified list.
}

int main()
{
// #define nContentType int // Used to define the conent type of the Node structures built.

	ifstream rdDB;
	rdDB.open(fileIntRd); // Read in the list file, change this file to read in a int list 
						  // or a char list from the constants named at top and change the 
						  // nContentType above to match the file contents.
	if (rdDB.fail()) // Check to see if file fails to open
	{
		cout << "-Failed to Open File-" << endl; // if it does then print msg to console and exit

		system("pause");
		exit(1);
	}

	// These separate Node structures below for ints and chars work fine, but I found it 
	// slightly more tedious to change the main code to receive chars or ints using these 
	// Node structs. With a template structure you only need to change the nContentType 
	// and opened file above (line 83 and 86), instead of having, in addition to the file, 
	// the need to change every Node type, and make sure pointers reference the appropriate  
	// Node type. This of course is the very benefit of using templates. It didn’t seem much 
	// of an extra step to make a template for the structure as well. I Left these here as they 
	// were what was expected for this assignment, and so that it is shown that changing between 
	// these would not have required altering the inputs of the sort function; it would only have
	// been a matter of changing the file and commenting out the struct pointers of the
	// wrong data type, and referencing the desired node on line 124

	struct iNode * listHead = NULL;
	struct iNode * movingPtr;
	struct iNode * createdNode;

//	struct aNode * listHead = NULL;
//	struct aNode * movingPtr;
//	struct aNode * createdNode;

	// Node structure using a template for variable content types //
	// struct Node<nContentType> * listHead = NULL;
	// struct Node<nContentType> * movingPtr;
	// struct Node<nContentType> * createdNode;

	bool dbComplete = false;
	while (!dbComplete) { // To begin we make a loop that runs until instream is empty
		createdNode = new iNode; // Create a node to fit the content type
		if (rdDB >> createdNode->value) // if there is content read in from file
			listHead = sortNode(listHead, createdNode); // then run function to sort input
														// and return a pointer to be 
														// the new head of list
		else { // if there is not content to be read in
			rdDB.close(); // close the file
			delete createdNode; // delete the node we created to hold the instream
			dbComplete = true;  // and exit the loop
		}
	}
	
	// PRINT CONTENTS AND DELETE //
	movingPtr = listHead; // Set up moving pointer to read the list
	if (movingPtr == NULL) { // If moving pointer is empty 
		cout << "No data in file." << endl; // then print to console that nothing was read from file
		  								    // then (from below) delete node, and exit.
	}
	else {
		while (movingPtr->nextNode != NULL) {  // While not at the end of list 
			cout << movingPtr->value << endl;  // print the value of Node struct
			listHead = movingPtr;              // use listHead to select the Node for deletion
			movingPtr = movingPtr->nextNode;   // and advance to the next Node
			delete listHead;                   // now delete the previously read Node, then repeat
		} // This loop will not print out the last value, as its 'nextNode' is NULL
		cout << movingPtr->value << endl; // finish by printing the last item on the list
	}
	delete movingPtr;                 // then delete that last remaining Node

	system("pause");
	return 0;
}