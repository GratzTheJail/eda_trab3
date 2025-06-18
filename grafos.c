/*
Guilherme Melo Gratz - 2211068 - 3WA
Vinicius Lucena - 2210458 - 3WA

MODULO GRAFOS
*/
#ifndef GRAFOS
#define GRAFOS
#include "grafos.h"
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
            novoViz->obj = (void*)postInsert(novoViz->obj, countNodes(novoViz->obj));
            findNode(novoViz->obj, countNodes(novoViz->obj) - 1)->obj = (void*)atual; // faz nova aresta apontar para o vertice criado
        }
    }

    return 1;
}

// imprime cada vértice e seus vizinhos (com pesos)
void imprimirGrafo(Grafo* grafo) {
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

void dfs(Grafo* grafo, int verticeInicial){
    //implementacao inicial da busca em profundidade (DFS)
    if (findNode(grafo->viz, verticeInicial) == NULL) {
        printf("Vertice %d nao existe no grafo.\n", verticeInicial);
        return; // se o vertice inicial nao existe, nao faz nada
    }
    int visitados[MAX_VERTICES] = {0}; // vetor para marcar os vértices visitados
    printf("DFS a partir do vertice %d:\n", verticeInicial);
    dfsRecursiva(grafo, verticeInicial, visitados); //inicio da busca
}

void dfsRecursiva(Grafo* grafo, int v, int visitados[]){
    visitados[v] = 1; // marca o vertice como visitado
    printf("visitando o vertice %d\n", v); // imprime o vertice visitado

    Node* nodeVertice = findNode(grafo->viz, v); // encontra o vertice e pega sua lista de vizinhos
    if (nodeVertice == NULL || nodeVertice->obj == NULL)
        return; // se o vertice nao tem vizinhos, acaba
    
    Node* listaVizinhos = (Node*)nodeVertice->obj; // pega a lista de vizinhos do vertice
    while (listaVizinhos != NULL)
    {
        Viz* vizinho = (Viz*)listaVizinhos->obj; // pega o vizinho atual
        if (!visitados[vizinho->n]) // se o vizinho nao foi visitado
        {
            dfsRecursiva(grafo, vizinho->n, visitados); // chama a funcao recursiva para visitar o vizinho
        }        
        listaVizinhos = listaVizinhos->next;
    }
}
// funcao enqueue para adicionar um elemento ao final da fila
void enqueue(int fila[], int* inicio, int* fim, int valor) {
    fila[(*fim)++] = valor; // adiciona o valor ao final da fila
}

// funcao dequeue para remover o primeiro elemento da fila
int dequeue(int fila[], int* inicio){ 
    return fila[(*inicio)++]; // remove o primeiro elemento da fila e atualiza o inicio
}

// funcao bfs para realizar a busca em largura
void bfs(Grafo* grafo, int verticeInicial){
    int visitados[MAX_VERTICES] = {0}; // vetor para marcar os vértices visitados
    int fila[MAX_FILA]; // fila para armazenar os vértices a serem visitados
    int inicio = 0, fim = 0; // variaveis para controlar o inicio e o fim da fila

    visitados[verticeInicial] = 1;
    enqueue(fila, &inicio, &fim, verticeInicial); // adiciona o vertice inicial na fila 

    printf("BFS iniciado a partir do vertice %d:\n", verticeInicial);

    while (inicio < fim)
    {
        int v = dequeue(fila, &inicio); // remove o primeiro elemento da fila
        printf("visitando vertice %d\n", v); // imprime o vertice visitado

        Node* nodeVertice = findNode(grafo->viz, v); // encontra o vertice e pega sua lista de vizinhos
        if (nodeVertice == NULL || nodeVertice->obj == NULL)
            printf("vertice %d sem vizinhos", v);
    
        Node* listaVizinhos = (Node*)nodeVertice->obj; // pega a lista de vizinhos do vertice
        while (listaVizinhos != NULL)
        {
            Viz* vizinho = (Viz*)listaVizinhos->obj;
            int vDestino = vizinho->n;

            if(!visitados[vDestino]) {
                visitados[vDestino] = 1; // marca o vizinho como visitado
                enqueue(fila, &inicio, &fim, vDestino); // adiciona o vizinho na fila
            }
            listaVizinhos = listaVizinhos->next; // passa para o proximo vizinho
        }
    }
}

// cria um Union-Find com n elementos
UnionFind* criarUnionFind(int n){ 
    UnionFind* uf = (UnionFind*)malloc(sizeof(UnionFind));
    if(uf == NULL) exit(1);
    uf->tam = n;
    // aloca espaço para os arrays pai e rank
    uf->pai = (int*)malloc(n * sizeof(int));
    uf->rank = (int*)malloc(n * sizeof(int));
    if(uf->pai == NULL || uf->rank == NULL) exit(1);
    
    for (int i = 1; i <= n; i++)
    {
        uf->pai[i] = i; //cada vertice é seu próprio pai inicialmente
        uf->rank[i] = 0; //rank inicial é 0
    }
    return uf; //retorna o UnionFind criado
}

//encontra o pai do vertice x
int find(UnionFind* uf, int x) { 
    if (uf->pai[x] != x)
    {
        uf->pai[x] = find(uf, uf->pai[x]); //caminho comprimido
    }
    return uf->pai[x]; //retorna o pai do vertice x
}

//une dois conjuntos
void unite(UnionFind* uf, int x, int y){
    int rx = find(uf, x); //encontra o pai do vertice x
    int ry = find(uf, y); //encontra o pai do vertice y

    if (rx == ry) return; //se os pais forem iguais, ja estao unidos
    
    if (uf->rank[rx] > uf->rank[ry])
    {
        uf->pai[ry] = rx; //une o conjunto de y ao conjunto de x
    }
    else
    {
        uf->pai[rx] = ry; //une o conjunto de x ao conjunto de y
        if (uf->rank[rx] == uf->rank[ry])
        {
            uf->rank[ry]++; //incrementa o rank se os ranks forem iguais
        }
    }
}

//por ser um grafo nao direcionado, precisa remover duplicatas
Aresta* extrairArestas(Grafo* grafo, int* qtdArestas){
    Node* vertice = grafo->viz;
    int maxArestas = grafo->na;

    Aresta* arestas = (Aresta*)malloc(maxArestas * sizeof(Aresta));
    *qtdArestas = 0;

    while (vertice != NULL)
    {
        int u = vertice->n;
        Node* listaVizinhos = (Node*)vertice->obj;

        while (listaVizinhos != NULL)
        {
            Viz* vizinho = (Viz*)listaVizinhos->obj;
            int v = vizinho->n;
            float peso = vizinho->peso;

            // evita adicionar arestas iguais na lista de arestas
            if (u < v)
            {
                arestas[*qtdArestas].u = u;
                arestas[*qtdArestas].v = v;
                arestas[*qtdArestas].peso = peso;
                (*qtdArestas)++;
            }
            listaVizinhos = listaVizinhos->next; // passa para o proximo vizinho
        }
        vertice = vertice->next; // passa para o proximo vertice
    }
    
    return arestas; //retorna o array de arestas
}

int compararArestas(void* a, void* b){
    Aresta* arestaA = (Aresta*)a;
    Aresta* arestaB = (Aresta*)b;
    if (arestaA->peso < arestaB->peso)
        return -1;
    if (arestaA->peso > arestaB->peso)
        return 1;
    return 0; // se os pesos forem iguais, retorna 0
}

void kruskal(Grafo* grafo){
    int qtdArestas;
    Aresta* arestas = extrairArestas(grafo, &qtdArestas);

    // ordena as arestas pelo peso
    qsort(arestas, qtdArestas, sizeof(Aresta), compararArestas);

    UnionFind* uf = criarUnionFind(grafo->nv); //numero total de vertices

    printf("Arestas do MST:\n");
    float custoTotal = 0;

    for (int i = 0; i < qtdArestas && grafo->na < grafo->nv - 1; i++)
    {
        Aresta a = arestas[i];
        int u = a.u;
        int v = a.v;
        float peso = a.peso;

        if (find(uf, u) != find(uf, v))
        {
            printf("Aresta: %d - %d, Peso: %.2f\n", u, v, peso);
            custoTotal += peso;
            unite(uf, u, v);
        }
    }
    printf("Custo total da AGM: %.2f\n", custoTotal);
    free(arestas); // libera a memoria alocada para as arestas
    free(uf->pai); // libera a memoria alocada para o array pai
    free(uf->rank); // libera a memoria alocada para o array rank
    free(uf); // libera a memoria alocada para o UnionFind
}