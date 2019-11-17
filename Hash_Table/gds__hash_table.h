/*
 * gds__hash_table.h
 *
 *  Created on: 16 nov. 2019
 *      Author: ajuvenn
 */

#ifndef HASH_TABLE_GDS__HASH_TABLE_H_
#define HASH_TABLE_GDS__HASH_TABLE_H_

#include "../gds__include.h"


#define _GdsPair(type1, type2) _Gds__##type1##__##type2##__Pair
#define _GdsPairPointer(type1, type2) _Gds__##type1##__##type2##__PairPointer
#define _GdsTableTemplate(keyType, valueType) _GdsTable__##keyType##__##valueType##__Template

#define GDS_TABLE_DEFINE(keyType, valueType)\
		\
typedef struct {\
	keyType key;\
	valueType value;\
} _GdsPair(keyType, valueType);\
\
typedef _GdsPair(keyType, valueType) * _GdsPairPointer(keyType, valueType);\
\
GDS_LIST_DEFINE(_GdsPair(keyType, valueType));\
GDS_LIST_DEFINE(_GdsPairPointer(keyType, valueType));\
	\
typedef struct {\
	size_t hashArraySize;\
	GdsList(_Gds__##keyType##__##valueType##__PairPointer) ** hashArray;\
	GdsList(_Gds__##keyType##__##valueType##__Pair) iterator;\
} _GdsTableTemplate(keyType, valueType)\

#define GdsTable(keyType, valueType) _GdsTableTemplate(keyType, valueType)


#define GDS_TABLE_KEYTYPEOF(tPtr) typeof((tPtr)->iterator.firstElement->key)
#define GDS_TABLE_VALUETYPEOF(tPtr) typeof((tPtr)->iterator.firstElement->value)

#define GDS_TABLE_KEYSIZEOF(tPtr) sizeof((tPtr)->iterator.firstElement->key)
#define GDS_TABLE_VALUESIZEOF(tPtr) sizeof((tPtr)->iterator.firstElement->value)


#define gdsTableSet(tPtr, key, value)\
	do {\
		GDS_TABLE_KEYTYPEOF(tPtr) _GDS_KEY_TO_SET = (key);\
		GDS_TABLE_VALUETYPEOF(tPtr) _GDS_VALUE_TO_SET = (value);\
		_gdsTableSet((tPtr), & _GDS_KEY_TO_SET, & _GDS_VALUE_TO_SET,\
				GDS_TABLE_KEYSIZEOF(tPtr), GDS_TABLE_VALUESIZEOF(tPtr));\
	} while (0)


#define gdsTableGetPtr(tPtr, key)\
	({GDS_TABLE_KEYTYPEOF(tPtr) _GDS_KEY_TO_SEEK = (key);\
	(GDS_TABLE_VALUETYPEOF(tPtr) *) _gdsTableGetPtr(tPtr, & _GDS_KEY_TO_SEEK, GDS_TABLE_KEYSIZEOF(tPtr));\
	})


void gdsTableAllocate(void * tPtr, size_t hashArraySize);
void gdsTableDeallocate(void * tPtr);

void * gdsTableNew(size_t hashArraySize);
void gdsTableFree(void * tPtr);

void _gdsTableSet(void * tPtr, void * keyPtr, void * valuePtr, size_t keySize, size_t valueSize);

int _gdsTableGet(void * tPtr, void * keyPtr, void * dstValuePtr, size_t keySize, size_t valueSize);
void * _gdsTableGetPtr(void * tPtr, void * keyPtr, size_t keySize);

int _gdsTableKeyIsKnown(void * tPtr, void * keyPtr, size_t keySize);

int _gdsTableRemove(void * tPtr, void * keyPtr, size_t keySize, size_t valueSize);



#endif /* HASH_TABLE_GDS__HASH_TABLE_H_ */
