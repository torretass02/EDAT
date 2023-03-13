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


int main(int argc, char**argv){
    FILE * f;
    Graph * g;
    long *id_from, *id_to;

    g = graph_init();

    f = fopen(argv[1], "r");
    if(!f){
        printf("ERROR, el nombre del archivo es incorrecto.\n"); 
        return -1;
    }

    id_from = str2int(argv[2]);
    id_to = str2int(argv[3]);

    graph_readFromFile(f, g);

    printf("Imput graph:\n");
    graph_print(stdout, g);

    printf("From Vertex id: %ld\n", *id_from);
    printf("To Vertex id: %ld\n", *id_to);

    graph_depthSearch(g, *id_from, *id_to);

    printf("Output:\n");

    graph_print(stdout, g);

    
}