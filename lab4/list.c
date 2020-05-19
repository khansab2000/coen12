//Sabiq Khan Lab 4 List Tuesday 2:15
#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include <assert.h>

typedef struct node{
	struct node *next;
	struct node *prev;
	void *data;
}NODE;

struct list{
	int count;
	NODE *head;
	int (*compare)();
};

//CREATE LIST RUNTIME: O(1)
LIST *createList(int (*compare)()){
	LIST *lp=malloc(sizeof(LIST));
	assert(lp!=NULL);
	lp->count=0;
	lp->compare=compare;
	lp->head=malloc(sizeof(NODE));
	assert(lp->head!=NULL);
	//make the list circular
	lp->head->prev=lp->head;
	lp->head->next=lp->head;//initializing the "dummy" node
	lp->head->data=NULL;
	return lp;
}

//DESTROY LIST RUNTIME:O(n)
void destroyList(LIST *lp){
	assert(lp!=NULL);
	NODE *pDel, *pNext;
	pDel=lp->head;
	do{
		pNext=pDel->next;
		free(pDel);//destroying each node
		pDel=pNext;
	}while(pDel!=lp->head);
	free(lp);
}

//NUMITEMS RUNTIME: O(1)
int numItems(LIST *lp){
	assert(lp!=NULL);
	return lp->count;
}

//ADDFIRST RUNTIME: O(1)
void addFirst(LIST *lp, void *item){
	assert(lp!=NULL && item!=NULL);
	NODE* new=malloc(sizeof(NODE));
	new->data=item;
	new->next=lp->head->next;
	lp->head->next->prev=new;
	lp->head->next=new;
	new->prev=lp->head;
	new->next->prev=new;
	lp->count++;//adding the new node to the beginning of the list and having the dummy node point to it
}

//ADDLAST RUNTIME O(1)
void addLast(LIST* lp, void* item){
	assert(lp!=NULL && item!=NULL);
	NODE* new=malloc(sizeof(NODE));
	new->data=item;
	new->next=lp->head;
	new->prev=lp->head->prev;
	lp->head->prev->next=new;
	lp->head->prev=new;
	new->prev->next=new;
	lp->count++;//adding the new node to the end of the list and having it point to the dummy node
}

//REMOVEFIRST RUNTIME O(1)
void* removeFirst(LIST* lp){
	assert(lp!=NULL);
	NODE *p= lp->head->next;
	void* firstData=p->data;
	lp->head->next=p->next;
	p->next->prev=lp->head;
	free(p);
	lp->count--;
	return firstData;//removing the first node in the list and returning the same node
}
//REMOVELAST RUNTIME O(1)
void* removeLast(LIST* lp){
	assert(lp!=NULL);
	NODE *p=lp->head->prev;
	void* lastData=p->data;
	lp->head->prev=p->prev;
	p->prev->next=lp->head;
	free(p);
	lp->count--;
	return lastData;//removing the last node in the list and returning the same node
}

//GETFIRST RUNTIME O(1)
void *getFirst(LIST* lp){
	assert(lp!=NULL);
	return lp->head->next->data;
}

//GETLAST RUNTIME O(1)
void* getLast(LIST *lp){
	assert(lp!=NULL);
	return lp->head->prev->data;
}

//REMOVEITEM RUNTIME O(n)
void removeItem(LIST* lp, void* item){
	assert(lp!=NULL&&item!=NULL);
	NODE* pDel=lp->head->next;
	int i;
	for(i=0;i<lp->count;i++){
		if((*lp->compare)(item, pDel->data) == 0){
			pDel->next->prev=pDel->prev;
			pDel->prev->next=pDel->next;
			free(pDel);
		}
		pDel=pDel->next;
	}
	lp->count--;
}//removing a node from the middle of the list

//FINDITEM RUNTIME O(n)
void* findItem(LIST* lp, void* item){
	assert(lp!=NULL);
	NODE* pFind=lp->head->next;
	int i;
	for(i=0;i<lp->count;i++){
		if((*lp->compare)(item, pFind->data) == 0){
			return (pFind->data);
		}
		pFind=pFind->next;
	}
	return NULL;
}//finding an item in the list. if its not found, return NULL

//GETITEMS RUNTIME O(n)
void* getItems(LIST *lp){
	void** copy;
	copy=malloc(sizeof(void*)*lp->count);
	assert(copy!=NULL);
	int i;
	NODE* p=lp->head->next;
	for(i=0;i<lp->count;i++){
		copy[i]=p->data;
		p=p->next;
	}
	return copy;
}//allocate and return an array of items in the list pointed to by lp
