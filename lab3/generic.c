//Sabiq Khan 2:15 Tuesday Lab 2
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "set.h"
#define EMPTY 0
#define FILLED 1
#define DELETED 2

typedef struct set
{
    int count;
    int length;
    void* *data;
	char* flags;
	int (*compare)();
	unsigned (*hash)();
}SET;
/*
 * Function: createSet
 *
 * Description: creates the set that holds the  array
 * O(1)
 */
SET *createSet(int maxElts, int (*compare)(), unsigned (*hash)() )
{
	int i;
    SET *sp;
    sp = malloc(sizeof(SET)); //allocate for set
    assert(sp != NULL);
    //initialize the length and count
	sp->compare=(compare);
	sp->hash=(hash);
    sp->length = maxElts;
    sp->count = 0;
    sp->data = malloc(sizeof(void*)*maxElts);	//allocate for the data array
    assert(sp->data != NULL);
	sp->flags=malloc(sizeof(char)*maxElts);
	for(i=0;i<maxElts;i++){
		sp->flags[i]=EMPTY;
	}
	assert(sp->flags!=NULL);
    return(sp);
}
	


/*
 *Function: search
 *
 * Description: find the needed element in the array
 *     O(logn)
 *
 */
static int search(SET *sp, void* elt, bool* found){
	assert(sp!=NULL);
	int idx=(((*sp->hash)(elt))%(sp->length));
	int start=idx;
	while(sp->flags[idx]!=EMPTY){
		if(sp->flags[idx]==FILLED){	
			if((*sp->compare)(sp->data[idx], elt)==0){
			*found=true;
			return idx;
		}
		}
		idx = (idx + 1) % (sp->length);
		if(idx==start){
			found=false;
			break;
		}
	}
	*found=false;
	return idx;
}
/*
 * Function: destroySet
 *
 * Description: destroys the array
 *
 *     O(n)
 */
void destroySet(SET *sp)
{
    assert(sp != NULL);
    int i;
    //iterate through the array first freeing the data individually then free the data array then the whole set
    free(sp->data);
	free(sp->flags);
    free(sp);
	return;
}
/*
 *Function: findElement
 *
 *Description: uses search to return the index
 *        O(logn)
 */
void *findElement(SET *sp, void *elt)
{
    assert(sp != NULL);
    int idx;
    bool found;
    idx = search(sp, elt, &found);
    if(found==false)
        return(NULL);
    return(sp->data[idx]); //return the index, this is used to delete
}
/*
 *Function: addElement
 *
 *Description: adds the elements to the array
 *    O(n)
 */

void addElement(SET *sp, void *elt)
{
    assert(sp != NULL);
    assert(elt != NULL);
    if(sp->count == sp->length) //if the count is the same as the length the array is full
        return;
	bool found=true;
	int idx;
	idx=search(sp, elt, &found);
	if(found==true)
		return;
	int i= sp->hash(elt)%sp->length;
	while(sp->flags[i]==FILLED){
		i++;
		i=i%sp->length;
	}
	sp->data[idx] =elt;
	sp->flags[idx] = FILLED;
	sp->count++;
	return;
	}

/*
 *Function: removeElement
 *
 * Description: removes an element from the array if it is already there
 *        O(n)
 */
void removeElement(SET *sp, void *elt)
{
    assert(sp != NULL);
    assert(elt != NULL);
	bool found=false;
    int idx=search(sp, elt, &found);
  	if(found == true){
		sp->data[idx]=NULL;
		sp->flags[idx] = DELETED;
		sp->count--;
		return;
	}
	return;
	
}

/*
 *Function: numElements
 *
 *Description: Returns the number of elements in the array
 *    O(1)
 *
 */
int numElements(SET *sp)
{
	assert(sp!=NULL);
	return sp->count;
}
/*
 *Function: getElements
 *
 * Description: creates new set of arrays for given words
 *    O(n)
 *
 */
void *getElements(SET *sp)
{
    assert(sp!=NULL);
	int i;
	int j=0;
    void**words=malloc(sizeof(void*)*sp->length);
	assert(words!=NULL);
    for(i=0;i<sp->length;i++){
		if(sp->flags[i] == FILLED){
			words[j] = sp->data[i];	
			j++;
		}
	}
    return words;
}

