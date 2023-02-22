#include <stdlib.h>
#include <stdio.h>
#include "vertex.h"

int main(){
    Vertex * v1;
    Vertex * v2;
    Vertex * v3;

    v1 = vertex_init();
    v2 = vertex_init();

    if(vertex_setId(v1, 10)==ERROR){
        printf("ERROR al asignar ID.\n");
        return -1;
    }
    else if(vertex_setId(v2, 20)==ERROR){
        printf("ERROR al asignar ID.\n");
        return -1;
    }
    else if(vertex_setTag(v1, "one")==ERROR){
        printf("ERROR al asignar TAG.\n");
        return -1;
    }
    else if(vertex_setTag(v2, "two")==ERROR){
        printf("ERROR al asignar TAG.\n");
        return -1;
    }
    else if(vertex_setState(v1, WHITE)==ERROR){
        printf("ERROR al asignar STATELUIS.\n");
        
    }
    else if(vertex_setState(v2, BLACK)==ERROR){
        printf("ERROR al asignar STATE.\n");
        return -1;
    }
    else if(vertex_print(stdout, v1)==-1){
        printf("ERROR al IMPRIMIR vertex.\n");
        return -1;
    }
    else if(vertex_print(stdout, v2)==-1){
        printf("ERROR al IMPRIMIR vertex.\n");
        return -1;
    }
    printf("\n");

    printf("Equals? ");
    if(vertex_cmp(v1, v2)==0){
        printf("Yes\n");
    }
    else{
        printf("No\n");
    }

    printf("Vertex 2 tag: %s\n", vertex_getTag(v2));
    
    v3 = vertex_copy(v1);
    
    printf("Vertex 3 id: %ld\n", vertex_getId(v3));

    if(vertex_print(stdout, v1)==-1){
        printf("ERROR al IMPRIMIR vertex.\n");
        return -1;
    }
    else if(vertex_print(stdout, v3)==-1){
        printf("ERROR al IMPRIMIR vertex.\n");
        return -1;
    }

    printf("\n");

    printf("Equals? ");
    if(vertex_cmp(v1, v3)==0){
        printf("Yes\n");
    }
    else{
        printf("No\n");
    }

    vertex_free(v1);
    vertex_free(v2);
    vertex_free(v3);
}
