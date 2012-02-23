#include <stdio.h>
#include <stdlib.h>

void generate1d(int n);
void generate2d(int n);
void generate3d(int n);
void generate4d(int n);

int
main(int argc, char *argv[]){
    
    int numpoints, numtrials, mode;
    int (*generateGraph)(int);
    if (argc != 5) {
        printf("usage: randmst mode numpoints numtrials dimension\n");
        return 1;
    }
    
    if ((numpoints = atoi(argv[2]) < 0)) {
        printf("numpoints must be at least 0\n");
        return 1;
    }
    
    if ((numtrials = atoi(argv[3]) < 0)) {
        printf("numtrials must be at leaset 0\n");
        return 1;
    }
    
    if ((mode = atoi(argv[3]) < 0)) {
        printf("mode must be between 0 and 3, inclusive\n");
        return 1;
    }
    
    switch (atoi(argv[4])) {
        case 1:
            generate1d;
            break;
        case 2:
            generate2d;
        case 3:
            generate3d;
        case 4:
            generate4d;
        default:
            printf("dimensions must be between 1 and 4\n");
            return 1;
            break;
    }    
    
    
    
}

void
generate1d(int n){
    
}

void
generate2d(int n){
    
}
void
generate3d(int n){
    
}
void
generate4d(int n){
    
}
