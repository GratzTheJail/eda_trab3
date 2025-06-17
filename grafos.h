/*
Guilherme Melo Gratz - 2211068 - 3WA
Vinicius Lucena - 2210458 - 3WA

MODULO GRAFOS
*/

#ifndef LIST
#define LIST
#include "list/list.h"
#endif
// teste
typedef struct _viz Viz;
struct _viz {
    int n;
    float peso;
    // Node* prox;
};

typedef struct _grafo Grafo;
struct _grafo {
    int nv; /* numero de nos ou vertices */
    int na; /* numero de arestas */
    Node* viz; /* viz[i] aponta para a lista de arestas incidindo em i */
};

Grafo* inicializaGrafo();

// cria um vertice na ultima posição da lista de vertices do grafo
// adiciona seus vizinhos (suas arestas)
// no campo de cada vizinho adiciona o novo vértice como vizinho (aresta)
int criaVertice(Grafo* grafo, int vizinhos[], float peso[], int tam);

// imprime cada vertice e cada aresta de cada vértice
void imprimirGrafo(Grafo* grafo);

// TODO
void deletaGrafo(Grafo* grafo);

void dfs(Grafo* grafo, int verticeInicial);

void bfs(Grafo* grafo, int verticeInicial);