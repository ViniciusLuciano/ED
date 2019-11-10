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

bool pontoEquals(Ponto p1, Ponto p2) {
    pPonto ponto1 = (pPonto) p1;
    pPonto ponto2 = (pPonto) p2;
    return ponto1->x == ponto2->x && ponto1->y == ponto2->y;
}

int Ponto_compararChave(Ponto a, Ponto b) {
    pPonto ponto_a = (pPonto) a;
    pPonto ponto_b = (pPonto) b;

    if (ponto_a->x > ponto_b->x) return 1;
    else if (ponto_a->x < ponto_b->x) return -1;
    else {
        if (ponto_a->y > ponto_b->y) return 1;
        else if (ponto_a->y < ponto_b->y) return -1;
        else return 0;
    }
}