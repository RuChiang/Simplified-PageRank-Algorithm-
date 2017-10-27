// BSTree.h ... interface to binary search tree ADT

#ifndef BSTREE_H
#define BSTREE_H

typedef struct BSTNode *BSTree;
typedef struct URL * URLP;

typedef struct URL
{
	char * url;
	int occur;
	URLP next;
}URL;


typedef struct BSTNode {
	char * word;
	URLP l;
	int PageNo;
	BSTree  left,right;
} BSTNode;

// create an empty BSTree
BSTree newBSTree();
// recursively calls outoutputBSTreeNode
void outputBSTreeInfix(BSTree , FILE *);
//writes output to file
void outputBSTreeNode(BSTree , FILE *);
// free memory associated with BSTree
void dropBSTree(BSTree);
// print values in infix order
void BSTreeInfix(BSTree);
//print output to console
void showBSTreeNode(BSTree);
// insert a new value into a BSTree
BSTree BSTreeInsert(BSTree, char*);
// check whether a value is in a BSTree
BSTree BSTreeFind(BSTree, char *);

#endif
