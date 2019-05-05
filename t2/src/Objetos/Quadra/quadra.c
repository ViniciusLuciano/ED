#include "quadra.h"

typedef struct quadra{
    char cep[100], cfill[100], cstrok[100], sw[20];
    double x, y, w, h;
} *ponteiroQuadra;

Quadra criarQuadra(char *cep, double x, double y, double w, double h, char *cfill, char *cstrok, char *sw) {
    ponteiroQuadra q = malloc(sizeof(struct quadra));
    Quadra quadra = q;
    strcpy(q->cep, cep);
    q->x = x;
    q->y = y;
    q->w = w;
    q->h = h;
    strcpy(q->cfill, cfill);
    strcpy(q->cstrok, cstrok);
    strcpy(q->sw, sw);
    return quadra;
}

void destruirQuadra(Quadra quadra) {
    ponteiroQuadra q = (ponteiroQuadra) quadra;
    free(q);
}

char* getQuadra_cep(Quadra quadra) {
    ponteiroQuadra q = (ponteiroQuadra) quadra;
    return q->cep;
}

double getQuadra_x(Quadra quadra) {
    ponteiroQuadra q = (ponteiroQuadra) quadra;
    return q->x;
}

double getQuadra_y(Quadra quadra) {
    ponteiroQuadra q = (ponteiroQuadra) quadra;
    return q->y;
}

double getQuadra_w(Quadra quadra) {
    ponteiroQuadra q = (ponteiroQuadra) quadra;
    return q->w;
}

double getQuadra_h(Quadra quadra) {
    ponteiroQuadra q = (ponteiroQuadra) quadra;
    return q->h;
}

bool quadraEquals(Quadra quadra1, char *cep) {
    ponteiroQuadra q1 = (ponteiroQuadra) quadra1;
    //printf("%s %s\n", q1->cep, q2->cep);
    return strcmp(q1->cep, cep) == 0;
}

void imprimirQuadra(Quadra quadra) {
    ponteiroQuadra q = (ponteiroQuadra) quadra;
    printf("cep %s\n", q->cep);
}
