/*
 * =============================================================================
 *
 *       Filename:  mpool.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/10/2016 03:07:58 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matthew Gruda (mg), matthewgruda@gmail.com
 *   Organization:  
 *
 * =============================================================================
 */

#ifndef _MPOOL_H
#define _MPOOL_H

#include <stdint.h>
#include <stdlib.h>

struct mpool_node{
	uint8_t *mem;
	uint8_t *used;
	struct mpool_node *next;
	int    size, inuse;
};

struct mpool{
	size_t szof;
	int align;
	struct mpool_node *next;

};

typedef struct mpool mpool;

mpool *mpool_create(size_t szof, int align, int dsz);

void *mpool_alloc(mpool *mp);

void mpool_free(mpool *mp, void *tdel);

void mpool_destroy(mpool *mp);

void mpool_count(mpool *mp, int *t_spaces, int *u_spaces);

#endif 





