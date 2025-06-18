/*
Guilherme Melo Gratz - 2211068 - 3WA
Vinicius Lucena - 2210458 - 3WA

MODULO PRINCIPAL: TESTES
*/

#include <stdio.h>
#include "grafos.h"

int main() {
    // Inicializa o grafo
    Grafo* grafo = inicializaGrafo();

    // Vetores temporários para inserir vizinhos
    int vizinhos[15];
    float peso[15];

    // Vértice 1 -> conectado a 2 e 3
    vizinhos[0] = 2; peso[0] = 5.0f;
    vizinhos[1] = 3; peso[1] = 3.0f;
    criaVertice(grafo, vizinhos, peso, 2);

    // Vértice 2 -> conectado a 1, 5 e 4
    vizinhos[0] = 1; peso[0] = 5.0f;
    vizinhos[1] = 5; peso[1] = 2.0f;
    vizinhos[2] = 4; peso[2] = 6.0f;
    criaVertice(grafo, vizinhos, peso, 3);

    // Vértice 3 -> conectado a 1 e 5
    vizinhos[0] = 1; peso[0] = 3.0f;
    vizinhos[1] = 5; peso[1] = 4.0f;
    criaVertice(grafo, vizinhos, peso, 2);

    // Vértice 4 -> conectado a 2
    vizinhos[0] = 2; peso[0] = 6.0f;
    criaVertice(grafo, vizinhos, peso, 1);

    // Vértice 5 -> conectado a 2 e 3
    vizinhos[0] = 2; peso[0] = 2.0f;
    vizinhos[1] = 3; peso[1] = 4.0f;
    criaVertice(grafo, vizinhos, peso, 2);

    // Imprime o grafo
    printf("== GRAFO CRIADO ==\n");
    imprimirGrafo(grafo);
    printf("\nVertices: %d | Arestas: %d\n\n", grafo->nv, grafo->na);

    // Testa DFS a partir do vértice 1
    printf("== BUSCA EM PROFUNDIDADE (DFS) ==\n");
    dfs(grafo, 1);
    printf("\n");

    // Testa BFS a partir do vértice 1
    printf("\n== BUSCA EM LARGURA (BFS) ==\n");
    bfs(grafo, 1);
    printf("\n");

    return 0;
}
/*
COMPILAÇÃO
Linux Fedora 42 
gcc 15.1.1

comando:
gcc -Wall -o prog main.c grafos.c list/list.c
*/