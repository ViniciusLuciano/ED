#include "retangulo.h"

struct retangulo {
    char cfill[100], cstrok[100], rw[20];
    double x, y, w, h;
};

Retangulo criarRetangulo(double x, double y, double w, double h, char *cfill, char *cstrok, char *rw) {
    Retangulo retangulo = malloc(sizeof(struct retangulo));
    retangulo->x = x;
    retangulo->y = y;
    strcpy(retangulo->cfill, cfill);
    strcpy(retangulo->cstrok, cstrok);
    strcpy(retangulo->rw, rw);
    return retangulo;
}

void destruirRetangulo(Retangulo retangulo) {
    free(retangulo);
}

double getRetangulo_x(Retangulo retangulo) {
    return retangulo->x;
}

double getRetangulo_y(Retangulo retangulo) {
    return retangulo->y;
}

double getRetangulo_w(Retangulo retangulo) {
    return retangulo->w;
}

double getRetangulo_h(Retangulo retangulo) {
    return retangulo->h;
}

char* getRetangulo_cfill(Retangulo retangulo) {
    return retangulo->cfill;
}

char* getRetangulo_cstrok(Retangulo retangulo) {
    return retangulo->cstrok;
}

char* getRetangulo_cw(Retangulo retangulo) {
    return retangulo->rw;
}

double getRetangulo_max_x(Retangulo retangulo) {
    return retangulo->x + retangulo->w;
}

double getRetangulo_max_y(Retangulo retangulo) {
    return retangulo->y + retangulo->h;
}