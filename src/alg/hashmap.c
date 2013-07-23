/*
 * =====================================================================================
 *
 *       Filename:  hashmap.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/15/2013 03:26:49 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <stdlib.h>
#include "hashmap.h"
#include "darray.h"
#include <string.h>


int default_cmp(void *a, void *b){
	return strcmp(a, b);
}

uint32_t default_hash(void *a){{
	size_t len = strlen(a);
	char *key = a;
	uint32_t hash = 0;
	uint32_t i = 0;

	for(hash = i = 0; i < len; ++i){
        	hash += key[i];
        	hash += (hash << 10);
       		hash ^= (hash >> 6);
	}

	hash += (hash << 3);
	hash ^= (hash >> 11);
	hash += (hash << 15);
	return hash;
}


}



struct node{
	uint32_t hash;
	void *dat;
	void *key;
};

struct hashmap{
	hashmap_hash hashf;
	hashmap_cmp cmpf;
	struct darray **buckets;
};

struct hashmap *hashmap_new(hashmap_cmp cmpf, hashmap_hash hashf){
	struct hashmap *map = malloc(sizeof(struct hashmap));
	if(!map) return NULL;

	map->cmpf = cmpf;
	map->hashf = hashf;
	map->buckets = calloc(sizeof(struct darray *), HMAP_DEF_SZ);
	if(!map->buckets){
		free(map);
		return NULL;
	}
	return map;
}

static struct darray *get_bucket(struct hashmap *map, uint32_t hash, int create){
	int bucketn = hash % HMAP_DEF_SZ;

	struct darray *bucket = *(map->buckets + bucketn);

	if(!bucket && create == 1){
		bucket = darray_new();
		*(map->buckets+bucketn) = bucket;
	}

	return bucket;
//error:
//	return NULL;
}

static struct node *node_new(uint32_t hash, void *key, void *dat){
	struct node *n = malloc(sizeof(struct node));
	
	n->key = key;
	n->dat = dat;
	n->hash = hash;

	return n;
//error:
//	return NULL;
}

int hashmap_set(struct hashmap *map, void *key, void *data){
	uint32_t hash = map->hashf(key);
	struct darray *bucket = get_bucket(map, hash, 1);
//	check(bucket, "no bucket");

	struct node *n = node_new(hash, key, data);
//	check_mem(n);
	
	darray_add(bucket, n);

	return 0;
//error:
//	return -1;

}

static int get_node(struct darray *bucket, struct hashmap *map, void *key, uint32_t hash){
	int i = 0;
	struct node *node = NULL;
	for(i = 0; i < darray_usize(bucket); i++){
		node = darray_get(bucket, i);
		if(node->hash == hash){
			if(map->cmpf(key, node->key) == 0){
				return i;
			}
		}
	}
	return -1;
}

void *hashmap_get(struct hashmap *map, void *key){
	uint32_t hash = map->hashf(key);
	struct darray *bucket = get_bucket(map, hash, 0);
	if(!bucket) return NULL;
	int i = get_node(bucket, map, key, hash);
	if(i == -1) return NULL;

	return ((struct node *)darray_get(bucket, i))->dat;

}

int hashmap_trav(struct hashmap *map, hashmap_traverse travf){
	int i = 0;
	int c = 0;
	int rc = 0;

	for(i = 0; i < HMAP_DEF_SZ; i++){
		struct darray *b = *(map->buckets+i);
		if(b){
			for(c = 0; c < darray_usize(b); c++){
				struct node *n = darray_get(b, c);
				rc = travf(n->key, n->dat);
				if(rc != 0) return rc;
			}
		}
	}
	return 0;


}

void hashmap_del(struct hashmap *map){
	if(map){
		if(map->buckets){
			int i = 0;
			int c = 0;	
			for(i = 0; i < HMAP_DEF_SZ; i++){
				struct darray *b = *(map->buckets+i);
				if(b){
					for(c = 0; c < darray_usize(b); c++){
	//					log_info("freeing node %d", c);
						free(darray_get(b, c));
					}
	///				log_info("freeing bucket %d", i);
					darray_del(b);
				}
			}
			free(map->buckets);
		}
		free(map);
	}
}
