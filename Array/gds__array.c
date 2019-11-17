/*
 * gds_array.c
 *
 *  Created on: 11 oct. 2019
 *      Author: ajuvenn
 */

#include "../gds__include.h"






void _gdsArrayTemplateAllocate(void * t_ptr, const size_t nbElements, const size_t elementSize)
{
	_GdsArrayCharTemplate * t = t_ptr;
	t->nbElements = nbElements;
	t->_maxNbElements = nbElements == 0 ? 1 : nbElements;
	GDS_SIMPLE_ALLOC(t->elements, elementSize * t->_maxNbElements);
}




_GdsArrayCharTemplate * _gdsArrayTemplateNew(const size_t nbElements, const size_t elementSize)
{
	_GdsArrayCharTemplate * t;
	GDS_SIMPLE_ALLOC(t, 1);
	_gdsArrayTemplateAllocate(t, nbElements, elementSize);
	return t;
}


void gdsArrayDeallocate(void * t_ptr)
{
	_GdsArrayCharTemplate * t = t_ptr;
	free(t->elements);
}



void gdsArrayFree(void * t_ptr)
{
	gdsArrayDeallocate(t_ptr);
	free(t_ptr);
}


void _gdsArrayTemplateExtend(void * t_ptr, const size_t nbElementsToAdd, const size_t elementSize)
{
	_GdsArrayCharTemplate * const t = t_ptr;
	const size_t newNbElements = t->nbElements + nbElementsToAdd;

	t->nbElements = newNbElements;

	if (newNbElements <= t->_maxNbElements){
		return;
	}

	const size_t newMaxNbElements = 2 * (newNbElements + 1);
	GDS_SIMPLE_REALLOC(t->elements, t->elements, newMaxNbElements * elementSize);
	t->_maxNbElements = newMaxNbElements;
}


void _gdsArrayTemplateRetract(void * t_ptr, const size_t nbElementsToRemove, const size_t elementSize)
{
	_GdsArrayCharTemplate * const t = t_ptr;
	const size_t newNbElements = t->nbElements > nbElementsToRemove ? t->nbElements - nbElementsToRemove : 0;

	t->nbElements = newNbElements;

	if (newNbElements > t->_maxNbElements / 4){
		return;
	}

	const size_t newMaxNbElements = 2 * (newNbElements + 1);
	GDS_SIMPLE_REALLOC(t->elements, t->elements, newMaxNbElements * elementSize);
	t->_maxNbElements = newMaxNbElements;
}


void _gdsArrayTemplateAppend(void * t_ptr, void * elementPtr, const size_t elementSize)
{
	_GdsArrayCharTemplate * t = t_ptr;
	_gdsArrayTemplateExtend(t, 1, elementSize);
	memcpy(t->elements + elementSize * (t->nbElements - 1), elementPtr, elementSize);
}


int _gdsArrayTemplateRemoveLast(void * t_ptr, void * elementToFill, const size_t elementSize)
{
	_GdsArrayCharTemplate * t = t_ptr;

	if (t->nbElements == 0){
		return EXIT_FAILURE;
	}

	if (elementToFill != NULL){
		memcpy(elementToFill, t->elements + elementSize * (t->nbElements - 1), elementSize);
	}

	_gdsArrayTemplateRetract(t_ptr, 1, elementSize);

	return EXIT_SUCCESS;
}



void _gdsArraySwapAux(char * const elements, const size_t index1, const size_t index2, const size_t elementSize)
{
	char tmp[elementSize];
	void * element1Addr = elements + index1 * elementSize;
	void * element2Addr = elements + index2 * elementSize;

	memcpy(tmp, element1Addr, elementSize);
	memcpy(element1Addr, element2Addr, elementSize);
	memcpy(element2Addr, tmp, elementSize);
}



int _gdsArraySwap(_GdsArrayCharTemplate * const t, const size_t index1, const size_t index2, const size_t elementSize)
{
	if (index1 >= t->nbElements || index2 >= t->nbElements){
		return EXIT_FAILURE;
	}

	_gdsArraySwapAux(t->elements, index1, index2, elementSize);

	return EXIT_SUCCESS;
}



size_t _gdsArrayPartition(char * const elements, const size_t nbElements, const size_t elementSize, int (*comparisonFunction)(void *, void *), size_t pivotIndex)
{
	size_t lastIndex = nbElements - 1;
	size_t j = 0;

	_gdsArraySwapAux(elements, pivotIndex, lastIndex, elementSize);

	for (size_t i = 0 ; i < lastIndex ; i++){

		if (comparisonFunction(elements + i * elementSize, elements + lastIndex * elementSize)){
			_gdsArraySwapAux(elements, i, j, elementSize);
			j++;
		}
	}

	_gdsArraySwapAux(elements, j, lastIndex, elementSize);

	return j;
}


void _gdsArraySortAux(char * const elements, const size_t nbElements, const size_t elementSize, int (*comparisonFunction)(void *, void *))
{
	if (nbElements <= 1){
		return;
	}

	size_t pivotIndex = _gdsArrayPartition(elements, nbElements, elementSize, comparisonFunction, ((size_t) rand()) % nbElements);

	_gdsArraySortAux(elements, pivotIndex, elementSize, comparisonFunction);
	_gdsArraySortAux(elements + (pivotIndex + 1) * elementSize, nbElements - pivotIndex - 1, elementSize, comparisonFunction);
}


void _gdsArrayTemplateSort(void * t_ptr, const size_t elementSize, int (*comparisonFunction)(void *, void *))
{
	_GdsArrayCharTemplate * t = t_ptr;
	_gdsArraySortAux(t->elements, t->nbElements, elementSize, comparisonFunction);
}


void _gdsArrayTemplateCopy(void * const dst_ptr, const void * const src_ptr, const size_t elementSize)
{
	_GdsArrayCharTemplate * const dst = dst_ptr;
	const _GdsArrayCharTemplate * const src = src_ptr;

	_gdsArrayTemplateAllocate(dst, src->nbElements, elementSize);

	memcpy(dst->elements, src->elements, elementSize * src->nbElements);
}

