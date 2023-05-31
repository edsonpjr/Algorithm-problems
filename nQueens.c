// Problema: https://vjudge.net/problem/CodeChef-TIC04

#include <stdio.h>
#include <stdlib.h>

int cnt=0;
int queens(int l, char matrix[100][100], int n);
int valid(char matrix[100][100], int l, int i, int n);

int main() {
    char m[100][100];
    int n;
   
    scanf("%d", &n);
        
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            m[i][j] = '-';
        }
    }
        
        if (!queens(0, m, n)) printf("Not Possible");
    
    return 0;
}

int valid(char matrix[100][100], int l, int i, int n){
    int coluna = i;
    int linha = l;
    int l_aux = l;
    while(l > 0){
        if(matrix[l - 1][coluna] == 'Q') return 0;
        
        l--;
    }

    while(linha > 0 && coluna > 0){
        if(matrix[linha - 1][coluna - 1] == 'Q') return 0;
        
        linha--;
        coluna--;
    }
    while(l_aux > 0 && i < n){
        if(matrix[l_aux - 1][i + 1] == 'Q') return 0;
        
        i++;
        l_aux--;
    }

    return 1; 
}

int queens(int l, char matrix[100][100], int n){
    if(l == n){ 
      cnt++;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                printf("%c ", matrix[i][j]);
            }  
            
            printf("\n");
        } 
        
        printf("\n");
        
        return 1;
    }else{
        int controle = 0;
        for(int i = 0; i < n; i++){
            if(valid(matrix, l, i, n)){
                matrix[l][i] = 'Q';

                if(queens(l + 1, matrix, n)){
                    controle = 1;
                }
                matrix[l][i] = '-';
            }
        }
        return controle;  
    }
}
