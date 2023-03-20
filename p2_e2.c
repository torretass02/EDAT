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
    int*id_from = NULL, *id_to=NULL;

    if(argc < 4){
        printf("ERROR, debe incluir más argumentos.\n");
        return -1;
    }

    if(argc > 4){
        printf("ERROR, ha introducido demasiados argumentos.\n");
        return -1;
    }

    g = graph_init();
    if(!g) {
        printf("ERROR, no se pudo inicializar el grafo.\n");
        return -1;
    }

    f = fopen(argv[1], "r");
    if(!f){
        printf("ERROR, el nombre del archivo es incorrecto.\n");
        graph_free(g);
        return -1;
    }

    id_from = str2int(argv[2]);
    if(!id_from){
        fclose(f);
        graph_free(g);
        if (id_from) free(id_from);
        return -1;
    }

    id_to = str2int(argv[3]);
    if(!id_to){
        fclose(f);
        graph_free(g);
        if (id_from) free(id_from);
        if (id_to) free(id_to);
        return -1;
    }
    
    graph_readFromFile(f, g);
    fclose(f);
    printf("Imput graph:\n");
    graph_print(stdout, g);

    printf("From Vertex id: %d\n", *id_from);
    printf("To Vertex id: %d\n", *id_to);

    printf("Output:\n");
    if(graph_depthSearch(g, *id_from, *id_to)==ERROR){
        graph_free(g);
        if (id_from) free(id_from);
        if (id_to) free(id_to);
        return -1;
    }
    graph_free(g);
    if (id_from) free(id_from);
    if (id_to) free(id_to);
    return 0;
}