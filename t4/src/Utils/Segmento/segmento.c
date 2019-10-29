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

void Segmento_set_distancia(Segmento s, double distancia) {
    pSegmento segmento = (pSegmento) s;
    segmento->distancia = distancia;
}

double Segmento_get_distancia(Segmento s) {
    pSegmento segmento = (pSegmento) s;
    return segmento->distancia;
}