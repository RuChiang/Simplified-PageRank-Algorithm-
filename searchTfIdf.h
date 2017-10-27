#ifndef SEARCHTFIDF_H
#define SEARCHTFIDF_H

#include <stdlib.h>
#include <stdio.h>
#include "invertedIndex.h"
#include "readData.h"
#include "searchTfIdf.h"
#include "BSTree.h"
#include "graph.h"
#include "math.h"

typedef struct TfIdfNode * TI;


typedef struct  TfIdfNode
{
	char * url;
	float tf;
	float idf;
	float totalTfIdf;
	TI next;
} TfIdfNode;

TI tfidf(BSTree ,char *, TI);
TI TfIdfnewNode();
TI findTfIdfNode(TI, URLP);
void printfTfIdf (TI);



#endif