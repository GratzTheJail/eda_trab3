/*
Guilherme Melo Gratz - 2211068 - 3WA
Vinicius Lucena - 2210458 - 3WA

MODULO GRAFOS
*/

#ifndef LIST
#define LIST
#include "list/list.h"
#endif

typedef struct _grafo Grafo;
struct _grafo {
    int nv; /* numero de nos ou vertices */
    int na; /* numero de arestas */
    Node* viz; /* viz[i] aponta para a lista de arestas incidindo em i */
};

Grafo* inicializaGrafo();

// vizinhos, peso = vetores com índices dos vertices que são vizinhos do nó a ser criado
//                  e o peso da respectiva aresta
// tam = quantidade de vizinhos (tamanho do vetor)
// retorna 1 caso insira corretamente, aborta programa caso contrário
// 
// nao pode ter deleção ou modificação
// cada posição no vetor grafo->viz corresponde a um vertice QUE EXISTE
// primeiro vértice tem n = 1, segundo tem n = 2, etc. Não existe vértice com n = 0.
// NÃO CRIAR vértice com "arestas futuras"
int criaVertice(Grafo* grafo, int vizinhos[], float peso[], int tam);

// imprime cada vértice e seus vizinhos (com pesos)
void printGrafo(Grafo* grafo);

// libera memoria do grafo
void deletaGrafo(Grafo* grafo);

// Faz busca em profundida no grafo a partir do vértice inicial desejado
// (imprime cada vertice que visita)
void dfs(Grafo* grafo, int verticeInicial);

// realiza busca em amplitude
// (imprime cada vertice que visita)
void bfs(Grafo* grafo, int verticeInicial);

// Retorna um subgrafo do grafo g que contém a árvore geradora de custo mínimo
Grafo* kruskal(Grafo* g);