/*
 * =====================================================================================
 *
 *       Filename:  intBuffer.h
 *
 *    Description:  This implements a resizeable array of ints. It should be rather fast
 *    		    althogh it uses malloc/realloc ... maybe mem pool later
 *
 *        Version:  1.0
 *        Created:  05/30/2013 03:17:02 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matthew Gruda 
 *   Organization:  
 *
 * =====================================================================================
 */


#ifndef _INTBUFFER_H
#define _INTBUFFER_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define DEFAULT_INCIB 20
#define DEFAULT_SIZEIB 100

struct ibuf{
	int tsize, usize, incsz;
	int *arr;
};

static inline struct ibuf *ibuf_new0i(){
	struct ibuf* buf = (struct ibuf *)malloc(sizeof(struct ibuf));
	if(!buf) return NULL;
	buf->tsize = DEFAULT_SIZEIB;
	buf->usize = 0;
	buf->incsz = DEFAULT_INCIB;
	buf->arr = malloc(sizeof(int) * DEFAULT_SIZEIB);
	if(!buf->arr){
		free(buf);
		return NULL;
	}
	return buf;
}

static inline struct ibuf *ibuf_new1i(int initalsz){
	struct ibuf* buf = (struct ibuf *)malloc(sizeof(struct ibuf));
	if(!buf) return NULL;
	buf->tsize = initalsz;
	buf->usize = 0;
	buf->incsz = DEFAULT_INCIB;
	buf->arr = malloc(sizeof(int) * initalsz);
	if(!buf->arr){
		free(buf);
		return NULL;
	}
	return buf;
}

static inline struct ibuf *ibuf_new2i(int initalsz, int incsz){
	struct ibuf* buf = (struct ibuf *)malloc(sizeof(struct ibuf));
	if(!buf) return NULL;
	buf->tsize = initalsz;
	buf->usize = 0;
	buf->incsz = incsz;
	buf->arr = malloc(sizeof(int) * initalsz);
	if(!buf->arr){
		free(buf);
		return NULL;
	}
	return buf;
}

static inline void ibuf_print(struct ibuf *buf){
	int i = 0;
	printf("tsize=%d usize=%d arr:",buf->tsize, buf->usize);
	for (; i < buf->usize; i++){
		printf("%d, ", *(buf->arr + i));
	}
	printf("\n");
}

static inline void ibuf_putAll(struct ibuf *buf, int len, int *arr){
	if(len+buf->usize-1 > buf->tsize){
		buf->arr = (int *) realloc(buf->arr, sizeof(int) * (buf->tsize + len));
		buf->tsize += len;	
	}
	memcpy(buf->arr+buf->usize, arr, sizeof(int)*len);
	buf->usize += len;
}

static inline void ibuf_put(struct ibuf *buf, int f){
	*(buf->arr+buf->usize) = f;
	buf->usize++;
	if(buf->usize == buf->tsize - 1){
		buf->arr = (int *) realloc(buf->arr,sizeof(int)* (buf->tsize + buf->incsz));
		buf->tsize += buf->incsz;
	}
}

#define IB_GET(A, B) *(A->arr + B)

static inline int ibuf_get(struct ibuf *buf, int i){
	if(i < 0 || i > buf->usize) return 0;
	return *(buf->arr + i);
}

#define IB_SET(A, B, C) *(A->arr+B) = C

static inline void ibuf_set(struct ibuf *buf, int i, int f){
	if(i < 0 || i > buf->usize || !buf->arr) return;
	*(buf->arr+i) = f;
}
static inline void ibuf_trim(struct ibuf *buf){
	buf->arr = (int *) realloc(buf->arr, sizeof(int)*buf->usize);
	buf->tsize = buf->usize;
}


static inline void ibuf_clear(struct ibuf *buf){
	buf->usize = 0;
	ibuf_trim(buf);
}

static inline ibuf_del(struct ibuf *buf){
	free(buf->arr);
	free(buf);
}

#define IB_TSIZE(A) A->tsize

static inline int *ibuf_tsize(struct ibuf *buf){
	return &(buf->tsize);
}

#define IB_USIZE(A) A->usize

static inline int *ibuf_usize(struct ibuf *buf){
	return &(buf->usize);
}

#endif
