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


/*

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

*/


typedef char * String;
GDS_LIST_DEFINE(String);

void testList()
{
	static char * s = "coucou ca va ?";

	GdsList(String) * l = gdsListNew();

	for (size_t i = 0 ; i < 10 ; i++){
		gdsListAppend(l, s + i);
	}

	GDS_LIST_FOR(l, i, it,
			printf("[%lu] %s\n", i, *it);
	);

	printf("Removed element : %s\n", gdsListRemove(l, GDS_LIST_NEXT(GDS_LIST_NEXT(l->firstElement))));
	printf("Removed element : %s\n", gdsListRemove(l, l->lastElement));

	GDS_LIST_FOR(l, i, it,
			printf("[%lu] %s\n", i, *it);
	);
}

/*

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
*/


GDS_ARRAY_DEFINE(int);



void myPrintArray(const GdsArray(int) * const a)
{
	GDS_ARRAY_FOR(a, i, it,
			printf("[%lu] %d\n", i, *it);
	);
}


void testArrays()
{
	GdsArray(int) * t;

	GDS_ARRAY_NEW(t, 10);


	GDS_ARRAY_FOR(t, i, it,
		*it = rand() % 100;
	);


	myPrintArray(t);

	gdsArraySort(t, leq);

	GdsArray(int) tCopy;
	gdsArrayAllocate(&tCopy, 0);
	gdsArrayCopy(&tCopy, t);

	myPrintArray(&tCopy);

	gdsArrayDeallocate(&tCopy);
	gdsArrayFree(t);
}



int main(int argc, char **argv) {

	srand(time(NULL));

	testArrays();
	testList();

	return 0;
}
