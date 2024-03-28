#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
  List* list = (List*) malloc (sizeof(List));
  list->head = NULL;
  list->tail = NULL;
  list->current = NULL;
  return list;
}

void * firstList(List * list) 
{
  list->current = list->head;
  if(list->current) return list->current->data;
  return NULL;
}

void * nextList(List * list) {
  if(list->current != NULL)
    list->current = list->current->next;
  if(list->current != NULL)
    return list->current->data;
  return NULL;
}

void * lastList(List * list) {
  if(list->tail != NULL)
  {
    list->current = list->tail;
    return list->tail->data;
  }
    return NULL;
}

void * prevList(List * list) {
  if(list->current != NULL && list->current->prev != NULL)
  {
    list->current = list->current->prev;
    return list->current->data;
  }
    return NULL;
}

void pushFront(List * list, void * data) {
  Node * nuevo_nodo = createNode(data);
  if(list->head == NULL)
    {
      list->head = nuevo_nodo;
      list->tail = nuevo_nodo;
    }
  else
  {
    nuevo_nodo->next = list->head;
    list->head->prev = nuevo_nodo;
    list->head = nuevo_nodo;
  }
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
  if(list->current == NULL)
    pushFront(list ,data);
  else{
    Node * nuevo_nodo = createNode(data);
    nuevo_nodo->prev = list->current;
    nuevo_nodo->next = list->current->next;
    if(list->current->next != NULL)
      list->current->next->prev = nuevo_nodo;
    else
      {
        list->tail = nuevo_nodo;
      }
    list->current->next = nuevo_nodo;
  }
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
  if(list->current == NULL)
    return NULL;

  void * data = list->current->data;
  Node * aux = list->current;

  if(list->current == list->head)
    {
      list->head = list->head->next;
      if(list->head != NULL)
        list->head->prev = NULL;
    }
  else if(list->current == list->tail)
    {
      list->tail = list->current->prev;
      if(list->tail != NULL)
        list->tail->next = NULL;
    }
  else
    {
      list->current->prev->next = list->current->next;
      list->current->next->prev = list->current->prev;
    }

    
  list->current = list->current->next;
  free(aux);
  return data;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}