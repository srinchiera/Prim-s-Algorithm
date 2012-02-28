#include <stdio.h>
#include <stdlib.h>
#include "binHeap.h"
#include "generate.h"

float length(int vertex1, int vertex2, float *graph);
float prims(float *graph);

int n;

int
main(int argc, char *argv[]){
    
    int numpoints, numtrials, mode, dimension;
    float *(*generateGraph)(int, int, float *);
    
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
    
    float *adjmatrix = malloc((numpoints*(numpoints +1))/2 * sizeof(float));
    float weightSum = 0;
    int i = 0;
    mode = atoi(argv[1]);
    
    if (mode == 0)
	do {
		generateGraph(mode, numpoints, adjmatrix);
        i++; 
        weightSum += prims(adjmatrix);
    } while (i < numtrials);
    else if (mode == 1){
        float tmpTotal;
        
        do {
            generateGraph(mode, numpoints, adjmatrix);
            
             for (int k = 0; k < numpoints; k++){
                 for (int j = 0; j < numpoints-k; j++){
                     printf("%f ",adjmatrix[(k*numpoints)-((k*(k+1))/2)+j + k]);
                 }
             printf("\n");
             }
            
            i++;
            tmpTotal = prims(adjmatrix);
            printf("MPT weight: %f\n", tmpTotal);
            weightSum += tmpTotal;
            
        } while (i < numtrials);
    }
    
    printf("%f %d %d %d\n", 
          weightSum/numtrials, numpoints, numtrials, dimension);
    
    free(adjmatrix);
    //prims (adjmatrix)
   /* float test[] = {0,16,5,2,8,16,0,9,14,4,5,9,0,12,3,2,14,12,0,1,8,4,3,1,0};
    prims(test);*/
    
}

float
prims(float *graph){
    
	double dist[n]; // distance from source
    int setS[n], zeroOutS; // vertices in set S
    for (zeroOutS = 0; zeroOutS < n; zeroOutS++) // zero out set S
        setS[zeroOutS] = 0;
    
    int vertex;  // vertex
    int vertex2; // vertex that forms edge
    float testEdge; // length of edge
    
    heapElt *heapPtr[n];
    
    for (int i = 0; i < n; i++)
        heapPtr[i] = NULL;
    
    binHeap heap = initialize(n);
    insert(0, 0, &heap, heapPtr);
    
    // set all distances to source to infinity
    for (int i = 0; i < n; i++)
        dist[i] = -1;
    
    dist[0] = 0;
    
    while(!isEmpty(&heap)){
        // our next edge is the smallest edge we can get to
        vertex = deleteMin(&heap, heapPtr);
        
        // insert it into S
        setS[vertex] = vertex;
        
        // this node is no longer in the heap
        heapPtr[vertex] = NULL;
        
        // skipping over all the edges we've already seen
        for (vertex2 = 0; vertex2 < n; vertex2++)
            if (!(setS[vertex2])) {
                if (dist[vertex2] > (testEdge = length(vertex, vertex2, graph)) || 
                    dist[vertex2] == -1){
                    dist[vertex2] = testEdge;
                    if (heapPtr[vertex2]){ // check to see if node is in heap first
                        heapPtr[vertex2]->edgeSize = dist[vertex2];
                        heapify(&heap, heapPtr[vertex2]);
                    }
                    else
                        insert(vertex2, dist[vertex2], &heap, heapPtr);
                }
            }
    }
    
    float totalWeight = 0;
    for (int i = 0; i < n; i++){
        totalWeight += dist[i];
    }
    
    return totalWeight;
}

inline float
length(int vertex1, int vertex2, float *graph) {
    
    
    
    return vertex1 < vertex2 ? graph[(vertex1*n)-(vertex1*(vertex1+1))/2+vertex2] 
            : graph[(vertex2*n)-(vertex2*(vertex2+1))/2+vertex1];
}
