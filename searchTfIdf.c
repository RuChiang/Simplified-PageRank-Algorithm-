#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "invertedIndex.h"
#include "readData.h"
#include "searchTfIdf.h"
#include "BSTree.h"
#include "math.h"



TI tfidf(BSTree ,char *, TI);
TI TfIdfnewNode();
TI findTfIdfNode(TI, URLP);
void printfTfIdf (TI);
TI TfIdfOrder(TI );

int main(int argc, char* argv[]){
	int c = 1;
	if(argc > 1){
		TI x;
		BSTree t = GetInvertedList();
		while (c < argc) {
			if (c == 1) {
				x = tfidf(t, argv[c], NULL);
			}else{
				x = tfidf(t, argv[c], x);
			}
			c++;
		}
		printfTfIdf(x);
		dropBSTree(t);
		TI tmp;
		while(x != NULL){
			tmp = x;
			x = x->next;
			free(tmp->url);
			free(tmp);
		}
		return 1;
	} else {
		printf("too few arguments!\n");
		return 0;
	}

}



TI TfIdfnewNode(char * url){
	TI n = malloc(sizeof(TfIdfNode));
	n->url = strdup(url);
	n->tf = 0.0;
	n->idf = 0.0;
	n->totalTfIdf = 0.0;
	n->next = NULL;
	return n;
}

TI tfidf(BSTree t ,char * str, TI head){
	BSTree q = BSTreeFind(t,  str);
	if (q == NULL) {	//if search term not found
		return NULL;
	}
	URLP p = q->l;
	URLP count = q->l;
	float length = 0;
	float pageC = 0;
	Queue a = GetCollection();
	while(!emptyQueue(a)){
		leaveQueue(a);
		pageC ++;
	}
	while(count != NULL){
		length++;
		count = count->next;
	}

	while(p != NULL){
		TI i = findTfIdfNode(head, p);
		if(i == NULL) {
		//url found in treenode dosent exist in the list
			i = TfIdfnewNode(p->url);
			i->tf =  p->occur;
			i->idf = log10(pageC/length);
			i->totalTfIdf = (i->tf * i->idf);
			if(head == NULL){
				head = i;
			}else{
				i->next = head;
				head = i;
			}
		} else {
			i->tf = p->occur;
			i->idf = log10(pageC/length);
			i->totalTfIdf = i->totalTfIdf + (i->tf * i->idf);
		}
		//
		p = p->next;
	}
	TI ret = TfIdfOrder(head);
	return ret;
}

TI findTfIdfNode(TI head, URLP p){
	if(head == NULL){
		return NULL;	//empty list
	}
	while(head != NULL){
		if(strcmp(head->url, p->url)==0){
			return head;	//found in list
		}else{
			head = head->next;
		}
	}
	return NULL;	//not found
}


TI TfIdfOrder(TI head){
	TI ordered = NULL;
	TI cur = head;
	TI tmp = NULL;
	while(cur!= NULL){
		if(ordered == NULL){	//insert into empty list
			ordered = cur;
			cur = cur->next;
			ordered->next = NULL;
		}else if(cur->totalTfIdf > ordered->totalTfIdf){	//head insertion
			tmp = cur;
			cur = cur->next;
			tmp->next = ordered;
			ordered = tmp;
		}else{
			TI itr = ordered;
			while(itr != NULL){
				if (cur->totalTfIdf <= itr->totalTfIdf && itr->next == NULL){	//tail insertion
					tmp = cur;
					cur = cur->next;
					itr->next = tmp;
					tmp->next = NULL;
					break;
				}else if (cur->totalTfIdf <= itr->totalTfIdf && cur->totalTfIdf > itr->next->totalTfIdf){	//normal insertion
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


void printfTfIdf (TI head) {
	int n = 0;
	//printf("enter\n");
	while(head != NULL && n < 10) {
		printf("%s %.6f\n", head->url, head->totalTfIdf);
		head = head->next;
		n++;
	}
}
