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
    
	int dist[n]; // distance from source
	int prev[n]; // previous vertex
    int setS[n], zeroOutS; // vertices in set S
    for (zeroOutS = 0; zeroOutS < n; zeroOutS++) // zero out set S
        setS[zeroOutS] = 0;
    
    int vertex;  // vertex
    int vertex2; // vertex that forms edge
    float testEdge; // length of edge
    
    binHeap heap = initialize(n);
    insert(0, 0, &heap);
    
    for (int i = 0; i < n; i++){
        dist[i] = -1;
        prev[i] = 0;
    }

    dist[0] = 0;
    
    while(!isEmpty(heap)){
        /* in this implementation, heaps may contain some vertices more than once. 
            if this is ever the case, and we use deleteMin more than once on some vertex
            it will discard this vertex. However, in this implementation we will be using delete
            min many more times than V. Also, our maxheap must be much higher.
            How can we do better? */
        
   //     do {
            vertex = deleteMin(&heap);
 //       } while (setS[vertex]);
        
        setS[vertex] = vertex;
        for (vertex2 = 0; vertex2 < n; vertex2++)
            if (!(setS[vertex2])) {
                if (dist[vertex2] > (testEdge = length(vertex, vertex2, graph)) || 
                    dist[vertex2] == -1){
                    dist[vertex2] = testEdge;
                    printf("%d\n", dist[vertex2]);
                    prev[vertex2] = vertex;
                    insert(vertex2, dist[vertex2], &heap);
                }
            }
    }
    for (int i = 0; i < n; i++)
        printf("%d\n", dist[i]);
               
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
