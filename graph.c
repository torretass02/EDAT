#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "graph.h"
#define MAX_VTX 4096

struct _Graph {
    Vertex *vertices[MAX_VTX];
    Bool connections[MAX_VTX][MAX_VTX];
    int num_vertices;
    int num_edges;
};
/* START [Private_functions] */
Vertex * graph_GetVertexFromIndex(const Graph * g, int ix);
Vertex * graph_GetVertexFromTag(const Graph * g, char * tag);
int _graph_findVertexByTag(const Graph *, char *tag);
Status _graph_insertEdgeFromIndices(Graph *g, const long origIx, const long destIx);
int _graph_getNumConnections(const Graph *g, int ix);
long *_graph_getConnections(const Graph *g, int ix);
void _graph_setVertexState (Graph *g, Label l);
/* END [Private_functions] */


/* START [Private_functions] */
Vertex * graph_GetVertexFromIndex(const Graph * g, int ix){
    if(!g || !ix) return NULL;

    int i;

    for(i=0; i<g->num_vertices; i++){
        if(vertex_getIndex(g->vertices[i])==ix){
            return g->vertices[i];
        }
    }

    return NULL;
}

Vertex * graph_GetVertexFromTag(const Graph * g, char * tag){
    if(!g || !tag) return NULL;

    int i;

    for(i=0; i<g->num_vertices; i++){
        if(strcmp(vertex_getTag(g->vertices[i]), tag)==0){
            return g->vertices[i];
        }
    }

    return NULL;
}

int _graph_getNumConnections(const Graph *g, int ix) {
    if(!g || ix < 0 || ix >= MAX_VTX) return -1;

    int i, num = 0;

    Vertex * v = graph_GetVertexFromIndex(g, ix);

    if(!v) return -1;

    for(i = 0; i < MAX_VTX; i++){
        if(graph_connectionExists(g, vertex_getId(v), i) == TRUE){
            num++;
        }
    }
    
    return num;
}

long *_graph_getConnections(const Graph *g, int ix){
    if(!g || !ix) return NULL;

    int i, num = 0;
    long int * array;
    Vertex * v = graph_GetVertexFromIndex(g, ix);

    if(_graph_getNumConnections(g, ix) == 0) return NULL;
    array = malloc(sizeof(long int)*_graph_getNumConnections(g, ix));
    if(!array) return NULL;

    for(i=0;i<MAX_VTX;i++){
        if(graph_connectionExists(g, vertex_getId(v), i)==TRUE){
            array[num] = i;
            num++;
        }
    }

    vertex_free(v);

    return array;
}

void _graph_setVertexState (Graph *g, Label l){
    if(!g || !l) return;
    int n, i;
    Vertex ** vertices;

    n = g->num_vertices;
    vertices = graph_get_all_vertex(g);

    for(i=0; i<n; i++){
        if(vertex_setState(vertices[i], l)==ERROR) return;
    }

}
/* END [Private_functions] */

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
    if(!g) return;

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
        vertex_setIndex(g->vertices[g->num_vertices], g->num_vertices);
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
    long * array;

    array = malloc(sizeof(long)*graph_getNumberOfConnectionsFromId(g, id));
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

    int i, num = 0;

    for(i=0;i<MAX_VTX;i++){
        if(graph_connectionExists(g, vertex_getId(graph_GetVertexFromTag(g, tag)), i)==TRUE){
            num++;
        }
    }
           
    return num;
}

long *graph_getConnectionsFromTag(const Graph *g, char *tag){
    if(!g || !tag) return NULL;

    int i, num = 0;
    long int * array;

    array = malloc(sizeof(int)*MAX_VTX);
    if(!array) return NULL;

    for(i=0;i<MAX_VTX;i++){
        if(graph_connectionExists(g, vertex_getId(graph_GetVertexFromTag(g, tag)), i)==TRUE){
            array[num] = i;
            num++; 
        }
    }

    return array;
}

Vertex ** graph_get_all_vertex(Graph * g){
    if(!g) return NULL;

    return g->vertices;
}

Vertex * graph_get_Vertex(Graph *g, long id){
    if(!g || !id) return NULL;

    int i;

    for(i=0; i<g->num_vertices; i++){
        if(id == vertex_getId(g->vertices[i])){
            return g->vertices[i];
        }
    }

    return NULL;
}  

Status graph_depthSearch(Graph *g, long from_id, long to_id) {
    if (!g || from_id == 0 || to_id == 0) return ERROR;

    Status st = OK;
    Stack *s = stack_init();
    int i = 0;
    Vertex *vf = NULL, *v0 = NULL, *vt = NULL;
    long *connections = NULL;
    long id_v0 = 0;

    vf = graph_get_Vertex(g, from_id);
    if (!vf) {
        stack_free(s);
        printf("ERROR, no existe vertice con el id %ld.\n", from_id);
        return ERROR;
    }

    vt = graph_get_Vertex(g, to_id);
    if (!vt) {
        stack_free(s);
        printf("ERROR, no existe vertice con el id %ld.\n", to_id);
        return ERROR;
    }

    _graph_setVertexState(g, WHITE);
    if(stack_push(s, vf)==ERROR) return ERROR;

    while (stack_isEmpty(s) == FALSE && st == OK) {
        v0 = stack_pop(s);
        vertex_print(stdout, v0);
        printf("\n");
        if (vertex_cmp(v0, vt) == 0) {
            st = OK;
            break;
        }

        if (vertex_getState(v0) == WHITE) {
            vertex_setState(v0, BLACK);
            id_v0 = vertex_getId(v0);
            connections = graph_getConnectionsFromId(g, id_v0);
            for (i = 0; i < graph_getNumberOfConnectionsFromId(g, vertex_getId(v0)); i++) {
                Vertex *v = graph_get_Vertex(g, connections[i]);
                if (v && vertex_getState(v) == WHITE) {
                    if(stack_push(s, v)==ERROR) return ERROR;
                }
            }
            free(connections);
        }
    }
    
    stack_free(s);
    return st;
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
        desc[strcspn(desc, "\n")] = '\0';
        graph_newVertex(g, desc);
    }

    while(fgets(desc, 1024,fin)!=NULL){
        sscanf(desc, "%ld %ld", &num1, &num2);
        graph_newEdge(g, num1, num2);
    }

    return OK;
}
