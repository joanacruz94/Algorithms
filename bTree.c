#include <stdio.h>
#include <stdlib.h>

typedef struct btree {
    int value;
    struct btree *left, *right;
} Node, *BTree;

int size(BTree b){
    if(b == NULL) return 0;
    else return size(b->left) + size(b->right) + 1;
}

int height(BTree b){
    if(b == NULL) return 0;
    else{
        int hRight = 1 + height(b->right);
        int hLeft = 1 + height(b->left);

        if(hRight > hLeft) return hRight;
        else return hLeft;
    }
}

BTree newNode(int data){
    struct btree* tree = (struct btree*) malloc(sizeof(struct btree));
    tree->value = data;
    tree->right = NULL;
    tree->left = NULL;
      
    return tree; 
}

BTree add(BTree b, int data){
    if(b == NULL) 
     return newNode(data);

    else if(data <= b->value){
        b->left = add(b->left, data);
    }
    else if(data > b->value){
        b->right = add(b->right, data);
    }

    return b;
}

void inorder(BTree b){ 
    if (b != NULL){ 
        inorder(b->left); 
        printf("%d \n", b->value); 
        inorder(b->right);
    } 
}

int search(BTree b, int data){
    if(b == NULL) return 1;
    else{
        if(data == b->value) return 0;
        else return search(b->left, data) || search(b->right, data);
    }
}

int max(BTree b){

    while(b->right){
        b = b->right;
    }

    return b->value;
}

int main(){
    BTree tree = malloc(sizeof(Node));
    tree = add(tree, 7);
    tree = add(tree, 3);
    tree = add(tree, 10);
    tree = add(tree, 12);
    
    int h = height(tree);
    int s = size(tree);

    printf("The size of the tree is %d and the height is %d\n", s, h);

    inorder(tree);

    s = size(tree);
    printf("The size of the tree is %d\n", s);

    int found = search(tree, 7);
    printf("Found the number %d\n", found);

    int maximum = max(tree);
    printf("The maximum number is %d\n", maximum);

    return 0;
}
 
    
