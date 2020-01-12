#include <stdio.h>
#include <stdlib.h>

#define NV 6
#define NE 9

typedef int GraphMat[NV][NV];

typedef struct edge{
    int destination;
    int cost;
    struct edge *next;
}*Edge;

typedef Edge GraphList[NV];

typedef struct edgeV{
    int destination;
    int cost;
}EdgeV;

typedef struct{
    int vertex[NV+1];
    EdgeV edges[NE];
}GraphVertex;

void listToMat(GraphList list, GraphMat mat){
    int i = 0;
    Edge edge;

    for(; i < NV; i++){
        for(edge = list[i]; edge != NULL; edge = edge->next){
            mat[i][edge->destination] = edge->cost;
        }
    }
}

void matToList(GraphMat mat, GraphList list){
    int i, j;

    for(i = 0; i < NV; i++) list[i] = NULL;

    for(i = 0; i < NV; i++){
        for(j = NV - 1; j >= 0; j--){
            if(mat[i][j] != 0){
                Edge edge = (Edge)malloc(sizeof(Edge));
                edge->destination = j;
                edge->cost = mat[i][j];
                edge->next = list[i];
                list[i] = edge;
            }
        }
    }
}

int inDegreeMat(GraphMat mat, int vertex){
    int result = 0, i = 0;

    for(; i < NV; i++) if(mat[i][vertex] != 0) result++;

    return result;
}

int inDegreeList(GraphList list, int vertex){
    int result = 0, i = 0;
    Edge edge;

    for(; i < NV; i++){
        for(edge = list[i]; edge != NULL; edge = edge->next){
            if(edge->destination == vertex) result++;
        }
    }

    return result;
}

int outDegreeMat(GraphMat mat, int vertex){
    int result = 0, i = 0;

    for(; i < NV; i++) if(mat[vertex][i] != 0) result++;

    return result;
}

int outDegreeList(GraphList list, int vertex){
    int result = 0;
    Edge edge = list[vertex];

    for(; edge != NULL; edge = edge->next) result++;

    return result;
}

int capacityMat(GraphMat mat, int vertex){
    return inDegreeMat(mat, vertex) - outDegreeMat(mat, vertex);
}

int capacityList(GraphList list, int vertex){
    return inDegreeList(list, vertex) - outDegreeList(list, vertex);
}

int maxCapacityMat(GraphMat mat){
    
}

int maxCapacityList(GraphList list){

}

void printMat(GraphMat mat){
    int i, j;

    for(i = 0; i < NV; i++){
        for(j = 0; j < NV; j++){
            printf("%d ",mat[i][j]);
        }
        printf("\n");
    }
}

void printList(GraphList list){
    int i;
    Edge edge;

    for(i = 0; i < NV; i++){
        printf("| %d | -->", i);
        for(edge = list[i]; edge != NULL; edge = edge->next){
            printf("|%d|%d|->", edge->destination, edge->cost);
        }
        printf("\n");
    }
}

Edge newEdge(int dest, int c){
    Edge edge = (Edge)malloc(sizeof(Edge));
    edge->destination = dest;
    edge->cost = c;
    edge->next = NULL;

    return edge;
}

void insertEdge(GraphList list, int origin, Edge edge){
    edge->next = list[origin];
    list[origin] = edge;
}

void initList(GraphList list){
    int i;

    for(i = 0; i < NV; i++){
        list[i] = NULL;
    }
}

int main(){
    
    GraphMat mat /* = { 0 };*/
                    = {{0,2,7,0,0,0},
                    {0,0,0,1,0,0},
                    {0,0,0,0,0,1},
                    {5,0,0,0,8,0},
                    {3,0,0,0,0,0},
                    {4,0,0,3,2,0}};

    printMat(mat);


    /*Edge e01 = newEdge(1,2);
    Edge e02 = newEdge(2,7);
    Edge e13 = newEdge(3,1);
    Edge e25 = newEdge(5,1);
    Edge e30 = newEdge(0,5);
    Edge e34 = newEdge(4,8);
    Edge e40 = newEdge(0,3);
    Edge e50 = newEdge(0,4);
    Edge e53 = newEdge(3,3);
    Edge e54 = newEdge(4,2);*/

    GraphList list;

    initList(list);

    /*insertEdge(list, 0, e01);
    insertEdge(list, 0, e02);
    insertEdge(list, 1, e13);
    insertEdge(list, 2, e25);
    insertEdge(list, 3, e30);
    insertEdge(list, 3, e34);
    insertEdge(list, 4, e40);
    insertEdge(list, 5, e50);
    insertEdge(list, 5, e53);
    insertEdge(list, 5, e54);

    printList(list);*/

    matToList(mat, list);
    printList(list);

    printf("IN DEGREE MATRIX IN VERTEX 0 %d\n", inDegreeMat(mat, 0));
    printf("IN DEGREE LIST IN VERTEX 0 %d\n", inDegreeList(list, 0));
    printf("OUT DEGREE MATRIX IN VERTEX 0 %d\n", outDegreeMat(mat, 0));
    printf("OUT DEGREE LIST IN VERTEX 0 %d\n", outDegreeList(list, 0));

    return 0;
}