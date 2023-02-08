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
    if (!g) return NULL;
    g->num_vertices = 0;
    g->num_edges = 0;
}

void graph_free(Graph *g){
    free(g);
}

Status graph_newVertex(Graph *g, char *desc){
    if(!g || !desc) return ERROR;

    Vertex * v;
    v = vertex_initFromString(desc);
    if(!v) return ERROR;

    if(graph_contains(g, vertex_getId(v))==FALSE){
        g->vertices[g->num_vertices] = v;
        g->num_vertices++;
        return OK;
    }
    else{
        vertex_free(v);
        return ERROR;
    }
}

Status graph_newEdge(Graph *g, long orig, long dest){
    if(!g || !orig || !dest) return ERROR;

    if(graph_contains(g, orig) == TRUE && graph_contains(g, dest) == TRUE){
        g->connections[orig][dest] = TRUE;
        g->num_edges++;
        return OK;
    }
    else return ERROR;
}


Bool graph_contains(const Graph *g, long id){
    if(!g || !id) return FALSE;

    int i;
    for(i=0;i<g->num_vertices;i++){
        if(id==vertex_getId(g->vertices[i])){
            return TRUE;
        }
    }
    return FALSE;
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
    if(!g || !orig || !dest) return FALSE;

    if(g->connections[orig][dest] == TRUE) return TRUE;

    return FALSE; 
}

int graph_getNumberOfConnectionsFromId(const Graph *g, long id){
    if(!g || !id) return -1;

    int i, j, num=0;

    for(i=0;i<g->num_vertices;i++){
        for(j=0;j<g->num_vertices;j++){
            if(graph_connectionExists(g, id, j)==TRUE){
                num++;
            }
        }
    }

    return num;
}

long *graph_getConnectionsFromId(const Graph *g, long id){
    if(!g || !id) return NULL;

    int i, j, num = 0, array[MAX_VTX];

    for(i=0;i<g->num_vertices;i++){
        for(j=0;j<g->num_vertices;j++){
            if(graph_connectionExists(g, id, j)==TRUE){
                array[num] = j;
                num++;
            }
        }
    }
    return array;
}

int graph_getNumberOfConnectionsFromTag(const Graph *g, char *tag){

}

long *graph_getConnectionsFromTag(const Graph *g, char *tag){

}

int graph_print (FILE *pf, const Graph *g){

}

Status graph_readFromFile (FILE *fin, Graph *g){

}

