#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include "graph.h"
#include "queue.h"
#include "readData.h"

#define BUFSIZE 1024


Queue GetCollection();
Graph GetGraph();

// GetCollection returns a queue URLs from collection.txt
Queue GetCollection(){	
	Queue a = newQueue();
	FILE *fp;
	char buff[BUFSIZE];
	fp = fopen("collection.txt", "r");
	assert(fp!=NULL); //if cannot open a file

	while(fscanf(fp, "%s", buff) != EOF){
		enterQueue(a,strdup(buff));
	}
	fclose(fp);
	return a;
}


//the GetCollection() is called to obtain the queue, so no need to parse it in as an argument
Graph GetGraph(){
	Queue a = GetCollection();
	int num  = NumOfElement(a);
	Graph g = newGraph(num);

	char * u;
	while(!emptyQueue(a)){//read all the url in the set, find their files
		u = leaveQueue(a);
		char * utxt = strdup(u);
		strcat(utxt,".txt");
		FILE *fp;
		char buff[BUFSIZE];
		fp = fopen(utxt,"r");
		assert(fp!=NULL);	//ensure the file is correctly opened

		while(fscanf(fp, "%s", buff) != EOF && strcmp(buff,"Section-1")); //read section1

		while(fscanf(fp, "%s", buff) != EOF && strcmp(buff,"#end")){ //read section1
			addEdge(g, u, buff);
		}	
	}
	return g;
}

