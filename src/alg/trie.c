/*
 * =====================================================================================
 *
 *       Filename:  trie.c
 *
 *    Description:  Implementation of a trie data structure
 *
 *        Version:  1.0
 *        Created:  09/26/2013 08:11:45 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matthew Gruda (mg), matthewgruda@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include "alg/trie.h"
#include "alg/darray.h"
#include <string.h>
#include <stdlib.h>

struct node{
	struct node *bel;
	void *dat;
	unsigned int dpt, nbel;
	char *s;
	char c;
};

struct trie{
	struct node *root;	
};

struct trie *trie_new(){
	struct trie *t = malloc(sizeof(struct trie));
	t->root = calloc(sizeof(struct node), 1);
	return t;
}

struct trie *trie_newa(char **strs, void **val, unsigned int sz){
	struct trie *t = trie_new();
	unsigned int i = 0;
	while(i < sz){
		trie_add(t, strs[i], val[i]);
	}
	return t;
}

int has_bel(struct node *n, char c){
	if(n->nbel == 0) return FALSE;
	int i = 0;
	for(i = 0; i < n->nbel; i++){
		if((n->bel+i)->c == c) return i;
	}
	return FALSE;
}



void trie_add(struct trie *t, char *s, void *dat){
	
}

void *trie_get(struct trie *t, char *s);

void trie_del(struct trie *t);


