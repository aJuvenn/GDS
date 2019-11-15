/*
 * gds__linked_list.h
 *
 *  Created on: 4 nov. 2019
 *      Author: ajuvenn
 */

#ifndef LINKED_LIST_GDS__LINKED_LIST_H_
#define LINKED_LIST_GDS__LINKED_LIST_H_

#include "../gds__include.h"




#define GdsList(type) GdsList__##type

#define GDS_LIST_DEFINE(type)\
	typedef _GdsListTemplate(type) GdsList(type)

#define _GdsListTemplate(type) struct {type * firstElement; type * lastElement; size_t nbElements;}



#define _GdsLink(type) struct {type * nextElement; type * previousElement; type element;}




typedef _GdsLink(char) _GdsLinkCharTemplate;
typedef _GdsListTemplate(char) _GdsListCharTemplate;


#define GDS_LINK_PTR(elPtr) ((_GdsLink(typeof(*(elPtr))) *) (((void **) (elPtr)) - 2))




#define GDS_LIST_NEXT(elPtr) (GDS_LINK_PTR(elPtr)->nextElement)
#define GDS_LIST_PREVIOUS(elPtr) (GDS_LINK_PTR(elPtr)->previousElement)


#define GDS_LIST_ELTYPEOF(lPtr) typeof(*((lPtr)->firstElement))
#define GDS_LIST_ELSIZEOF(lPtr) sizeof(*((lPtr)->firstElement))



#define GDS_LIST_FOR(lPtr, indexName, iteratorName, instruction)\
	do {\
		size_t indexName = 0;\
		for (GDS_LIST_ELTYPEOF(lPtr) * iteratorName = (lPtr)->firstElement ; \
			 iteratorName != NULL ; \
			 ({iteratorName = GDS_LIST_NEXT(iteratorName); indexName++;})\
			){\
			{instruction}\
		}\
	} while(0)


#define GDS_LIST_REVERSE_FOR(lPtr, indexName, iteratorName, instruction)\
	do {\
		size_t indexName = 0;\
		for (GDS_LIST_ELTYPEOF(lPtr) * iteratorName = (lPtr)->lastElement ; \
			 iteratorName != NULL ; \
			 ({iteratorName = GDS_LIST_PREVIOUS(iteratorName) ; indexName++;})\
			){\
			{instruction}\
		}\
	} while(0)


void gdsListAllocate(void * lPtr);
void * gdsListNew();


void _gdsListTemplateAppend(void * lPtr, void * elementPtr, size_t elementSize);

#define gdsListAppend(lPtr, element)\
		do {\
			GDS_LIST_ELTYPEOF(lPtr) _GDS_ELEMENT_TO_APPEND = (element);\
			_gdsListTemplateAppend((lPtr), & _GDS_ELEMENT_TO_APPEND, GDS_LIST_ELSIZEOF(lPtr));\
		} while (0)


void _gdsListTemplateAppendBefore(void * lPtr, void * elementPtr, size_t elementSize);


#define gdsListAppendBefore(lPtr, element)\
		do {\
			GDS_LIST_ELTYPEOF(lPtr) _GDS_ELEMENT_TO_APPEND = (element);\
			_gdsListTemplateAppendBefore((lPtr), & _GDS_ELEMENT_TO_APPEND, GDS_LIST_ELSIZEOF(lPtr));\
		} while (0)





void _gdsListTemplateInsertAfter(void * lPtr, void * elementToInsertPtr, void * elementInListPtr, size_t elementSize);


#define gdsListInsertAfter(lPtr, elementToInsert, elementInListPtr)\
	do {\
		GDS_LIST_ELTYPEOF(lPtr) _GDS_ELEMENT_TO_INSERT = (elementToInsert);\
		_gdsListTemplateInsertAfter(lPtr, & _GDS_ELEMENT_TO_INSERT, elementInListPtr, GDS_LIST_ELSIZEOF(lPtr));\
	} while (0)





void _gdsListTemplateInsertBefore(void * lPtr, void * elementToInsertPtr, void * elementInListPtr, size_t elementSize);


#define gdsListInsertBefore(lPtr, elementToInsert, elementInListPtr)\
	do {\
		GDS_LIST_ELTYPEOF(lPtr) _GDS_ELEMENT_TO_INSERT = (elementToInsert);\
		_gdsListTemplateInsertBefore(lPtr, & _GDS_ELEMENT_TO_INSERT, elementInListPtr, GDS_LIST_ELSIZEOF(lPtr));\
	} while (0)




void _gdsListTemplateRemove(void * lPtr, void * elementPtr, void * destToCopy, size_t elementSize);

#define gdsListRemove(lPtr, elementPtr)\
		({GDS_LIST_ELTYPEOF(lPtr) _GDS_LIST_ELEMENT_TO_RETURN;\
		_gdsListTemplateRemove((lPtr), (elementPtr), & _GDS_LIST_ELEMENT_TO_RETURN, GDS_LIST_ELSIZEOF(lPtr));\
		_GDS_LIST_ELEMENT_TO_RETURN;})


#endif /* LINKED_LIST_GDS__LINKED_LIST_H_ */
