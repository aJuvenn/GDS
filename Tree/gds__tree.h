/*
 * gds__tree.h
 *
 *  Created on: 8 nov. 2019
 *      Author: ajuvenn
 */

#ifndef TREE_GDS__TREE_H_
#define TREE_GDS__TREE_H_


#define GdsTreeNode(type) struct {type * father; type * leftSon; type * rightSon; type element;}

#define GdsTree(type) struct {type * rootElement; size_t nbElements;}




#endif /* TREE_GDS__TREE_H_ */
