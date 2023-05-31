// Problema: https://vjudge.net/problem/Aizu-GRL_4_B

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <stack>

typedef struct g{
    bool **matrix;
    char *mark;
    int qtdV;
}GRAPH;

GRAPH *create_graph(int n);
int first(GRAPH *g, int v);
int next(GRAPH *g, int v, int w);
void setEdge(GRAPH *g, int i, int j);
void toposort(GRAPH *g, int v, std::stack<int>* s);
int n(GRAPH *g){    return g->qtdV;     }


int main() {
    int qtdV;
    long long int qtdA;
    scanf("%d %lld", &qtdV, &qtdA);
    
    GRAPH *g = create_graph(qtdV);
    int origem, fim;
    for(long long int i = 0; i < qtdA; i++){
        scanf("%d %d", &origem, &fim);
        setEdge(g, origem, fim);
    }
    
    std::cout << std::endl;

    std::stack<int> pilha;
    for(int j = 0; j < n(g); j++)
        toposort(g, j, &pilha);

    while(!pilha.empty()){
        std::cout << pilha.top() << std::endl;
        pilha.pop();
    }
    
    return 0;
}

GRAPH *create_graph(int n){
    GRAPH *g = (GRAPH *) malloc(sizeof(GRAPH));

    g->mark = (char *) malloc(n * sizeof(char));    
    g->matrix = (bool **) malloc(n * sizeof(bool*)); 
    for(int i = 0; i < n; i++){
        g->mark[i] = 'U';
        g->matrix[i] = (bool *) calloc(n, sizeof(bool)); 

    }
   // g->numEdge = 0;
    g->qtdV = n;
    
    return g;
}

int first(GRAPH *g, int v){
    for(int i = 0; i < n(g); i++){
        if(g->matrix[v][i] != 0) return i;
    }
    
    return n(g);
}

int next(GRAPH *g, int v, int w){
    for(int i = w + 1; i < n(g); i++){
        if(g->matrix[v][i] != 0) return i;
    }
    
    return n(g);
}

void setEdge(GRAPH *g, int i, int j){
    if(g->matrix[i][j] == 0 && i != j){
        g->matrix[i][j] = 1;
    }
    
    return;
}

void toposort(GRAPH *g, int v, std::stack<int>* s){
    if(g->mark[v] == 'V') return;
    
    g->mark[v] = 'V';
    int w = first(g, v);

    while(w < n(g)){
        if(g->mark[w] == 'U'){
            toposort(g, w, s);
        }

        w = next(g, v, w);
    }

    s->push(v);
    
    return;
}
