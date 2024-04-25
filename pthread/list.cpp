#include "list_lock.h"

#include <stdio.h>
#include <stdlib.h>

void listInit(list_lock_t* list) {
   //perror("This function is not implemented");
   list->head = NULL;
   pthread_mutex_init(&(list->mutex), NULL);
   pthread_cond_init((&list->cond), NULL);
}

void producer(list_lock_t* list, DataType value) {
  //perror("This function is not implemented");
  LNode * new_node = (LNode*)malloc(sizeof(LNode));
  if(new_node == NULL) 
  {
    perror("malloc error");
    return;
  }
  new_node->value = value;
  pthread_mutex_lock(&(list->mutex));
  new_node->next=list->head;
  list->head = new_node;
  pthread_cond_signal(&(list->cond));
  pthread_mutex_unlock(&(list->mutex));
}

void consumer(list_lock_t* list) {
   //perror("This function is not implemented");
   pthread_mutex_lock(&(list->mutex));
   while(list->head == NULL) {
     pthread_cond_wait(&(list->cond), &(list->mutex));
   }
   LNode * node = list->head;
   DataType value = node->value;
   list->head = list->head->next;
   free(node);
   pthread_mutex_unlock(&(list->mutex));
}

int getListSize(list_lock_t* list) {
  //perror("This function is not implemented");
  int size = 0;
  pthread_mutex_lock(&(list->mutex));
  LNode *current = list->head;
  while(current!= NULL) 
  {
    size++;
    current = current->next;
  }
  pthread_mutex_unlock(&(list->mutex));
  return size;
}