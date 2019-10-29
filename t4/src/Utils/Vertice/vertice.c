#include "vertice.h"

typedef struct vertice {
    Ponto p;
    Segmento s;
    bool inicio, visivel;
    double angulo, distancia; //
} *pVertice;

Vertice criarVertice(double x, double y, double x_centro, double y_centro) {
    Vertice v = malloc(sizeof(struct vertice));
    pVertice vertice = (pVertice) v;
    Ponto p = criarPonto(x, y);
    vertice->p = p;
    vertice->angulo = calcularAngulo(p, x_centro, y_centro);
    vertice->distancia = distanciaL2(x, y, x_centro, y_centro);
    return vertice;
}

void destruirVertice(Vertice v) {
    pVertice vertice = (pVertice) v;
    destruirPonto(vertice->p);
    if(vertice->inicio) destruirSegmento(vertice->s);
    free(vertice);
}

double Vertice_get_angulo(Vertice v) {
    pVertice vertice = (pVertice) v;
    return vertice->angulo;
}

void Vertice_set_inicio(Vertice v, bool inicio) {
    pVertice vertice = (pVertice) v;
    vertice->inicio = inicio;
}

bool Vertice_get_inicio(Vertice v) {
    pVertice vertice = (pVertice) v;
    return vertice->inicio;
}

double Vertice_get_x(Vertice v) {
    pVertice vertice = (pVertice) v;
    return Ponto_get_x(vertice->p);
}

double Vertice_get_y(Vertice v) {
    pVertice vertice = (pVertice) v;
    return Ponto_get_y(vertice->p);
}

Ponto Vertice_get_p(Vertice v) {
    pVertice vertice = (pVertice) v;
    return vertice->p;
}

double Vertice_set_s(Vertice v, Segmento s) {
    pVertice vertice = (pVertice) v;
    vertice->s = s;
}

Segmento Vertice_get_s(Vertice v) {
    pVertice vertice = (pVertice) v;
    return vertice->s;
}

void Vertice_set_angulo(Vertice v, double angulo) {
    pVertice vertice = (pVertice) v;
    vertice->angulo = angulo;
}

double Vertice_get_distancia(Vertice v) {
    pVertice vertice = (pVertice) v;
    return vertice->distancia;
}

int Vertice_size() {
    return sizeof(struct vertice);
}

bool Vertice_equals(Vertice v1, Vertice v2) {
    return Ponto_get_x(v1) == Ponto_get_x(v2) && Ponto_get_y(v1) == Ponto_get_y(v2);
}