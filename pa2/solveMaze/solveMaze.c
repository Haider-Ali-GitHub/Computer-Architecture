#include "../graphutils.h" // header for functions to load and free adjacencyList
#include "../queue/queue.h" // header for queue

// A program to solve a maze that may contain cycles using BFS

int main ( int argc, char* argv[] ) {

    // First, read the query file to get the source and target nodes in the maze
    /* ... */

   FILE* inputFile = fopen(argv[2], "r");
    if (!inputFile) 
    {
        perror("fopen failed");
        return EXIT_FAILURE;
    }

    // char sourceString[32];
    // char targetString[32];

    graphNode_t source; 
    graphNode_t target; 
    fscanf (inputFile, "%zu", &source);
    fscanf (inputFile, "%zu", &target);
    fclose(inputFile);


    // fscanf (inputFile, "%s\n%s", sourceString, targetString);

    // // graphNode_t current = strtol(currentString, NULL, 10);
    // // graphNode_t target = strtol(targetString, NULL, 10);

    // graphNode_t current = atoi(sourceString);
    // graphNode_t target = atoi(targetString);




    // READ INPUT FILE TO CREATE GRAPH ADJACENCY LIST
    AdjacencyListNode* adjacencyList = NULL;
    /* ... */
    size_t graphNodeCount = adjMatrixToList(argv[1], &adjacencyList);

    // USE A QUEUE TO PERFORM BFS
    Queue queue = { .front = NULL, .back = NULL };
    //enqueue(&queue , &current);
   
 


    // An array that keeps track of who is the parent node of each graph node we visit
    graphNode_t* parents = calloc( graphNodeCount, sizeof(graphNode_t) );
    for (size_t i=0; i< graphNodeCount; i++) {
        parents[i] = -1; // -1 indicates that a nodes is not yet visited
    }
    parents[adjacencyList[source].graphNode] = adjacencyList[source].graphNode;;
    /* ... */
    graphNode_t current = adjacencyList[source].graphNode;
    while ( current != target ) 
    {
        // so long as we haven't found the target node yet, iterate through the adjacency list
        // add each neighbor that has not been visited yet (has no parents) to the queue of nodes to visit
        /* ... */

            // size_t current = dequeue(&queue);
       
            AdjacencyListNode* currentNode = &adjacencyList[current];
            while (currentNode)
            {   
                //currentNode = dequeue(&queue);
                graphNode_t neighbor = currentNode->graphNode;
                if (parents[neighbor] == -1)
                {
             
                 enqueue(&queue, currentNode);
                 parents[neighbor] = current;
            
                }
                currentNode = currentNode->next;
            }
                // Visit the next node at the front of the queue of nodes to visit
               /* ... */
            //    graphNode_t* current = dequeue(&queue); 
               AdjacencyListNode* node = dequeue(&queue);
               current = node->graphNode;
                    
    }

    // Now that we've found the target graph node, use the parent array to print maze solution
    // Print the sequence of edges that takes us from the source to the target node
    /* ... */
        //  for( int i = 0; i < graphNodeCount; i++){

        //      printf("%ln ", &parents[i]);
        //  }

        //  for (size_t i = target; i != current; i = parents[i]) {
        //   printf("%zu ", i);
        // }
        // printf("%zu\n", current);
        int count = target;
        do{ 
            printf("%d %ld \n", count, parents[count]);
            count = parents[count];
        }while(count != source);

    //free any queued graph nodes that we never visited because we already solved the maze
    while ( queue.front ) {
        /* ... */
        // dequeue(&queue);
        QueueNode* clear = queue.front; 
        queue.front = queue.front->next;
        free(clear); 
    }

         free (parents);
         freeAdjList ( graphNodeCount, adjacencyList );
 
    return EXIT_SUCCESS;
}
