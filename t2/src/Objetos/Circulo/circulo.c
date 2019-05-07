#include "circulo.h"

struct circulo{
    char id[100], cfill[100], cstrok[100], cw[20];
    double x, y, r;
};

Circulo criarCirculo(char *id, double x, double y, double r, char *cfill, char *cstrok, char *cw) {
    Circulo circulo = malloc(sizeof(struct circulo));
    strcpy(circulo->id, id);
    circulo->x = x;
    circulo->y = y;
    circulo->r = r;
    strcpy(circulo->cfill, cfill);
    strcpy(circulo->cstrok, cstrok);
    strcpy(circulo->cw, cw);
    return circulo;
}

void destruirCirculo(Circulo circulo) {
    free(circulo);
}

char* getCirculo_id(Circulo circulo) {
    return circulo->id;
}

double getCirculo_x(Circulo circulo) {
    return circulo->x;
}

double getCirculo_y(Circulo circulo) {
    return circulo->y;
}

double getCirculo_r(Circulo circulo) {
    return circulo->r;
}

char* getCirculo_cfill(Circulo circulo) {
    return circulo->cfill;
}

char* getCirculo_cstrok(Circulo circulo) {
    return circulo->cstrok;
}

char* getCirculo_cw(Circulo circulo) {
    return circulo->cw;
}

double getCirculo_max_x(Circulo circulo) {
    return circulo->x + circulo->r;
}

double getCirculo_max_y(Circulo circulo) {
    return circulo->y + circulo->r;
}

double getCirculo_min_x(Circulo circulo) {
    return circulo->x - circulo->r;
}

double getCirculo_min_y(Circulo circulo) {
    return circulo->y - circulo->r;
}

bool circuloEquals(Circulo circulo, char *id) {
    return strcmp(circulo->id, id) == 0;
}

void imprimirCirculo(Circulo circulo) {
    printf("id %s\n", circulo->id);
}
