#ifndef prims_binHeap_h
#define prims_binHeap_h

typedef struct heapElt
{
    int vertex;
    float edgeSize;
    
} heapElt;

typedef struct binHeap
{
    int maxSize;
    int size;
    heapElt *nodes;
} binHeap;

binHeap initialize(int maxElements);
void insert(int elt, float dist, binHeap *heap, heapElt **heapPtr);
int deleteMin(binHeap *h, heapElt **heapPtr);
int isEmpty(binHeap h);

#endif

