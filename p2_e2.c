#include "stack.h"
#include "file_utils.h"
#include "vertex.h"
#include "graph.h"

/**
 * @brief: Makes a search from the origin vertex to the destination vertex
of a graph using the depth-first search algorithm
 * using an ADT Stack
 *
 * The function prints each visited vertex while traversing the graph
 *
 * @param g, Pointer to graph
 * @param from_id, id of the origin Vertex
 * @param to_id, id of the destination Vertex
 * @return The function returns OK or ERROR
**/
Status graph_depthSearch (Graph *g, long from_id, long to_id);

Status graph_depthSearch (Graph *g, long from_id, long to_id){
    if(!g || !from_id || !to_id) return ERROR;

    Status st;
    Stack * s;

    s = stack_init();
    stack_push(s, )

    while(stack_isEmpty(s)==FALSE && st = OK){
        
    }
}

int main(){
    Graph * g;

    g = graph_init();

    graph_newVertex(g, "id:500 tag:MARICON state:1");
    graph_newVertex(g, "id:800 tag:SISISI state:1");
    graph_newVertex(g, "id:53 tag:HOLAAA state:1");

    graph_print(stdout, g);

}