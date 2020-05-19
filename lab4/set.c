//Sabiq Khan SET Lab 4 Tuesday 2:15
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "set.h"
#include "list.h"

struct set{
	int count;
	int length;
	LIST** lists;
	int (*compare)();
	unsigned (*hash)();
};

//CREATESET RUNTIME O(n)
SET *createSet(int maxElts, int (*compare)(), unsigned (*hash)()){
	SET* sp;
	sp=malloc(sizeof(SET));
	assert(sp!=NULL);
	sp->count=0;
	sp->length = maxElts;
	sp->lists = malloc(sizeof(void *)*sp->length);
	sp->compare = compare;
	sp->hash = hash;
	int i;
	for(i = 0; i < sp->length; i++){
		sp->lists[i] = createList(compare);
	}
	assert(sp->lists != NULL);
	return sp;
}//creating a set

//DESTROYSET RUNTIME O(n)
void destroySet(SET* sp){
	free(sp->lists);
	free(sp);
}//destroying the set

//NUMELEMENTS RUNTIME O(1)
int numElements(SET* sp){
	assert(sp!=NULL);
	return (sp->count);
}

//ADDELEMENTS RUNTIME O(n)
void addElement(SET* sp, void* elt){
	assert(sp != NULL && elt != NULL);
	int idx = (*sp->hash)(elt)%sp->length;
	if(findItem(sp->lists[idx],elt) == NULL){
		addFirst(sp->lists[idx], elt);
		sp->count++;
	}
}//adding a node using the hash function and the addfirst function from list.c

//REMOVEELEMENT RUNTIME O(n)
void removeElement(SET* sp, void* elt){
	assert(sp != NULL && elt != NULL);
	int idx = (*sp->hash)(elt)%sp->length;
	if(findItem(sp->lists[idx], elt) != NULL){
		removeItem(sp->lists[idx], elt);
		sp->count--;
	}
}//removing a node using the hash function and the removeitem function from list.c

//FINDELEMENT RUNTIME O(n)
void *findElement(SET *sp, void *elt){
	assert(sp != NULL && elt != NULL);
	int idx = (*sp->hash)(elt)%sp->length;
	return(findItem(sp->lists[idx], elt));
}//finds an item in the set and uses finditem frmo list.c to do so. Returns Null if not found

//GETELEMENTS RUNTIME O(n^2)
void *getElements(SET *sp){
	assert(sp != NULL);
	void **arr;
	void **copy;
	int count = 0;
	int i, j;
	arr = malloc(sizeof(void*)*sp->count);
	for(i = 0; i < sp->length; i++){
		copy = getItems(sp->lists[i]);
		for(j = 0; j< numItems(sp->lists[i]); j++){
			arr[count] = copy[j];
			count++;
		}
	}
	return arr;
}//returns all the elements of the set
