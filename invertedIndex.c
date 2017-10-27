#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include "queue.h"
#include "readData.h"
#include "BSTree.h"
#include "invertedIndex.h"

#define BUFSIZE 1024
BSTree GetInvertedList();
void InsertURLP(BSTree , char * );
char * normalise(char * );
void writeILtoFile(BSTree );



void writeILtoFile(BSTree n){
	FILE *a = fopen("invertedIndex.txt","w");
	fclose(a);
	FILE *f = fopen("invertedIndex.txt","a");
	if (f == NULL){
    	printf("Error opening file!\n");
    	exit(1);
    }
    outputBSTreeInfix(n,f);
   
	fclose(f);
}


BSTree GetInvertedList(){

	Queue a = GetCollection();
	BSTree t = newBSTree();
	char * u;
	char * lower;
	while(!emptyQueue(a)){
		u = leaveQueue(a);
		char * utxt = strdup(u);
		strcat(utxt,".txt");
		FILE *fp;
		char buff[BUFSIZE];
		fp = fopen(utxt,"r");
		assert(fp!=NULL);
		while(fscanf(fp, "%s", buff) != EOF && strcmp(buff,"Section-2")); //skip everything unitl reaches section2
		while(fscanf(fp, "%s", buff) != EOF && strcmp(buff,"#end")){ //read section2
			int i = 0;
			while(buff[i]!='\0'){
				buff[i] = tolower(buff[i]);
				i++;
			}
			lower = strdup(buff);
			lower = normalise(lower);
			t = BSTreeInsert(t, lower);
			BSTree n = BSTreeFind(t,lower);
			InsertURLP(n,u);
		}
	}
	return t;
}


//insert urls into Tree node that contains a particular word
void InsertURLP(BSTree t, char * urlpassed){
	URLP p = t->l;
	int found = 0; //indicate if the url is found in the list
	while(p != NULL){
		if(strcmp(p->url,urlpassed)==0){
			p->occur ++;
			found = 1;
			break;
		}
		p = p->next;
	}
	//finish finding process
	if(found == 0){
		URLP j = malloc(1 * sizeof(URL));
		j->next = t->l;
		t->l = j;
		j->occur = 1;
		j->url = strdup(urlpassed);
		t->PageNo ++;
	}
}

char * normalise(char * a){
	int i = 0;
	int j = 0;
	char temp[50];
	while(a[i] != '\0'){
		if(isalnum(a[i]) != 0 ){ // is alphabet or number, put it into another string
			temp[j] = a[i];
			j++;
		}
		i++;
	}
	temp[j]='\0';
	strcpy(a,temp);
	return a;
}