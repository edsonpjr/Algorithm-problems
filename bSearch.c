// Problema: https://vjudge.net/problem/SPOJ-BSEARCH1

#include <stdio.h>
#include <stdlib.h>

long long int binarySearch(long long int *vet, long long int tam, long long int elemento){    
    long long int left = 0;
    long long int right = tam - 1;

    while(left <= right){
        long long int position = (left + right)/2; 
        if(elemento == vet[position]){
            return position;
        }else if(elemento < vet[position]){
            right = position - 1;
        }else{
            left = position + 1;
        }  
    }
    return -1;
}

int main() {
    long long int tamVet;
    long long int qtdConsultas;
    scanf("%lld %lld", &tamVet, &qtdConsultas);

    long long int *vet = (long long int *) malloc(tamVet * sizeof(long long int));
    if(vet == NULL) exit(1);

    long long int elemento;
    for(long long int i = 0; i < tamVet; i++){
        scanf("%lld", &elemento);
        vet[i] = elemento;
    }

    long long int pos;
    for(long long int j = 0; j < qtdConsultas; j++){
        scanf("%lld", &elemento);
        pos = binarySearch(vet, tamVet, elemento);

        if(pos != -1){
            int terminou = 0;
            while(!terminou){
                if(vet[pos - 1] == vet[pos]){
                    pos--;
                }else{
                    terminou = 1;
                }            
            }
            printf("%lld\n", pos);
        }else{
            printf("%lld\n", pos);
        }
    }
    
  return 0;
}
