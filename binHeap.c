#include "binHeap.h"
#include <stdlib.h>
#include <stdio.h>

binHeap 
initialize(int maxElements){
    binHeap heap;
    heap.maxSize = maxElements;
    heap.size = 0;
    heap.nodes = malloc((maxElements + 1)*sizeof(heapElt));
    heap.nodes[0].edgeSize = -1;
    return heap;
}

void insert(int vertex, float size, binHeap *heap, heapElt **heapPtr){
    int i;
    
    // if vertex is not in heap
    if(!heapPtr[vertex]) {
        for(i = ++heap->size; heap->nodes[i/2].edgeSize > size; i /= 2 ) {
            heap->nodes[i] = heap->nodes[i/2];
            heapPtr[heap->nodes[i].vertex] = &(heap->nodes[i]);
        }
        
        heap->nodes[i].vertex = vertex;
        heap->nodes[i].edgeSize = size;        
        heapPtr[heap->nodes[i].vertex] = &(heap->nodes[i]);
        
    }
    // if vertex is already in heap
    else {
        heapPtr[vertex]->edgeSize = size;
        int index = ((int)heapPtr[vertex]- (int) heap->nodes)/(sizeof(heapElt));
        
        heapify(heap, vertex, size, index, heapPtr);
    }

};

inline void
heapify(binHeap *heap, int vertex, float size, int index, heapElt **heapPtr){
    int i;
    
    for(i = index; heap->nodes[i/2].edgeSize > size; i /= 2 ) {
        heap->nodes[i] = heap->nodes[i/2];
        heapPtr[heap->nodes[i].vertex] = &(heap->nodes[i]);
    }
    
    heap->nodes[i].vertex = vertex;
    heap->nodes[i].edgeSize = size;        
    heapPtr[vertex] = &(heap->nodes[i]); 
}

int
deleteMin(binHeap *heap, heapElt **heapPtr){
    int i, child;
    heapElt minElt, lastElt;
    
    minElt = heap->nodes[1];

    lastElt = heap->nodes[heap->size--];
    int heapSize = heap->size;
    float lastEltEdge = lastElt.edgeSize;
    
    for(i = 1; i*2 <= heapSize; i = child ) {
        child = i * 2;
        
        // if we haven't overstepped bounds of heap get the lowest child
        if(child != heapSize && heap->nodes[child+1].edgeSize < heap->nodes[child].edgeSize)
            child++;
        
        // if the last element's size is bigger than the child's size, then move
        // the child up one
        
        if(lastEltEdge > heap->nodes[child].edgeSize) {
            heap->nodes[i].vertex = heap->nodes[child].vertex;
            heap->nodes[i].edgeSize = heap -> nodes[child].edgeSize;
            heapPtr[heap->nodes[i].vertex] = &(heap->nodes[i]);
        }
        else
            break;
    }
    
    // when you're at the end, put the last element back where it belongs
    heap->nodes[i].vertex = lastElt.vertex;
    heap->nodes[i].edgeSize = lastEltEdge;
    heapPtr[heap->nodes[i].vertex] = &(heap->nodes[i]);
    
    return minElt.vertex;
};

int isEmpty(binHeap *heap){
    return heap->size == 0;
};
