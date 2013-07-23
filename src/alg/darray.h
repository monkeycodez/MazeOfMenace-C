/*
 * =====================================================================================
 *
 *       Filename:  darray.h
 *
 *    Description:  header for darray
 *
 *        Version:  1.0
 *        Created:  06/28/2013 08:08:45 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matthew Gruda
 *   Organization:  
 *
 * =====================================================================================
 */


#ifndef _DARRAY_H
#define _DARRAY_H

#define DARRAY_DEFAULT_SZ 100
#define DARRAY_DEFAULT_INC 50

struct darray;

struct darray *darray_new();

struct darray *darray_new1i(int defsz);

struct darray *darray_new2i(int defsz, int inc);

void darray_add(struct darray *arr, void *dat);

void darray_set(struct darray *arr, void *dat, unsigned int idx);

void *darray_get(struct darray *arr, unsigned int idx);

int darray_usize(struct darray *arr);

void darray_clear(struct darray *arr);

void darray_trim(struct darray *arr);

void *darray_remove(struct darray *arr, int idx);

void darray_del(struct darray *arr);

void darray_sort(struct darray *arr, int (*compare_func)(void *l, void *r));

int darray_search(struct darray *arr, void *dat);

int darray_bsearchFunc(struct darray *arr, void *dat, int (*equal_func)(void *a, void *b));

#endif
