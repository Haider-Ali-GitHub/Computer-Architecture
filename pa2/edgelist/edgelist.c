#include "../graphutils.h" // header for functions to load and free adjacencyList

// A program to print the edge list of a graph given the adjacency matrix
int main ( int argc, char* argv[] ) {

//    // FIRST, READ THE ADJACENCY MATRIX FILE
       AdjacencyListNode* adjacencyList = NULL;
       size_t graphTemp = adjMatrixToList(argv[1], &adjacencyList);

    for (size_t source=0; source < graphTemp; source++) {
        AdjacencyListNode* current = adjacencyList[source].next;

      
        while (current) {
            if (current->graphNode > source ) { // check if edge has already been printed
                printf("%ld %ld\n", source, current->graphNode);
            }
            current = current->next; // iterator moves to next
        }

    }
    freeAdjList(graphTemp, adjacencyList);

    return EXIT_SUCCESS;
}




