// Ch13-1-Linked List.  This sample shows some of the issues
// related to building and traversing a "linked list".  It
// implements a simple service-queue making use of "nodes"
// that contain a string as well as a pointer to another node.
// Think of a FIFO waiting list at a restaurant.  People get
// added to the back of the list, served at the front of the 
// list, etc.  The ORDER IN WHICH ACTIONS ARE TAKEN IS CRUCIAL
// when working with linked lists, so that you don't wind
// up with "lost" nodes (ones where you no longer have a valid
// pointer to access them).

#include "stdafx.h"
#include <iostream>
#include <string>
using namespace std;

// Basic structure is capable of holding a string, as well as
// a pointer to another instance of the same kind of structure.
struct Party {
	string partyName;
	struct Party * nextParty; // So-called "self-referential" structure
};

int main()
{
	// For any linked list, a pointer to the HEAD of the list must
	// exist.  Each node in the list will then point at the NEXT
	// one in the list, with the node at the END of the list
	// pointing at nothing.  NULL is a reserved word used to
	// mean that a pointer or node is pointing nowhere.  We
	// start with an empty list...
	struct Party * waitListHead = NULL;
	
	// To traverse the nodes in a list, you need a pointer
	// that can be pointed at any node you choose.  The one
	// pointing at the head of the list must ALWAYS point
	// there, or you will "lose" the whole list!
	struct Party * movingPtr;

	// Nodes are dynamically created by "new" commands that
	// allocate memory from the freestore.  We'll use this
	// variable each time we want to create a new node.
	struct Party * createdNode;

	char choice;  // A char that holds the user's menu choice
	int partyCount = 0; // Running tally of how many nodes are in list

	do
	{
		cout << "********************************** Waiting List ****************************************\n";
		cout << "Select: (W)aiting , (A)dd party, (S)erve party, add (V)ip, (Q)uitter, (C)ut line, e(X)it\n";
		cin >> choice;

		switch (choice)
		{
		case 'W': case 'w':  // Display the list, starting at the head
			movingPtr = waitListHead;  // Start at head of list
			while (movingPtr != NULL) // Any MORE list to go?
			{
				cout << movingPtr->partyName << endl; // Show party name in this node
				movingPtr = movingPtr->nextParty; // Traverse to next node in the list
				//movingPtr = (*movingPtr).nextParty; // Clunkier syntax that also works...
			}
			break;

		case 'A': case 'a': // (A)dd a new party to the back of the list
			partyCount++;
			createdNode = new Party;  // Dynamically create new node
			cout << "Party name? ";
			cin >> createdNode->partyName;  // Fetch name directly into struct

			// There are TWO possibilities...  Is the list EMPTY?
				if (waitListHead == NULL) { // No list exists
					waitListHead = createdNode;  // Our new node BECOMES head of list!
					waitListHead->nextParty = NULL;  // Show that no other nodes are in list...
				}

			// NOT an empty list.  Put new node at END of list.
				else {
					movingPtr = waitListHead;  // We'll traverse, to FIND end of list
					while (movingPtr->nextParty != NULL)
						movingPtr = movingPtr->nextParty;

					// At this point, movingPtr is pointing at the last node in the list.
					movingPtr->nextParty = createdNode;  // New node tacked on end of list
					createdNode->nextParty = NULL;		// Show that no nodes are beyond...
				}
			break;
	
		case 'C': case 'c': //  Party (C)uts line.  For this demo, I will only proceed
							// if there are at least 2 nodes in the list.  The new node will be put
							// between node #1 and #2.
			if (partyCount >= 2) {
				createdNode = new Party;
				createdNode->partyName = "Cutter";
				partyCount++;

				// At this point, have pointer to new node (createdNode) and pointer to
				// the node BEYOND WHICH it will be inserted (waitListHead, which is #1)
				// Got to FIRST make use of #1 to make the PTR in createdNode point at what will become #3
				createdNode->nextParty = waitListHead->nextParty;

				// Only then can you change the PTR within #1 to point to createdNode (the new #2)
				waitListHead->nextParty = createdNode;
			}
			else cout << "Need 2 or more in line before I can cut someone into the #2 spot\n";
			break;

		case 'Q': case 'q': //  Party (Q)uits waiting, out of boredom.  For this demo
			// example, I will ONLY delete the 2nd node out of 3 or more in line, for sake
			// of simplicity.  Wanting to demo the removal of a node in middle of list.
			if (partyCount >= 3) {
				movingPtr = waitListHead->nextParty;

				// At this point, I have a pointer to the node I will remove (movingPtr)
				// AND I have a pointer to the node AHEAD of it in the list (waitListHead).
				// Need BOTH those pointers in order to succeed.
				waitListHead->nextParty = movingPtr->nextParty; // Make #1 point to #3
				//waitListHead->nextParty = (waitListHead->nextParty)->nextParty;  // This ALSO makes #1 point to #3 ;-)
				delete movingPtr; // Delete #2
				partyCount--;
			}
			else cout << "Need 3 or more in line before I will delete #2\n";
			break;

		case 'V': case 'v': //  Add a (V)ip party to the FRONT of the list.
			partyCount++;
			createdNode = new Party;  // Dynamically create new node
			cout << "VIP's name? ";
			cin >> createdNode->partyName; // Fetch name directly into struct

			// There are TWO possibilities...  Is the list EMPTY?
			if (waitListHead == NULL) { // No list exists
				waitListHead = createdNode;  // Our new node BECOMES head of list!
				waitListHead->nextParty = NULL;  // Show that no other nodes are in list...
			}

			// NOT an empty list.  Put new node at FRONT of list. Order of actions is crucial!
			else {
				createdNode->nextParty = waitListHead; // Must do this while waitListHead references existing list!
				waitListHead = createdNode;  // THEN can revise waitListHead to reference the new node
			}
			break;

		case 'S': case 's': //  Here, (S)erve a party, which removes the party at the front of the list

			// TWO possibilities.  Is the list empty?
			if (waitListHead == NULL)
				cout << "No one in line!\n";

			// One or more nodes in list.
			else {
				cout << "Served " << waitListHead->partyName << endl;
				movingPtr = waitListHead; // Establish PTR to first node for use by "delete" in a moment...
				waitListHead = waitListHead->nextParty; // Move head PTR to next in list (which could be NULL)
				delete movingPtr; // Return obsolete node to freestore
				partyCount--;
			}
			break;

		case 'X': //  Here, (X)exit the program
		default:
			return (0);
		}
	} while (true);
}

