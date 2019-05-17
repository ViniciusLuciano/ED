#include "retangulo.h"

typedef struct retangulo {
    char cfill[100], cstrok[100], rw[20];
    double x, y, w, h;
}*pRetangulo;

Retangulo criarRetangulo(double x, double y, double w, double h, char *cfill, char *cstrok, char *rw) {
    Retangulo r = malloc(sizeof(struct retangulo));
    pRetangulo retangulo = (pRetangulo) r;
    retangulo->x = x;
    retangulo->y = y;
    retangulo->w = w;
    retangulo->h = h;
    strcpy(retangulo->cfill, cfill);
    strcpy(retangulo->cstrok, cstrok);
    strcpy(retangulo->rw, rw);
    return retangulo;
}

void destruirRetangulo(Retangulo r) {
    pRetangulo retangulo = (pRetangulo) r;
    free(retangulo);
}

double getRetangulo_x(Retangulo r) {
    pRetangulo retangulo = (pRetangulo) r;
    return retangulo->x;
}

double getRetangulo_y(Retangulo r) {
    pRetangulo retangulo = (pRetangulo) r;
    return retangulo->y;
}

double getRetangulo_w(Retangulo r) {
    pRetangulo retangulo = (pRetangulo) r;
    return retangulo->w;
}

double getRetangulo_h(Retangulo r) {
    pRetangulo retangulo = (pRetangulo) r;
    return retangulo->h;
}

char* getRetangulo_cfill(Retangulo r) {
    pRetangulo retangulo = (pRetangulo) r;
    return retangulo->cfill;
}

char* getRetangulo_cstrok(Retangulo r) {
    pRetangulo retangulo = (pRetangulo) r;
    return retangulo->cstrok;
}

char* getRetangulo_cw(Retangulo r) {
    pRetangulo retangulo = (pRetangulo) r;
    return retangulo->rw;
}

double getRetangulo_max_x(Retangulo r) {
    pRetangulo retangulo = (pRetangulo) r;
    return retangulo->x + retangulo->w;
}

double getRetangulo_max_y(Retangulo r) {
    pRetangulo retangulo = (pRetangulo) r;
    return retangulo->y + retangulo->h;
}

void escreverRetangulo_svg(Retangulo r, FILE *svg) {
    pRetangulo retangulo = (pRetangulo) r;
	fprintf(svg, "<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" stroke=\"%s\" fill=\"%s\" stroke-width=\"%s\" />\n",
            retangulo->x,
            retangulo->y, 
            retangulo->w, 
            retangulo->h, 
            retangulo->cstrok,
            retangulo->cfill,
            retangulo->rw);
}