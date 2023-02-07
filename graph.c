#include <string.h>
#include "graph.h"
#define MAX_VTX 4096

struct _Graph {
    Vertex *vertices[MAX_VTX];
    Bool connections[MAX_VTX][MAX_VTX];
    int num_vertices;
    int num_edges;
};

Graph * graph_init(){
    Graph * g;
    g = malloc(sizeof(Graph));
}

void graph_free(Graph *g){
    free(g);
}

Status graph_newVertex(Graph *g, char *desc){
    
}

Status graph_newEdge(Graph *g, long orig, long dest){

}

Bool graph_contains(const Graph *g, long id){

}

int graph_getNumberOfVertices(const Graph *g){
    if(!g) return -1;

    return g->num_vertices;
}

int graph_getNumberOfEdges(const Graph *g){
    if(!g) return -1;

    return g->num_edges;
}   

Bool graph_connectionExists(const Graph *g, long orig, long dest){

}

int graph_getNumberOfConnectionsFromId(const Graph *g, long id){

}

long *graph_getConnectionsFromId(const Graph *g, long id){
    
}

int graph_getNumberOfConnectionsFromTag(const Graph *g, char *tag){

}

long *graph_getConnectionsFromTag(const Graph *g, char *tag){

}

int graph_print (FILE *pf, const Graph *g){

}

Status graph_readFromFile (FILE *fin, Graph *g){

}

