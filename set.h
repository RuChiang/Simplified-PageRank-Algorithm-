// set.h ... interface to simple Set of Strings
// Written by John Shepherd, September 2015

#ifndef SET_H
#define SET_H

typedef struct SetRep *Set;

// Function signatures

typedef struct Node *Link;

typedef struct Node {
	char *val;
	Link  next;
} Node;

typedef struct SetRep {
	int   nelems;
	Link  elems;
} SetRep;

Set newSet();
void disposeSet(Set);
void insertInto(Set,char *);
void dropFrom(Set,char *);
int  isElem(Set,char *);
int  nElems(Set);
void showSet(Set );
int size(Set);
void Show(Set );

#endif
