// Ch13-2-Tree.cpp.  This file demonstrates the use of
// pointers to construct a "binary tree" (p.760 Savitch).
// As with a linked list, the tree consists of "nodes"
// but in this case, each node has pointers that point
// to TWO other nodes -- a left branch, and a right branch.
// A tree is inherently a recursive structure, so the
// file also demonstrates construction of
// the tree via recursion. (Ch 14 Savitch).

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// A node in a binary tree has a stored value, as well as 
// TWO self-referential pointers -- one to each of the limbs
// that branch away from the given node.
struct tNode
{
	char content;
	tNode * leftN;
	tNode * rightN;
};

// A tree is well-suited to recursive treatment, because any
// given node is the "root" of a sub-tree emanating from that
// node.  Below is a recursive function that builds a tree
// from char values within a disk file.  The file contains
// 31 values, which is 2 to the FIFTH power, minus 1.  So, this
// tree will have a "depth" of FIVE.  Root is level 1, then there
// are 2 nodes at level 2, 4 at level 3, 8 at level 4, 16 at
// level 5, for a total of 31 nodes.  The argument "int depth"
// is used as the "stopping case" for the recursion, preventing
// the tree from building beyond the 5th level.  The parameter 
// "subroot" is a pointer used as the root of the recursively
// encompassed sub-tree.
tNode * buildTree(int depth, tNode * subRoot, ifstream& inF)
{
	tNode * localP; // Simple local variable
	if (depth) // Skips functionality once "depth" decrements to 0
	{
		localP = new tNode; // Create a new node...
		subRoot = localP;   //  ... which will be the root of a sub-tree
		localP->leftN = NULL; // Make sure the node has no sub-trees yet.
		localP->rightN = NULL;

		// Next, we read the char from the file and store it into the node.
		// Because we're storing it the FIRST time we touch this node, it's
		// considered "pre-order" traversal.  If we had instead made BOTH
		// recursive calls to build left/right and only then stored a value
		// into this node, it would have been "post-order".  "In-order"
		// is the instance in which this node is populated AFTER the left
		// sub-tree is built, but BEFORE the right sub-tree is built.
		inF >> localP->content;
		cout << localP->content << " ";

		// Here's the recursion.  Build a sub-tree using the left-node pointer,
		// and a sub-tree using the right-node pointer.  In each case, the return
		// value from the recursive call will either be NULL (if max. depth was
		// reached) or will be the pointer to the constructed sub-tree.
		depth--; // Decrement toward "stopping" case
		localP->leftN = buildTree(depth, localP->leftN, inF); 
		localP->rightN = buildTree(depth, localP->rightN, inF);
	}
	// Return the pointer to the sub-tree.
	return(subRoot);
}

int main()
{
	ifstream inF;
	inF.open("C:\\users\\ddavi\\treedecode.txt");

	int depth; // Target depth of tree
	tNode * root = nullptr; // Pointer that will point to ENTIRE tree

	inF >> depth; // First thing in file is int identifying the depth of the tree
	cout << "Depth = " << depth << endl;

	// Here's the beginning of the recursion. We pass it a nullptr to
	// begin with, together with the target "depth".  When it returns,
	// the tree is complete, and we use "root" to access the tree.
	root = buildTree(depth, root, inF);
	cout << endl;

	// For the lab assignment, you should call your recursive
	// "traverseTree()" function here.  It should do a "post-order"
	// traversal of the tree, printing out each node's content to
	// the console.  You'll know when it's working correctly...
	
	inF.close();
	return 0;
}

