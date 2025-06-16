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