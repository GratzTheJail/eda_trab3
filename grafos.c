//TESTE
#ifndef GRAFOS
#define GRAFOS
#include "grafos.h"
#endif
#include <stdlib.h>

Grafo* inicializaGrafo(){
    Grafo* grafo = (Grafo*)malloc(sizeof(Grafo));
    if(grafo == NULL)
        exit(1);
    grafo->viz = NULL;
    grafo->nv = 0;
    return grafo;
}

// vizinhos, peso = vetores com índices dos vertices que são vizinhos do nó a ser criado
//                  e o peso da respectiva aresta
// tam = quantidade de vizinhos (tamanho do vetor)
// retorna 1 caso insira corretamente, aborta programa caso contrário
// 
// nao pode ter deleção ou modificação
// cada posição no vetor grafo->viz corresponde a um vertice QUE EXISTE
// primeiro vértice tem n = 1, segundo tem n = 2, etc. Não existe vértice com n = 0.
int criaVertice(Grafo* grafo, int vizinhos[], float peso[], int tam){
    // aumenta o contador de vértices
    grafo->nv++;
    // insere novo vertice e o inicializa
    grafo->viz = postInsert(grafo->viz, grafo->nv);
    Node* vAtual = findNode(grafo->viz, grafo->nv);
    vAtual->obj = NULL;

    // se não tem vizinhos, não há mais nada a fazer
    if(tam == 0){
        return  1;
    }

    // para cada vértice dado na entrada (vizinhos) adicionar este vértice e seu peso à lista dos vizinhos
    for(int i = 0; i < tam; i++){
        // cria vizinho com peso efetivamente
        Viz* viz = (Viz*)malloc(sizeof(Viz));
        if(viz == NULL) exit(1);
        viz->peso = peso[i];
        viz->n = vizinhos[i];
        
        // insere novo elemento à lista
        vAtual->obj = (void*)postInsert(vAtual->obj, countNodes(vAtual->obj));
        Node* novoViz = findNode(vAtual->obj, countNodes(vAtual->obj) - 1);
        novoViz->obj = (void*)viz; // faz novo elemento apontar para o vizinho criado


        
        // para cada vizinho, adicionar na lista de arestas deste vizinho o novo vertice (vAtual)
        
        // cria a aresta para o vizinho respectivo com peso correto
        Viz* atual = (Viz*)malloc(sizeof(Viz));
        if(atual == NULL) exit(1);
        atual->peso = peso[i];
        atual->n = grafo->nv;

        // insere no na lista de arestas do vizinho
        novoViz = findNode(grafo->viz, vizinhos[i]);
        novoViz->obj = (void*)postInsert(novoViz->obj, countNodes(novoViz->obj));
        findNode(novoViz->obj, countNodes(novoViz->obj) - 1)->obj = (void*)atual; // faz nova aresta apontar para o vertice criado
    }

    return 1;
}

// imprime cada vértice e seus vizinhos (com pesos)
void imprimirGrafo(Grafo* grafo) {
    Node* vertice = grafo->viz;

    while (vertice != NULL) {
        printf("Vértice %d:", vertice->n);

        Node* vizinhos = (Node*)vertice->obj;

        while (vizinhos != NULL) {
            Viz* v = (Viz*)vizinhos->obj;
            if (v != NULL)
                printf(" -> %d (peso %.1f)", v->n, v->peso);
            vizinhos = vizinhos->next;
        }

        printf("\n");
        vertice = vertice->next;
    }
}