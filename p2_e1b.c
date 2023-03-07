#include "stack.h"
#include "file_utils.h"
#include "graph.h"


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
    Stack * s1;
    Stack * s2; 
    Stack * merged;
    Graph * g1;
    Graph *g2;
    int n1, n2;
    s1 = stack_init();
    s2 = stack_init();
    merged = stack_init();
    Vertex **vertices;

    f1 = fopen(argv[1], "r");
    if(!f1){
        printf("ERROR, el nombre del archivo 1 es incorrecto.\n"); 
        return -1;
    }

    f2 = fopen(argv[2], "r");
    if(!f2){
        printf("ERROR, el nombre del archivo 1 es incorrecto.\n"); 
        return -1;
    }

    graph_readFromFile(f1, g1);
    graph_readFromFile(f2, g2);

    n1 = graph_getNumberOfVertices(g1);
    n2 = graph_getNumberOfVertices(g2);

    vertices = graph_get_vertex(g1);

    for(int i=0; i<n1; i++){
        vertex_print(stdout, vertices[i]);
    }
    
    for(int i = 0; i<n1; i++){
        stack_push(s1, &vertices[i]);
    }
}