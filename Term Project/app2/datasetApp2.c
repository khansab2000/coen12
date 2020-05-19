//
//  dataset.c
//
//
//  Created by Sabiq Khan on 6/3/19.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "setApp2.h"
#define EMPTY 0
#define FILLED 1
#define DELETED 2

typedef struct set
{
    int *idx;
    int *age;
    int count;
    int length;
    char* flags;
    int (*hash)();
}SET;
/*
 * Function: createSet
 *
 * Description: creates the set that holds the  array
 * O(1)
 */
SET *createDataSet(int maxElts, int (*hash)())
{
    int i;
    SET *sp;
    sp = malloc(sizeof(SET)); //allocate for set
    assert(sp != NULL);
    sp->length=maxElts;
    sp->hash=hash;
    sp->age=malloc(sizeof(int)*maxElts);
    sp->idx=malloc(sizeof(int)*maxElts);
    sp->count=0;
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
 * Description: find the needed element in the array, and return the appropriate location
 *     Expected O(1), worst case O(n)
 *
 */
int searchID(SET *sp, int id, bool* found){
    assert(sp!=NULL);
    printf("Searching for ID: %d\n", id);
    int index=(((sp->hash)(id))%(sp->length));
    if(sp->flags[index]==EMPTY){
        *found=false;
        printf("ID not found\n");
        return index;
    }
    int firstDeleted=-1;
    while(sp->flags[index]!=EMPTY){
        if(sp->idx[index]==id &&sp->flags[index]!=DELETED){
            *found=true;
            printf("Found ID: %d\n", id);
            return index;
        }
        if(sp->flags[index] == DELETED && firstDeleted == -1){
            firstDeleted=index;
            
        }
        index = (index + 1) % (sp->length);
    }
    printf("ID not found\n");
    *found=false;
    if(firstDeleted!=-1){
        index=firstDeleted;
    }
    return index;
    }
    /*
     * Function: destroySet
     *
     * Description: destroys the SET
     *
     *     O(1)
     */
void destroySet(SET *sp)
    {
        assert(sp != NULL);
        free(sp->age);
        free(sp->idx);
        free(sp->flags);
        free(sp);
        return;
    }
           
    /*
     *Function: addElement
     *
     *Description: adds the elements to the array
     *    O(n) worst case
     */
           
void insert(SET *sp, int id, int age)
    {
        assert(sp != NULL);
        if(sp->count == sp->length){ //if the count is the same as the length the array is full
            printf("System is full, could not add\n");
            return;
        }
        int index;
        bool found=true;
        index=searchID(sp, id, &found);
        sp->idx[index] = id;
        sp->age[index] = age;
        sp->flags[index] = FILLED;
        sp->count++;
        return;
    }

    /*
     *Function: removeElement
     *
     * Description: removes an element from the array if it is already there
     *        O(n) worst case
     */
void deletion(SET *sp, int id)
    {
        assert(sp != NULL);
        bool found=false;
        int index=searchID(sp, id, &found);
        if(found == true){
            sp->flags[index] = DELETED;
            sp->count--;
            printf("Successfully deleted ID: %d\n", id);
            return;
        }
        printf("Could not Delete ID: %d\n", id);
        return;
        
    }
           
           
           
