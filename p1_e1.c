#include <stdlib.h>
#include <stdio.h>
#include "vertex.h"

int main(){
    Vertex * v1;
    Vertex * v2;
    Vertex * v3;

    v1 = vertex_init();
    v2 = vertex_init();

    vertex_setId(v1, 10);
    vertex_setId(v2, 20);
    vertex_setTag(v1, "one");
    vertex_setTag(v2, "two");
    vertex_setState(v1, WHITE);
    vertex_setState(v2, BLACK);

    vertex_print(stdout, v1);
    vertex_print(stdout, v2);
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

    vertex_print(stdout, v1);
    vertex_print(stdout, v3);

    printf("Equals? ");
    if(vertex_cmp(v1, v3)==0){
        printf("Yes\n");
    }
    else{
        printf("No\n");
    }


}
