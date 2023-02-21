#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "graph.h"

int main(){
    Graph * g;
    FILE * f;

    g = graph_init();

    f = fopen("file.txt", "r");

    graph_readFromFile(f, g);
    
    graph_print(stdout, g);

    fclose(f);
         
}