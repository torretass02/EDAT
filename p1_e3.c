#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "graph.h"

int main(int argc, char**argv){
    Graph * g;
    FILE * f;

    if(argc>2){
        printf("ERROR, introduzca solo un argumento, el nombre del fichero.\n");
        return -1;
    }
    else if(argc<2){
        printf("ERROR, debe introducir el nombre del fichero.\n");
        return -1;
    }

    g = graph_init();

    f = fopen(argv[1], "r");
    if(!f){
        printf("ERROR, el nombre del archivo es incorrecto.\n"); 
        return -1;
    }

    graph_readFromFile(f, g);
    
    graph_print(stdout, g);

    graph_free(g);

    fclose(f);       
}