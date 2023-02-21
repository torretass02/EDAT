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
    int i, j;

    g = malloc(sizeof(Graph));
    if (!g) return NULL;

    for(i=0; i<MAX_VTX; i++){
        for(j=0; j<MAX_VTX; j++){
            g->connections[i][j] = FALSE;
        }
    }
    g->num_vertices = 0;
    g->num_edges = 0;

    return g;
}

void graph_free(Graph *g){
    int i;

    for(i = 0; i<g->num_vertices;i++){
        vertex_free(g->vertices[i]);
    }

    free(g);
}

Status graph_newVertex(Graph *g, char *desc){
    if(!g || !desc) return ERROR;

    Vertex * v;
    v = vertex_initFromString(desc);
    if(!v) return ERROR;

    if(g->num_vertices == MAX_VTX){
        vertex_free(v);
        return ERROR;
    }

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

    int i, num=0;

    for(i=0;i<MAX_VTX;i++){
        if(graph_connectionExists(g, id, i)==TRUE){
            num++;
        }
    }

    return num;
}

long *graph_getConnectionsFromId(const Graph *g, long id){
    if(!g || !id) return NULL;

    int i, num = 0;
    long int * array;

    array = malloc(sizeof(int)*graph_getNumberOfConnectionsFromId(g, id));
    if(!array) return NULL;

    for(i=0;i<MAX_VTX;i++){
        if(graph_connectionExists(g, id, i)==TRUE){
            array[num] = i;
            num++;
        }
    }

    return array;
}

int graph_getNumberOfConnectionsFromTag(const Graph *g, char *tag){
    if(!g || !tag) return -1;

    int i, j, num = 0;

    for(i=0; i<g->num_vertices; i++){
        if(strcmp(vertex_getTag(g->vertices[i]), tag)==0){
            for(j=0;j<MAX_VTX;j++){
                if(graph_connectionExists(g, vertex_getId(g->vertices[i]), j)==TRUE){
                    num++;
                }
            }
        }    
    }

    return num;
}

long *graph_getConnectionsFromTag(const Graph *g, char *tag){
    if(!g || !tag) return NULL;

    int i, j, num = 0;
    long int * array;

    array = malloc(sizeof(int)*MAX_VTX);
    if(!array) return NULL;

    for(i=0; i<g->num_vertices; i++){
        if(strcmp(vertex_getTag(g->vertices[i]), tag)==0){
            for(j=0;j<MAX_VTX;j++){
                if(graph_connectionExists(g, vertex_getId(g->vertices[i]), j)==TRUE){
                    array[num] = j;
                    num++;
                }
            }
        }    
    }

    return array;
}

int graph_print (FILE *pf, const Graph *g){
    if(!pf || !g) return -1;

    int i, j, cont = 0;

    for(i=0; i<g->num_vertices; i++){
        cont += vertex_print(pf, g->vertices[i]);
        cont += fprintf(pf, ": ");
        for(j=0; j<g->num_vertices; j++){
            if(graph_connectionExists(g, vertex_getId(g->vertices[i]), vertex_getId(g->vertices[j]))==TRUE){
                cont += vertex_print(pf, g->vertices[j]);
            }
        }
        cont += fprintf(pf, "\n");
    }
    
    return cont;
}

Status graph_readFromFile (FILE *fin, Graph *g){
    if(!fin || !g) return ERROR;
    int i, num;
    char desc[1024];
    long num1, num2;

    fgets(desc, 1024, fin);

    sscanf(desc, "%d", &num);

    for(i=0; i<num; i++){
        fgets(desc, 1024, fin);
        graph_newVertex(g, desc);
    }

    while(fgets(desc, 1024,fin)!=NULL){
        sscanf(desc, "%ld %ld", &num1, &num2);
        graph_newEdge(g, num1, num2);
    }

    return OK;
}
