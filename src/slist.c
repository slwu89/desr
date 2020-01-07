/* --------------------------------------------------------------------------------
#
#   Discrete Event Simultion: A First Course
#   Single-linked list
#   Sean Wu (slwu89@berkeley.edu)
#   January 2019
#
-------------------------------------------------------------------------------- */

#include "slist.h"


/* --------------------------------------------------------------------------------
#   initialize the list to point to null
-------------------------------------------------------------------------------- */

void init_int_slist(int_slist* list){
  list->head = NULL;
  list->tail = NULL;
};


/* --------------------------------------------------------------------------------
#   append data to the list
-------------------------------------------------------------------------------- */

void add_int_slist(int_slist* list, int val){

  /* the new data node */
  int_node* node = (int_node*)malloc(sizeof(int_node));
  node->value = val;
  node->next = NULL;

  /* if the list empty, append at the head */
  if(list->head == NULL){
    list->head = node;
  /* if not empty, find the old tail and make it point to the new node */
  } else {
    list->tail->next = node;
  }

  /* now set the new tail equal to the new node */
  list->tail = node;
};

/* --------------------------------------------------------------------------------
#   free the list
-------------------------------------------------------------------------------- */

void free_int_slist(int_slist* list){

  int_node* current;

  while(list->head != NULL){
     current = list->head;
     list->head = list->head->next;
     free(current);
  }
};
