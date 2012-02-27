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
    
    for(i = 1; i*2 <= heap->size; i = child )
    {
        child = i * 2;
        if(child != heap->size && heap->nodes[child+1].edgeSize < heap->nodes[child].edgeSize)
            child++;
        
        if(lastElt.edgeSize > heap->nodes[child].edgeSize) {
            heap->nodes[i].vertex = heap->nodes[child].vertex;
            heap->nodes[i].edgeSize = heap -> nodes[child].edgeSize;
            heapPtr[heap->nodes[i].vertex] = &(heap->nodes[i]);
        }
        else
            break;
    }
    
    heap->nodes[i] = lastElt;
    heapPtr[heap->nodes[i].vertex] = &(heap->nodes[i]);

    return minElt.vertex;
};

int isEmpty(binHeap heap){
    
    return heap.size == 0;

};
