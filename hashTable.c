#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASHSIZE 31
#define EMPTY ""
#define DELETED "-"

typedef char KeyType[9];
typedef void *Info;

typedef struct entry {
    KeyType key;
    Info info;
} Entry, HashTable[HASHSIZE];


int hash(KeyType key){
    int total = 0, k; 

    for (k = 0; key[k] != '\0'; k++) 
        total += (int)key[k]; 
  
    return total % strlen(key); 
}

void initializeTable(HashTable hTable){
    int i;

    for(i = 0; i < HASHSIZE; i++){
        strcpy(hTable[i].key, EMPTY);
        hTable[i].info = NULL;
    }
}

void clearTable(HashTable hTable){
    int i;

    for(i = 0; i < HASHSIZE; i++){
        free(hTable[i].key);
        free(hTable[i].info);
    }
}

void insertTable_LP(HashTable hTable, KeyType k, Info i){
    int index = hash(k);

    while(strcmp(hTable[index].key, EMPTY)){
        index++;
        if(HASHSIZE == index - 1){
            index = 0;
        }
    }

    strcpy(hTable[index].key, k);
    hTable[index].info = i;
}

void deleteTable_LP(HashTable hTable, KeyType k){
    int index = hash(k);
    
    while(strcmp(hTable[index].key, k)){
        index++;
        if(HASHSIZE == index - 1){
            index = 0;
        }
    }

    strcpy(hTable[index].key, DELETED);
    hTable[index].info = NULL;
}

int retrieveTable_LP(HashTable hTable, KeyType k){
    int index = hash(k);
    int found = index;
    
    while(strcmp(hTable[index].key, k)){
        index++;
        if(HASHSIZE == index - 1){
            index = 0;
        }
        if(found == index) return -1;
    }

    return index;
}

int hash_QP(KeyType key, int d){
    int total = 0, k; 

    for (k = 0; key[k] != '\0'; k++) 
        total += (int)key[k]; 
  
    return (total % strlen(key)) + d; 
}

void insertTable_QP(HashTable hTable, KeyType k, Info i){
   
}

void deleteTable_QP(HashTable hTable, KeyType k){

}

int retrieveTable_QP(HashTable hTable, KeyType k){
   
}

int main(){
    HashTable hash_table;
    initializeTable(hash_table);
    insertTable_LP(hash_table, "joana", "nothing");
    insertTable_LP(hash_table, "joanaaa", "nothing");
    deleteTable_LP(hash_table, "joanaaa");
    for(int i = 0; i < HASHSIZE; i++){
        printf("i = %d | key = %s | info = %s\n", i, hash_table[i].key, hash_table[i].info);
    }

    int f1 = retrieveTable_LP(hash_table, "joana");
    int f2 = retrieveTable_LP(hash_table, "ola");

    printf("%d %d\n", f1, f2);

    return 0;
}