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

    // GRAFO DO EX3 COMEÇANDO DO 1 AO INVES DE 0

    // Vértice 1 -> conectado a 2 e 8 (por enquanto sem aresta)
    criaVertice(grafo, vizinhos, peso, 0);

    // Vértice 2 -> conectado a 1, 8 e 3 (por enquanto sem aresta com 9 e 4)
    vizinhos[0] = 1; peso[0] = 4.0f;
    criaVertice(grafo, vizinhos, peso, 1);

    // Vértice 3 -> conectado a 2, 9, 6 e 4 (por enquanto só 2)
    vizinhos[0] = 2; peso[0] = 8.0f;
    criaVertice(grafo, vizinhos, peso, 1);

    // Vértice 4 -> conectado a 3, 6 e 5 (por enqnt só 3)
    vizinhos[0] = 3; peso[0] = 7.0f;
    criaVertice(grafo, vizinhos, peso, 1);

    // Vértice 5 -> conectado a 4 e 6 (p enqnt só 4)
    vizinhos[0] = 4; peso[0] = 9.0f;
    criaVertice(grafo, vizinhos, peso, 1);

    // Vértice 6 -> conectado a 3, 4, 5 e 7 (p enqnt só 3, 4 e 5)
    vizinhos[0] = 3; peso[0] = 4.0f;
    vizinhos[1] = 4; peso[1] = 14.0f;
    vizinhos[2] = 5; peso[2] = 10.0f;
    criaVertice(grafo, vizinhos, peso, 3);

    // Vértice 7 -> conectado a 6, 8 e 9 (p enqnt só 6)
    vizinhos[0] = 6; peso[0] = 2.0f;
    criaVertice(grafo, vizinhos, peso, 1);

    // Vértice 8 -> conectado a 1, 2, 9 e 7 (p enqnt só 1, 2, e 7)
    vizinhos[0] = 1; peso[0] = 8.0f;
    vizinhos[1] = 2; peso[1] = 11.0f;
    vizinhos[2] = 7; peso[2] = 1.0f;
    criaVertice(grafo, vizinhos, peso, 3);  
    
    // Vértice 9 -> conectado a 3, 7, e 8
    vizinhos[0] = 3; peso[0] = 2.0f;
    vizinhos[1] = 7; peso[1] = 6.0f;
    vizinhos[2] = 8; peso[2] = 7.0f;
    criaVertice(grafo, vizinhos, peso, 3);      
    
    // Imprime o grafo
    printf("== GRAFO CRIADO ==\n");
    printGrafo(grafo);
    printf("\nVertices: %d | Arestas: %d\n\n", grafo->nv, grafo->na);

    // Testa DFS a partir do vértice 1
    printf("== BUSCA EM PROFUNDIDADE (DFS) ==\n");
    printf("DFS a partir do vertice %d:\n", 1);
    dfs(grafo, 1);
    printf("\n");

    // Testa BFS a partir do vértice 1
    printf("\n== BUSCA EM AMPLITUDE (BFS) ==\n");
    printf("BFS iniciado a partir do vertice %d:\n", 1);
    bfs(grafo, 1);
    printf("\n");

    printf("\n== CRIAÇÃO DA ÁRVORE GERADORA MÍNIMA USANDO KRUSKAL==\n");
    Grafo* arvore = kruskal(grafo);
    if(arvore != NULL)
        printGrafo(arvore);

    deletaGrafo(grafo);
    deletaGrafo(arvore);

    return 0;
}
/*
COMPILAÇÃO
Linux Fedora 42 
gcc 15.1.1

comando:
gcc -Wall -o prog main.c grafos.c list/list.c
*/
