#include "verticeG.h"

typedef struct verticeG {
    char id[50];
    double x, y;
    int numVert;
    bool inicial;
    Lista listaArestas;
} *pVerticeG;

VerticeG criarVerticeG(char *id, double x, double y, int numVert) {
    VerticeG v = malloc(sizeof(struct verticeG));
    pVerticeG verticeG = (pVerticeG) v;
    strcpy(verticeG->id, id);
    verticeG->x = x;
    verticeG->y = y;
    verticeG->numVert = numVert;
    verticeG->listaArestas = criarLista(ArestaG_equals, destruirArestaG);
    verticeG->inicial = true;
    return verticeG;
}

void destruirVerticeG(VerticeG v) {
    pVerticeG verticeG = (pVerticeG) v;
    destruirLista(verticeG->listaArestas);
    free(verticeG);
}

double VerticeG_get_x(VerticeG v) {
    pVerticeG verticeG = (pVerticeG) v;
    return verticeG->x;
}

double VerticeG_get_y(VerticeG v) {
    pVerticeG verticeG = (pVerticeG) v;
    return verticeG->y;
}

bool VerticeG_equals(VerticeG v1, char *id) {
    pVerticeG vertice1 = (pVerticeG) v1;
    return strcmp(vertice1->id, id) == 0;
}

char* VerticeG_getChave(VerticeG v) {
    pVerticeG vertice = (pVerticeG) v;
    return vertice->id;
}

void VerticeG_inserirArestaG(VerticeG v, ArestaG aresta) {
    pVerticeG vertice = (pVerticeG) v;
    Lista_inserir(vertice->listaArestas, aresta);
}

int VerticeG_compararChave(VerticeG v1, VerticeG v2) {
    pVerticeG vertice1 = (pVerticeG) v1;
    pVerticeG vertice2 = (pVerticeG) v2;

    if (vertice1->x > vertice2->x) return 1;
    else if (vertice1->x < vertice2->x) return -1;
    else {
        if (vertice1->y > vertice2->y) return 1;
        else if (vertice1->y < vertice2->y) return -1;
        else return 0;
    }
}

Lista VerticeG_get_listaArestas(VerticeG v) {
    pVerticeG verticeG = (pVerticeG) v;
    return verticeG->listaArestas;
}

int VerticeG_get_numVert(VerticeG v) {
    pVerticeG verticeG = (pVerticeG) v;
    return verticeG->numVert;
}

bool Vertige_get_inicial(VerticeG v) {
    pVerticeG verticeG = (pVerticeG) v;
    return verticeG->inicial;
}

void VerticeG_set_inicial(VerticeG v, bool inicial) {
    pVerticeG verticeG = (pVerticeG) v;
    verticeG->inicial = inicial;
}

void VerticeG_destruirArestasNoPoligono(VerticeG v, Poligono poligono) {
    pVerticeG verticeG = (pVerticeG) v;

    Ponto p = criarPonto(verticeG->x, verticeG->y);
    if (PontoInternoPoligono(p, poligono)) {

        for (Node node = Lista_getPrimeiro(verticeG->listaArestas); node != NULL; node = Node_getProx(node)) {
            ArestaG aresta = Lista_Node_getObjeto(node);
            ArestaG_set_cmp(aresta, INFINITY);
            ArestaG_set_vm(aresta, 0);
        }

    } else {
        for (Node node = Lista_getPrimeiro(verticeG->listaArestas); node != NULL; node = Node_getProx(node)) {
            ArestaG aresta = Lista_Node_getObjeto(node);

            pVerticeG verticeG2 = ArestaG_get_v2(aresta);

            Vertice v1 = criarVertice(verticeG->x, verticeG->y, 0, 0);
            Vertice v2 = criarVertice(verticeG2->x, verticeG2->y, 0, 0);
            Segmento s = criarSegmento(v1, v2);

            if(SegmentoInterceptaPoligono(s, poligono)) {
                ArestaG_set_cmp(aresta, INFINITY);
                ArestaG_set_vm(aresta, 0);
            }

            destruirSegmento(s);
        }
    }

    destruirPonto(p);
}

VerticeG VerticeG_getPosic(VerticeG v, char posic) {
    pVerticeG verticeG = (pVerticeG) v;

    for (Node node = Lista_getPrimeiro(verticeG->listaArestas); node != NULL; node = Node_getProx(node)) {
        ArestaG aresta = Lista_Node_getObjeto(node);
        pVerticeG verticeG2 = ArestaG_get_v2(aresta);

        if (verticeG->x == verticeG2->x && verticeG->y > verticeG2->y && posic == 'N') {
            return verticeG2;

        } else if (verticeG->x == verticeG2->x && verticeG->y < verticeG2->y && posic == 'S') {
            return verticeG2;

        } else if (verticeG->x < verticeG2->x && verticeG->y == verticeG2->y && posic == 'L') {
            return verticeG2;

        } else if (verticeG->x > verticeG2->x && verticeG->y == verticeG2->y && posic == 'O') {
            return verticeG2;
        }
    }

    return NULL;
}