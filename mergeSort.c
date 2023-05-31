// Problema: https://codeforces.com/problemset/problem/1132/B

#include <stdio.h>
#include <stdlib.h>

void mergeSort(long long int *vet, long long int left, long long int right, long long int *vetAux);
void merge(long long int *vet, long long int left, long long int right, long long int *vetAux);

int main(){
    long long int tamVet;
    scanf("%lld", &tamVet);

    long long int *vet = (long long int *) malloc(sizeof(long long int) * tamVet);
    long long int *vetAux = (long long int *) malloc(sizeof(long long int) * tamVet);
    
    long long int valorBarra;
    long long int soma = 0;
    
    for(long long int i = 0; i < tamVet; i++){
        scanf("%lld", &valorBarra);
        vet[i] = valorBarra;
        soma += vet[i];
    }
    
    mergeSort(vet, 0, tamVet - 1, vetAux);
    
    long long int qtdCupons;
    scanf("%lld", &qtdCupons);
    
    long long int valorCupom;
    
    for(long long int j = 0; j < qtdCupons; j++){
        scanf("%lld", &valorCupom);
        valorBarra = vet[tamVet - valorCupom];
        soma -= valorBarra;
        printf("%lld\n", soma);
        soma += valorBarra;
    }

    free(vet);
    free(vetAux);
    return 0;
}

void merge(long long int *vet, long long int left, long long int right, long long int *vetAux){
    for(long long int k = left; k <= right; k++){
        vetAux[k] = vet[k];
    }
    long long int meio = (left + right)/2;
    long long int i = left;
    long long int j = meio + 1;
    
    for(long long int atual = left; atual <= right; atual++){
        if(i == meio + 1){
            vet[atual] = vetAux[j];
            j++;
        }else if(j > right){
            vet[atual] = vetAux[i];
            i++;
        }else if(vetAux[i] <= vetAux[j]){
            vet[atual] = vetAux[i];
            i++;
        }else{
            vet[atual] = vetAux[j];
            j++;
        }
    }
    
    return;
}

void mergeSort(long long int *vet, long long int left, long long int right, long long int *vetAux){
    if(left < right){
        long long int meio = (left + right)/2;
        mergeSort(vet, left, meio, vetAux);
        mergeSort(vet, meio + 1, right, vetAux);
        merge(vet, left, right, vetAux);
    }
    
    return;
}
