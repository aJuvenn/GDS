/*
 * gds__stack.h
 *
 *  Created on: 12 oct. 2019
 *      Author: ajuvenn
 */

#ifndef ARRAY_GDS__STACK_H_
#define ARRAY_GDS__STACK_H_

#include "../gds__include.h"


#define GdsStack(type) GdsArray(type)


#define GDS_STACK_ELTYPEOF(s) typeof(*((s)->elements))
#define GDS_STACK_ELSIZEOF(s) sizeof(*((s)->elements))




void gdsStackTemplateAllocate(void * s, size_t elementSize);

#define gdsStackAllocate(s)\
	do {\
		gdsStackTemplateAllocate((s), GDS_STACK_ELSIZEOF(s));\
	} while (0)


#define gdsStackDeallocate gdsArrayDeallocate


void * gdsStackTemplateNew(size_t elementSize);

#define GDS_STACK_NEW(s)\
	do {\
		(s) = (void *) gdsStackTemplateNew(GDS_STACK_ELSIZEOF(s));\
	} while (0)


#define gdsStackFree gdsArrayFree


#define gdsStackPush gdsArrayAppend


int gdsStackTemplatePop(void * s_ptr, void * elementToFill, size_t elementSize);

#define gdsStackPop(s)\
	({GDS_STACK_ELTYPEOF(s) _GDS_STACK_ELEMENT_TO_RETURN;\
	  gdsStackTemplatePop(s, & _GDS_STACK_ELEMENT_TO_RETURN, GDS_STACK_ELSIZEOF(s));\
	  _GDS_STACK_ELEMENT_TO_RETURN;})


void * gdsStackTemplateTop(void * s_ptr, size_t elementSize);

#define gdsStackTop(s)\
	gdsStackTemplateTop((s), GDS_STACK_ELSIZEOF(s))


#define gdsStackCopy gdsArrayCopy



#endif /* ARRAY_GDS__STACK_H_ */
