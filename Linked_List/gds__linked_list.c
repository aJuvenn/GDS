/*
 * gds__linked_list.c
 *
 *  Created on: 4 nov. 2019
 *      Author: ajuvenn
 */

#include "../gds__include.h"


void gdsLinkedListAllocate(void * lPtr)
{
	GdsLinkedListTemplate * l = lPtr;
	l->firstElement = NULL;
	l->lastElement = NULL;
	l->nbElements = 0;
}


void * gdsLinkedListNew()
{
	GdsLinkedListTemplate * l;
	GDS_SIMPLE_ALLOC(l, 1);
	gdsLinkedListAllocate(l);
	return l;
}


void gdsLinkedListTemplateInsertAfter(void * lPtr, void * elementToInsertPtr, void * elementInListPtr, size_t elementSize)
{
	GdsLinkedListTemplate * l = lPtr;
	char * newLnkData;
	GDS_SIMPLE_ALLOC(newLnkData, 2 * sizeof(void *) + elementSize);
	GdsLinkTemplate * newLnk = (void *) newLnkData;

	memcpy(&(newLnk->element), elementToInsertPtr, elementSize);

	if (elementInListPtr != NULL){

		GdsLinkTemplate * lnkInList = (void *) GDS_LINK_PTR((char *) elementInListPtr);

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



void gdsLinkedListTemplateInsertBefore(void * lPtr, void * elementToInsertPtr, void * elementInListPtr, size_t elementSize)
{
	if (elementInListPtr == NULL){
		gdsLinkedListTemplateInsertAfter(lPtr, elementToInsertPtr, ((GdsLinkedListTemplate *) lPtr)->lastElement, elementSize);
		return;
	}

	void * previousElementInList = GDS_LINK_PTR((char *) elementInListPtr)->previousElement;

	gdsLinkedListTemplateInsertAfter(lPtr, elementToInsertPtr, previousElementInList, elementSize);
}


void gdsLinkedListTemplateAppend(void * lPtr, void * elementPtr, size_t elementSize)
{
	gdsLinkedListTemplateInsertBefore(lPtr, elementPtr, NULL, elementSize);
}


void gdsLinkedListTemplateAppendBefore(void * lPtr, void * elementPtr, size_t elementSize)
{
	gdsLinkedListTemplateInsertAfter(lPtr, elementPtr, NULL, elementSize);
}




