#include "retangulo.h"

typedef struct retangulo {
    char cfill[100], cstrk[100], rw[20];
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
    strcpy(retangulo->cstrk, cstrok);
    strcpy(retangulo->rw, rw);
    return retangulo;
}

void destruirRetangulo(Retangulo r) {
    pRetangulo retangulo = (pRetangulo) r;
    free(retangulo);
}

double Retangulo_get_x(Retangulo r) {
    pRetangulo retangulo = (pRetangulo) r;
    return retangulo->x;
}

double Retangulo_get_y(Retangulo r) {
    pRetangulo retangulo = (pRetangulo) r;
    return retangulo->y;
}

double Retangulo_get_w(Retangulo r) {
    pRetangulo retangulo = (pRetangulo) r;
    return retangulo->w;
}

double Retangulo_get_h(Retangulo r) {
    pRetangulo retangulo = (pRetangulo) r;
    return retangulo->h;
}

double Retangulo_get_max_x(Retangulo r) {
    pRetangulo retangulo = (pRetangulo) r;
    return retangulo->x + retangulo->w;
}

double Retangulo_get_max_y(Retangulo r) {
    pRetangulo retangulo = (pRetangulo) r;
    return retangulo->y + retangulo->h;
}

char* Retangulo_get_cfill(Retangulo r) {
    pRetangulo retangulo = (pRetangulo) r;
    return retangulo->cfill;
}

void Retangulo_escreverSvg(Retangulo r, FILE *svg) {
    pRetangulo retangulo = (pRetangulo) r;
	fprintf(svg, "<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" stroke=\"%s\" fill=\"%s\" stroke-width=\"%s\" />\n",
            retangulo->x,
            retangulo->y, 
            retangulo->w, 
            retangulo->h, 
            retangulo->cstrk,
            retangulo->cfill,
            retangulo->rw);
}

Retangulo criarRetangulo_Predio(Predio p) {
    double x = Predio_get_x(p), y = Predio_get_y(p);
    double w = Predio_get_x_max(p) - x, h = Predio_get_y_max(p) - y;
    return criarRetangulo(x, y, w, h, "", "", "");
}

Retangulo criarRetangulo_Quadra(Quadra q) {
    double x = Quadra_get_x(q), y = Quadra_get_y(q);
    double w = Quadra_get_w(q), h = Quadra_get_h(q);
    return criarRetangulo(x, y, w, h, "", "", "");
}