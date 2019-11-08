/*
 * gds__queue.c
 *
 *  Created on: 31 oct. 2019
 *      Author: ajuvenn
 */



#include "../gds__include.h"


void gdsQueueTemplateAllocate(void * const ptr, const size_t nbElements, const size_t elementSize)
{
	GdsQueueTemplate * q = ptr;

	GDS_SIMPLE_ALLOC(q->elements, nbElements * elementSize);
	q->_maxNbElements = nbElements;
	q->inputIndex = 0;
	q->outputIndex = 0;
}


void * gdsQueueTemplateNew(const size_t nbElements, const size_t elementSize)
{
	GdsQueueTemplate * q;

	GDS_SIMPLE_ALLOC(q, 1);
	gdsQueueTemplateAllocate(q, nbElements, elementSize);

	return q;
}


int gdsQueueIsEmpty(const GdsQueueTemplate * const q)
{
	return ((q->outputIndex - q->inputIndex) % q->_maxNbElements == 0);
}


int gdsQueueIsFull(const GdsQueueTemplate * const q)
{
	return ((q->outputIndex - q->inputIndex) % q->_maxNbElements == 1);
}


void gdsQueueTemplateExtend(GdsQueueTemplate * const q, const size_t elementSize)
{
	const size_t oldMaxNbElements = q->_maxNbElements;
	const size_t newMaxNbElements = 2 * oldMaxNbElements;

	GDS_SIMPLE_REALLOC(q->elements, q->elements, elementSize * newMaxNbElements);
	q->_maxNbElements = newMaxNbElements;

	if (q->outputIndex <= q->inputIndex){
		return;
	}

	const size_t nbLeftElements = q->inputIndex;
	const size_t nbRightElements = oldMaxNbElements - q->outputIndex;

	if (nbLeftElements < nbRightElements){

		memcpy(q->elements + elementSize * oldMaxNbElements,
				q->elements,
				elementSize * nbLeftElements);
		q->inputIndex = oldMaxNbElements + nbLeftElements;

	} else {

		memcpy(q->elements + elementSize * (newMaxNbElements - nbRightElements),
				q->elements + elementSize * q->outputIndex,
				elementSize * nbRightElements);
		q->outputIndex = (newMaxNbElements - nbRightElements) % newMaxNbElements;
	}
}


void gdsQueueTemplateInsert(void * const qPtr, const void * const element, const size_t elementSize)
{
	GdsQueueTemplate * q = qPtr;

	if (gdsQueueIsFull(q)){
		gdsQueueTemplateExtend(q, elementSize);
	}

	memcpy(q->elements + q->inputIndex * elementSize, element, elementSize);
	q->inputIndex = (q->inputIndex + 1) % q->_maxNbElements;
}


int gdsQueueTemplateRemove(void * const qPtr, void * const elementToFill, const size_t elementSize)
{
	if (gdsQueueIsEmpty(qPtr)){
		return EXIT_FAILURE;
	}

	GdsQueueTemplate * q = qPtr;

	memcpy(elementToFill, q->elements + elementSize * q->outputIndex, elementSize);
	q->outputIndex = (q->outputIndex + 1) % q->_maxNbElements;

	// TODO : if queue is small, retract allocated memory

	return EXIT_SUCCESS;
}


void * gdsQueueTemplateNextOutput(void * qPtr, const size_t elementSize)
{
	if (gdsQueueIsEmpty(qPtr)){
		return NULL;
	}

	GdsQueueTemplate * q = qPtr;

	return q->elements + elementSize * q->outputIndex;
}


void gdsQueueDeallocate(void * qPtr)
{
	GdsQueueTemplate * q = qPtr;
	free(q->elements);
}


void gdsQueueFree(void * qPtr)
{
	gdsQueueDeallocate(qPtr);
	free(qPtr);
}



