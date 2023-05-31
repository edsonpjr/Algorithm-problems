// Problema: https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3769

#include <stdio.h>
#include <stdlib.h>

typedef struct BSTNode{
    long long int element;
    struct BSTNode *left;
    struct BSTNode *right;    
}BST_NODE;

typedef struct bst{
    BST_NODE *root;
    int qtdNodes;
}BST;

BST_NODE *createNode(long long int elemento);
BST *createBST();
void insert(BST *bst, long long int elemento);
BST_NODE *insertNode(BST_NODE *rt, long long int elemento);
void postOrder(BST *bst);
void postOrder_print(BST_NODE *rt);

int main() {
    BST *bst = createBST();

    long long int chave;
    while(scanf("%lld", &chave) != EOF){
        insert(bst, chave);    
    }

    postOrder(bst);
    
  return 0;
}


BST_NODE *createNode(long long int elemento){
    BST_NODE *node = (BST_NODE *) malloc(sizeof(BST_NODE));
    node -> element = elemento;
    node -> left = NULL;
    node -> right = NULL;
    
    return node;
}

BST *createBST(){
    BST *bst = (BST *) malloc(sizeof(BST));
    bst -> root = NULL;
    bst -> qtdNodes = 0;
    
    return bst;
}

void insert(BST *bst, long long int elemento){
    bst -> root = insertNode(bst -> root, elemento);
    bst -> qtdNodes += 1;
    
    return;
}

BST_NODE *insertNode(BST_NODE *rt, long long int elemento){
    if(rt == NULL) return createNode(elemento);

    if(rt -> element > elemento){
        rt -> left = insertNode(rt -> left, elemento);
    }else{
         rt -> right = insertNode(rt -> right, elemento);
    }
    
    return rt;
}

void postOrder(BST *bst){
    postOrder_print(bst -> root);
    
    return;
}

void postOrder_print(BST_NODE *rt){
    if(rt != NULL){
        postOrder_print(rt -> left);
        postOrder_print(rt -> right);
        printf("%lld\n", rt -> element);
        free(rt);
    }
    
    return;
}
