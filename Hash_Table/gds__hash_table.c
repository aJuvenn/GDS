/*
 * gds__hash_table.c
 *
 *  Created on: 17 nov. 2019
 *      Author: ajuvenn
 */


#include "../gds__include.h"

GDS_TABLE_DEFINE(char, char);
typedef GdsTable(char, char) _GdsTableTemplate;


void gdsTableAllocate(void * tPtr, size_t hashArraySize)
{
	_GdsTableTemplate * t = tPtr;

	t->hashArraySize = hashArraySize;

	GDS_SIMPLE_ALLOC(t->hashArray, hashArraySize);
	memset(t->hashArray, 0, hashArraySize * sizeof(*(t->hashArray)));

	gdsListAllocate(&(t->iterator));
}


void gdsTableDeallocate(void * tPtr)
{
	_GdsTableTemplate * t = tPtr;

	for (size_t i = 0 ; i < t->hashArraySize ; i++){
		if (t->hashArray[i] != NULL){
			gdsListFree(t->hashArray[i]);
		}
	}

	gdsListDeallocate(&(t->iterator));
}


void * gdsTableNew(size_t hashArraySize)
{
	_GdsTableTemplate * t;
	GDS_SIMPLE_ALLOC(t, 1);
	gdsTableAllocate(t, hashArraySize);
	return t;
}


void gdsTableFree(void * tPtr)
{
	gdsTableDeallocate(tPtr);
	free(tPtr);
}


size_t _gdsTableHashFunction(void * keyPtr, size_t keySize)
{
	size_t output = 1;
	char * key = keyPtr;

	for (size_t i = 0 ; i < keySize ; i++){
		output = ((output + 1) * ((size_t) key[i])) & ~(output - 1);
	}

	return output;
}



void * _gdsTableGetPtr(void * tPtr, void * keyPtr, size_t keySize)
{
	_GdsTableTemplate * t = tPtr;

	size_t bucketIndex = (_gdsTableHashFunction(keyPtr, keySize)) % t->hashArraySize;

	if (t->hashArray[bucketIndex] == NULL){
		return NULL;
	}

	GDS_LIST_FOR(t->hashArray[bucketIndex], i, it,{

			if (memcmp(*it, keyPtr, keySize) != 0){
				continue;
			}

			void * valuePtr = ((char *) *it) + keySize;
			return valuePtr;
	});

	return NULL;
}



int _gdsTableGet(void * tPtr, void * keyPtr, void * dstValuePtr, size_t keySize, size_t valueSize)
{
	void * valuePtr = _gdsTableGetPtr(tPtr, keyPtr, keySize);

	if (valuePtr == NULL){
		return EXIT_FAILURE;
	}

	memcpy(dstValuePtr, valuePtr, valueSize);

	return EXIT_SUCCESS;
}



void _gdsTableSet(void * tPtr, void * keyPtr, void * valuePtr, size_t keySize, size_t valueSize)
{
	_GdsTableTemplate * t = tPtr;

	size_t bucketIndex = (_gdsTableHashFunction(keyPtr, keySize)) % t->hashArraySize;

	if (t->hashArray[bucketIndex] == NULL){
		t->hashArray[bucketIndex] = gdsListNew();
	}

	GDS_LIST_FOR(t->hashArray[bucketIndex], i, it,{

			if (memcmp(*it, keyPtr, keySize) != 0){
				continue;
			}
			/* Key has been found */
			void * dstValuePtr = ((char *) *it) + keySize;
			memcpy(dstValuePtr, valuePtr, valueSize);
			return;
	});

	/* Key is unknown */

	struct {
		char key[keySize];
		char value[valueSize];
	} bucket;

	memcpy(&(bucket.key), keyPtr, keySize);
	memcpy(&(bucket.value), valuePtr, valueSize);

	_gdsListTemplateAppendBefore(&(t->iterator), &bucket, sizeof(bucket));
	_gdsListTemplateAppendBefore(t->hashArray[bucketIndex], &(t->iterator.firstElement), sizeof(t->iterator.firstElement));
}


int _gdsTableKeyIsKnown(void * tPtr, void * keyPtr, size_t keySize)
{
	return (_gdsTableGetPtr(tPtr, keyPtr, keySize) != NULL);
}



//int _gdsTableRemove(void * tPtr, void * keyPtr, size_t keySize, size_t valueSize);
