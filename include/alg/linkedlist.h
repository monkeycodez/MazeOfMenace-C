/*
 * =====================================================================================
 *
 *       Filename:  linkedlist.h
 *
 *    Description:  Header for linked list implementation
 *
 *        Version:  1.0
 *        Created:  05/30/2013 09:08:39 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matthew Gruda
 *   Organization:  
 *
 * =====================================================================================
 */


#ifndef  _LINKEDLIST_H
#define  _LINKEDLIST_H

struct llist;

typedef struct llist llist;

struct llist *llist_new();

void llist_push(struct llist *list, void *data);

void *llist_pop(struct llist *list);

void llist_del(struct llist *list);

int llist_size(struct llist *list);

void llist_shift(struct llist *list, void *data);

void *llist_unshift(struct llist *list);

void *llist_get(struct llist *list, int i);

void *llist_peek(struct llist *list);

void *llist_look(struct llist *list);

#endif     /* -----  not _LINKEDLIST_H  ----- */
