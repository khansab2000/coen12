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
#include "setApp1.h"

typedef struct set
{
    int *idx;
    int *age;
    int count;
    int length;
}SET;
/*
 * Function: createSet
 *
 * Description: creates the set that holds the  array
 * O(1)
 */
SET *createDataSet(int maxElts)
{
    int i;
    SET *sp;
    sp = malloc(sizeof(SET)); //allocate for set
    assert(sp != NULL);
    sp->length=maxElts;
    //initialize the length and count
    sp->age=malloc(sizeof(int)*maxElts);
    sp->idx=malloc(sizeof(int)*maxElts);
    sp->count=0;
    return(sp);
}
/*
 *Function: search
 *
 * Description: find the needed element in the array
 *     O(logn)
 *
 */
int searchAge(SET *sp, int elt, bool *found)
{
    printf("searching for age %d\n", elt);
    *found=false;
    int lo, hi, mid;
    lo = 0;
    hi = sp->count;
    while(lo<=hi)
    {
        mid = (lo+hi)/2; //set mid
        if(elt<sp->age[mid]) //when is less than 1 the top half of the array doens't have the string
            hi = mid -1; //hi is now mid, begin again
        else if(elt>sp->age[mid]) //when is greater than 0 the bottom half of the array doesn't have the string
            lo = mid +1; //lo is now mid
        else
        {
            //when the string is found mid is the location
            *found=true;
            printf("Age found\n");
            return mid;
        }
    }
    printf("Age not found\n");
    return lo;
}
/*
 * Function: destroyDataSet
 *
 * Description: destroys the array
 *
 *     O(1)
 */
void destroyDataSet(SET *sp)
{
    assert(sp != NULL);
    free(sp->age);
    free(sp->idx);
    free(sp);
    return;
}

/*
 *Function: addElement
 *
 *Description: adds the elements to the array
 *    O(n)
 */

void insert(SET *sp, int id, int age)
{
    assert(sp != NULL);
    if(sp->count == sp->length){
        printf("Array is full\n");//if the count is the same as the length the array is full
        return;
    }
    bool found;
    int i, index;
    index=searchAge(sp, age, &found);
    for(i = sp->count; i>=index; i--){
        sp->age[i+1] = sp->age[i];
        sp->idx[i+1] = sp->idx[i];
    }//moves the elements into the set
    sp->age[index] = age;
    sp->idx[index] = id;
    sp->count++;
    return;
    
}
/*
 *Function: removeElement
 *
 * Description: removes all the id's given a certain age
 *        O(n)
 */
void deletion(SET *sp, int age)
{
    assert(sp != NULL);
    printf("Removing age %d\n", age);
    int index;
    int i, hi, lo, range;
    range=0;
    bool found=false;
    index = searchAge(sp, age, &found); //pass the element to findElement to check for it
    if(found == false){
        printf("Could not remove, age not in system\n");
        return;
    }
    //not found
    hi=index;
    lo=index;
    while(sp->age[hi]==sp->age[index]){
        hi++;
        range++;
    }
    while(sp->age[lo]==sp->age[index]){
        lo--;
        range++;
    }
    for(i = hi+1; i < sp->count; i++){
        sp->age[i-range] = sp->age[i];
        sp->idx[i-range] = sp->idx[i];
    } //shift the elements down
    sp->count=(sp->count)-range;
    printf("Age %d deleted\n", age);
    return;
}

/*
 *Function: maxAge
 *
 *Description: Returns the gap between the oldest and youngest students
 *    O(1)
 *
 */

void maxAgeGap(SET* sp){
    printf("Max age gap is %d \n", (sp->age[(sp->count)-1]-(sp->age[1])));
           }
