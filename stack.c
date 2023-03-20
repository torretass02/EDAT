#include "stack.h"
#include "file_utils.h"
#include "graph.h"

#define INIT_CAPACITY 2 // init stack capacity
#define FCT_CAPACITY 2 // multiply the stack capacity

struct _Stack {
 void **item; /*!<Static array of elements*/
 int top; /*!<index of the top element in the stack*/
 int capacity; /*!<xcapacity of the stack*/
};

Bool _stack_isFull (const Stack *s);

Bool _stack_isFull (const Stack *s){
    if (s == NULL) {
        return TRUE;
    }
    if (s ->top == s->capacity - 1) {
        return TRUE;
    }
    return FALSE;
}

Stack * stack_init (){
    Stack *ps = NULL;
    int i;
    ps = (Stack *) malloc(sizeof(Stack));
    if (ps == NULL) {
        return NULL;
    }

    ps->item = (void **) malloc(INIT_CAPACITY * sizeof(void *));//aqui pq pone 16, tendria que poner capacity 

    for (i = 0; i < INIT_CAPACITY ; i++) {
        ps->item[i] = NULL;
    }

    ps ->top = -1;
    ps->capacity = INIT_CAPACITY; 
    return ps;
}


void stack_free (Stack *s){
    free(s->item);
    free(s);
}

Status stack_push (Stack *s, const void *ele){
    if (s == NULL || ele == NULL) {
        return ERROR;
    }
    if (_stack_isFull(s) == TRUE) {
        void **new_item = (void **) realloc(s->item, s->capacity * FCT_CAPACITY * sizeof(void *));
        if (new_item == NULL) {
            return ERROR;
        }
        s->item = new_item;
        s->capacity *= FCT_CAPACITY;
    }
    s->top++;
    s->item[s->top] = (void *)ele;
    return OK;
}

void * stack_pop (Stack *s){
    void *e = NULL;

    if (s == NULL || stack_isEmpty (s) == TRUE) {
        return NULL;
    }
    e = s->item[s->top ];
    s->item[s->top] = NULL;
    s->top --;
    return e;
}

void * stack_top (const Stack *s){
    if (s == NULL || stack_isEmpty (s) == TRUE) {
        return NULL;
    }
    return s->item[s->top ];
}

Bool stack_isEmpty (const Stack *s){
    if (s == NULL) {
        return TRUE;
    }
    if (s->top == -1) {
        return TRUE;
    }
    return FALSE;
}

size_t stack_size (const Stack *s){
    if (!s) {
        return 0;
    }
    return s->top + 1;
}

int stack_print(FILE* fp, const Stack *s, P_stack_ele_print f) {
    if (fp == NULL || s == NULL || f == NULL) {
        return ERROR;
    }

    fprintf(fp, "SIZE: %ld\n", stack_size(s));
    
    for (int i = s->top; i >= 0; i--) {
        f(fp, s->item[i]);
        fprintf(fp, "\n");
    }
    
    return OK;
}