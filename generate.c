#include "generate.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

struct timeval;

vertexEdge **
generate1d(int mode, int numpoints, vertexEdge **linkedList){
    struct timeval tim;
    
    //random seed
    gettimeofday(&tim, NULL);
    unsigned int seed = (unsigned int) tim.tv_sec * (unsigned int) tim.tv_usec;
    srand(seed);
    
    int i, j;
    float a = RAND_MAX;
    vertexEdge *nodePtr;
    float randNum;
    
    //defines edgelengths
    for (i = 0; i < numpoints; i++) {
        linkedList[i] = malloc((numpoints-i+1) * sizeof(vertexEdge));
        nodePtr = linkedList[i];
        nodePtr->edgeSize = 0;
        nodePtr->vertex = i;
        nodePtr++;
        for (j = i+1; j < numpoints; j++){
            randNum = rand()/a;
            nodePtr->edgeSize = randNum;
            nodePtr->vertex = j;
            if ((numpoints > 1000 && randNum > 0.02) ||
                (numpoints > 10000 && randNum > 0.003) ||
                (numpoints > 20000 && randNum > 0.0015)){
                nodePtr--;
            }
            nodePtr++;
        }
        (nodePtr)->vertex = -1;
    }
    return linkedList;
}

vertexEdge **
generate2d(int mode, int numpoints, vertexEdge **linkedList){
    struct timeval tim;
    gettimeofday(&tim, NULL);
    unsigned int seed = (unsigned int) tim.tv_sec * (unsigned int)tim.tv_usec;
    srand(seed);
    
    float a = RAND_MAX;
	float points[numpoints][2];
	float distance, xd, yd;
    int i, j;
    vertexEdge *nodePtr;
    
    for (i = 0; i < numpoints; i++){
        for (j = 0; j < 2; j++){
            points[i][j] = rand() / a;
        }
    }
    
    for (i = 0; i < numpoints; i++) {

        linkedList[i] = malloc((numpoints-i+1) * sizeof(vertexEdge));
        nodePtr = linkedList[i];
        nodePtr->edgeSize = 0;
        nodePtr->vertex = i;
        nodePtr++;
        
        for (j = i+1; j < numpoints; j++){
            xd = (points[i][0] - points[j][0]);
            yd = (points[i][1] - points[j][1]);
            distance = sqrt(xd * xd + yd * yd);
            nodePtr->edgeSize = distance;
            nodePtr->vertex = j;
            if ((numpoints > 1000 && distance > 0.1) ||
                (numpoints > 10000 && distance > 0.05) ||
                (numpoints > 20000 && distance > 0.025)){
                nodePtr--;
            }
            nodePtr++;
        }
        (nodePtr)->vertex = -1;
    }
    return linkedList;
}

vertexEdge **
generate3d(int mode, int numpoints, vertexEdge **linkedList){
    struct timeval tim;
    gettimeofday(&tim, NULL);
    unsigned int seed = (unsigned int) tim.tv_sec * (unsigned int)tim.tv_usec;
    srand(seed);
    
    float a = RAND_MAX;
	float points[numpoints][3];
	float distance, xd, yd, zd;
    int i, j;
    vertexEdge *nodePtr;
    
    for (i = 0; i < numpoints; i++){
        for (j = 0; j < 3; j++){
            points[i][j] = rand() / a;
        }
    }
    
    for (i = 0; i < numpoints; i++) {

        linkedList[i] = malloc((numpoints-i+1) * sizeof(vertexEdge));
        nodePtr = linkedList[i];
        nodePtr->edgeSize = 0;
        nodePtr->vertex = i;
        nodePtr++;
        
        for (j = i+1; j < numpoints; j++){
            xd = (points[i][0] - points[j][0]);
            yd = (points[i][1] - points[j][1]);
            zd = (points[i][2] - points[j][2]);
            distance = sqrt(xd * xd + yd * yd + zd * zd);
            nodePtr->edgeSize = distance;
            nodePtr->vertex = j;
            if ((numpoints > 1000 && distance > 0.15) ||
                (numpoints > 10000 && distance > 0.09) ||
                (numpoints > 20000 && distance > 0.055)){
                nodePtr--;
            }
            nodePtr++;
        }
        (nodePtr)->vertex = -1;
    }
    return linkedList;
}

vertexEdge **
generate4d(int mode, int numpoints, vertexEdge **linkedList){
    struct timeval tim;
    gettimeofday(&tim, NULL);
    unsigned int seed = (unsigned int) tim.tv_sec * (unsigned int)tim.tv_usec;
    srand(seed);
    
    float a = RAND_MAX;
	float points[numpoints][4];
	float distance, xd, yd, zd, wd;
    int i, j;
    vertexEdge *nodePtr;
    
    for (i = 0; i < numpoints; i++){
        for (j = 0; j < 4; j++){
            points[i][j] = rand() / a;
        }
    }
    
    for (i = 0; i < numpoints; i++) {

        linkedList[i] = malloc((numpoints-i+1) * sizeof(vertexEdge));
        nodePtr = linkedList[i];
        nodePtr->edgeSize = 0;
        nodePtr->vertex = i;
        nodePtr++;
        
        for (j = i+1; j < numpoints; j++){
            xd = (points[i][0] - points[j][0]);
            yd = (points[i][1] - points[j][1]);
            zd = (points[i][2] - points[j][2]);
            wd = (points[i][3] - points[j][3]);
            distance = sqrt(xd * xd + yd * yd + zd * zd + wd * wd);
            nodePtr->edgeSize = distance;
            nodePtr->vertex = j;
            if ((numpoints > 1000 && distance > 0.25) ||
                (numpoints > 10000 && distance > 0.18) ||
                (numpoints > 20000 && distance > 0.15)){
                nodePtr--;
            }
            nodePtr++;
        }
        (nodePtr)->vertex = -1;
    }
    return linkedList;
}
