/*
 * =====================================================================================
 *
 *       Filename:  hashmap.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/15/2013 03:19:09 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */


#ifndef _HASHMAP_H
#define _HASHMAP_H

#include <stdint.h>

#define HMAP_DEF_SZ 200

typedef int (*hashmap_cmp)(void *a, void *b);
typedef uint32_t (*hashmap_hash)(void *key);
typedef int (*hashmap_traverse)(void *key, void *dat);

struct hashmap;

struct hashmap *hashmap_new(hashmap_cmp cmpf, hashmap_hash hashf);

int hashmap_set(struct hashmap *map, void *key, void *data);

void *hashmap_get(struct hashmap *map, void *key);

int hashmap_trav(struct hashmap *map, hashmap_traverse travf);

void hashmap_del(struct hashmap *map);

uint32_t default_hash(void *a);

int default_cmp(void *a, void *b);

#endif
