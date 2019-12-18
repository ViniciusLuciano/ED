#include "grafo.h"

typedef struct grafo {
    TabelaHash tabelaHashVertices;
    int numVetices;
} *pGrafo;

Grafo criarGrafo(int numVertices) {
    Grafo g = malloc(sizeof(struct grafo));
    pGrafo grafo = (pGrafo) g;
    grafo->tabelaHashVertices = criarTabelaHash(numVertices, VerticeG_equals, VerticeG_getChave, NULL);
    grafo->numVetices = numVertices;
    return grafo;
}

void destruirGrafo(Grafo g) {
    pGrafo grafo = (pGrafo) g;
    destruirTabelaHash(grafo->tabelaHashVertices);
    free(grafo);
}

void Grafo_inserirVerticeG(Grafo g, VerticeG vertice) {
    pGrafo grafo = (pGrafo) g;
    TabelaHash_inserir(grafo->tabelaHashVertices, vertice);
}

void Grafo_inserirArestaG(Grafo g, ArestaG aresta) {
    pGrafo grafo = (pGrafo) g;

    // Buscando vertice na tabela
    VerticeG v = TabelaHash_getObjeto(grafo->tabelaHashVertices, VerticeG_getChave(ArestaG_get_v1(aresta)));
    if (v != NULL) {
        VerticeG_inserirArestaG(v, aresta);
    }
}

VerticeG Grafo_getVerticeG(Grafo g, char* id) {
     pGrafo grafo = (pGrafo) g;
     return TabelaHash_getObjeto(grafo->tabelaHashVertices, id);
}



void printarVetorInt(int* vet) {
    for(int i = 0; i < 4; i++) {
        printf("%d ", vet[i]);
    }
     printf("\n");
}

void printarVetorDouble(double* vet) {
    for(int i = 0; i < 4; i++) {
        printf("%.1lf ", vet[i] == DBL_MAX ? 300000 : vet[i]);
    }
    printf("\n");
}

VerticeG* Dijkstra(Grafo grafo, VerticeG verticeOrigem, VerticeG verticeDestino, double(*comparador)(Objeto objeto)) {
    pGrafo g = (pGrafo) grafo;
    double novaDist, min;
    int *m = (int*)malloc(g->numVetices*sizeof(int)); // Determina se vertice ja foi visitado
    double *l = (double*)malloc(g->numVetices*sizeof(double)); // Comprimento do caminho mais curto
    VerticeG *a = (VerticeG*)malloc(g->numVetices*sizeof(VerticeG)); // Caminho mais curto entre origem e destino

    for (int i = 0; i < g->numVetices; i++) {
        m[i] = 0;
        a[i] = NULL;
        l[i] = DBL_MAX;
    }

    VerticeG vert = verticeOrigem;
    int numVert = VerticeG_get_numVert(vert); // VERT GET NUM
    l[numVert] = 0;

    while (vert != verticeDestino && numVert != -1) { 
        Lista adjacentes = VerticeG_get_listaArestas(vert);
        //printf("Vertice: %s, adjacentes:\n", VerticeG_getChave(vert));
        for (Node adj = Lista_getPrimeiro(adjacentes); adj != NULL; adj = Node_getProx(adj)) {
            ArestaG aresta = Node_getObjeto(adj);
            VerticeG verticeAdjacente = ArestaG_get_v2(aresta);
            int i = VerticeG_get_numVert(verticeAdjacente);
            //printf(" -> %s\n", VerticeG_getChave(verticeAdjacente));
            if (m[i] == 0) { // Verifica se o vertice adjacente ainda nao foi visitado
                novaDist = l[numVert] + comparador(aresta);
                //printf(" -> Nova dist: %lf %lf\n", novaDist, l[VerticeG_get_numVert(verticeAdjacente)]);
                if (novaDist < l[i]) {
                    l[i] = novaDist;
                    a[i] = vert;
                }
            }
        }
        m[numVert] = 1;
        min = DBL_MAX;
        numVert = -1;
        for (int i = 0; i < TabelaHash_length(g->tabelaHashVertices); i++) {
            Node nodeVertice = TabelaHash_getPosic(g->tabelaHashVertices, i);
            for (Node nVertice = nodeVertice; nVertice != NULL; nVertice = TabelaHash_Node_getProx(nVertice)) {
                VerticeG vertice = TabelaHash_Node_getObjeto(nVertice);
                int nvert = VerticeG_get_numVert(vertice);
                //printf("OIee %s %d %lf\n", VerticeG_getChave(vertice), m[nvert], l[nvert]);
                if (m[nvert] == 0 && l[nvert] < min) {
                    min = l[nvert];
                    numVert = nvert;
                    vert = vertice;
                }  
            }
        }
        //printf("OI %d\n", numVert);
        // printf("M :");
        // printarVetorInt(m);
        // printf("L :");
        // printarVetorDouble(l);
    }

    if (vert == verticeDestino) {
        // printf("Tem caminho de tamanho %lf\n", l[VerticeG_get_numVert(verticeDestino)]);
        VerticeG *caminho = (VerticeG*)malloc(g->numVetices*3*sizeof(VerticeG));
        VerticeG *caminhoFinal = (VerticeG*)malloc(g->numVetices*3*sizeof(VerticeG));
        caminho[0] = verticeDestino;
        int k = 1;

        while (vert != verticeOrigem) {
            caminho[k] = a[VerticeG_get_numVert(vert)];
            vert = a[VerticeG_get_numVert(vert)];
            k++;
        }

        int index = 0;
        for (int i = k-1; i >= 0; i--) {
            printf(" -> %s\n", VerticeG_getChave(caminho[i]));
            caminhoFinal[index] = caminho[i];
            if (i == 0) VerticeG_set_inicial(caminhoFinal[index], false);
            index++;
        }
        free(caminho);
        free(m);
        free(l);
        free(a);

        return caminhoFinal;
    }

    free(m);
    free(l);
    free(a);
    return NULL;
}
