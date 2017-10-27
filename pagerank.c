#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "graph.h" 
#include "queue.h"
#include "pagerank.h"
#include "readData.h" 



typedef struct connectURL
{
	char * name;
	CURL  next;
}connectURL;

typedef struct PRnode
{
	char * name;
	int outDegree;
	float currv;
	float prev;
	CURL urls;
	Node  next;
}PRnode;


CURL connectedBy( Graph, int );
void printStructure(Node);
Node calculatePageRank(Graph ,float , float , float );
float sumOfConnectedBy(Graph , Node , Node );
void writePRtoFile(Node );
Node PROrder(Node);
void dropPRnodeList(Node );



int main(int argc, char* argv[]){
	if(argc == 4){
		float d = atof(argv[1]);
		float diffPR = atof(argv[2]);
		float maxit = atof(argv[3]);
		Graph g = GetGraph();
		Node n = calculatePageRank(g,d,diffPR, maxit);	
		writePRtoFile(n);
		disposeGraph(g);
		dropPRnodeList(n);
		return 1;
	}else{
		printf("Wrong number of inputs\n");
		return 0;
	}

}

void dropPRnodeList(Node n){
	Node tmp = NULL;
	CURL temp = NULL;
	CURL cur = NULL;
	while(n!=NULL){
		tmp = n;
		cur = n->urls;
		n = n->next;
		while(cur != NULL){
			temp = cur;
			cur = cur->next;
			free(temp->name);
			free(temp);
		}
		free(tmp->name);
		free(tmp);
	}

}


void writePRtoFile(Node n){
	FILE *a = fopen("pagerankList.txt","w");
	fclose(a);
	FILE *f = fopen("pagerankList.txt","a");
	if (f == NULL){
    	printf("Error opening file!\n");
    	exit(1);
    }
	while(n!=NULL){
		fprintf(f,"%s, %d, %.7f\n", n->name,n->outDegree,n->currv);
		n = n->next;
	}    
	fclose(f);
}


void printStructure(Node n){
	assert(n!= NULL);
	while(n!=NULL){
		printf("%s, %d, %.7f\n", n->name,n->outDegree,n->currv);
		n = n->next;

	}
}

Node calculatePageRank(Graph g,float d, float diffPR, float maxit){
	Node head;
	int i;
	int firstInsertion = 0;

	for (i = 0 ; i < nVertices(g); i++){

		Node n = malloc(sizeof(PRnode));
		n->name = strdup(getVname(g,i));
		n->prev = n->currv = 1.0 / nVertices(g);
		n->urls = connectedBy(g,i);
		n->outDegree = outDegree(g , n->name );

		if(firstInsertion == 0){
			firstInsertion = 1;
			n->next = NULL;
			head = n;
		}else{
			n->next = head;
			head = n;
		}
	} 
	//now we have a list in a reversed order


	int iteration = 0;
	float diff = diffPR;

	while(iteration < maxit && diff >= diffPR){
		iteration++;

		Node calNodePR = head;
		while(calNodePR!=NULL){	////For each url pi in the collection
			calNodePR->currv = (1-d)/nVertices(g) + (d * sumOfConnectedBy(g,calNodePR,head));
			calNodePR = calNodePR->next;
		}

		Node calNodeDiff = head;
		while(calNodeDiff!=NULL){	//For each url pi in the collection
			diff = diff + abs(calNodeDiff->currv - calNodeDiff->prev);
			calNodeDiff = calNodeDiff -> next;
		}

		Node advance = head;
		while(advance != NULL){
			advance->prev = advance->currv;
			advance = advance ->next;
		}
	}

	Node ret;
	ret = PROrder(head);
	return ret;
}



Node PROrder(Node head){
	Node ordered = NULL;
	Node cur = head;
	Node tmp = NULL;
	while(cur!= NULL){
		if(ordered == NULL){	//insert into empty list
			ordered = cur;
			cur = cur->next;
			ordered->next = NULL;
		}else if(cur->currv > ordered->currv){	//head insertion
			tmp = cur;
			cur = cur->next;
			tmp->next = ordered;
			ordered = tmp;
		}else{
			Node itr = ordered;
			while(itr != NULL){
				if (cur->currv <= itr->currv && itr->next == NULL){	//tail insertion
					tmp = cur;
					cur = cur->next;
					itr->next = tmp;
					tmp->next = NULL;
					break;
				}else if (cur->currv <= itr->currv && cur->currv > itr->next->currv){	//normal insertion
					tmp = cur;
					cur = cur->next;
					tmp->next = itr->next;
					itr->next = tmp;
					break;
				}
				itr= itr->next;
			}
		}
	}
	return ordered;
}


float sumOfConnectedBy(Graph g, Node n, Node head){
	float sum =0.0;
	CURL c = n->urls;
	while(c != NULL){
		Node itr = head;
		while(itr != NULL){
			if(strcmp(c->name,itr->name)==0){
				sum = sum + itr->prev/itr->outDegree;
				break;
			}
			itr = itr->next;
		}
		c = c->next;
	}
	return sum;
}


CURL connectedBy( Graph g, int i){
	CURL head;
	int k;
	int firstInsertion = 0;
	for ( k = 0; k < nVertices(g) ; k++){
		if(i != k && isConnected(g,getVname(g,k),getVname(g,i))){
			CURL url = malloc(sizeof(connectURL));
			url->name = strdup(getVname(g,k));
			if(firstInsertion == 0){
				firstInsertion = 1;
				url->next = NULL;
				head = url;
			}else{
				url->next = head;
				head = url;
			}
		}
	}
	return head;
}
