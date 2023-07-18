#include "../graphutils.h"

// A program to find a cycle in a directed graph
bool isCycleDFS(
    size_t graphNodeCount,
    AdjacencyListNode* adjacencyList,
    bool* visited,
    bool* repeatCycle,
    unsigned* path,
    unsigned depth,
    graphNode_t startNode,
    graphNode_t current
) {
    if (visited[current] && repeatCycle[current]) {
        return false;
    }

    if (visited[current]) {
        for (unsigned i = 0; i < depth; i++) {
            if (path[i] == current) {
                printf("%ld", current);
                for (unsigned j = i + 1; j < depth; j++) {
                    printf(" %d", path[j]);
                    repeatCycle[path[j]] = true;
                }
                printf("\n");
                return true; // Cycle found, return true
            }
        }
        return false;
    }

    visited[current] = true;
    path[depth] = current;

    AdjacencyListNode* neighbor = adjacencyList[current].next;
    while (neighbor) {
        if (neighbor->graphNode != current) {
            if (isCycleDFS(graphNodeCount, adjacencyList, visited, repeatCycle, path, depth + 1, startNode, neighbor->graphNode)) {
                return true; // Cycle found, return true
            }
        }
        neighbor = neighbor->next;
    }

    path[depth] = 0;
    visited[current] = false;

    return false;
}

int main(int argc, char* argv[]) {

    AdjacencyListNode* adjacencyList;
    /* ... */
    size_t graphNodeCount = adjMatrixToList(argv[1], &adjacencyList);

    bool isCyclic = false;

    for (unsigned source = 0; source < graphNodeCount; source++) {
        bool* visited = calloc(graphNodeCount, sizeof(bool));
        bool* repeatCycle = calloc(graphNodeCount, sizeof(bool));
        unsigned* path = calloc(graphNodeCount, sizeof(unsigned));
        isCyclic = isCycleDFS(graphNodeCount, adjacencyList, visited, repeatCycle, path, 0, source, source);
        free(repeatCycle);
        free(visited);  
        free(path);
        if (isCyclic) {
            break;
        }
    }

    if (!isCyclic) { // Check if isCyclic is false
        printf("DAG\n");
    }

    freeAdjList(graphNodeCount, adjacencyList);
    return EXIT_SUCCESS;
}
