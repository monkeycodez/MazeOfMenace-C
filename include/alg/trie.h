/*
 * =====================================================================================
 *
 *       Filename:  trie.h
 *
 *    Description:  A "trie" data structure.  Good for associating strings
 *    			with values
 *
 *        Version:  1.0
 *        Created:  09/26/2013 07:47:51 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matthew Gruda (mg), matthewgruda@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef _TRIE_H
#define _TRIE_H

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

struct trie;

struct trie *trie_new();

struct trie *trie_newa(char **strs, void **val, unsigned int sz);

void trie_add(struct trie *t, char *s, void *dat);

void *trie_get(struct trie *t, char *s);

void trie_del(struct trie *t);

#endif
