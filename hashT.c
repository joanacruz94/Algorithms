#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASHSIZE 31

typedef char KeyType[9];
typedef void *Info;

typedef struct entry {
    KeyType key;
    Info info;
    struct entry *next;
} Entry, *HashTable[HASHSIZE];

int hash(KeyType key){
    int total = 0, k; 

    for (k = 0; key[k] != '\0'; k++) 
        total += (int)key[k]; 
  
    return total % strlen(key); 
}

void initializeTable(HashTable hTable){
    int i = 0;

    for(; i < HASHSIZE; i++) hTable[i] = NULL;
}

void clearTable(HashTable hTable){
    int i = 0;
    Entry* it, *tmp;

    for(; i < HASHSIZE; i++){
        it = hTable[i];
        while(it != NULL){
            tmp = it;
            it = it->next;
            free(tmp);
        }
        hTable[i] = NULL;
    }
}

void insertTable(HashTable hTable, KeyType k, Info i){
    int h = hash(k);
    Entry* entry;

    for(entry = hTable[h]; entry != NULL && strcmp(entry->key, k); entry = entry->next);

    if(entry != NULL){
        strcpy(entry->info, i);
    }
    else{
        entry = (Entry*)malloc(sizeof(struct entry));
        strcpy(entry->key, k);
        entry->info = (char*)malloc(sizeof(char) * strlen(i));
        strcpy(entry->info, i);
        entry->next = hTable[h];
        hTable[h] = entry;
    }
}

void deleteTable(HashTable hTable, KeyType k){
    int h = hash(k);
    Entry **it, *tmp;
    for (it = hTable+h; *it !=NULL && strcmp((*it)->key,k); it = &((*it)->next));
    tmp = *it;
    *it = (*it)->next;
    free(tmp);
}

Entry *retrieveTable(HashTable hTable, KeyType k){
    int h = hash(k);
    Entry *entry;

    for(entry = hTable[h]; entry != NULL && strcmp(entry->key, k); entry = entry->next);
    
    return entry;
}

void printHashTable(HashTable hTable){
    int i = 0;
    Entry *entry;

    for(; i < HASHSIZE; i++){
        printf("INDEX   %d", i);
        for(entry = hTable[i]; entry != NULL; entry = entry->next){
            printf("    ---> KEY %s VALUE %s", entry->key, entry->info);
        }
        printf("\n");
    }
}

int main(){
    HashTable hashTable;

    initializeTable(hashTable);

    insertTable(hashTable, "Joana", "ola");
    insertTable(hashTable, "Joanaaa", "qlqlql");
    insertTable(hashTable, "Joanaaaa", "infoo");
    
    printHashTable(hashTable);

    Entry *entry = retrieveTable(hashTable, "Joana");
    if(entry != NULL)
        printf("%s  %s\n", entry->key, entry->info);
   
    deleteTable(hashTable, "Joana");
    
    printHashTable(hashTable);

    clearTable(hashTable);

    printHashTable(hashTable);

    return 0;
}