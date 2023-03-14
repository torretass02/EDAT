//--------------------------------------------------------------------------
// Dequeue implementation with (void *)
//--------------------------------------------------------------------------

#include "dequeue.h"
#include <stdio.h>
#include <stdlib.h>

#ifndef MAX_DEQUEUE
#define MAX_DEQUEUE 40
#endif

struct _Dequeue {
  void *data[MAX_DEQUEUE];
  int front;
  int rear;
  Bool is_empty;
};

//--------------------------------------------------------------------------
// Private functions:
//--------------------------------------------------------------------------
Bool _dequeue_isFull(const Dequeue *q);

//--------------------------------------------------------------------------
Dequeue *dequeue_new() {
  Dequeue *q = NULL;
  int i;

  // Allocate Dequeue:
  q = (Dequeue *)malloc(sizeof(Dequeue));
  if (q == NULL) {
    return NULL;
  }

  // Initialize data pointers, front, rear and is_empty:
  for (i = 0; i < MAX_DEQUEUE; i++) {
    q->data[i] = NULL;
  }
  q->front = 0;
  q->rear = 0;
  q->is_empty = TRUE;

  return q;
}

//--------------------------------------------------------------------------
void dequeue_free(Dequeue *q) { free(q); }

//--------------------------------------------------------------------------
Bool dequeue_isEmpty(const Dequeue *q) {
  if (q == NULL) {
    return TRUE;
  }
  return q->is_empty;
}

//--------------------------------------------------------------------------
Bool _dequeue_isFull(const Dequeue *q) {
  if (q == NULL) {
    return TRUE;
  }
  if (q->is_empty == FALSE && q->front == q->rear) {
    return TRUE;
  }
  return FALSE;
}

//--------------------------------------------------------------------------
Status dequeue_pushBack(Dequeue *q, const void *ele) {
  if (q == NULL || ele == NULL || _dequeue_isFull(q) == TRUE) {
    return ERROR;
  }

  q->data[q->rear] = (void *)ele;
  q->rear = (q->rear + 1) % MAX_DEQUEUE;
  q->is_empty = FALSE;

  return OK;
}

//--------------------------------------------------------------------------
void *dequeue_popFront(Dequeue *q) {
  void *e = NULL;

  if (q == NULL || dequeue_isEmpty(q) == TRUE) {
    return NULL;
  }

  e = q->data[q->front];
  q->data[q->front] = NULL;
  q->front = (q->front + 1) % MAX_DEQUEUE;

  if (q->front == q->rear) {
    q->is_empty = TRUE;
  }

  return e;
}
//
//--------------------------------------------------------------------------
void *dequeue_getFront(const Dequeue *q) {
  if (q == NULL || dequeue_isEmpty(q) == TRUE) {
    return NULL;
  }

  return q->data[q->front];
}

//--------------------------------------------------------------------------
void *dequeue_getBack(const Dequeue *q) {
  int last_elem;

  if (q == NULL || dequeue_isEmpty(q) == TRUE) {
    return NULL;
  }

  last_elem = (MAX_DEQUEUE + q->rear - 1) % MAX_DEQUEUE;
  return q->data[last_elem];
}

//--------------------------------------------------------------------------
void *dequeue_popBack(Dequeue *q){
  if (q == NULL) return NULL; // deque nulo
  
  if (q->is_empty) return NULL; // deque vacío
  
  void *elem = q->data[q->rear];
  
  if (q->front == q->rear) { // si el deque tenía un solo elemento
    q->front = -1;
    q->rear = -1;
    q->is_empty = TRUE;
  } 
  else{
    q->rear = (q->rear + MAX_DEQUEUE - 1) % MAX_DEQUEUE;
  }
  return elem;
}
 

//--------------------------------------------------------------------------
Status dequeue_pushFront(Dequeue *q, const void *elem){ 
  if (q == NULL) return ERROR; // deque nulo
    if (q->is_empty == TRUE) { // si el deque está vacío
        q->front = 0;
        q->rear = 0;
        q->data[0] = (void *) elem;
        q->is_empty = FALSE;
    } 
    else if (_dequeue_isFull(q) == TRUE) { // si el deque está lleno
      return ERROR;
    } 
    else { // si el deque tiene elementos pero no está lleno
      q->front = (q->front + MAX_DEQUEUE - 1) % MAX_DEQUEUE;
      0  q->data[q->front] = (void *) elem;
    }
    return OK; 
}

//--------------------------------------------------------------------------
size_t dequeue_size(const Dequeue *q) {
  if (q == NULL)
    return 0;
  if (dequeue_isEmpty(q) == TRUE)
    return 0;
  if (q->rear == q->front)
    return MAX_DEQUEUE;
  return (MAX_DEQUEUE + q->rear - q->front) % MAX_DEQUEUE;
}

//--------------------------------------------------------------------------
int dequeue_print(FILE *fp, const Dequeue *q, print_elem_fn print_elem) {
  int i;

  if (fp == NULL || q == NULL || print_elem == NULL) {
    return -1;
  }

  i = q->front;
  if (_dequeue_isFull(q)) {
    print_elem(fp, q->data[i]);
    i = (i + 1) % MAX_DEQUEUE;
  }

  while (i != q->rear) {
    print_elem(fp, q->data[i]);
    i = (i + 1) % MAX_DEQUEUE;
  }

  fprintf(fp, "\n");

  return 0;
  fprintf(fp, "\n");

  return 0;
}
