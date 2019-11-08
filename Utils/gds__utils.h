/*
 * gds_utils.h
 *
 *  Created on: 18 janv. 2019
 *      Author: ajuvenn
 */

#ifndef GDS__UTILS_H_
#define GDS__UTILS_H_

#include "../gds__include.h"

#define GDS_SIMPLE_ALLOC(ptr, nb_elements)\
	do {\
	if ((nb_elements) == 0){\
		fprintf(stderr, "GDS_SIMPLE_ALLOC (in %s) : received 0 as number of elements\n", __FUNCTION__);\
		exit(EXIT_FAILURE);\
	}\
	(ptr) = malloc((nb_elements) * sizeof(*(ptr)));\
	if ((ptr) == NULL){\
		fprintf(stderr, "GDS_SIMPLE_ALLOC (in %s) : malloc returned NULL\n", __FUNCTION__);\
		exit(EXIT_FAILURE);\
	}\
	} while (0)



#define GDS_SIMPLE_REALLOC(dst, src, nb_elements)\
	do {\
	if ((nb_elements) == 0){\
		fprintf(stderr, "GDS_SIMPLE_REALLOC (in %s) : received 0 as number of elements\n", __FUNCTION__);\
		exit(EXIT_FAILURE);\
	}\
	(dst) = realloc((src), (nb_elements) * sizeof(*(dst)));\
	if ((dst) == NULL){\
		fprintf(stderr, "GDS_SIMPLE_REALLOC (in %s) : realloc returned NULL\n", __FUNCTION__);\
		exit(EXIT_FAILURE);\
	}\
	} while (0)



#define GDS_ELTYPEOF(xPtr) typeof(*((xPtr)->elements))

#define GDS_ELSIZEOF(xPtr) sizeof(*((xPtr)->elements))



#endif /* GDS_UTILS_H_ */
