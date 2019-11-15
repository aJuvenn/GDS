/*
 * gds_array.h
 *
 *  Created on: 18 janv. 2019
 *      Author: ajuvenn
 */

#ifndef GDS__ARRAY_H_
#define GDS__ARRAY_H_

#include "../gds__include.h"


/*
 * 			TYPE DEFINITION
 */


#define GdsArray(type) GdsArray__##type

#define GDS_ARRAY_DEFINE(type)\
		typedef _GdsArrayTemplate(type) GdsArray(type);


#define _GdsArrayTemplate(type) struct {size_t nbElements; size_t _maxNbElements; type * elements;}




/*
 * 			ALLOCATION
 */


#define gdsArrayAllocate(t, nbElements) \
		do {\
			_gdsArrayTemplateAllocate((t), (nbElements), GDS_ELSIZEOF(t));\
		} while (0)


void gdsArrayDeallocate(void * t_ptr);






#define GDS_ARRAY_NEW(t, nbElements)\
		do {\
			(t) = (void *) _gdsArrayTemplateNew((nbElements), GDS_ELSIZEOF(t));\
		} while (0)

void gdsArrayFree(void * t_ptr);



/*
 * 			DYNAMIC ARRAY SIZE MODIFICATION
 */


#define gdsArrayAppend(t, element)\
		do {\
			GDS_ELTYPEOF(t) _GDS_ELEMENT_TO_APPEND = (element);\
			_gdsArrayTemplateAppend((t), & _GDS_ELEMENT_TO_APPEND, GDS_ELSIZEOF(t));\
		} while (0)



#define gdsArrayRemoveLast(t)\
	({GDS_ELTYPEOF(t) _GDS_ARRAY_ELEMENT_TO_RETURN;\
	_gdsArrayTemplateRemoveLast(t, & _GDS_ARRAY_ELEMENT_TO_RETURN, GDS_ELSIZEOF(t));\
	_GDS_ARRAY_ELEMENT_TO_RETURN;})



#define gdsArrayExtend(t, nbElementsToAdd)\
		do {\
			_gdsArrayTemplateExtend((t), (nbElementsToAdd), GDS_ELSIZEOF(t));\
		} while (0)


#define gdsArrayRetract(t, nbElementsToRemove)\
		do {\
			_gdsArrayTemplateRetract((t), (nbElementsToRemove), GDS_ELSIZEOF(t));\
		} while (0)



/*
 * 			ITERATION
 */



#define GDS_ARRAY_FOR(tPtr, index, iterator, instruction)\
		do {\
			for (size_t index = 0 ; index < (tPtr)->nbElements ; index++){\
				GDS_ELTYPEOF(tPtr) * iterator = (tPtr)->elements + index;\
				{ instruction }\
			}\
		} while (0)



/*
 * 			FUNCTIONALITIES
 */


#define gdsArrayCopy(dst, src)\
		do {\
			if (GDS_ELSIZEOF(dst) != GDS_ELSIZEOF(src)){\
				fprintf(stderr, "Invalid array copy : wrong types\n");\
				exit(EXIT_FAILURE);\
			} else {\
				_gdsArrayTemplateCopy(dst, src, GDS_ELSIZEOF(src));\
			}\
		} while (0)



#define gdsArraySort(t, comparisonFunction)\
		do {\
			_gdsArrayTemplateSort((t), GDS_ELSIZEOF(t), (int (*)(void *, void *)) (comparisonFunction));\
		} while (0)









/*
 * 			HIDDEN FUNCTIONS
 */

typedef _GdsArrayTemplate(char) _GdsArrayCharTemplate;
void _gdsArrayTemplateAllocate(void * t_ptr, const size_t nbElements, const size_t elementSize);
_GdsArrayCharTemplate * _gdsArrayTemplateNew(const size_t nbElements, const size_t elementSize);
void _gdsArrayTemplateExtend(void * t_ptr, const size_t nbElementsToAdd, const size_t elementSize);
void _gdsArrayTemplateRetract(void * t_ptr, const size_t nbElementsToRemove, const size_t elementSize);
void _gdsArrayTemplateAppend(void * t_ptr, void * elementPtr, const size_t elementSize);
int _gdsArrayTemplateRemoveLast(void * t_ptr, void * elementToFill, const size_t elementSize);
void _gdsArrayTemplateCopy(void * const dst_ptr, const void * const src_ptr, const size_t elementSize);
void _gdsArrayTemplateSort(void * t_ptr, const size_t elementSize, int (*comparisonFunction)(void *, void *));


#endif /* GDS_ARRAY_H_ */


