#include <stdbool.h>
typedef struct set SET;
SET *createDataSet(int maxElts);
int searchAge(SET *sp, int elt, bool *found);
void destroyDataSet(SET *sp);
void insert(SET *sp, int id, int age);
void deletion(SET *sp, int age);
void maxAgeGap(SET* sp);


