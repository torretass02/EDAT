#include "stack.h"
#include "file_utils.h"


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
    int *n1, *n2;
    
    while(stack_isEmpty(sin1)==FALSE && stack_isEmpty(sin2)==FALSE){
        n1 = stack_top(sin1);
        n2 = stack_top(sin2);
        if(*n1>*n2){
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
        break;
    }
    
    return OK;
}

int main(int argc, char**argv){
    FILE * f1;
    FILE * f2;
    int num_grades;
    char desc[1024];
    Stack * s1;
    Stack * s2; 
    Stack * merged;
    float * array;

    s1 = stack_init();
    s2 = stack_init();
    merged = stack_init();

    f1 = fopen(argv[1], "r");
    if(!f1){
        printf("ERROR, el nombre del archivo 1 es incorrecto.\n"); 
        return -1;
    }

    fgets(desc, 1024, f1);
    sscanf(desc, "%d", &num_grades);

    array = malloc(sizeof(float)*num_grades);

    for(int i = 0; i<num_grades; i++){
        fgets(desc, 1024, f1);
        sscanf(desc, "%f", &array[i]);
    }

    for(int i = 0; i<num_grades; i++){
        stack_push(s1, &array[i]);
    }

    printf("Ranking 0:\n");

    stack_print(stdout, s1, float_print);
    
    f2 = fopen(argv[2], "r");
    if(!f1){
        printf("ERROR, el nombre del archivo 1 es incorrecto.\n"); 
        return -1;
    }

    fgets(desc, 1024, f2);
    sscanf(desc, "%d", &num_grades);

    array = malloc(sizeof(float)*num_grades);

    for(int i = 0; i<num_grades; i++){
        fgets(desc, 1024, f2);
        sscanf(desc, "%f", &array[i]);
    }

    for(int i = 0; i<num_grades; i++){
        stack_push(s2, &array[i]);
    }

    printf("Ranking 1:\n");

    stack_print(stdout, s2, float_print);

    mergeStacks(s1, s2,merged);
    
    stack_print(stdout, merged, float_print);

    stack_free(s1);
    stack_free(s2);
    stack_free(merged);
    float_free(array);
}