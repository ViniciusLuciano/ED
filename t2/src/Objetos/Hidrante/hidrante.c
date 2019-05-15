#include "hidrante.h"

struct hidrante {
    char id[100], cfill[100], cstrok[100], sw[20];
    double x, y;
};

Hidrante criarHidrante(char *id, double x, double y, char *cfill, char *cstrok, char *sw) {
    Hidrante hidrante = malloc(sizeof(struct hidrante));
    strcpy(hidrante->id, id);
    hidrante->x = x;
    hidrante->y = y;
    strcpy(hidrante->cfill, cfill);
    strcpy(hidrante->cstrok, cstrok);
    strcpy(hidrante->sw, sw);
    return hidrante;
}

void destruirHidrante(Hidrante hidrante) {
    free(hidrante);
}

char* getHidrante_id(Hidrante hidrante) {
    return hidrante->id;
}

double getHidrante_x(Hidrante hidrante) {
    return hidrante->x;
}

double getHidrante_y(Hidrante hidrante) {
    return hidrante->y;
}

void setHidrante_x(Hidrante hidrante, double x) {
    hidrante->x = x;
}

void setHidrante_y(Hidrante hidrante, double y) {
    hidrante->y = y;
}

void escreverHidrante_svg(Hidrante h, FILE *svg) {
    fprintf(svg, "<circle cx=\"%lf\" cy=\"%lf\" r=\"5\" stroke=\"%s\" fill=\"%s\" stroke-width=\"%s\" />\n", 
            h->x,
            h->y,
            h->cstrok, 
            h->cfill,
            h->sw);
}

bool hidranteEquals(Hidrante hidrante, char *id) {
    return strcmp(hidrante->id, id) == 0;
}

void imprimirHidrante(Hidrante hidrante) {
    printf("id %s | cfill %s\n", hidrante->id, hidrante->cfill);
}
