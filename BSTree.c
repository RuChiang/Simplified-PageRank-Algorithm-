// BSTree.c ... implementation of binary search tree ADT

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "BSTree.h"

// make a new node containing a value
static
BSTree newBSTNode(char * s)
{
	BSTree new = malloc(sizeof(BSTNode));
	assert(new != NULL);
	//new->word = malloc(sizeof(char *));
	new->word = strdup(s);
	new->l = NULL;
	new->PageNo = 0;
	new->left = new->right = NULL;
	return new;
}

// create a new empty BSTree
BSTree newBSTree()
{
	return NULL;
}

// free memory associated with BSTree

void dropBSTree(BSTree t)
{
	if (t == NULL) return;
	dropBSTree(t->left);
	dropBSTree(t->right);
	URLP p = t->l;
	URLP tmp = NULL;
	while(p!=NULL){
		tmp = p;
		p = p->next;
		free(tmp->url);
		free(tmp);
	}
	free(t->word);
	free(t);
}


// display BSTree root node
void showBSTreeNode(BSTree t)
{
	if (t == NULL) return;
	printf("----------------word: %s PageNo: %d-------------\n", t->word, t->PageNo);
	URLP a = t->l;
	while(a != NULL){
		printf("url: %s occurs: %d\n",a->url,a->occur);
		a = a->next;
	}
}


void outputBSTreeNode(BSTree t, FILE *f)
{
	
	if (t == NULL) return;
	fprintf(f,"%s ", t->word);
	URLP a = t->l;
	while(a != NULL){
		fprintf(f,"%s ", a->url);
		a = a->next;
	}
	fprintf(f,"\n");
	
}


void outputBSTreeInfix(BSTree t, FILE *f)
{
	if (t == NULL){return;}
	outputBSTreeInfix(t->left,f);
	outputBSTreeNode(t,f);
	outputBSTreeInfix(t->right,f);

}

// print values in infix order
void BSTreeInfix(BSTree t)
{
	if (t == NULL){return;}
	BSTreeInfix(t->left);
	showBSTreeNode(t);
	BSTreeInfix(t->right);

}

BSTree BSTreeInsert(BSTree t, char * v)
{
	if (t == NULL){
		//printf("fuck\n");
		return newBSTNode(strdup(v)); ;
	}
	else if (strcmp(v, t->word) < 0){
		//printf("left\n");
		t->left = BSTreeInsert(t->left, v);
	}
	else if (strcmp(v, t->word) > 0){
		//printf("right\n");
		t->right = BSTreeInsert(t->right, v);
	}
	else{
		//printf("duplicate\n");
	}
	return t;
}

// check whether a value is in a BSTree
BSTree BSTreeFind(BSTree t, char * v)
{
	if (t == NULL)
		return NULL;
	else if (strcmp(v, t->word) < 0)
		return BSTreeFind(t->left, v);
	else if (strcmp(v, t->word) > 0)
		return BSTreeFind(t->right, v);
	else // (v == t->value)
		return t;
}

