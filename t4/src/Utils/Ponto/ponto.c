#include "ponto.h"

typedef struct ponto {
    double x, y;
} *pPonto;

Ponto criarPonto(double x, double y) {
    Ponto p = malloc(sizeof(struct ponto));
    pPonto ponto = (pPonto) p;
    ponto->x = x;
    ponto->y = y;
    return ponto;
}

void destruirPonto(Ponto p) {
    pPonto ponto = (pPonto) p;
    free(ponto);
}

double Ponto_get_x(Ponto p) {
    pPonto ponto = (pPonto) p;
    return ponto->x;
}

double Ponto_get_y(Ponto p) {
    pPonto ponto = (pPonto) p;
    return ponto->y;
}

void Ponto_set_x(Ponto p, double x) {
    pPonto ponto = (pPonto) p;
    ponto->x = x;
}

void Ponto_set_y(Ponto p, double y) {
    pPonto ponto = (pPonto) p;
    ponto->y = y;
}

void Ponto_setMin(Ponto p, double x, double y) {
    pPonto ponto = (pPonto) p;
    if(x < ponto->x) ponto->x = x;
    if(y< ponto->y) ponto->y = y;
}

void Ponto_setMax(Ponto p, double x, double y) {
    pPonto ponto = (pPonto) p;
    if(x > ponto->x) ponto->x = x;
    if(y > ponto->y) ponto->y = y;
}

int Ponto_getSize() {
    return sizeof(struct ponto);
}