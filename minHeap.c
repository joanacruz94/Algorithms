#include <stdio.h>
#include <stdlib.h>

#define PARENT(i) (i-1)/2
#define LEFT(i) 2*i + 1
#define RIGHT(i) 2*i + 2

typedef int Elem;

typedef struct minHeap{
    int size;
    int used;
    Elem *values;
}Heap;

Heap* newHeap(int size){
    struct minHeap* heap = (struct minHeap*)malloc(sizeof(struct minHeap));
    heap->size = size;
    heap->used = 0;
    heap->values = (Elem *)malloc(sizeof(int) * size);

    return heap;
}

int insertHeap(Heap *h, Elem x){
    if(h->used == h->size){
        h->size = 2 * (h->size);
        h->values = (Elem *)realloc(h->values, sizeof(int) * h->size);
    }
    h->values[h->used] = x;
    h->used++;

    return 0;
}

void insertArrayHeap(Heap *heap, Elem h[], int size){
    int i = 0;
    for(; i < size; i++) insertHeap(heap, h[i]);
}

void bubbleUp(Elem h[], int i){
    int elem = 0;
    while(h[PARENT(i)] > h[i]){
        elem = h[i];
        h[i] = h[PARENT(i)];
        h[PARENT(i)] = elem;
        i = PARENT(i);
    }
}

void printArray(Elem h[], int size){
    int i = 0;
    printf("[ ");
    for(; i < size; i++) printf("%d, ", h[i]);
    printf("]\n");
}

void bubbleDown(Elem h[], int N){
    int elem = 0;
    while(h[N] < h[LEFT(N)] || h[N] < h[RIGHT(N)]){
        elem = h[N];
        if(LEFT(N) < RIGHT(N)){
            h[N] = h[LEFT(N)];
            h[LEFT(N)] = elem;
            N = LEFT(N);
        }
        else{
            h[N] = h[RIGHT(N)];
            h[RIGHT(N)] = elem;
            N = RIGHT(N);
        }
    }
}

int extractMin(Heap *h){
    h->values[0] = h->values[h->used - 1];
    h->values[h->used - 1] = 0;
    h->used--;
    bubbleDown(h->values, 0);

    return 0;
}

int minHeapOKAux(Heap *h, int i){
    if(i == h->used) return 0;
    printf("passei");
    return h->values[i] < h->values[LEFT(i)] && 
           h->values[i] < h->values[RIGHT(i)] &&
           minHeapOKAux(h, LEFT(i)) &&
           minHeapOKAux(h, RIGHT(i));
}

int minHeapOK(Heap *h){
    if(h == NULL) return 0;
    return minHeapOKAux(h, 0); 
}

int main(){
    Heap* heap = newHeap(15);
    Elem elements[10] = {4, 10, 21, 45, 13, 25, 22, 60, 100, 20}; 
    insertArrayHeap(heap, elements, 10);
    insertHeap(heap,6);
    printf("The size of the heap is %d and the number of used is %d\n", heap->size, heap->used);
    printArray(heap->values, heap->size);
    bubbleUp(heap->values, heap->used - 1);
    printArray(heap->values, heap->size);

    extractMin(heap);
    printArray(heap->values, heap->size);
    printf("Result of minHeapOk %d", minHeapOK(heap));
    return 0;
}





