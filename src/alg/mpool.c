/*
 * =============================================================================
 *
 *       Filename:  mpool.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/10/2016 03:12:09 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matthew Gruda (mg), matthewgruda@gmail.com
 *   Organization:  
 *
 * =============================================================================
 */

#include <stdio.h>
#include "alg/mpool.h"
#define LOG_FILE stderr
#include "logger.h"
#include "dbg.h"

#define BLOCK_SZ 4096

struct mpool_node *mp_new(int blocsz, int perbloc){
	struct mpool_node *fnode = malloc(sizeof(struct mpool_node));
	check_mem(fnode);
	fnode->mem = malloc(blocsz * sizeof(uint8_t));
	check_mem(fnode->mem);
	fnode->used = calloc(perbloc, sizeof(uint8_t));
	check_mem(fnode->used);
	fnode->size = perbloc;
	fnode->inuse = 0;
	fnode->next = NULL;
	return fnode;
}

void mp_free(struct mpool_node *n){
	free(n->mem);
	free(n->used);
	free(n);
}

struct mpool_node *mp_atleast(int num, size_t size){
	int perbloc = BLOCK_SZ / size;
	int nexnodes  = num / perbloc;

	struct mpool_node *fnode = mp_new(BLOCK_SZ, perbloc);
	struct mpool_node *curr = fnode;

	for(int i = 0; i < nexnodes; i++){
		struct mpool_node *nnode = mp_new(BLOCK_SZ, perbloc); 
		curr->next = nnode;
		curr = nnode;
	}
	return fnode;
}

void mpn_count(struct mpool_node *mn, int *t_spaces, int *u_spaces){
	struct mpool_node *curr = mn;
	*t_spaces = 0;
	*u_spaces = 0;
	for(; curr != NULL; curr = curr->next){
		*t_spaces += curr->size;
		*u_spaces += curr->inuse;
	}
}

void mpool_count(mpool *mp, int *t_spaces, int *u_spaces){
	return mpn_count(mp->next, t_spaces, u_spaces);
}

mpool *mpool_create(size_t szof, int align, int dsz){
	mpool *mp = malloc(sizeof(mpool));
	check_mem(mp);
	mp->szof = szof % align == 0 ? szof : 
		((szof / align) * align) + align;
	mp->align = align;
	mp->next = mp_atleast(mp->szof, dsz);
	log_add("mp->next = %p", mp->next);
	return mp;
}

void *mpool_alloc(mpool *mp){
	struct mpool_node *curr = mp->next;
	while(curr->inuse == curr->size){
		curr = curr->next;
	}
	int idx = 0;
	while(*(curr->used + idx)) idx++;
	void *ret = curr->mem + mp->szof * idx;
	*(curr->used + idx) = 1;
	curr->inuse++;
	return ret;
}

void mpool_free(mpool *mp, void *tdel){
	struct mpool_node *curr = mp->next;
	while( curr && (tdel - (void *)curr->mem) > curr->size * mp->szof ){
		curr = curr->next;
	}
	check(curr != NULL, "Tried to free a non-existent ptr");
	int idx = (tdel - ((void *)curr->mem)) / mp->szof;
	*(curr->used + idx) = 0;
	curr->inuse--;
}

void mpool_destroy(mpool *mp){
	struct mpool_node *curr, *next;
	curr = mp->next;
	while(curr != NULL){
		next = curr->next;
		mp_free(curr);
		curr = next;
	}
	free(mp);
}










