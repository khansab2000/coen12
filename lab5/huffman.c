//Sabiq Khan Tuesday 2:15 Project 5
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include "pack.h"
#include "pqueue.h"

typedef struct node NODE;
static  NODE *mknode(int data, NODE* left, NODE*right);



/*
 * Function: hopNumber
 * Summary: This function takes in a leaf of a tree and traverses up the tree until it reaches the root.
 * While doing so, it counts the number of hops it takes to get there and returns how far away the specified
 * leaf is from the root.
 * Runtime: O(n)
 */

int hopNumber(struct node *leaf) {
	int hops = 0;
	NODE *p=leaf;
	while (p->parent!=NULL) {
		p = p->parent;
		hops++;
	}
	return hops;
}
/*
 * Function: compare
 * Summary: Like integer compare, but this time compares the data in two nodes.
 * Runtime: O(1)
 */

int compare(struct node *first, struct node *second) {
	return (first->count < second->count) ? -1 : (first->count >= second->count);
}
//runtime O(nlogn)
int main(int argc, char *argv[]){
	FILE *fp = fopen(argv[1],"r");	// Initialize pointer to file and open it to be read	
	if (fp == NULL) {
		return 0;
	}
	int i;
	int occurences[257];
	for(i=0;i<257;i++){
		occurences[i]=0;
	}
	do{
		char c;
		c=fgetc(fp);
		if( feof(fp) ){
			break;
		}
		occurences[(int)c]++;
	}while(1);
	PQ *pqueue = createQueue(compare);
	struct node* leaves[257] = {0};//creates leaves array
	for (int i = 0; i < 257; i++) {
		leaves[i]=NULL;
	}
	for (int i = 0; i < 256; i++){
		if (occurences[i]>0){
			NODE *thenode = mknode(occurences[i], NULL, NULL);
			addEntry(pqueue,thenode);
			leaves[i]= thenode;
		}
	}
	// creating a tree with a zero count for the end of file marker
	NODE *zeroCountNode = mknode(0, NULL, NULL);
	addEntry(pqueue,zeroCountNode);
	leaves[256] = zeroCountNode;

	while (numEntries(pqueue)>1) {
		NODE *first = removeEntry(pqueue); // the first of the lowest priority trees
		NODE *second = removeEntry(pqueue); // the second of the lowest priority trees
		NODE *third = mknode((first->count) + (second->count), first, second); // the new node created that will have its count as the count of its two children (the ones we just removed)
		addEntry(pqueue, third); // we add that new tree back into the priority queue
	}
	for (int i = 0; i < 257; i++){
		if (leaves[i]!=NULL) {
			int numberOfHops;
			numberOfHops = hopNumber(leaves[i]);
			if (isprint(i)){//checks if the character is printable
				printf("%c: %d x %d bits = %d\n", i, occurences[i], numberOfHops, occurences[i]*numberOfHops);
			}
			else{
				printf("%03o: %d x %d bits = %d\n", i, occurences[i], numberOfHops, occurences[i]*numberOfHops);
			}
		}
	}
	pack(argv[1],argv[2],leaves);
	destroyQueue(pqueue);
}

//runtime O(1)
static NODE *mknode(int data, NODE* left, NODE*right){
	NODE* np=malloc(sizeof(NODE));
	assert(np!=NULL);
	np->count=data;
	np->parent=NULL;
	if(right!=NULL)right->parent=np;
	if(left!=NULL)left->parent=np;
	return np;
}
