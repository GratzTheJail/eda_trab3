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
    return grafo;
}

int criaVertice(Grafo* grafo, int vizinhos[], int peso[], int tam){
    grafo->nv++;
    grafo->viz = postInsert(grafo->viz, grafo->nv);
    Node* vAtual = findNode(grafo->viz, grafo->nv);
    vAtual->obj = NULL;

    if(tam == 0){
        return  1;
    }

    for(int i = 0; i < tam; i++){
        Viz* viz = (Viz*)malloc(sizeof(Viz));
        if(viz == NULL) exit(1);

        viz->peso = peso[i];
        viz->n = vizinhos[i];

        vAtual->obj = (void*)postInsert(vAtual->obj, countNodes(vAtual->obj));
    }

    return 1;
}

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
