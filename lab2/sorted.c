//Sabiq Khan 2:15 Tuesday Lab 2
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "set.h"

typedef struct set
{
    int count;
    int length;
    char* *data;
}SET;
/*
 * Function: createSet
 *
 * Description: creates the set that holds the  array
 * O(1)
 */
SET *createSet(int maxElts)
{
    SET *sp;
    sp = malloc(sizeof(SET)); //allocate for set
    assert(sp != NULL);
    //initialize the length and count
    sp->length = maxElts;
    sp->count = 0;
    sp->data = malloc(sizeof(char*)*maxElts); //allocate for the data array
    assert(sp->data != NULL);
    return(sp);
}
/*
 *Function: search
 *
 * Description: find the needed element in the array
 *     O(logn)
 *
 */
static int search(char **data, int size, char *elt, int *found)
{
    int lo, hi, mid;
    lo = 0;
    hi = size;
    while(lo<=hi)
    {
        mid = (lo+hi)/2; //set mid
        if(strcmp(elt, data[mid])<0) //when is less than 1 the top half of the array doens't have the string
            hi = mid -1; //hi is now mid, begin again
        else if(strcmp(elt, data[mid])>0) //when is greater than 0 the bottom half of the array doesn't have the string
            lo = mid +1; //lo is now mid
        else
        {
            //when the string is found mid is the location
            *found = 1;
            return mid;
        }
    }
    return(lo);
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
	for(i = (sp->length)-1; i>0 ; i--){
        free(sp->data[i]);
	}
    free(sp->data);
    free(sp);
	return;
}
/*
 *Function: findElement
 *
 *Description: uses search to return the index
 *        O(logn)
 */
char *findElement(SET *sp, char *elt)
{
    assert(sp != NULL);
    int i;
    int found=0;
    i = search(sp->data, sp->count-1, elt, &found);
    if(!found)
        return(NULL);
    return(sp->data[i]); //return the index, this is used to delete
}
/*
 *Function: addElement
 *
 *Description: adds the elements to the array
 *    O(n)
 */

void addElement(SET *sp, char *elt)
{
    assert(sp != NULL);
    assert(elt != NULL);
    if(sp->count == sp->length) //if the count is the same as the length the array is full
        return;
	int check=0;
	int i, idx=search(sp->data, sp->count-1, elt, &check);
	if(check==1){
		return;
	}
	for(i = sp->count; i>=idx; i--)
        sp->data[i+1] = sp->data[i]; //moves the elements into the set
        //copy elements into array
    sp->data[idx] = strdup(elt);
	sp->count++;
	return;
    
}
/*
 *Function: removeElement
 *
 * Description: removes an element from the array if it is already there
 *        O(n)
 */
void removeElement(SET *sp, char *elt)
{
    assert(sp != NULL);
    assert(elt != NULL);
    int idx;
    int i;
    int found=0;;
    idx = search(sp->data, sp->count-1, elt, &found); //pass the element to findElement to check for it
	if(found == 0)
        return; //not found
	free(sp->data[idx]);
    for(i = idx; i < (sp->count-1); i++) //shift the element down
        sp->data[i] = sp->data[i+1];
	sp->data[sp->count-1]=NULL;
    (sp->count)--;
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
char **getElements(SET *sp)
{
    assert(sp!=NULL);
    char **words=malloc(sizeof(char*)*sp->count);
    for(int i=0;i<sp->count;i++){
        words[i]=sp->data[i];
    }
    return words;
}
