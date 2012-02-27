#include <stdio.h>
#include <stdlib.h>
#include "binHeap.h"


float length(int vertex1, int vertex2, float *graph);
float *generate1d(int n);
float *generate2d(int n);
float *generate3d(int n);
float *generate4d(int n);
int prims(float *graph);

int n;

int
main(int argc, char *argv[]){
    
    int numpoints, numtrials, mode;
    float *(*generateGraph)(int);
    
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
    
    if (((mode = atoi(argv[3])) < 0)) {
        printf("mode must be between 0 and 3, inclusive\n");
        return 1;
    }
    
    switch (atoi(argv[4])) {
        case 1:
            generateGraph = generate1d;
            break;
        case 2:
            generateGraph = generate2d;
        case 3:
            generateGraph = generate3d;
        case 4:
            generateGraph = generate4d;
        default:
            printf("dimensions must be between 1 and 4\n");
            return 1;
            break;
    }
    
    float test[] = {0,16,5,2,8,16,0,9,14,4,5,9,0,12,3,2,14,12,0,1,8,4,3,1,0};
    prims(test);
    
}

int
prims(float *graph){
    
	double dist[n]; // distance from source
	//int prev[n];
    /* previous vertex I don't think we need to keep track of previous for 
     This assignment */
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
    for (int i = 0; i < n; i++){
        dist[i] = -1;
        //prev[j] = 0;
    }

    dist[0] = 0;
    
    while(!isEmpty(heap)){
       // how do we make sure each vertex is going to the heap only once?
    /* create an array of size v. each index will store the address in the heap
     where some vertex v is. during an insert, it will first check the array to see if that vertex
     is in the array, if so, it will just update the value array[vertex]->edgeSize = blah.
     Also whenever there is an insert binHeap will rearrange this array as necessary.
     Deletemin will Null out this pointer*/
        vertex = deleteMin(&heap, heapPtr);
        
        setS[vertex] = vertex;
        heapPtr[vertex] = NULL; // node is no longer in heap
        for (vertex2 = 0; vertex2 < n; vertex2++)
            if (!(setS[vertex2])) {
                if (dist[vertex2] > (testEdge = length(vertex, vertex2, graph)) || 
                    dist[vertex2] == -1){
                    dist[vertex2] = testEdge;
                    if (heapPtr[vertex2]) // check to see if node is in heap first
                        heapPtr[vertex2]->edgeSize = dist[vertex2];
                        /*HEAPIFY AND THEN WE'RE DONE;*/
                    else
                        insert(vertex2, dist[vertex2], &heap, heapPtr);
                }
            }
    }
    
    // prints weight of MST
    int totalWeight = 0;
    for (int i = 0; i < n; i++){
        totalWeight += dist[i];
    }
    
    printf("Total Weight: %d\n", totalWeight);
    return 0;
}

float
length(int vertex1, int vertex2, float *graph) {
    return vertex1 < vertex2 ? graph[vertex1*n+vertex2] : graph[vertex2*n+vertex1];
}


float
*generate1d(int n){
    return 0;
}

float
*generate2d(int n){
    return 0;
}

float
*generate3d(int n){
    return 0;
}

float
*generate4d(int n){
    return 0;
}

