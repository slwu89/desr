/* --------------------------------------------------------------------------------
#
#   Discrete Event Simultion: A First Course
#   Single-linked list
#   Sean Wu (slwu89@berkeley.edu)
#   January 2019
#
-------------------------------------------------------------------------------- */

#ifndef SLIST_H
#define SLIST_H

#include <stdlib.h>
#include <stdio.h>

/* --------------------------------------------------------------------------------
#   single liked list for ints
-------------------------------------------------------------------------------- */

typedef struct _int_node {
  int value;
  struct _int_node* next;
} int_node ;

typedef struct _int_slist {
  int       size;
  int_node* head;
  int_node* tail;
} int_slist ;

/* initialize the list to point to null */
void init_int_slist(int_slist* list);

/* append data to the list */
void add_int_slist(int_slist* list, int val);

/* free the list */
void free_int_slist(int_slist* list);

#endif
