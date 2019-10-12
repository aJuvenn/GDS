/*
 * main.c
 *
 *  Created on: 11 oct. 2019
 *      Author: ajuvenn
 */

#include "gds__include.h"



GDS_ARRAY_DEFINE(int, int)
GDS_STACK_DEFINE(char, char)




int leq(int * a, int * b)
{
	return *a <= *b;
}

void testArrays()
{
	GdsArray(int) * t;

	GDS_ARRAY_NEW(t, 100000);


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


int main(int argc, char **argv) {

	srand(time(NULL));

	testStack();

	return 0;
}
