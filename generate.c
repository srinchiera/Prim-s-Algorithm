#include "generate.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

struct timeval;

float*
generate1d(int mode, int numpoints, float *array){
    struct timeval tim;
    
    gettimeofday(&tim, NULL);
    unsigned int seed = (unsigned int) tim.tv_sec * (unsigned int) tim.tv_usec;
    srand(seed);
    
    int i, j;
    
    float a = RAND_MAX;
    for (i = 0; i < numpoints; i++){
        for (j = i; j < numpoints; j++){
            if (i == j){
                array[i*numpoints + j] = 0;
            }
            else {
                array[i*numpoints + j] = rand() / a;
                array[j*numpoints + i] = array[i*numpoints + j];
            }
        }
    }
    
    return array;
}

float*
generate2d(int mode, int numpoints, float *array){
    struct timeval tim;
    gettimeofday(&tim, NULL);
    unsigned int seed = (unsigned int) tim.tv_sec * (unsigned int)tim.tv_usec;
    srand(seed);
    
    float a = RAND_MAX;
	float points[numpoints][2];
	float distance, xd, yd;
    int i, j;
    
    for (i = 0; i < numpoints; i++){
        for (j = 0; j < 2; j++){
            points[i][j] = rand() / a;
        }
    }
    
    for (i = 0; i < numpoints; i++){
        for (j = i; j < numpoints; j++){
            if (i == j){
                array[i*numpoints + j] = 0;
            }
            else {
                xd = (points[i][0] - points[j][0]);
                yd = (points[i][1] - points[j][1]);
                distance = sqrt(xd * xd + yd * yd);
                array[i*numpoints + j] = distance;
                array[j*numpoints + i] = array[i*numpoints + j];
            }
        }
    }
    
    return array;
}
float*
generate3d(int mode, int numpoints, float *array){
    struct timeval tim;
    gettimeofday(&tim, NULL);
    unsigned int seed = (unsigned int)tim.tv_sec * (unsigned int)tim.tv_usec;
    srand(seed);
    
    float a = RAND_MAX;
	float points[numpoints][3];
	float distance, xd, yd, zd;
    int i, j;
    
    for (i = 0; i < numpoints; i++){
        for (j = 0; j < 3; j++){
            points[i][j] = rand() / a;
        }
    }
    
    for (i = 0; i < numpoints; i++){
        for (j = i; j < numpoints; j++){
            if (i == j){
                array[i*numpoints + j] = 0;
            }
            else {
                xd = (points[i][0] - points[j][0]);
                yd = (points[i][1] - points[j][1]);
                zd = (points[i][2] - points[j][2]);
                distance = sqrt(xd * xd + yd * yd + zd * zd);
                array[i*numpoints + j] = distance;
                array[j*numpoints + i] = array[i*numpoints + j];
            }
        }
    }
    
    return array;
}

float*
generate4d(int mode, int numpoints, float *array){
    struct timeval tim;
    gettimeofday(&tim, NULL);
    unsigned int seed = (unsigned int) tim.tv_sec * (unsigned int) tim.tv_usec;
    srand(seed);
    
    float a = RAND_MAX;
	float points[numpoints][4];
	float distance, xd, yd, zd, wd;
    int i, j;
    
    for (i = 0; i < numpoints; i++){
        for (j = 0; j < 4; j++){
            points[i][j] = rand() / a;
        }
    }
    
    for (i = 0; i < numpoints; i++){
        for (j = i; j < numpoints; j++){
            if (i == j){
                array[i*numpoints + j] = 0;
            }
            else {
                xd = (points[i][0] - points[j][0]);
                yd = (points[i][1] - points[j][1]);
                zd = (points[i][2] - points[j][2]);
                wd = (points[i][3] - points[j][3]);
                distance = sqrt(xd * xd + yd * yd + zd * zd + wd * wd);
                array[i*numpoints + j] = distance;
                array[j*numpoints + i] = array[i*numpoints + j];
            }
        }
    }
    
    return array;
}
