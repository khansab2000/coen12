t//
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
#include "setApp1.h"
#define MAX_STUDENTS 3000
typedef struct set SET;


int main(int argc, char*argv[]){
    srand(time(NULL));
    SET *college;
    college = createDataSet(MAX_STUDENTS);//creating the set to hold the info
    int i, firstNum, id, idPrev, age;
    
    for(i = 0; i < 1000; i++)
    {
        firstNum = (rand() % (2+1-1)+1);
        id = firstNum + idPrev;
        idPrev = id;
        age = (rand() % (30+1-18)+18);
        insert(college, id, age);
    }//filling the set with information
    
    int sAge = (rand() % 13)+18;
    bool found=false;
    searchAge(college, sAge, &found);//searching for a random aged student
    
    int dAge = (rand() % 13)+18;
    deletion(college, dAge);//deleting a random age group of students
    
    maxAgeGap(college);//returning the age difference between the oldest and youngest students
    
    destroyDataSet(college);
    
}
