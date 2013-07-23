/*
 * =====================================================================================
 *
 *       Filename:  darray.c
 *
 *    Description:  Dynamic array implementaion
 *
 *        Version:  1.0
 *        Created:  06/28/2013 08:08:01 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matthew Gruda
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "darray.h"

struct darray{
	void **dat;
	unsigned int tsize, usize, inc;
};

struct darray *darray_new(){
	return darray_new2i(DARRAY_DEFAULT_SZ, DARRAY_DEFAULT_INC);
}

struct darray *darray_new1i(int defsz){
	return darray_new2i(defsz, DARRAY_DEFAULT_INC);
}

struct darray *darray_new2i(int defsz, int inc){
	struct darray *n = (struct darray *)malloc(sizeof(struct darray));
	if(!n) return NULL;
	n->inc = inc;
	n->tsize = defsz;
	n->usize = 0;
	n->dat = malloc(defsz * sizeof(void *));
	if(!n->dat){
		free(n);
		return NULL;
	}
	return n;
}

void darray_add(struct darray *arr, void *dat){
	if(arr->tsize == arr->usize){
		arr->dat = realloc(arr->dat, sizeof(void *)* (arr->tsize+arr->inc));
		arr->tsize += arr->inc;
	}
	*(arr->dat + arr->usize) = dat;
	arr->usize++;
}

void darray_set(struct darray *arr, void *dat, unsigned int idx){
	if(idx < arr->usize){
		*(arr->dat + idx) = dat;
	}
}

void *darray_get(struct darray *arr, unsigned int idx){
	if(0 <= idx && idx  < arr->usize){
		return *(arr->dat + idx);
	}
	return NULL;
}

int darray_usize(struct darray *arr){
	return arr->usize;
}

void darray_trim(struct darray *arr){
	arr->dat = realloc(arr->dat, sizeof(void *) * arr->usize);
}

void *darray_remove(struct darray *arr, int idx){
	void *tmp = darray_get(arr, idx);
	if(!tmp) return NULL;
	memcpy(arr->dat+idx, arr->dat+idx+1, sizeof(void *) * (arr->tsize - idx - 1));
	arr->usize--;
	return tmp;
}

void darray_del(struct darray *arr){
	if(arr){
		if(arr->dat){
			free(arr->dat);
		}
		free(arr);
	}
}

void darray_sort(struct darray *arr, int (*compare_func)(void *l, void *r)){
	if(arr->usize <= 1) return;
	int n = arr->usize;
	for(; n > 1; n--){
		int im = 0, i = 1;
		for(; i < n; i++){
			if(compare_func(arr->dat[i], arr->dat[im]) > 0){
				im = i;
			}
		}
		void *tmp = arr->dat[im];
		arr->dat[im] = arr->dat[n-1];
		arr->dat[n-1] = tmp;
	}
}

int darray_search(struct darray *arr, void *dat){
	unsigned int i = 0;
	while(i < arr->usize){
		if(*(arr->dat+i) == dat) return i;
		i++;
	}
	return -1;
}

int darray_bsearchFunc(struct darray *arr, void *dat, int (*equal_func)(void * a, void *b)){
	int i = arr->usize / 2;
	int top = arr->usize - 1, bot = 0;
	int comp = 0;
	while(1){
		comp = equal_func(dat, *(arr->dat+i));
		if(comp == 0){
			return i;
		}else if(comp < 0){
			if(i == top || i == bot) break;
			top = i;
			i = (top-bot) / 2;
		}else if(comp > 0){
			if(i == top || i == bot) break;
			bot = i;
			i = (top - bot)/ 2;
		}
	}
	
	return -1;
}

void darray_clear(struct darray *arr){
	arr->usize = 0;
}
