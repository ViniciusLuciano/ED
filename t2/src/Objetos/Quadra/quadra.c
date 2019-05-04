#include "quadra.h"

typedef struct quadra{
    char cep[100];
    double x, y, w, h;
} *ponteiroQuadra;

Quadra criarQuadra(double x, double y, double w, double h, char *cep) {
    ponteiroQuadra q = malloc(sizeof(struct quadra));
    Quadra quadra = q;
    strcpy(q->cep, cep);
    q->x = x;
    q->y = y;
    q->w = w;
    q->h = h;
    return quadra;
}

char* getQuadra_cep(Quadra q) {
    ponteiroQuadra quadra = (ponteiroQuadra) q;
    return quadra->cep;
}

double getQuadra_x(Quadra q) {
    ponteiroQuadra quadra = (ponteiroQuadra) q;
    return quadra->x;
}

double getQuadra_y(Quadra q) {
    ponteiroQuadra quadra = (ponteiroQuadra) q;
    return quadra->y;
}

double getQuadra_w(Quadra q) {
    ponteiroQuadra quadra = (ponteiroQuadra) q;
    return quadra->w;
}

double getQuadra_h(Quadra q) {
    ponteiroQuadra quadra = (ponteiroQuadra) q;
    return quadra->h;
}

bool quadraEquals(Quadra quadra1, Quadra quadra2) {
    ponteiroQuadra q1 = (ponteiroQuadra) quadra1;
    ponteiroQuadra q2 = (ponteiroQuadra) quadra2;
    //printf("%s %s\n", q1->cep, q2->cep);
    return strcmp(q1->cep, q2->cep) == 0;
}

void imprimirQuadra(Quadra quadra) {
    ponteiroQuadra q = (ponteiroQuadra) quadra;
    printf("cep %s\n", q->cep);
}
