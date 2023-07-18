#include "../graphutils.h" // header for functions to load and free adjacencyList

// A program to print the edge list of a graph given the adjacency matrix
int main ( int argc, char* argv[] ) {

    // FIRST, READ THE ADJACENCY MATRIX FILE
  // AdjacencyListNode* adjacencyList = NULL;
    /* ... */

    

    FILE* fp = fopen(argv[1], "r");
    char buf[256];
    char* string = fgets(buf, 256, fp);
    int size = atoi(string);

    int Matrix[size][size];
    if (!fp) {
        perror("fopen failed");
        return EXIT_FAILURE;
    }
    int key;
    while ( fscanf(fp, "%d", &key)!=EOF ) {

    for (int i = 1; i <= size; i++) {
    for (int j = 1; j <= size; j++) {
        {
          int matrix = atoi(string);
          Matrix[i][j] = &matrix; 
          printf("%d ",  Matrix[i][j] );
        }
     }
    }
   }
    fclose(fp);
    


    // NEXT, TRAVERSE THE ADJACENCY LIST AND PRINT EACH EDGE, REPRESENTED AS A PAIR OF NODES
    // Example of traversing the adjacency list is in the freeAdjList() function in graphutils.h
    /* ... */   

    // NOW, BE SURE TO FREE THE ADJACENCY LIST
    /* ... */

    return EXIT_SUCCESS;
}
