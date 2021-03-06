#include <stdio.h>
#include <stdlib.h>
#include "binHeap.h"
#include "generate.h"

float length(int vertex1, int vertex2, vertexEdge **graph);
float prims(vertexEdge **graph);
float findVertex (int vertex, vertexEdge *row);
int n;

float max;

int
main(int argc, char *argv[]){
    
    int numpoints, numtrials, mode, dimension;
    vertexEdge **(*generateGraph)(int, int, vertexEdge **);
    
    if (argc != 5) {
        printf("usage: randmst mode numpoints numtrials dimension\n");
        return 1;
    }
    
    if (((numpoints = atoi(argv[2])) < 0)) {
        printf("numpoints must be at least 0\n");
        return 1;
    }
    else
        n = numpoints;
    
    if (((numtrials = atoi(argv[3])) < 0)) {
        printf("numtrials must be at leaset 0\n");
        return 1;
    }
    
    if ((mode = atoi(argv[3]) < 0 || mode > 3)) {
        printf("mode must be between 0 and 3, inclusive\n");
        return 1;
    }
    
    dimension = atoi(argv[4]);
    
    switch (dimension) {
        case 0:
            generateGraph = generate1d;
            break;
        case 2:
            generateGraph = generate2d;
            break;
        case 3:
            generateGraph = generate3d;
            break;
        case 4:
            generateGraph = generate4d;
            break;
        default:
            printf("dimensions must be between 0,2,3 or 4\n");
            return 1;
            break;
    
    }
    
    vertexEdge **adjlist = malloc(numpoints * sizeof(vertexEdge));
    float weightSum = 0;
    int i = 0;
    mode = atoi(argv[1]);
    
    
    if (mode == 0){
        float tmpTotal;
        do {
            generateGraph(mode, numpoints, adjlist);
            i++;
            tmpTotal = prims(adjlist);
            printf("%f\n",max);
            //printf("%f\n", tmpTotal);
            weightSum += tmpTotal;
            
            
        } while (i < numtrials);
    }
    
    else if (mode == 1){
        float tmpTotal;
        do {
            generateGraph(mode, numpoints, adjlist);

            i++;
            int j,k;
            
            vertexEdge *nodePtr;
            for (k = 0; k < numpoints; k++) {
                nodePtr = adjlist[k];
                printf("%f ",nodePtr->edgeSize);
                nodePtr++;
                while (nodePtr->vertex != -1){
                    printf("%f ",nodePtr->edgeSize);
                    nodePtr++;
                }
                printf("\n");
            }
            
            tmpTotal = prims(adjlist);
            printf("%f\n",max);
            printf("MPT weight: %f\n", tmpTotal);
            weightSum += tmpTotal;
            
        } while (i < numtrials);
    }

    printf("%f %d %d %d\n", 
          weightSum/numtrials, numpoints, numtrials, dimension);
    
    for (int freeNum = 0; freeNum < numpoints; freeNum++)
        free(adjlist[freeNum]);

    free(adjlist);
    
}

float
prims(vertexEdge **graph){
    
	double dist[n]; // distance from source
    int setS[n], zeroOutS; // vertices in set S
    for (zeroOutS = 0; zeroOutS < n; zeroOutS++) // zero out set S
        setS[zeroOutS] = 0;
    
    int vertex;  // vertex
    int vertex2; // vertex that forms edge
    float testEdge; // length of edge
    
    heapElt **heapPtr = malloc(n * sizeof(heapElt)); // points to vertex location inside heap, NULL if not present
    
    for (int i = 0; i < n; i++)
        heapPtr[i] = NULL;
    
    binHeap heap = initialize(n); // creates heap
    insert(0, 0, &heap, heapPtr); // put source into heap
    
    // set all distances to source to infinity
    for (int i = 0; i < n; i++)
        dist[i] = -1;
    
    dist[0] = 0; // distance from source to source is 0
    
    while(!isEmpty(&heap)){

        // our next edge is the smallest edge we can get to
        vertex = deleteMin(&heap, heapPtr);
        
        // insert it into S
        setS[vertex] = 1;
        
        // this node is no longer in the heap
        heapPtr[vertex] = NULL;
        
        // for all edges connecting to vertex
        for (vertex2 = 0; vertex2 < n; vertex2++)

            // if it isn't already in our MSP
            if (!(setS[vertex2])) {
                // get it's length
                testEdge = length(vertex, vertex2, graph);
                // make sure we didn't ommit edge from graph
                if (testEdge != -1){
                    /* if size of edge is smaller than what is already stored,
                       or if  infinity is stored, then insert this into heap */
                    if ((dist[vertex2] > testEdge) || (dist[vertex2] == -1)){
                        dist[vertex2] = testEdge;
                        insert(vertex2, dist[vertex2], &heap, heapPtr);
                    }  
                }
            }
        
    }
    
    max = 0;
    float totalWeight = 0;
    for (int i = 0; i < n; i++){
        totalWeight += dist[i];
        if (max < dist[i])
            max = dist[i];
    }
    
    
    return totalWeight;
}

inline float
length(int vertex1, int vertex2, vertexEdge **graph){
    int smaller = vertex1 < vertex2 ? vertex1 : vertex2;
    int larger = vertex1 >= vertex2 ? vertex1 : vertex2;
    
    // nodePointer will point to where we left off in our linked list
    vertexEdge *nodePtr = graph[smaller];
    
    // while we are not at end of list
    while (nodePtr->vertex != -1) {
        if (nodePtr->vertex == larger)
            return nodePtr->edgeSize;
        // if it's not in list return -1
        else if (nodePtr->vertex > larger)
            return -1;
        else
            nodePtr++;
    }
    return -1;
}
