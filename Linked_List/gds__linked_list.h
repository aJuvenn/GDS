/*
 * gds__linked_list.h
 *
 *  Created on: 4 nov. 2019
 *      Author: ajuvenn
 */

#ifndef LINKED_LIST_GDS__LINKED_LIST_H_
#define LINKED_LIST_GDS__LINKED_LIST_H_

#include "../gds__include.h"




#define GdsLinkedList(type) struct {type * firstElement; type * lastElement; size_t nbElements;}
#define GdsLink(type) struct {type * nextElement; type * previousElement; type element;}


typedef GdsLink(char) GdsLinkTemplate;
typedef GdsLinkedList(char) GdsLinkedListTemplate;


#define GDS_LINK_PTR(elPtr) ((GdsLink(typeof(*(elPtr))) *) (((void **) (elPtr)) - 2))




#define GDS_LINKED_LIST_NEXT(elPtr) (GDS_LINK_PTR(elPtr)->nextElement)
#define GDS_LINKED_LIST_PREVIOUS(elPtr) (GDS_LINK_PTR(elPtr)->previousElement)


#define GDS_LINKED_LIST_ELTYPE(lPtr) typeof(*((lPtr)->firstElement))
#define GDS_LINKED_LIST_ELSIZE(lPtr) sizeof(*((lPtr)->firstElement))



#define GDS_LINKED_LIST_FOR(lPtr, indexName, iteratorName, instruction)\
	do {\
		size_t indexName = 0;\
		for (GDS_LINKED_LIST_ELTYPE(lPtr) * iteratorName = (lPtr)->firstElement ; \
			 iteratorName != NULL ; \
			 iteratorName = GDS_LINKED_LIST_NEXT(iteratorName)\
			){\
			{instruction}\
			indexName++;\
		}\
	} while(0)


#define GDS_LINKED_LIST_REVERSE_FOR(lPtr, indexName, iteratorName, instruction)\
	do {\
		size_t indexName = 0;\
		for (GDS_LINKED_LIST_ELTYPE(lPtr) * iteratorName = (lPtr)->lastElement ; \
			 iteratorName != NULL ; \
			 iteratorName = GDS_LINKED_LIST_PREVIOUS(iteratorName)\
			){\
			{instruction}\
			indexName++;\
		}\
	} while(0)


void gdsLinkedListAllocate(void * lPtr);
void * gdsLinkedListNew();


void gdsLinkedListTemplateAppend(void * lPtr, void * elementPtr, size_t elementSize);

#define gdsLinkedListAppend(lPtr, element)\
		do {\
			GDS_LINKED_LIST_ELTYPE(lPtr) _GDS_ELEMENT_TO_APPEND = (element);\
			gdsLinkedListTemplateAppend((lPtr), & _GDS_ELEMENT_TO_APPEND, GDS_LINKED_LIST_ELSIZE(lPtr));\
		} while (0)


void gdsLinkedListTemplateAppendBefore(void * lPtr, void * elementPtr, size_t elementSize);


#define gdsLinkedListAppendBefore(lPtr, element)\
		do {\
			GDS_LINKED_LIST_ELTYPE(lPtr) _GDS_ELEMENT_TO_APPEND = (element);\
			gdsLinkedListTemplateAppendBefore((lPtr), & _GDS_ELEMENT_TO_APPEND, GDS_LINKED_LIST_ELSIZE(lPtr));\
		} while (0)





void gdsLinkedListTemplateInsertAfter(void * lPtr, void * elementToInsertPtr, void * elementInListPtr, size_t elementSize);


#define gdsLinkedListInsertAfter(lPtr, elementToInsert, elementInListPtr)\
	do {\
		GDS_LINKED_LIST_ELTYPE(lPtr) _GDS_ELEMENT_TO_INSERT = (elementToInsert);\
		gdsLinkedListTemplateInsertAfter(lPtr, & _GDS_ELEMENT_TO_INSERT, elementInListPtr, GDS_LINKED_LIST_ELSIZE(lPtr));\
	} while (0)





void gdsLinkedListTemplateInsertBefore(void * lPtr, void * elementToInsertPtr, void * elementInListPtr, size_t elementSize);


#define gdsLinkedListInsertBefore(lPtr, elementToInsert, elementInListPtr)\
	do {\
		GDS_LINKED_LIST_ELTYPE(lPtr) _GDS_ELEMENT_TO_INSERT = (elementToInsert);\
		gdsLinkedListTemplateInsertBefore(lPtr, & _GDS_ELEMENT_TO_INSERT, elementInListPtr, GDS_LINKED_LIST_ELSIZE(lPtr));\
	} while (0)






#endif /* LINKED_LIST_GDS__LINKED_LIST_H_ */
