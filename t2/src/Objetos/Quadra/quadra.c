#include "quadra.h"

struct quadra {
    char cep[100], cfill[100], cstrok[100], sw[20];
    double x, y, w, h;
};

Quadra criarQuadra(char *cep, double x, double y, double w, double h, char *cfill, char *cstrok, char *sw) {
    Quadra quadra = malloc(sizeof(struct quadra));
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

void destruirQuadra(Quadra quadra) {
    free(quadra);
}

char* getQuadra_cep(Quadra quadra) {
    return quadra->cep;
}

double getQuadra_x(Quadra quadra) {
    return quadra->x;
}

double getQuadra_y(Quadra quadra) {
    return quadra->y;
}

double getQuadra_w(Quadra quadra) {
    return quadra->w;
}

double getQuadra_h(Quadra quadra) {
    return quadra->h;
}

// Para o comando cbq
void setQuadra_cstrk(Quadra quadra, char *cstrok) {
    strcpy(quadra->cstrok, cstrok);
}

void setQuadra_x(Quadra quadra, double x) {
    quadra->x = x;
}

void setQuadra_y(Quadra quadra, double y) {
    quadra->y = y;
}

// Terminar isso
void escreverQuadra_svg(Quadra q, FILE *svg) {

}

bool quadraEquals(Quadra quadra, char *cep) {
    return strcmp(quadra->cep, cep) == 0;
}

void imprimirQuadra(Quadra quadra) {
    printf("cep %s\n", quadra->cep);
}
