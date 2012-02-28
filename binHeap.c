#include "binHeap.h"
#include <stdlib.h>
#include <stdio.h>

binHeap 
initialize(int maxElements){
    binHeap heap;
    heap.maxSize = maxElements;
    heap.size = 0;
    heap.nodes = malloc((maxElements + 1)*sizeof(int));
    heap.nodes[0].edgeSize = -1;
    return heap;
}

void insert(int vertex, float size, binHeap *heap, heapElt **heapPtr){
    int i;
    
    for(i = ++heap->size; heap->nodes[i/2].edgeSize > size; i /= 2 ) {
        heap->nodes[i] = heap->nodes[i/2];
        heapPtr[heap->nodes[i].vertex] = &(heap->nodes[i]);
    }
    
    heap->nodes[i].vertex = vertex;
    heapPtr[vertex] = &(heap->nodes[i]);
    heap->nodes[i].edgeSize = size;

};

int
deleteMin(binHeap *heap, heapElt **heapPtr){
    int i, child;
    heapElt minElt, lastElt;
    
    minElt = heap->nodes[1];

    lastElt = heap->nodes[heap->size--];
    int heapSize = heap->size;
    float lastEltEdge = lastElt.edgeSize;
    
    for(i = 1; i*2 <= heapSize; i = child ) {
        child = i * 2; // store heap->size
        // if we haven't overstepped bounds of heap get the lowest child
        if(child != heapSize && heap->nodes[child+1].edgeSize < heap->nodes[child].edgeSize)
            child++;
        
        // store lastElt.edgesize
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

void
heapify(binHeap *heap, heapElt *heapPtr){
    int i;
    int displacement = (int) (heapPtr - heap->nodes); // memory address difference
    int indexOfElt = (displacement / sizeof(heapElt));
    int parent;
    
    heapElt lastElt = *heapPtr;
    
    for(i = indexOfElt; i/2 > 0; i = parent) {
        parent = i / 2;

        if(lastElt.edgeSize < heap->nodes[parent].edgeSize) {
            
            heap->nodes[i].vertex = heap->nodes[parent].vertex;
            heap->nodes[i].edgeSize = heap -> nodes[parent].edgeSize;
            heapPtr[heap->nodes[i].vertex] = heap->nodes[i];
        }
        else
            break;
    }
    
    heap->nodes[i].vertex = lastElt.vertex;
    heap->nodes[i].edgeSize = lastElt.edgeSize;
    heapPtr[heap->nodes[i].vertex] = heap->nodes[i];
    
}

int isEmpty(binHeap *heap){
    
    return heap->size == 0;

};