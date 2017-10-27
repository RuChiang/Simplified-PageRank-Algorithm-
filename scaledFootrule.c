#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "set.h"
#include "math.h"

typedef struct cNode * C;
typedef struct sNode * N;
typedef struct  fileInfo * file;


typedef struct sNode
{
	char * url;
	N next;
}sNode;

typedef struct cNode
{
	char * url;
	float curWcp;
	int prePos;	//keep the total MinWCP's position
	C next;
}cNode;


typedef struct  fileInfo
{
	char * fileN;
	int nE;
}fileInfo;


float preMin = 0; //for keeping track of the Min total WCP for a given URL
float curMin = 0;
//int firstWCP = 0;
int firstMin = 0; //flag for seeing if it's the firstMin value


N extract( char * , file );
N newsNode(char * );
C newcNode(char * );
void printCNodeList(C );
void swap(int* , int * );
void permute(int *, int , int );
void permuteAndUpdate(int *, int , int , C , N * , file , int );

void printArray(N * array, int argc, file infoArray);

int main( int argc, char ** argv){
	
	N array[argc -1];
	fileInfo infoArray[argc -1];

	int i = 0;

	for(i=0; i<argc;i++){
		infoArray[i].fileN = NULL;
		infoArray[i].nE = 0;
	}
	
	for(i = 1; i<argc ; i++){ 			//get the info from the files
		array[i-1] = extract( argv[i], infoArray+i-1);
	}

	Set s = newSet();	//creating a list containing all nodes
	N j;
	for( i =0; i<argc-1; i++){
		j = array[i];
		while(j!=NULL){
			insertInto(s,strdup(j->url));
			j = j->next;
		}
	}

	Link a = s->elems;

	C valHead = NULL;
	C tmp = NULL;
	while(a!=NULL){
		tmp = newcNode(a->val);
		if( valHead == NULL){
			valHead = tmp;
		}else{
			C cur = valHead;
			while(cur -> next != NULL) {
				cur = cur ->next;
			}
			cur->next = tmp;
		}
		a = a->next;
	}

	int k;
	
	int pos[size(s)];
	for(k = 1; k <= size(s); k++){
		pos[k-1] = k;
	}
	int h =0;
	for( h = 0; h<argc-1; h++)

	permuteAndUpdate(pos, 0, size(s)-1, valHead, array, infoArray, argc-1);
	
	printf("%f\n", preMin );
	for(k = 0 ;k <size(s); k++){
		C node = valHead;
		while(node != NULL){
			if (node ->prePos == k+1){
				printf("%s\n", node->url);
				break;
			}
			node = node ->next;
		}
	}
	return 0;

}

//int v = 0;	//debugging variable 
//int u =0;	//debugging variable 


//in each permutation, calculate the minimun WCP value, and do comparison with the previous minimum total WCP. Update the perMin accordingly
void permuteAndUpdate(int *a, int l, int r, C head, N * array, file info, int aSize)
{


   	int i;
   	if (l == r){

     	C itr = head;
     	int arrC;	//for iterating through the array of pointers which points to the pages contained by the rank.txt files
     	int itrC = 0;	//for iterating through the set, which contains the unique urls in order
     	curMin = 0.0;
     	while (itr != NULL){	//start with a url
     		itr->curWcp = 0.0;
     		for(arrC = 0; arrC < aSize ; arrC++){ //go through array to find all entry with the designated url
     			N node = array[arrC];
     			float arrayPos = 0.0;
     			while(node != NULL){
     				arrayPos ++;
     				if(strcmp(itr->url, node->url)==0){	//found the url in array, compute

     					itr->curWcp = itr->curWcp + fabs((arrayPos)/(float)info[arrC].nE - (float)a[itrC]/((float)l+(float)1));	
     					
     					break;
     				}
     				node = node ->next;
     			}
     		}
     		itrC++; 	
     		curMin = curMin + itr->curWcp;
     		itr = itr->next;
     	}

     	if(firstMin == 0){	//first preMin value assignment
     		preMin = curMin;
     		firstMin = 1;
     	}
     	if(curMin <= preMin){	//total WCP is smaller than the PreMin, update the values
     		preMin = curMin;
 	    	itr = head;
 	    	int m = 0;
    	 	while(itr != NULL){	//curMin is smaller than preMin, change all the cur to pre
     			itr->prePos = a[m];//update the the positions
     			m++;
     			itr = itr->next;
     		}
     	}

   	}else{
       	for (i = l; i <= r; i++)
       	{
          	swap((a+l), (a+i));
          	permuteAndUpdate(a, l+1, r, head, array, info, aSize);
          	swap((a+l), (a+i)); //backtrack
       	}
   	}

}
 


void printCNodeList(C head){
	C cur = head;
	while(cur != NULL){
		printf("url:%s cur: %f\n", cur->url, cur->curWcp);
		cur = cur ->next;
	}
}

void printArray(N * array, int argc, file infoArray){
	int i;
	for(i = 0; i<argc-1 ; i++){
		//printf("---%s---\n", argv[i]);
		printf("No. of element in %s %d\n",  infoArray[i].fileN, infoArray[i].nE );
		N cur =array[i];
	 	while(cur!=NULL){
	 		printf("%s\n",cur->url);
	 		cur = cur->next;
	 	}

	}
}

N newsNode(char * urlp){
	N n = malloc(sizeof(sNode));
	n->url = strdup(urlp);
	n->next = NULL;
	return n;
}



C newcNode(char * urlp){
	C n = malloc(sizeof(cNode));
	n->url = strdup(urlp);
	n->curWcp = 0.0;
	n->prePos = 0;
	n->next = NULL;
	return n;
}

N extract( char * fileName, file infoNode){

	FILE *f;
	char buff[100];
	f = fopen(fileName,"r");
	assert(f!=NULL);
	N head = NULL;
	N  cur = NULL;
	int count = 0;
	while(fscanf(f,"%s",buff)!= EOF){
		//printf("scanf\n");
		N node = newsNode(strdup(buff));
		assert(node!=NULL);
		if(head==NULL){
			head = node;		
		}else{
			cur = head;
			while(cur->next != NULL){
				cur = cur->next;
			}
			cur->next = node;
		}
		count ++;
	}

	//printf("here\n");
	infoNode->fileN = strdup(fileName);
	infoNode->nE = count;
	//printf("haskl\n");

	return head;
}




/* Function to swap values at two pointers */
void swap(int *x, int *y)
{
    char temp;
    temp = *x;
    *x = *y;
    *y = temp;
}
 
/* Function to print permutations of string
   This function takes three parameters:
   1. String
   2. Starting index of the string
   3. Ending index of the string. */
void permute(int *a, int l, int r)
{
   	int i;
   	if (l == r){
   	printf("permute print -----------\n");
     	for( i = 0; i<r+1; i++){
     		printf("%d\n", a[i] );
     	}
   	}else{
       	for (i = l; i <= r; i++)
       	{
          	swap((a+l), (a+i));
          	permute(a, l+1, r);
        	swap((a+l), (a+i)); //backtrack
       	}
   	}
}
