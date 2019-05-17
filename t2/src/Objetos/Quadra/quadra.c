#include "quadra.h"

typedef struct quadra {
    char cep[100], cfill[100], cstrok[100], sw[20];
    double x, y, w, h;
}*pQuadra;

Quadra criarQuadra(char *cep, double x, double y, double w, double h, char *cfill, char *cstrok, char *sw) {
    Quadra q = malloc(sizeof(struct quadra));
    pQuadra quadra = (pQuadra) q;
    strcpy(quadra->cep, cep);
    quadra->x = x;
    quadra->y = y;
    quadra->w = w;
    quadra->h = h;
    strcpy(quadra->cfill, cfill);
    strcpy(quadra->cstrok, cstrok);
    strcpy(quadra->sw, sw);
    return quadra;
}

void destruirQuadra(Quadra q) {
    pQuadra quadra = (pQuadra) q;
    free(quadra);
}

char* getQuadra_cep(Quadra q) {
    pQuadra quadra = (pQuadra) q;
    return quadra->cep;
}

double getQuadra_x(Quadra q) {
    pQuadra quadra = (pQuadra) q;
    return quadra->x;
}

double getQuadra_y(Quadra q) {
    pQuadra quadra = (pQuadra) q;
    return quadra->y;
}

double getQuadra_w(Quadra q) {
    pQuadra quadra = (pQuadra) q;
    return quadra->w;
}

double getQuadra_h(Quadra q) {
    pQuadra quadra = (pQuadra) q;
    return quadra->h;
}

// Para o comando cbq
void setQuadra_cstrk(Quadra q, char *cstrok) {
    pQuadra quadra = (pQuadra) q;
    strcpy(quadra->cstrok, cstrok);
}

void setQuadra_x(Quadra q, double x) {
    pQuadra quadra = (pQuadra) q;
    quadra->x = x;
}

void setQuadra_y(Quadra q, double y) {
    pQuadra quadra = (pQuadra) q;
    quadra->y = y;
}

// Terminar isso
void escreverQuadra_svg(Quadra q, FILE *svg) {
    pQuadra quadra = (pQuadra) q;
    fprintf(svg, "<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" stroke=\"%s\" fill=\"%s\" stroke-width=\"%s\" />\n",
            quadra->x,
            quadra->y, 
            quadra->w, 
            quadra->h, 
            quadra->cstrok,
            quadra->cfill,
            quadra->sw);
}

bool quadraEquals(Quadra q, char *cep) {
    pQuadra quadra = (pQuadra) q;
    return strcmp(quadra->cep, cep) == 0;
}

void imprimirQuadra(Quadra q) {
    pQuadra quadra = (pQuadra) q;
    printf("cep %s\n", quadra->cep);
}
