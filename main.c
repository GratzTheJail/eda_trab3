/*
Guilherme Melo Gratz - 2211068 - 3WA
Vinicius Lucena - 2210458 - 3WA

MODULO PRINCIPAL: TESTES
*/

#include <stdio.h>
#include "grafos.h"

int main(){
	Grafo* grafo = inicializaGrafo();
	int vizinhos[15];
	float peso[15];
	criaVertice(grafo, vizinhos, peso, 0);
	
	vizinhos[0] = 1;
	peso[0] = 8.0f;
	criaVertice(grafo, vizinhos, peso, 1);

	vizinhos[0] = 1;
	vizinhos[1] = 2;
	peso[0] = 4.0f;
	peso[1] = 12.0f;
	criaVertice(grafo, vizinhos, peso, 2);

	criaVertice(grafo, vizinhos, peso,0);

	vizinhos[0] = 55;
	peso[0] = 4.4f;
	criaVertice(grafo, vizinhos, peso, 1);

	imprimirGrafo(grafo);
	printf("Vertices: %d | Arestas: %d\n", grafo->nv, grafo->na);
	return 0;
}

/*
COMPILAÇÃO
Linux Fedora 42 
gcc 15.1.1

comando:
gcc -Wall -o prog main.c grafos.c list/list.c
*/