# Makefile for COMP1927 17s1 Assignment 2

CC=gcc
CFLAGS=-Wall -Werror -g -lm
LIBS= set.o graph.o readData.o queue.o  BSTree.o pagerank.o inverted.o searchTfIdf.o 


main : main.o $(LIBS)
	gcc -g -o main main.o $(LIBS) -lcurl -lm

queue.o : queue.c queue.h
set.o : set.c set.h
graph.o : graph.c graph.h
readData.o : readData.c readData.h
BSTree.o: BSTree.c BSTree.h
pagerank.o: pagerank.c pagerank.h
inverted.o: inverted.c inverted.h
searchTfIdf.o: searchTfIdf.c searchTfIdf.h

clean :
	rm -f main *.o core

PR: 
	 gcc -Wall -lm BSTree.c invertedIndex.c graph.c set.c queue.c readData.c pagerank.c -o pagerank

IL: 
	gcc -Wall -lm BSTree.c invertedIndex.c graph.c set.c queue.c readData.c inverted.c -o inverted

TfIdf: 
	gcc -Wall -lm graph.c invertedIndex.c readData.c BSTree.c queue.c searchTfIdf.c  -o searchTfIdf

SPR:
	gcc -Wall -lm BSTree.c invertedIndex.c graph.c set.c queue.c readData.c searchPagerank.c -o searchPagerank

SFR:
	gcc -Wall -lm BSTree.c invertedIndex.c graph.c set.c queue.c readData.c scaledFootrule.c -o scaledFootrule

TEST:
	gcc -Wall -lm test.c set.c -o test


All:
	make PR
	make IL
	make TfIdf
	make SPR
	make SFR