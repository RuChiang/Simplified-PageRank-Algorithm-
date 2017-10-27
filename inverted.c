#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include "queue.h"
#include "readData.h"
#include "BSTree.h"
#include "invertedIndex.h"

int main(int argc, char* argv[]){
	if(argc == 1){
		BSTree t = GetInvertedList();
		writeILtoFile(t);
		dropBSTree(t);
		return 1;
	}else{
		printf("There shouldn't be any argument\n");
		return 0;
	}

}