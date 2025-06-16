#include <stdio.h>
#include "grafos.h"

int main(){
	Grafo* grafo = inicializaGrafo();
	int vizinhos[15];
	float peso[15];
	if(criaVertice(grafo, vizinhos, peso, 0))
		printf("Inserido com sucesso!");
	
	vizinhos[0] = 1;
	peso[0] = 8.0f;
	criaVertice(grafo, vizinhos, peso, 1);

	vizinhos[0] = 1;
	vizinhos[1] = 2;
	peso[0] = 4.0f;
	peso[1] = 12.0f;
	criaVertice(grafo, vizinhos, peso, 2);

	criaVertice(grafo, vizinhos, peso,0);

	vizinhos[0] = 1;
	peso[0] = 4.4f;
	criaVertice(grafo, vizinhos, peso, 1);

	imprimirGrafo(grafo);
	return 0;
}