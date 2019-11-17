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

	gdsListFree(l);
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
	gdsArrayCopy(&tCopy, t);

	myPrintArray(&tCopy);

	gdsArrayDeallocate(&tCopy);
	gdsArrayFree(t);
}





GDS_TABLE_DEFINE(char, double);

void testTable()
{
	GdsTable(char, double) * t = gdsTableNew(3);

	gdsTableSet(t, 'a', 0.4);
	gdsTableSet(t, 'b', 0.1);
	gdsTableSet(t, 'c', 1000.7);
	gdsTableSet(t, 'd', 0.67367);
	gdsTableSet(t, 'e', 1000000000.1);

	for (char c = 'a' ; c <= 'e' ; c++){
		printf("%c -> %f\n", c, *gdsTableGetPtr(t, c));
	}

	gdsTableFree(t);
}


int main(int argc, char **argv) {

	srand(time(NULL));

	testTable();

	return 0;
}
