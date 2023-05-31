// Problema: https://vjudge.net/problem/SPOJ-KNAPSACK

#include <stdio.h>
#include <stdlib.h>

int knapsackTPD(int l, int c, int *w, int *v, int **m);
int max(int a, int b);

int main(void) {
    int limite, qtdItens;
    scanf("%d %d", &limite, &qtdItens);
    
    int *w = (int *) malloc((qtdItens + 1) * sizeof(int));
    int *v = (int *) malloc((qtdItens + 1) * sizeof(int));

    int tam, val;
    
    int **m;
    m = (int **) malloc((qtdItens + 1) * sizeof(int *));
    m[0] = (int *) malloc((limite + 1) * sizeof(int));
    for(int i = 1; i <= qtdItens; i++){
        scanf("%d %d", &tam, &val);
        
        w[i] = tam;
        v[i] = val;

        m[i] = (int *) malloc((limite + 1) * sizeof(int));
        m[i][0] = 0;
        for(int j = 1; j <= limite; j++){
            m[i][j] = -10;
            m[0][j] = 0;
        }
    }
    
    int solution = knapsackTPD(qtdItens, limite, w, v, m);

    printf("%d", solution);
   
    return 0;
}

int max(int a, int b){
    if(a >= b) return a;

    return b;
}

int knapsackTPD(int l, int c, int *w, int *v, int **m){
    if(m[l][c] < 0){
        int val;
        if(c < w[l]){
            val = knapsackTPD(l - 1, c, w, v, m);
        }else{
            val = max(knapsackTPD(l - 1, c, w, v, m), v[l] + knapsackTPD(l - 1, c - w[l], w, v, m));
        }
        m[l][c] = val;
    }

    return m[l][c];
}
