//
//  college.c
//
//
//  Created by Sabiq Khan on 6/3/19.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>
#include "setApp2.h"
#define MAX_STUDENTS 3000
typedef struct set SET;

int hash(int id){
    return id%1009;//hash function
}

int main(int argc, char*argv[]){
    srand(time(NULL));//seeding random
    SET *college;
    college = createDataSet(MAX_STUDENTS, hash);//creating the set to hold the info
    int i, id, idPrev, age, firstNum;
    
    for(i = 0; i < 1000; i++)
    {
        firstNum = (rand() % (2+1-1)+1);
        id = firstNum + idPrev;
        idPrev = id;
        age = (rand() % (30+1-18)+18);
        insert(college, id, age);
    }//filling the set with information
    
    int sID = (rand() % 2000)+1;
    bool found=false;
    searchID(college, sID, &found);//searching for a random ID
    
    int dID = (rand() % 2000)+1;
    deletion(college, dID);//deleting a random ID
    
    destroySet(college);
    
}
