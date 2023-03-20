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
    float *n1, *n2;
    
    while(stack_isEmpty(sin1)==FALSE && stack_isEmpty(sin2)==FALSE){
        n1 = stack_top(sin1);
        n2 = stack_top(sin2);
        if(*n1>*n2){
            e = stack_pop(sin1);
        }
        else{
            e = stack_pop(sin2);
        }
        if(stack_push(sout, e)==ERROR) return ERROR;
    }
    if(stack_isEmpty(sin1)==TRUE){
        ps = sin2;
    }
    else{
        ps = sin1;
    }
    while(stack_isEmpty(sout)==FALSE){
        e = stack_pop(ps);
        if(stack_push(sout, e)==ERROR)return ERROR;
        break;
    }
    
    return OK;
}

int main(int argc, char**argv){
    FILE *f1, *f2;
    int num_grades;
    char desc[1024];
    Stack *s1, *s2, *merged;
    float *array1, *array2;
    
    if(argc < 3){
        printf("ERROR, debe incluir más argumentos.\n");
        return -1;
    }

    if(argc > 3){
        printf("ERROR, ha introducido demasiados argumentos.\n");
        return -1;
    }

    s1 = stack_init();
    if(!s1){
        stack_free(s1);
        return -1;
    }

    s2 = stack_init();
    if(!s2){
        stack_free(s1);
        stack_free(s2);
        return -1;
    }

    merged = stack_init();
    if(!merged){
        stack_free(s1);
        stack_free(s2);
        stack_free(merged);
        return -1;
    }

    f1 = fopen(argv[1], "r");
    if(!f1){
        printf("ERROR, el nombre del archivo 1 es incorrecto.\n"); 
        return -1;
    }

    fgets(desc, 1024, f1);
    sscanf(desc, "%d", &num_grades);

    array1 = malloc(sizeof(float)*num_grades);

    for(int i = 0; i<num_grades; i++){
        fgets(desc, 1024, f1);
        sscanf(desc, "%f", &array1[i]);
    }

    for(int i = 0; i<num_grades; i++){
        if(stack_push(s1, &array1[i])==ERROR) return -1;
    }

    printf("Ranking 0:\n");

    stack_print(stdout, s1, float_print);
    
    f2 = fopen(argv[2], "r");
    if(!f2){
        printf("ERROR, el nombre del archivo 2 es incorrecto.\n"); 
        return -1;
    }

    fgets(desc, 1024, f2);
    sscanf(desc, "%d", &num_grades);

    array2 = malloc(sizeof(float)*num_grades);

    for(int i = 0; i<num_grades; i++){
        fgets(desc, 1024, f2);
        sscanf(desc, "%f", &array2[i]);
    }

    for(int i = 0; i<num_grades; i++){
        if(stack_push(s2, &array2[i])==ERROR) return -1;
    }

    printf("Ranking 1:\n");

    stack_print(stdout, s2, float_print);

    if(mergeStacks(s1, s2,merged)==ERROR){
        stack_free(s1);
        stack_free(s2);
        stack_free(merged);
        float_free(array1);
        float_free(array2);
        fclose(f1);
        fclose(f2);
        return -1;
    }
    printf("Joint Ranking:\n");
    
    stack_print(stdout, merged, float_print);

    stack_free(s1);
    stack_free(s2);
    stack_free(merged);
    float_free(array1);
    float_free(array2);
    fclose(f1);
    fclose(f2);
}