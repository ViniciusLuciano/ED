#include "segmento.h"

typedef struct segmento {
    Vertice v1, v2;
    double distancia;
} *pSegmento;

Segmento criarSegmento(Vertice v1, Vertice v2) {
    Segmento s = malloc(sizeof(struct segmento));
    pSegmento segmento = (pSegmento) s;
    segmento->v1 = v1;
    segmento->v2 = v2;
    return segmento;
}

void destruirSegmento(Segmento s) {
    pSegmento segmento = (pSegmento) s;
    destruirVertice(segmento->v1);
    destruirVertice(segmento->v2);
    free(segmento);
}

void Segmento_set_inicio_vertices(Segmento s) {
    pSegmento segmento = (pSegmento) s;
    double dAngulo = Vertice_get_angulo(segmento->v2) - Vertice_get_angulo(segmento->v1);
    if(dAngulo <= -M_PI) dAngulo+=(2*M_PI);
    if(dAngulo > M_PI) dAngulo-=(2*M_PI);

    bool inicio = dAngulo > 0 ? true : false;
    Vertice_set_inicio(segmento->v1, inicio);
    Vertice_set_inicio(segmento->v2, !inicio);
}

Vertice Segmento_get_v1(Segmento s) {
    pSegmento segmento = (pSegmento) s;
    return segmento->v1;
}

Vertice Segmento_get_v2(Segmento s) {
    pSegmento segmento = (pSegmento) s;
    return segmento->v2;
}

void Segmento_set_distancia(Segmento s, double x, double y) {
    pSegmento segmento = (pSegmento) s;
    double x1 = Vertice_get_x(segmento->v1);
    double y1 = Vertice_get_y(segmento->v1);
    double x2 = Vertice_get_x(segmento->v2);
    double y2 = Vertice_get_y(segmento->v2);

    segmento->distancia = distanciaL1(x, y, (x1+x2)/2, (y1+y2)/2);
}

double Segmento_get_distancia(Segmento s) {
    pSegmento segmento = (pSegmento) s;
    return segmento->distancia;
}

int Segmento_compararChave(Segmento a, Segmento b) {
    pSegmento segmento_a = (pSegmento) a;
    pSegmento segmento_b = (pSegmento) b;

    if (Vertice_get_x(segmento_a->v1) > Vertice_get_x(segmento_b->v1)) return 1;
    else if (Vertice_get_x(segmento_a->v1) < Vertice_get_x(segmento_b->v1)) return -1;
    else {
        if (Vertice_get_y(segmento_a->v1) > Vertice_get_y(segmento_b->v1)) return 1;
        else if (Vertice_get_y(segmento_a->v1) < Vertice_get_y(segmento_b->v1)) return -1;
        else return 0;
    }
}