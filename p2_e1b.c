#include "stack.h"
#include "file_utils.h"
#include "vertex.h"
#include "graph.h"

typedef int (*Function_cmp)(const void *, const void*);

/**
 * @brief: Merges two stacks
 *
 * @param sin1, first input stack
 * @param sin2, second input stack
 * @param sout, result stack
 * @return The function returns OK or ERROR
**/
Status mergeStacks (Stack *sin1, Stack *sin2, Stack *sout, Function_cmp cmp);



Status mergeStacks (Stack *sin1, Stack *sin2, Stack *sout, Function_cmp cmp){
    if(!sin1 || !sin2 || !sout) return ERROR;

    Stack * ps;
    void * e;
    void *n1, *n2;
    
    while(stack_isEmpty(sin1)==FALSE && stack_isEmpty(sin2)==FALSE){
        n1 = stack_top(sin1);
        n2 = stack_top(sin2);
        if(cmp(n1, n2)>0){
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
    FILE *f1, *f2;
    Stack *s1, *s2, *merged;
    Graph *g1, *g2;
    int n1, n2;
    Vertex **vertices;

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

    g1 = graph_init();
    if(!g1){
        stack_free(s1);
        stack_free(s2);
        stack_free(merged);
        graph_free(g1);
        return -1;
    }

    g2 = graph_init();
    if(!g2){
        stack_free(s1);
        stack_free(s2);
        stack_free(merged);
        graph_free(g1);
        graph_free(g2);
        return -1;
    }

    f1 = fopen(argv[1], "r");
    if(!f1){
        printf("ERROR, el nombre del archivo 1 es incorrecto.\n"); 
        return -1;
    }

    f2 = fopen(argv[2], "r");
    if(!f2){
        printf("ERROR, el nombre del archivo 2 es incorrecto.\n"); 
        return -1;
    }

    if(graph_readFromFile(f1, g1)==ERROR){
        stack_free(s1);
        stack_free(s2);
        stack_free(merged);
        graph_free(g1);
        graph_free(g2);
        return -1;
    }

    if(graph_readFromFile(f2, g2)==ERROR){
        stack_free(s1);
        stack_free(s2);
        stack_free(merged);
        graph_free(g1);
        graph_free(g2);
        return -1;
    }

    n1 = graph_getNumberOfVertices(g1);
    n2 = graph_getNumberOfVertices(g2);

    vertices = graph_get_all_vertex(g1);
    
    for(int i = 0; i<n1; i++){
        stack_push(s1, vertices[i]);
    }

    printf("Ranking 0:\n");

    stack_print(stdout, s1, vertex_print);

    vertices = graph_get_all_vertex(g2);

    for(int i = 0; i<n2; i++){
        stack_push(s2, vertices[i]);
    }

    printf("Ranking 1:\n");

    stack_print(stdout, s2, vertex_print);

    mergeStacks(s1, s2, merged, vertex_cmp);

    printf("Joint Ranking:\n");

    stack_print(stdout, merged, vertex_print);

    stack_free(s1);
    stack_free(s2);
    stack_free(merged);
    graph_free(g1);
    graph_free(g2);
}