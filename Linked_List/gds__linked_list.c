/*
 * gds__linked_list.c
 *
 *  Created on: 4 nov. 2019
 *      Author: ajuvenn
 */

#include "../gds__include.h"


void gdsListAllocate(void * lPtr)
{
	_GdsListCharTemplate * l = lPtr;
	l->firstElement = NULL;
	l->lastElement = NULL;
	l->nbElements = 0;
}


void * gdsListNew()
{
	_GdsListCharTemplate * l;
	GDS_SIMPLE_ALLOC(l, 1);
	gdsListAllocate(l);
	return l;
}


void _gdsListTemplateInsertAfter(void * lPtr, void * elementToInsertPtr, void * elementInListPtr, size_t elementSize)
{
	_GdsListCharTemplate * l = lPtr;
	char * newLnkData;
	GDS_SIMPLE_ALLOC(newLnkData, 2 * sizeof(void *) + elementSize);
	_GdsLinkCharTemplate * newLnk = (void *) newLnkData;

	memcpy(&(newLnk->element), elementToInsertPtr, elementSize);

	if (elementInListPtr != NULL){

		_GdsLinkCharTemplate * lnkInList = (void *) GDS_LINK_PTR((char *) elementInListPtr);

		newLnk->nextElement = lnkInList->nextElement;
		lnkInList->nextElement = &(newLnk->element);
		newLnk->previousElement = &(lnkInList->element);

	} else {

		newLnk->nextElement = l->firstElement;
		newLnk->previousElement = NULL;
		l->firstElement = &(newLnk->element);
	}

	if (newLnk->nextElement != NULL){
		GDS_LINK_PTR(newLnk->nextElement)->previousElement = &(newLnk->element);
	} else {
		l->lastElement = &(newLnk->element);
	}

	l->nbElements++;
}



void _gdsListTemplateInsertBefore(void * lPtr, void * elementToInsertPtr, void * elementInListPtr, size_t elementSize)
{
	if (elementInListPtr == NULL){
		_gdsListTemplateInsertAfter(lPtr, elementToInsertPtr, ((_GdsListCharTemplate *) lPtr)->lastElement, elementSize);
		return;
	}

	void * previousElementInList = GDS_LINK_PTR((char *) elementInListPtr)->previousElement;

	_gdsListTemplateInsertAfter(lPtr, elementToInsertPtr, previousElementInList, elementSize);
}


void _gdsListTemplateAppend(void * lPtr, void * elementPtr, size_t elementSize)
{
	_gdsListTemplateInsertBefore(lPtr, elementPtr, NULL, elementSize);
}


void _gdsListTemplateAppendBefore(void * lPtr, void * elementPtr, size_t elementSize)
{
	_gdsListTemplateInsertAfter(lPtr, elementPtr, NULL, elementSize);
}


void _gdsListTemplateRemove(void * lPtr, void * elementPtr, void * destToCopy, size_t elementSize)
{
	_GdsListCharTemplate * l = lPtr;

	char * previousElement = GDS_LIST_PREVIOUS((char *) elementPtr);
	char * nextElement = GDS_LIST_NEXT((char *) elementPtr);

	_GdsLinkCharTemplate * previousLink = previousElement ? (void *) GDS_LINK_PTR(previousElement) : NULL;
	_GdsLinkCharTemplate * nextLink = nextElement ? (void *) GDS_LINK_PTR(nextElement) : NULL;

	char * newNext = nextLink ? &(nextLink->element) : NULL;
	char * newPrevious = previousLink ? &(previousLink->element) : NULL;

	if (previousLink == NULL){
		l->firstElement = newNext;
	} else {
		previousLink->nextElement = newNext;
	}

	if (nextLink == NULL){
		l->lastElement = newPrevious;
	} else {
		nextLink->previousElement = newPrevious;
	}

	l->nbElements--;

	memcpy(destToCopy, elementPtr, elementSize);
	free(GDS_LINK_PTR((char *) elementPtr));
}


void gdsListDeallocate(void * lPtr)
{
	_GdsListCharTemplate * l = lPtr;
	char * nextElementToFree = l->firstElement;

	while (nextElementToFree != NULL){
		char * elementToFree = nextElementToFree;
		nextElementToFree = GDS_LIST_NEXT(elementToFree);
		free(GDS_LINK_PTR(elementToFree));
	}

	l->firstElement = NULL;
	l->lastElement = NULL;
	l->nbElements = 0;
}


void gdsListFree(void * lPtr)
{
	gdsListDeallocate(lPtr);
	free(lPtr);
}


