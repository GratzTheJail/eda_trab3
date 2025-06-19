/*
Guilherme Melo Gratz - 2211068 - 3WA
Vinicius Lucena - 2210458 - 3WA

MODULO GRAFOS
*/
#ifndef GRAFOS
#define GRAFOS
#include "grafos.h"
#include <float.h>
#include <stdio.h>
#define MAX_VERTICES 9
#define MAX_FILA 9
#endif
#include <stdlib.h>

Grafo* inicializaGrafo(){
    Grafo* grafo = (Grafo*)malloc(sizeof(Grafo));
    if(grafo == NULL)
        exit(1);
    grafo->viz = NULL;
    grafo->nv = 0;
    grafo->na = 0;
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
// NÃO CRIAR vértice com "arestas futuras"
int criaVertice(Grafo* grafo, int vizinhos[], float peso[], int tam){
    if(grafo == NULL)
        return 0;

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
        if(vizinhos[i] <= countNodes(grafo->viz)){
            grafo->na++;

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
            if(novoViz != NULL){
                // checa que essa aresta não foi adicionada ainda
                if(findNode(novoViz->obj, atual->n) == NULL){
                    // insere e faz nova aresta apontar para o vertice criado
                    novoViz->obj = (void*)postInsert(novoViz->obj, atual->n);
                    findNode(novoViz->obj, atual->n)->obj = (void*)atual; 
                }
            }
        }
    }

    return 1;
}

// imprime cada vértice e seus vizinhos (com pesos)
void printGrafo(Grafo* grafo) {
    if(grafo == NULL || grafo->viz == NULL)
        return;
    
    // percorre lista de vertices do grafo
    for(Node* v = grafo->viz; v != NULL; v = v->next) {
        printf("Vértice %d:", v->n);

        // percorre lista de arestas do grafo
        for(Node* vizs = (Node*)v->obj; vizs != NULL; vizs = vizs->next) {
            Viz* viz = (Viz*)vizs->obj;
            
            // imprime cada vizinho (aresta)
            if (viz != NULL)
                printf(" -> %d (peso %.1f)", viz->n, viz->peso);
        }

        printf("\n");
    }
}

// TODO
//void deletaGrafo(Grafo* grafo);

// Faz busca em profundida no grafo a partir do vértice inicial desejado
void dfs(Grafo* grafo, int verticeInicial){
    if(grafo == NULL || grafo->viz == NULL)
        return;

    // checa que o vertice inicial existe
    if (findNode(grafo->viz, verticeInicial) == NULL) {
        printf("Vertice %d nao existe no grafo.\n", verticeInicial);
        return; 
    }

    int visitados[MAX_VERTICES] = {0};
    // busca de fato é feita de forma recursiva
    dfsRecursiva(grafo, verticeInicial, visitados);
}

void dfsRecursiva(Grafo* grafo, int v, int visitados[]){
    if(grafo == NULL || grafo->viz == NULL)
        return;
    
    // marca o vertice como visitado
    visitados[v] = 1; 
    printf("Vertice visitado: %d\n", v);

    // encontra o vertice e pega sua lista de vizinhos
    
    Node* nodeVertice = findNode(grafo->viz, v); 
    
    // caso vertice nao tem vizinhos, a busca acaba
    if (nodeVertice == NULL || nodeVertice->obj == NULL)
        return;
    
    // percorre a lista de arestas
    for(Node* listaVizinhos = (Node*)nodeVertice->obj; 
        listaVizinhos != NULL; listaVizinhos = listaVizinhos->next){
        
        Viz* vizinho = (Viz*)listaVizinhos->obj;
        // caso o vizinho nao tenha sido visitado ainda, continua a procura a partir dele
        if (!visitados[vizinho->n]){
            dfsRecursiva(grafo, vizinho->n, visitados);
        }
    }
}


// funcao auxiliar de inserir na fila (sem struct auxiliar para a fila)
void fila_insere(int fila[], int* inicio, int* fim, int valor) {
    fila[(*fim)++] = valor;
}

// funcao auxiliar de remover na fila (sem struct auxiliar para fila)
int fila_retira(int fila[], int* inicio){ 
    return fila[(*inicio)++];
}

// realiza busca em amplitude
void bfs(Grafo* grafo, int verticeInicial){
    if(grafo == NULL || grafo->viz == NULL)
        return;

    // vetor que marca o vértices visitados
    int visitados[MAX_VERTICES] = {0};
    // fila para vértices a serem visitados
    int fila[MAX_FILA];
    int inicio = 0, fim = 0;

    // adiciona vertice inicial na fila 
    visitados[verticeInicial] = 1;
    fila_insere(fila, &inicio, &fim, verticeInicial);

    while (inicio < fim)
    {
        int v = fila_retira(fila, &inicio);
        printf("visitando vertice %d\n", v);
        
         // acessa vertice
        Node* nodeVertice = findNode(grafo->viz, v);
        
        // caso vertice nao tenha arestas, programa acaba
        if (nodeVertice == NULL || nodeVertice->obj == NULL)
            printf("vertice %d sem vizinhos", v);
    
        // percorre vizinhos
        for(Node* listaVizinhos = (Node*)nodeVertice->obj; listaVizinhos != NULL; 
                listaVizinhos = listaVizinhos->next){
            
            Viz* vizinho = (Viz*)listaVizinhos->obj;
            int vDestino = vizinho->n;
            
            // caso não tenha sido visitado ainda
            if(!visitados[vDestino]) {
                // marca como visitado e o adiciona na fila
                visitados[vDestino] = 1;
                fila_insere(fila, &inicio, &fim, vDestino);
            }
        }
    }
}

void addArestas(Grafo* g, Arst* arestas, int tam){
    if(g == NULL || g->viz == NULL)
        return;

    int i = 0;
    
    // percorre lista de vertices
    for(Node* v = g->viz; v != NULL; v = v->next){
        
        // percorre lista de arestas
        for(Node* viz = (Node*)v->obj; viz != NULL; viz = viz->next){
            Viz* vizinho = (Viz*)viz->obj;

            // para não adicionar 2 vezes a mesma aresta compara a ordem
            if (vizinho != NULL && v->n < vizinho->n && i < tam) {
                arestas[i].v1 = v->n;
                arestas[i].v2 = vizinho->n;
                arestas[i].peso = vizinho->peso;
                i++;
            }
        }
    }

    return;
}

// função que será usada por qsort
int cmpPeso(const void* a, const void* b){
    Arst* ar_a = (Arst*)a;
    Arst* ar_b = (Arst*)b;
    if (ar_a->peso < ar_b->peso) return -1;
    if (ar_a->peso > ar_b->peso) return 1;
    return 0;
}

// busca a raiz da árvore que contém o elemento
static int find(int x, int pai[]) {
    // caso base (encontrado a raíz)
    if (pai[x] == -1) {
        return x;
    }

    pai[x] = find(pai[x], pai);
    return pai[x];
}

// une dois grupos, fazendo com que a raiz de um grupo aponte para
static void Union(int x, int y, int pai[], int altura[]) {
    int raizX = find(x, pai);
    int raizY = find(y, pai);
    // caso sejam o mesmo conjunto não há nada a fazer
    if (raizX == raizY) return; 

    // caso a altura de um conjunto seja menor que de outro, apenas tornar a raíz de um
    // conjunto o pai da raíz do outro
    if (altura[raizX] < altura[raizY]) {
        pai[raizX] = raizY;
    } else if (altura[raizX] > altura[raizY]) {
        pai[raizY] = raizX;
    } 
    
    // caso a altura seja igual, escolhemos uma raíz que será pai da outra arbitráriamente
    // neste caso a altura aumenta em 1
    else {
        pai[raizY] = raizX;
        altura[raizX]++;
    }
}

// adicionar uma aresta entre 2 vértices diferentes na floresta de subgrafos
void conectaVertices(Grafo* floresta, int v1, int v2, float peso) {
    floresta->na += 2; 


    // insere v1 no final da lista de arestas de v2
    Node* vert1 = findNode((Node*)floresta->viz, v1);
    if(vert1 == NULL) exit(1);
    vert1->obj = postInsert(vert1->obj, v2);
    

    // cria de fato uma aresta nesta posição
    Node* novoViz = findNode(vert1->obj, v2);
    
    Viz* vizV2 = (Viz*)malloc(sizeof(Viz));
    if(vizV2 == NULL) exit(1);
    
    vizV2->n = v2;
    vizV2->peso = peso;
    novoViz->obj = (void*)vizV2;



    // insere v1 no final da lista de arestas de v2
    Node* vert2 = findNode(floresta->viz, v2);
    if(vert2 == NULL) exit(1);
    vert2->obj = postInsert(vert2->obj, v1);
        
    
    // cria de fato uma aresta nesta posição
    novoViz = findNode(vert2->obj, v1);
    
    Viz* vizV1 = (Viz*)malloc(sizeof(Viz));
    if(vizV1 == NULL) exit(1); 
    
    vizV1->n = v1;
    vizV1->peso = peso;
    novoViz->obj = vizV1;

    return;
}

// Retorna um subgrafo do grafo g que contém a árvore geradora de custo mínimo
Grafo* kruskal(Grafo* g){
    if(g == NULL || g->viz == NULL)
        return NULL;

    // Inicializa floresta (vértices sem as arestas)
    Grafo* floresta = inicializaGrafo();
    for (int i = 0; i < g->nv; i++) {
        criaVertice(floresta, NULL, NULL, 0);
    }

    // caso não haja arestas, não há arvore geradora maxima
    if(g->na == 0)
        return floresta;

    Arst* arestas = (Arst*)malloc(sizeof(Arst)*g->na);
    if(arestas == NULL) exit(1);
    addArestas(g, arestas, g->na);
    
    // ordena as arestas
    qsort(arestas, g->na, sizeof(*arestas), cmpPeso);

    // represetação dos conjuntos por vetores
    int pai[MAX_VERTICES];
    for (int i = 0; i < g->nv; i++) 
        pai[i] = -1;

    int altura[MAX_VERTICES];
    for(int i = 0; i < g->nv; i++)
        altura[i] = 0;

    // Construir floresta
    for (int i = 0; i < g->na; i++) {
        if (find(arestas[i].v1 - 1, pai) != find(arestas[i].v2 - 1, pai)) {
            conectaVertices(floresta, arestas[i].v1, arestas[i].v2, arestas[i].peso);
            Union(arestas[i].v1 - 1, arestas[i].v2 - 1, pai, altura);
        }
    }

    free(arestas);
    return floresta;
}