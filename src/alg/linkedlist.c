/*
 * =====================================================================================
 *
 *       Filename:  linkedlist.c
 *
 *    Description:  Implementation for linkedlist.h
 *
 *        Version:  1.0
 *        Created:  05/30/2013 09:08:24 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matthew Gruda
 *   Organization:  
 *
 * =====================================================================================
 */
#include "alg/linkedlist.h"
#include <stdlib.h>

struct lnode{
	struct lnode *next;
	struct lnode *prev;
	void *data;
};

struct llist{
	struct lnode *first;
	struct lnode *last;
	int size;
};

struct llist *llist_new(){
	struct llist *l = malloc(sizeof(struct llist));
	if(!l) return NULL;
	l->first = NULL;
	l->last = NULL;
	l->size = 0;
	return l;
}

static struct lnode *lnode_new(void *ptr){
	struct lnode *n = malloc(sizeof(struct lnode));
	if(!n) return NULL;
	n->data = ptr;
	n->next = NULL;
	n->prev = NULL;
	return n;
}

/* add a value to the end of the list */
void llist_push(struct llist *list, void *val){
	if(!list->first){
		struct lnode *n = lnode_new(val);
		list->first = n;
		list->last = n;
		list->size++;
		return;	
	}
	struct lnode *n = lnode_new(val), *p = list->last;
	p->next = n;
	n->prev = p;
	list->last = n;
	list->size++;
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  llist_pop
 *  Description:  removes a node from the end of the list
 * =====================================================================================
 */
void *llist_pop (struct llist *list){
	if (list->size > 1){
		struct lnode *n = list->last->prev;
		struct lnode *p = list->last;
		void *data = p->data;
		list->last = n;
		n->next = NULL;
		free(p);
		list->size--;
		return data;
	}else if(list->size == 1){
		struct lnode *n = list->last;
		void *data = n->data;
		free(n);
		list->last = NULL;
		list->first = NULL;
		list->size--;
		return data;
	}else{
		return NULL;
	}
}		/* -----  end of function llist_pop  ----- */

void *llist_get(struct llist *list, int i){
	if(list->size == 0){
		return NULL;
	}else if(list->size == 1){
		if(i == 0) return list->first->data;
		return NULL;
	}else{
		int c = 0;
		struct lnode *curr = list->first;
		lop:{
			if(curr){
				if(c == i) return curr->data;
				curr = curr->next;
			}else{
				return NULL;
			}
			c++;
		}goto lop;
	}
}

/* remove a node from the front of the list */
void *llist_unshift(struct llist *list){
	void *d = NULL;
	if(list->size == 1){
		d = list->first->data;
		free(list->first);
		list->last = NULL;
		list->first = NULL;
		list->size = 0;
		return d;
	}else if(list->size > 1){
		d = list->first->data;
		struct lnode *t = list->first->next;
		t->prev = NULL;
		free(list->first);
		list->first = t;
		list->size--;
		return d;
	}
	return NULL;
}

/*  put a node on the front of the list */
void llist_shift(struct llist *list, void *data){
	if(list->size == 0){
		struct lnode *n = lnode_new(data);
		list->last = n;
		list->first = n;
	}else{
		struct lnode *n = lnode_new(data), *t = list->first;
		t->prev = n;
		n->next = t;
		list->first = n;
	}

	list->size++;
}

int llist_size(struct llist *list){
	return list->size;
}


void llist_del(struct llist *list){
	if (list) {
		if(list->first){
			struct lnode *curr = list->first;
			int i = 0;
			for(; i < list->size; i++){
				struct lnode *tmp = curr;
				if(!tmp->next){
					free(tmp);
					break;
				}
				curr = tmp->next;
				free(tmp);
			}
		}
		free(list);
	}
}

void *llist_peek(struct llist *list){
	return (list->last != NULL) ? list->last->data : NULL;
}

void *llist_look(struct llist *list){
	return (list->first != NULL) ? list->first->data : NULL;
}


