typedef struct set SET;
SET *createDataSet(int maxElts, int (*hash)());
int searchID(SET *sp, int id, bool* found);
void destroySet(SET *sp);
void insert(SET *sp, int id, int age);
void deletion(SET *sp, int id);
