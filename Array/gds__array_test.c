/*
 * gds__array_test.c
 *
 *  Created on: 14 nov. 2019
 *      Author: ajuvenn
 */

#include "../gds__include.h"


GDS_ARRAY_DEFINE(int)

typedef char * String;
GDS_ARRAY_DEFINE(String);


int _gdsArrayTestAllocate()
{
	GdsArray(int) t;
	gdsArrayAllocate(&t, 10);

	if (t.nbElements != 10){
		gdsArrayDeallocate(&t);
		return EXIT_FAILURE;
	}

	GDS_ARRAY_FOR(&t, i, it,
			*it = (int) i;
	);

	for (size_t i = 0 ; i < t.nbElements ; i++){
		if (t.elements[i] != (int) i){
			gdsArrayDeallocate(&t);
			return EXIT_FAILURE;
		}
	}

	gdsArrayDeallocate(&t);

	return EXIT_SUCCESS;
}


int _gdsArrayTest()
{
	return _gdsArrayTestAllocate();
}
