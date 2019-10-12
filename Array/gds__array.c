/*
 * gds_array.c
 *
 *  Created on: 11 oct. 2019
 *      Author: ajuvenn
 */

#include "../gds__include.h"


void gdsArrayTemplateAllocate(void * t_ptr, const size_t nbElements, const size_t elementSize)
{
	GdsArrayTemplate * t = t_ptr;
	t->nbElements = nbElements;
	t->_maxNbElements = nbElements == 0 ? 1 : nbElements;
	GDS_SIMPLE_ALLOC(t->elements, elementSize * t->_maxNbElements);
}




GdsArrayTemplate * gdsArrayTemplateNew(const size_t nbElements, const size_t elementSize)
{
	GdsArrayTemplate * t;
	GDS_SIMPLE_ALLOC(t, 1);
	gdsArrayTemplateAllocate(t, nbElements, elementSize);
	return t;
}


void gdsArrayDeallocate(void * t_ptr)
{
	GdsArrayTemplate * t = t_ptr;
	free(t->elements);
}



void gdsArrayFree(void * t_ptr)
{
	gdsArrayDeallocate(t_ptr);
	free(t_ptr);
}


void gdsArrayTemplateExtend(void * t_ptr, const size_t nbElementsToAdd, const size_t elementSize)
{
	GdsArrayTemplate * const t = t_ptr;
	const size_t newNbElements = t->nbElements + nbElementsToAdd;

	t->nbElements = newNbElements;

	if (newNbElements <= t->_maxNbElements){
		return;
	}

	const size_t newMaxNbElements = 2 * (newNbElements + 1);
	GDS_SIMPLE_REALLOC(t->elements, t->elements, newMaxNbElements * elementSize);
	t->_maxNbElements = newMaxNbElements;
}


void gdsArrayTemplateRetract(void * t_ptr, const size_t nbElementsToRemove, const size_t elementSize)
{
	GdsArrayTemplate * const t = t_ptr;
	const size_t newNbElements = t->nbElements > nbElementsToRemove ? t->nbElements - nbElementsToRemove : 0;

	t->nbElements = newNbElements;

	if (newNbElements > t->_maxNbElements / 4){
		return;
	}

	const size_t newMaxNbElements = 2 * (newNbElements + 1);
	GDS_SIMPLE_REALLOC(t->elements, t->elements, newMaxNbElements * elementSize);
	t->_maxNbElements = newMaxNbElements;
}


void gdsArrayTemplateAppend(void * t_ptr, void * elementPtr, const size_t elementSize)
{
	GdsArrayTemplate * t = t_ptr;
	gdsArrayTemplateExtend(t, 1, elementSize);
	memcpy(t->elements + elementSize * (t->nbElements - 1), elementPtr, elementSize);
}


void gdsArrayTemplateRemoveLast(void * t_ptr, const size_t elementSize)
{
	gdsArrayTemplateRetract(t_ptr, 1, elementSize);
}




void gdsArraySwapAux(char * const elements, const size_t index1, const size_t index2, const size_t elementSize)
{
	char tmp[elementSize];
	void * element1Addr = elements + index1 * elementSize;
	void * element2Addr = elements + index2 * elementSize;

	memcpy(tmp, element1Addr, elementSize);
	memcpy(element1Addr, element2Addr, elementSize);
	memcpy(element2Addr, tmp, elementSize);
}



int gdsArraySwap(GdsArrayTemplate * const t, const size_t index1, const size_t index2, const size_t elementSize)
{
	if (index1 >= t->nbElements || index2 >= t->nbElements){
		return EXIT_FAILURE;
	}

	gdsArraySwapAux(t->elements, index1, index2, elementSize);

	return EXIT_SUCCESS;
}



size_t gdsArrayPartition(char * const elements, const size_t nbElements, const size_t elementSize, int (*comparisonFunction)(void *, void *), size_t pivotIndex)
{
	size_t lastIndex = nbElements - 1;
	size_t j = 0;

	gdsArraySwapAux(elements, pivotIndex, lastIndex, elementSize);

	for (size_t i = 0 ; i < lastIndex ; i++){

		if (comparisonFunction(elements + i * elementSize, elements + lastIndex * elementSize)){
			gdsArraySwapAux(elements, i, j, elementSize);
			j++;
		}
	}

	gdsArraySwapAux(elements, j, lastIndex, elementSize);

	return j;
}


void gdsArraySortAux(char * const elements, const size_t nbElements, const size_t elementSize, int (*comparisonFunction)(void *, void *))
{
	if (nbElements <= 1){
		return;
	}

	size_t pivotIndex = gdsArrayPartition(elements, nbElements, elementSize, comparisonFunction, ((size_t) rand()) % nbElements);

	gdsArraySortAux(elements, pivotIndex, elementSize, comparisonFunction);
	gdsArraySortAux(elements + (pivotIndex + 1) * elementSize, nbElements - pivotIndex - 1, elementSize, comparisonFunction);
}


void gdsArrayTemplateSort(void * t_ptr, const size_t elementSize, int (*comparisonFunction)(void *, void *))
{
	GdsArrayTemplate * t = t_ptr;
	gdsArraySortAux(t->elements, t->nbElements, elementSize, comparisonFunction);
}


void gdsArrayTemplateCopy(void * const dst_ptr, const void * const src_ptr, const size_t elementSize)
{
	GdsArrayTemplate * const dst = dst_ptr;
	const GdsArrayTemplate * const src = src_ptr;

	if (dst->nbElements < src->nbElements){
		gdsArrayTemplateExtend(dst, src->nbElements - dst->nbElements, elementSize);
	} else if (dst->nbElements > src->nbElements){
		gdsArrayTemplateRetract(dst, dst->nbElements - src->nbElements, elementSize);
	}

	memcpy(dst->elements, src->elements, elementSize * src->nbElements);
}

