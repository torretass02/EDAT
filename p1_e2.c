#include <stdlib.h>
#include <stdio.h>
#include "graph.h"

int main(){
    Graph * g;
    Vertex * v1;
    Vertex * v2;
    int a, b, i;
    long int * array;

    g = graph_init();
    v1 = vertex_initFromString("id:111 tag:Madrid state:0");
    v2 = vertex_initFromString("id:222 tag:Toledo state:0");

    a = graph_newVertex(g, "id:111 tag:Madrid state:0");
    if(a == ERROR){
        printf("ERROR al INSERTAR VERTEX en el grafo.\n");
        return -1;
    }
    printf("Inserting %s... result ...: %d\n", vertex_getTag(v1), a);

    b = graph_newVertex(g, "id:222 tag:Toledo state:0");
    if(b == ERROR){
        printf("ERROR al INSERTAR VERTEX en el grafo.\n");
        return -1;
    }
    printf("Inserting %s... result ...: %d\n", vertex_getTag(v2), b);

    if(graph_newEdge(g, vertex_getId(v2), vertex_getId(v1))==ERROR){
        printf("ERROR al IMPRIMIR vertex.\n");
        return -1;
    }
    printf("Inserting edge: %ld --> %ld\n", vertex_getId(v2),vertex_getId(v1));

    if(graph_connectionExists(g, vertex_getId(v1), vertex_getId(v2))==TRUE){
        printf("%ld --> %ld?: Yes\n", vertex_getId(v1), vertex_getId(v2));
    }
    else{
        printf("%ld --> %ld?: No\n", vertex_getId(v1), vertex_getId(v2));
    }

    if(graph_connectionExists(g, vertex_getId(v2), vertex_getId(v1))==TRUE){
        printf("%ld --> %ld?: Yes\n", vertex_getId(v2), vertex_getId(v1));

    }
    else{
        printf("%ld --> %ld?: No\n", vertex_getId(v2), vertex_getId(v1));
    }

    printf("Number of connections from 111: %d\n", graph_getNumberOfConnectionsFromId(g, 111));
    printf("Number of connections from Toledo: %d\n", graph_getNumberOfConnectionsFromTag(g, "Toledo"));

    array = graph_getConnectionsFromTag(g, "Toledo");
    if(array == NULL){
        printf("ERROR al OBTENER CONEXIONES a partir de un tag.\n");
        return -1;
    }

    printf("Connections from Toledo: ");
    for(i=0; i<graph_getNumberOfConnectionsFromId(g, vertex_getId(v2)); i++){
        printf("%ld ", array[i]);
    }
    printf("\n");
    printf("Graph:\n");
    graph_print(stdout, g);

    graph_free(g);
    vertex_free(v1);
    vertex_free(v2);
    free(array);
}