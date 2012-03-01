#ifndef prims_generate_h
#define prims_generate_h

typedef struct vertexEdge {
    int vertex;
    float edgeSize;
} vertexEdge;

vertexEdge** generate1d(int mode, int numpoints, vertexEdge **adjlist);
vertexEdge** generate2d(int mode, int numpoints, vertexEdge **adjlist);
vertexEdge** generate3d(int mode, int numpoints, vertexEdge **adjlist);
vertexEdge** generate4d(int mode, int numpoints, vertexEdge **adjlist);

#endif
