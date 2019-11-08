/*
 * gds__stack.c
 *
 *  Created on: 12 oct. 2019
 *      Author: ajuvenn
 */


#include "../gds__include.h"


void gdsStackTemplateAllocate(void * s, size_t elementSize)
{
	gdsArrayTemplateAllocate(s, 0, elementSize);
}


void * gdsStackTemplateNew(size_t elementSize)
{
	return gdsArrayTemplateNew(0, elementSize);
}



int gdsStackTemplatePop(void * s_ptr, void * elementToFill, size_t elementSize)
{
	GdsArray(char) * t = s_ptr;


	if (t->nbElements == 0){
		return EXIT_FAILURE;
	}

	if (elementToFill != NULL){
		memcpy(elementToFill, t->elements + elementSize * (t->nbElements - 1), elementSize);
	}

	gdsArrayTemplateRemoveLast(t, elementSize);

	return EXIT_SUCCESS;
}


void * gdsStackTemplateTop(void * s_ptr, size_t elementSize)
{
	GdsStack(char) * s = s_ptr;

	if (s->nbElements == 0){
		return NULL;
	}

	return s->elements + elementSize * (s->nbElements - 1);
}



