#include "libstack.a"
#include "stack.h"



/**
 * @brief: Merges two stacks
 *
 * @param sin1, first input stack
 * @param sin2, second input stack
 * @param sout, result stack
 * @return The function returns OK or ERROR
**/
Status mergeStacks (Stack *sin1, Stack *sin2, Stack *sout);


Status mergeStacks (Stack *sin1, Stack *sin2, Stack *sout){
    if(!sin1 || !sin2 || !sout) return ERROR;

    Stack * ps;
    void * e;
    
    while(stack_isEmpty(sin1)==FALSE && stack_isEmpty(sin2)==FALSE){
        if(stack_top(sin1)>stack_top(sin2)){
            e = stack_pop(sin1);
        }
        else{
            e = stack_pop(sin2);
        }
        stack_push(sout, e);
    }
    if(stack_isEmpty(sin1)==TRUE){
        ps = sin2;
    }
    else{
        ps = sin1;
    }
    while(stack_isEmpty(sout)==FALSE){
        e = stack_pop(ps);
        stack_push(sout, e);
    }
    
    return OK;
}

int main(int argc, char**argv){
    FILE * f1;
    FILE * f2;

    f1 = fopen(argv[1], "r");
    if(!f1){
        printf("ERROR, el nombre del archivo 1 es incorrecto.\n"); 
        return -1;
    }

    f2 = fopen(argv[2], "r");
    if(!f1){
        printf("ERROR, el nombre del archivo 1 es incorrecto.\n"); 
        return -1;
    }
}