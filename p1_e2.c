#include <stdlib.h>
#include <stdio.h>
#include "graph.h"

int main(){
    Graph * g;
    Vertex * v1;
    Vertex * v2;

    g = graph_init();
    v1 = vertex_initFromString("id:111 tag:Madrid state:0");
    v2 = vertex_initFromString("id:222 tag:Toledo state:0");

    graph_newVertex(g, "id:111 tag:Madrid state:0");
    graph_newVertex(g, "id:222 tag:Toledo state:0");

    graph_newEdge(g, vertex_getId(v2), vertex_getId(v1));

    graph_connectionExists(g, vertex_getId(v1), vertex_getID(v2));
    graph_connectionExists(g, vertex_getId(v2), vertex_getID(v1));

}