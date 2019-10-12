/*
 * gds_array.h
 *
 *  Created on: 18 janv. 2019
 *      Author: ajuvenn
 */

#ifndef GDS__ARRAY_H_
#define GDS__ARRAY_H_

#include "../gds__include.h"




typedef struct {

	size_t nbElements;
	size_t _maxNbElements;
	char * elements;

} GdsArrayTemplate;


void gdsArrayTemplateAllocate(void * t_ptr, const size_t nbElements, const size_t elementSize);
void gdsArrayDeallocate(void * t_ptr);

GdsArrayTemplate * gdsArrayTemplateNew(const size_t nbElements, const size_t elementSize);
void gdsArrayFree(void * t_ptr);

void gdsArrayTemplateExtend(void * t_ptr, const size_t nbElementsToAdd, const size_t elementSize);
void gdsArrayTemplateRetract(void * t_ptr, const size_t nbElementsToRemove, const size_t elementSize);
void gdsArrayTemplateAppend(void * t_ptr, void * elementPtr, const size_t elementSize);
void gdsArrayTemplateRemoveLast(void * t_ptr, const size_t elementSize);

void gdsArrayTemplateCopy(void * const dst_ptr, const void * const src_ptr, const size_t elementSize);
void gdsArrayTemplateSort(void * t_ptr, const size_t elementSize, int (*comparisonFunction)(void *, void *));


#define GdsArray(typeName) GdsArray__##typeName


#define GDS_ARRAY_DEFINE(typeName, type) \
	typedef struct {\
		size_t nbElements;\
		size_t _maxNbElements;\
		type * elements;\
	} GdsArray(typeName);\


#define gdsArrayAllocate(t, nbElements) \
	do {\
		gdsArrayTemplateAllocate((t), (nbElements), sizeof(*((t)->elements)));\
	} while (0)


#define GDS_ARRAY_NEW(t, nbElements)\
	do {\
		(t) = (void *) gdsArrayTemplateNew(nbElements, sizeof(*((t)->elements)));\
	} while (0)


#define gdsArrayExtend(t, nbElementsToAdd)\
	do {\
		gdsArrayTemplateExtend((t), (nbElementsToAdd), sizeof(*((t)->elements)));\
	} while (0)


#define gdsArrayRetract(t, nbElementsToRemove)\
	do {\
		gdsArrayTemplateRetract((t), (nbElementsToRemove), sizeof(*((t)->elements)));\
	} while (0)

#define gdsArrayAppend(t, element)\
	do {\
		typeof(*((t)->elements)) _GDS_ELEMENT_TO_APPEND = (element);\
		gdsArrayTemplateAppend((t), & _GDS_ELEMENT_TO_APPEND, sizeof(*((t)->elements)));\
	} while (0)

#define gdsArrayRemoveLast(t)\
	do {\
		gdsArrayTemplateRemoveLast((t), sizeof(*((t)->elements)));\
	} while (0)


#define GDS_ARRAY_FOR(tPtr, index, iterator, instruction)\
	do {\
		for (size_t index = 0 ; index < (tPtr)->nbElements ; index++){\
			typeof((tPtr)->elements) iterator = (tPtr)->elements + index;\
			do { instruction } while (0);\
		}\
	} while (0)



#define gdsArrayCopy(dst, src)\
	do {\
		if (sizeof(*((dst)->elements)) != sizeof(*((src)->elements))){\
			fprintf(stderr, "Invalid array copy : wrong types\n");\
			exit(EXIT_FAILURE);\
		} else {\
			gdsArrayTemplateCopy(dst, src, sizeof(*((src)->elements)));\
		}\
	} while (0)



#define gdsArraySort(t, comparisonFunction)\
	do {\
		gdsArrayTemplateSort((t), sizeof(*((t)->elements)), (int (*)(void *, void *)) (comparisonFunction));\
	} while (0)



#endif /* GDS_ARRAY_H_ */
