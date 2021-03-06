// lab07.cpp
// Author: Charles Mikkelborg
// Description: Reads an input file to poplulate a list of nodes and sorts them based on their value. Each node has a pointer to the next,
//		so each new node has to be inserted without losing a pointer to any other node. After all nodes are entered and sorted, then print the list.
// Last modified: 05/24/2018

#include "stdafx.h"
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

const string diskFileRd = "unsorted127.txt";

struct Numb { // structure to hold a value and a pointer to the next node
	int value;
	struct Numb * nextNumb;
};

int main()
{
	ifstream rdDB;

	struct Numb * numbListHead = NULL; // node to establish begining of list
	struct Numb * movingPtr; // node to traverse the list
	struct Numb * createdNode; // node to hold incoming values from file

	rdDB.open(diskFileRd); // read in list file
	if (rdDB.fail()) // check to see if file fails to open
	{
		cout << "-Failed to Open File-" << endl;

		system("pause");
		exit(1);
	}

	createdNode = new Numb; // create a empty Numb place holder for numbers coming in from file

	if (!(rdDB >> createdNode->value)) { // fill our new empty Numb and check to see if there are any numbers in the file
		cout << "No data in file.\n";

		system("pause");
		exit(1);
	}
	else { // if there is, set that first number to the list head
		numbListHead = createdNode;
		numbListHead->nextNumb = nullptr; // make list head the end of list
	}
	createdNode = new Numb; // create a new empty Numb place holder for next number coming in
	while (rdDB >> createdNode->value) { // Loop as long as there are numbers coming in from file
		if (createdNode->value <= numbListHead->value) { // Check to see if next new number is the smallest number so far
			createdNode->nextNumb = numbListHead; // if so set new number's pointer to point to old list head
			numbListHead = createdNode; // set new number as the new list head
		}
		else { // if it is not less than list head continue
			bool inserted = false;
			movingPtr = numbListHead; // establish a pointer to move through list
			while (!inserted) { // run while new number is not  yet inserted anywhere in list
				if (movingPtr->nextNumb == nullptr) { // first check to see if movingptr is at the end of the list
					movingPtr->nextNumb = createdNode; // if it is at the end of list, add new number to end of list
					createdNode->nextNumb = nullptr; // and set new number's pointer to be the new end of list
					inserted = true; // new number is now inserted
				}
				else if ((movingPtr->nextNumb)->value >= createdNode->value) { // else if moving pointer is not at end of list, check to see if
																			   // if the number moving pointer is pointing too is greater than
																			   // the new number
					createdNode->nextNumb = movingPtr->nextNumb; // if it is, put new number between moving pointer and what it is currently pointing to.
					movingPtr->nextNumb = createdNode;           // by first setting new number's pointer to the same as moving pointer's pointer, and then
					inserted = true;                             // setting moving pointer's pointer to point to new number, and show new number as sorted.
				}
				else
					movingPtr = movingPtr->nextNumb; // else move moving pointer forward by one in the list.
			}
		}
		createdNode = new Numb; // create a new empty Numb place holder for next number coming in
	}
	delete createdNode; // delete the empty place holder that was not used at the end

	movingPtr = numbListHead; // set up moving pointer to read the list
	while (movingPtr->nextNumb != NULL) { // while not at the end of list 
		cout << movingPtr->value << endl;     // print the value of Numb struct
		movingPtr = movingPtr->nextNumb;      // and advance to the next Numb, and repeat
	}
	cout << movingPtr->value << endl; // print the last item on the list since it is not printed above (having a NULL pointer)

	system("pause");
	return 0;
}

