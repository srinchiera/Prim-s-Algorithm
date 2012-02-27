randmst: prim.c binHeap.c binHeap.h generate.h generate.c
	gcc -o randmst prim.c binHeap.c generate.c -std=c99 -g
