/*
 * gds__queue.h
 *
 *  Created on: 31 oct. 2019
 *      Author: ajuvenn
 */

#ifndef QUEUE_GDS__QUEUE_H_
#define QUEUE_GDS__QUEUE_H_



#define GdsQueue(type) struct {size_t inputIndex; size_t outputIndex; size_t _maxNbElements; type * elements;}

typedef GdsQueue(char) GdsQueueTemplate;






void gdsQueueTemplateAllocate(void * const ptr, const size_t nbElements, const size_t elementSize);


#define gdsQueueAllocate(qPtr)\
		do {\
			gdsQueueTemplateAllocate((qPtr), GDS_ELSIZEOF(qPtr));\
		} while (0)


void gdsQueueDeallocate(void * qPtr);




void * gdsQueueTemplateNew(const size_t nbElements, const size_t elementSize);

#define GDS_QUEUE_NEW(qPtr, nbElements)\
		do {\
			(qPtr) = gdsQueueTemplateNew(nbElements, GDS_ELSIZEOF(qPtr));\
		} while (0)


void gdsQueueFree(void * qPtr);




int gdsQueueIsEmpty(const GdsQueueTemplate * const q);

int gdsQueueIsFull(const GdsQueueTemplate * const q);


void gdsQueueTemplateInsert(void * const qPtr, const void * const element, const size_t elementSize);

#define gdsQueueInsert(qPtr, element)\
		do {\
			GDS_ELTYPEOF(qPtr) _GDS_ELEMENT_TO_INSERT = (element);\
			gdsQueueTemplateInsert((qPtr), & _GDS_ELEMENT_TO_INSERT, GDS_ELSIZEOF(qPtr));\
		} while (0)


int gdsQueueTemplateRemove(void * const qPtr, void * const elementToFill, const size_t elementSize);

#define gdsQueueRemove(qPtr)\
		({GDS_ELTYPEOF(qPtr) _GDS_QUEUE_ELEMENT_TO_RETURN;\
		gdsQueueTemplateRemove(qPtr, & _GDS_QUEUE_ELEMENT_TO_RETURN, GDS_ELSIZEOF(qPtr));\
		_GDS_QUEUE_ELEMENT_TO_RETURN;})



void * gdsQueueTemplateNextOutput(void * qPtr, const size_t elementSize);

#define gdsQueueNextOutput(qPtr)\
		gdsQueueTemplateNextOutput((qPtr), GDS_ELSIZEOF(qPtr))


#define GDS_QUEUE_FOR(qPtr, indexName, iteratorName, instruction)\
		do {\
			for (size_t indexName =  (qPtr)->outputIndex;\
			indexName != (qPtr)->inputIndex ;\
			indexName = (indexName + 1) % (qPtr)->_maxNbElements \
			){\
				GDS_ELTYPEOF(qPtr) * iteratorName = (qPtr)->elements + indexName;\
				{ instruction }\
			}\
		} while (0)



#endif /* QUEUE_GDS__QUEUE_H_ */
