/*
 * =====================================================================================
 *
 *       Filename:  floatBuffer.h
 *
 *    Description:  This implements a resizeable array of floats. It should be rather fast
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


#ifndef _FLOATBUFFER_H
#define _FLOATBUFFER_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define DEFAULT_INCFB 20
#define DEFAULT_SIZEFB 100

struct fbuf{
	int tsize, usize, incsz;
	float *arr;
};

static inline struct fbuf *fbuf_new0i(){
	struct fbuf* buf = (struct fbuf *)malloc(sizeof(struct fbuf));
	if(!buf) return NULL;
	buf->tsize = DEFAULT_SIZEFB;
	buf->usize = 0;
	buf->incsz = DEFAULT_INCFB;
	buf->arr = malloc(sizeof(float) * DEFAULT_SIZEFB);
	if(!buf->arr){
		free(buf);
		return NULL;
	}
	return buf;
}

static inline struct fbuf *fbuf_new1i(int initalsz){
	struct fbuf* buf = (struct fbuf *)malloc(sizeof(struct fbuf));
	if(!buf) return NULL;
	buf->tsize = initalsz;
	buf->usize = 0;
	buf->incsz = DEFAULT_INCFB;
	buf->arr = malloc(sizeof(float) * initalsz);
	if(!buf->arr){
		free(buf);
		return NULL;
	}
	return buf;
}

static inline struct fbuf *fbuf_new2i(int initalsz, int incsz){
	struct fbuf* buf = (struct fbuf *)malloc(sizeof(struct fbuf));
	if(!buf) return NULL;
	buf->tsize = initalsz;
	buf->usize = 0;
	buf->incsz = incsz;
	buf->arr = malloc(sizeof(float) * initalsz);
	if(!buf->arr){
		free(buf);
		return NULL;
	}
	return buf;
}

static inline void fbuf_print(struct fbuf *buf){
	int i = 0;
	printf("tsize=%d usize=%d arr:",buf->tsize, buf->usize);
	for (; i < buf->usize; i++){
		printf("%lf, ", *(buf->arr + i));
	}
	printf("\n");
}

static inline void fbuf_putAll(struct fbuf *buf, int len, float *arr){
	if(len+buf->usize-1 > buf->tsize){
		buf->arr = (float *) realloc(buf->arr, sizeof(float) * (buf->tsize + len));
		buf->tsize += len;	
	}
	memcpy(buf->arr+buf->usize, arr, sizeof(float)*len);
	buf->usize += len;
}

static inline void fbuf_put(struct fbuf *buf, float f){
	*(buf->arr+buf->usize) = f;
	buf->usize++;
	if(buf->usize == buf->tsize - 1){
		buf->arr = (float *) realloc(buf->arr,sizeof(float)* (buf->tsize + buf->incsz));
		buf->tsize += buf->incsz;
	}
}

#define FB_GET(A, B) *(A->arr + B)

static inline float fbuf_get(struct fbuf *buf, int i){
	if(i < 0 || i > buf->usize) return 0;
	return *(buf->arr + i);
}

#define FB_SET(A, B, C) *(A->arr+B) = C

static inline void fbuf_set(struct fbuf *buf, int i, float f){
	if(i < 0 || i > buf->usize || !buf->arr) return;
	*(buf->arr+i) = f;
}

static inline void fbuf_trim(struct fbuf *buf){
	buf->arr = (float *) realloc(buf->arr, sizeof(float)*buf->usize);
	buf->tsize = buf->usize;
}


static inline void fbuf_clear(struct fbuf *buf){
	buf->usize = 0;
	fbuf_trim(buf);
}
static inline fbuf_del(struct fbuf *buf){
	free(buf->arr);
	free(buf);
}

#define FB_TSIZE(A) A->tsize

static inline int *fbuf_tsize(struct fbuf *buf){
	return &(buf->tsize);
}

#define FB_USIZE(A) A->usize

static inline int *fbuf_usize(struct fbuf *buf){
	return &(buf->usize);
}

#endif
