#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>


typedef struct SPRNode * SPR;

typedef struct SPRNode
{
	char * url;
	float rank;
	int count;
	SPR next;
}SPRNode;

SPR getList();
SPR NewSPRNode(char * , float  );
SPR updateWithCount(SPR , int , char ** );
void print(SPR , int );
void dropList(SPR );

int main(int argc, char* argv[]){
	SPR l = getList();
	l = updateWithCount(l,argc,argv);
	print(l,argc);
	dropList(l);

	return 0;
}

//free the memory
void dropList(SPR l){
	SPR tmp;
	while(l != NULL){
		tmp = l;
		l =l -> next;
		free(tmp->url);
		free(tmp);
	}
}



SPR updateWithCount(SPR l, int argc, char ** argv){
	char line[200];
	FILE * f;

	int wc;
	for(wc = 1; wc<argc; wc++){
		f = fopen("invertedIndex.txt","r");
		char * v  = fgets(line,200,f);
		if(v == NULL){
			return NULL;
		}
		char * j = calloc(100,sizeof(char));
		
		j=strcpy(j,v);
		char * t = strtok(j," ");	//the fist word in the line, used for comparison
		while(v!=NULL && strcmp(t,argv[wc])!=0){
			v  = fgets(line,200,f);
			if (v == NULL){	//reach the end of the file, word not found
				free(j);
				return NULL;
			}
			j=strcpy(j,v);
			t = strtok(j," ");
		}
		if (v == NULL){	//reach the end of the file, word not found
			free(j);
			return NULL;
		}

		char * pch;
		pch = strtok(line, ", \n");	//word
		pch = strtok(NULL, ", \n");
		while(pch != NULL  ){
			SPR head = l;
			while(head != NULL){
				if( strcmp(head->url, pch) == 0  ){
					head->count++;
					break;
				}else{
					head = head -> next;
				}
			}
			pch = strtok(NULL, ", \n");
		}
		free(j);	
	}
	
	return l;
	
}

SPR NewSPRNode(char * a, float b ){
	SPR n = malloc(sizeof(SPRNode));
	n-> url = strdup(a);
	n->rank = b;
	n->count = 0;
	n->next = NULL;
	return n;
}



SPR getList(){
	char line[200];
	FILE * f;
	f = fopen("pagerankList.txt","r");
	char * c[3];
	int n;
	SPR head = NULL;
	assert(f!=NULL);
	while(fgets(line,200,f)){
		char * pch;
		//printf("splitting %s", line);
		pch = strtok(line, ", \n");
		n = 0;
		while(pch != NULL && n<3){
			//printf("enter\n");
			//printf("value is :%s\n", pch);
			c[n] = strdup(pch);
			pch = strtok(NULL, ", \n");
			//printf("c[n] is :%s\n",c[n] );
			n++;
		}
		SPR node = NewSPRNode(c[0],atof(c[2]));
		SPR cur = head;
		if(head == NULL){
			head = node;
		}else{
			while(cur -> next != NULL){
				cur = cur->next;
			}
			cur->next = node;
		}
	}

	fclose(f);
	return head;
}

void print(SPR head, int argc){
	int n = 0;
	while(head != NULL && n<10){
		if( head->count == (argc -1)){
			printf("%s\n", head->url);
			n++;
		}
		head = head->next;

	}
}