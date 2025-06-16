#include <stdio.h>
#include "grafos.h"

int main(){
	Grafo* grafo = inicializaGrafo();
	int vizinhos[15];
	int peso[15];
	if(criaVertice(grafo, vizinhos, peso, 0))
		printf("Inserido com sucesso!");
	return 0;
}