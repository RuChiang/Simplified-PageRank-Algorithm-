#ifndef PAGERANK_H
#define PAGERANK_H

#include <stdlib.h>
#include <stdio.h>
#include "graph.h"
typedef struct connectURL * CURL;
typedef struct PRnode * Node;



Node calculatePageRank(Graph, float , float, float);
void printStructure(Node );
Node PROrder(Node);
void writePRtoFile(Node );
void dropPRnodeList(Node );



#endif