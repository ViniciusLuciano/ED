#include "circulo.h"

typedef struct circulo {
    char cfill[100], cstrok[100], cw[20];
    double x, y, r;
}*pCirculo;

Circulo criarCirculo(double x, double y, double r, char *cfill, char *cstrok, char *cw) {
    Circulo c = malloc(sizeof(struct circulo));
    pCirculo circulo = (pCirculo) c;
    circulo->x = x;
    circulo->y = y;
    circulo->r = r;
    strcpy(circulo->cfill, cfill);
    strcpy(circulo->cstrok, cstrok);
    strcpy(circulo->cw, cw);
    return circulo;
}

void destruirCirculo(Circulo c) {
    pCirculo circulo = (pCirculo) c;
    free(circulo);
}

double getCirculo_x(Circulo c) {
    pCirculo circulo = (pCirculo) c;
    return circulo->x;
}

double getCirculo_y(Circulo c) {
    pCirculo circulo = (pCirculo) c;
    return circulo->y;
}

double getCirculo_r(Circulo c) {
    pCirculo circulo = (pCirculo) c;
    return circulo->r;
}

char* getCirculo_cfill(Circulo c) {
    pCirculo circulo = (pCirculo) c;
    return circulo->cfill;
}

char* getCirculo_cstrok(Circulo c) {
    pCirculo circulo = (pCirculo) c;
    return circulo->cstrok;
}

char* getCirculo_cw(Circulo c) {
    pCirculo circulo = (pCirculo) c;
    return circulo->cw;
}

double getCirculo_max_x(Circulo c) {
    pCirculo circulo = (pCirculo) c;
    return circulo->x + circulo->r;
}

double getCirculo_max_y(Circulo c) {
    pCirculo circulo = (pCirculo) c;
    return circulo->y + circulo->r;
}

double getCirculo_min_x(Circulo c) {
    pCirculo circulo = (pCirculo) c;
    return circulo->x - circulo->r;
}

double getCirculo_min_y(Circulo c) {
    pCirculo circulo = (pCirculo) c;
    return circulo->y - circulo->r;
}

void escreverCirculo_svg(Circulo c, FILE *svg) {
    pCirculo circulo = (pCirculo) c;
	fprintf(svg, "<circle cx=\"%lf\" cy=\"%lf\" r=\"%lf\" stroke=\"%s\" fill=\"%s\" stroke-width=\"%s\" />\n", 
            circulo->x,
            circulo->y,
            circulo->r, 
            circulo->cstrok, 
            circulo->cfill,
            circulo->cw);
}