/*
 * main.c
 *
 *  Created on: 11 oct. 2019
 *      Author: ajuvenn
 */

#include "gds__include.h"




int leq(int * a, int * b)
{
	return *a <= *b;
}


void testArrays()
{
	GdsArray(int) * t;

	GDS_ARRAY_NEW(t, 10);


	GDS_ARRAY_FOR(t, i, it,
			*it = rand() % 100;
	);

	GDS_ARRAY_FOR(t, i, it,
			printf("[%lu] %d\n", i, *it);
	);

	gdsArraySort(t, leq);

	GdsArray(int) tCopy;
	gdsArrayAllocate(&tCopy, 0);
	gdsArrayCopy(&tCopy, t);


	GDS_ARRAY_FOR(&tCopy, i, it,
			printf("[%lu] %d\n", i, *it);
	);

	gdsArrayDeallocate(&tCopy);
	gdsArrayFree(t);
}


void testStack()
{
	GdsStack(char) s;
	gdsStackAllocate(&s);

	gdsStackPush(&s, 'a');


	gdsStackPush(&s, 'b');

	char top = gdsStackPop(&s);

	gdsStackPush(&s, 'c');


	printf("Removed element : %c\n", top);

	GDS_ARRAY_FOR(&s, i, it,
			printf("[%lu] %c\n", i, *it);
	);

	gdsStackDeallocate(&s);
}



void testList()
{
	static char * s = "coucou ca va ?";

	GdsLinkedList(char *) * l = gdsLinkedListNew();

	for (size_t i = 0 ; i < 10 ; i++){
		gdsLinkedListAppend(l, s + i);
	}

	GDS_LINKED_LIST_FOR(l, i, it,
			printf("[%lu] %s\n", i, *it);
	);
}



void testQueue()
{
	GdsQueue(float) * q;
	GDS_QUEUE_NEW(q, 2);

	for (float x = 0. ; x < 1 ; x += 0.1){
		gdsQueueInsert(q, x);
	}

	GDS_QUEUE_FOR(q, i, it,
			printf("[%lu] %f\n", i, *it);
	);

	for (int i = 0 ; i < 5 ; i++){
		float x = gdsQueueRemove(q);
		printf("\nRemoved element : %f\nNew queue : ", x);
		GDS_QUEUE_FOR(q, i, it,
				printf("[%lu] %f\n", i, *it);
		);
	}


}



int main(int argc, char **argv) {

	srand(time(NULL));

	testQueue();

	return 0;
}
