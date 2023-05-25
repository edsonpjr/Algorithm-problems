// Problema: https://iudex.io/problem/6153526597713f0001036ac9/statement

#include <stdio.h>
#include <stdlib.h>

typedef struct node{
	int id;
	int tempo;
	struct node *next;
	struct node *previous;
}NODE;

NODE *criaNo(int idNo, int tempoNo){
	NODE *node = (NODE*) malloc(sizeof(NODE));
	node -> id = idNo;
	node -> tempo = tempoNo;
	node -> next = NULL;
	node -> previous = NULL;

	return node;
}

void carregaPraPilha(NODE *headCircular, NODE *escalonador, NODE *headLifo, int *qtdNoCircular){
	int qtdAux = *qtdNoCircular;
	NODE *escalonadorW;
	NODE *escalonadorW_Aux;
	
	escalonador = escalonador -> next;
	
	if(escalonador -> tempo == 0){

		if(qtdAux == 1){
			headCircular -> next = NULL;
		}else if(qtdAux == 2){
			escalonadorW = headCircular -> next;
			escalonadorW -> next = escalonadorW;
			escalonadorW -> previous = escalonadorW;
		}else{
			escalonadorW = headCircular -> next;
			escalonadorW_Aux = escalonador -> next;
			escalonadorW_Aux -> previous = escalonador -> previous;
			escalonadorW -> next = escalonador -> next;
		}

		escalonador -> previous = NULL;

		escalonador -> next = headLifo -> next;
		headLifo -> next = escalonador;

		*qtdNoCircular = qtdAux - 1;
	}
	
}

void carregaPraFilaW(NODE *headFifo, NODE *headCircular, NODE *escalonador, int *qtdNoCircular){
	int qtdAux = *qtdNoCircular;
	
	headFifo -> next = escalonador -> next;
	NODE *escalonadorW;
	NODE *escalonadorW_Aux;
	if(qtdAux == 0){
		headCircular -> next = escalonador;
		escalonador -> next = escalonador;
		escalonador -> previous = escalonador;
	}else{
		escalonadorW = headCircular -> next;
		escalonadorW_Aux = escalonadorW -> next;
		escalonador -> next = escalonadorW -> next;
		escalonador -> previous = escalonadorW_Aux -> previous;
		escalonadorW -> next = escalonador;
		escalonadorW_Aux -> previous = escalonador;
	}

	*qtdNoCircular = qtdAux + 1;
}

void ProcessaNo_GiraFila(int tempoProcesso, NODE *headCircular, NODE *escalonador, int qtdNoCircular){
	int tempoAux;
	if(qtdNoCircular > 0){
		escalonador = headCircular -> next;
		tempoAux = escalonador -> tempo;
		tempoAux = tempoAux - tempoProcesso;

		if(tempoAux >= 0){
			escalonador -> tempo = tempoAux;
		}else{
			escalonador -> tempo = 0;
		}

		printf("PROC %d %d\n", escalonador -> id, escalonador -> tempo);
	}else{
		printf("PROC -1 -1\n");
	}

	headCircular -> next = escalonador -> previous; // girou
}

void descarregaPilha(NODE *headLifo){
	NODE *descarregador = headLifo -> next;

	headLifo -> next = descarregador -> next;
	descarregador -> next = NULL;

	printf("UNLD %d\n", descarregador -> id);
	
	free(descarregador);
}

int main(){
	int tempoProcesso;
	scanf("%d", &tempoProcesso);

	NODE *headFifo = (NODE*) malloc(sizeof(NODE));
	headFifo -> next = NULL;
	NODE *tailFifo = headFifo;

	NODE *headCircular = (NODE*) malloc(sizeof(NODE));
	headCircular -> next = NULL;
	int qtdNoCircular = 0;

	NODE *headLifo = (NODE*) malloc(sizeof(NODE));
	headLifo -> next = NULL;

	NODE *escalonador;
	NODE *escalonadorAux;
	int idNo, tempoNo;
	char operador[5];
	int terminou = 0;

	while(!terminou){
		scanf(" %s", operador);

		if(operador[0] == 'L'){
			scanf("%d %d", &idNo, &tempoNo);
			if(headFifo -> next == NULL){
				tailFifo = headFifo;
			}
			tailFifo -> next = criaNo(idNo, tempoNo);
			tailFifo = tailFifo -> next;
		}else if(operador[0] == 'P'){
			if(qtdNoCircular > 0){ //Fase 1
				escalonadorAux = headCircular -> next;
				carregaPraPilha(headCircular, escalonadorAux, headLifo, &qtdNoCircular);
			}

			if(headFifo -> next != NULL){ //Fase 2
				escalonador = headFifo -> next;
				carregaPraFilaW(headFifo, headCircular, escalonador, &qtdNoCircular);
			}

			ProcessaNo_GiraFila(tempoProcesso, headCircular, escalonador, qtdNoCircular); //Fase 3
			

		}else if(operador[0] == 'U'){
			if(headLifo -> next != NULL){
				descarregaPilha(headLifo);
			}
			
		}else if(operador[0] == 'E'){
			free(headFifo);
			free(headCircular);
			free(headLifo);
			terminou = 1;

		}else{
			continue;
		}
	}

	return 0;
}
