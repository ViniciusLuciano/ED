#include "hidrante.h"

typedef struct hidrante {
    char id[100], cfill[100], cstrok[100], sw[20];
    double x, y;
}*pHidrante;

Hidrante criarHidrante(char *id, double x, double y, char *cfill, char *cstrok, char *sw) {
    Hidrante h = malloc(sizeof(struct hidrante));
    pHidrante hidrante = (pHidrante) h;
    strcpy(hidrante->id, id);
    hidrante->x = x;
    hidrante->y = y;
    strcpy(hidrante->cfill, cfill);
    strcpy(hidrante->cstrok, cstrok);
    strcpy(hidrante->sw, sw);
    return hidrante;
}

void destruirHidrante(Hidrante h) {
    pHidrante hidrante = (pHidrante) h;
    free(hidrante);
}

char* getHidrante_id(Hidrante h) {
    pHidrante hidrante = (pHidrante) h;
    return hidrante->id;
}

double getHidrante_x(Hidrante h) {
    pHidrante hidrante = (pHidrante) h;
    return hidrante->x;
}

double getHidrante_y(Hidrante h) {
    pHidrante hidrante = (pHidrante) h;
    return hidrante->y;
}

void setHidrante_x(Hidrante h, double x) {
    pHidrante hidrante = (pHidrante) h;
    hidrante->x = x;
}

void setHidrante_y(Hidrante h, double y) {
    pHidrante hidrante = (pHidrante) h;
    hidrante->y = y;
}

void escreverHidrante_svg(Hidrante h, FILE *svg) {
    pHidrante hidrante = (pHidrante) h;
    fprintf(svg, "<circle cx=\"%lf\" cy=\"%lf\" r=\"5\" stroke=\"%s\" fill=\"%s\" stroke-width=\"%s\" />\n", 
            hidrante->x,
            hidrante->y,
            hidrante->cstrok, 
            hidrante->cfill,
            hidrante->sw);
}

bool hidranteEquals(Hidrante h, char *id) {
    pHidrante hidrante = (pHidrante) h;
    return strcmp(hidrante->id, id) == 0;
}

void imprimirHidrante(Hidrante h) {
    pHidrante hidrante = (pHidrante) h;
    printf("id %s | cfill %s\n", hidrante->id, hidrante->cfill);
}
