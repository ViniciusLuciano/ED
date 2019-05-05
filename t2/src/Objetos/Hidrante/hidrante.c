#include "hidrante.h"

typedef struct hidrante{
    char id[100], cfill[100], cstrok[100], sw[20];
    double x, y;
} *ponteiroHidrante;

Hidrante criarHidrante(char *id, double x, double y, char *cfill, char *cstrok, char *sw) {
    ponteiroHidrante h = malloc(sizeof(struct hidrante));
    Hidrante hidrante = h;
    strcpy(h->id, id);
    h->x = x;
    h->y = y;
    strcpy(h->cfill, cfill);
    strcpy(h->cstrok, cstrok);
    strcpy(h->sw, sw);
    return hidrante;
}

void destruirHidrante(Hidrante hidrante) {
    ponteiroHidrante h = (ponteiroHidrante) hidrante;
    free(h);
}

char* getHidrante_id(Hidrante hidrante) {
    ponteiroHidrante h = (ponteiroHidrante) hidrante;
    return h->id;
}

double getHidrante_x(Hidrante hidrante) {
    ponteiroHidrante h = (ponteiroHidrante) hidrante;
    return h->x;
}

double getHidrante_y(Hidrante hidrante) {
    ponteiroHidrante h = (ponteiroHidrante) hidrante;
    return h->y;
}

bool hidranteEquals(Hidrante hidrante, char *id) {
    ponteiroHidrante h = (ponteiroHidrante) hidrante;
    return strcmp(h->id, id) == 0;
}

void imprimirHidrante(Hidrante hidrante) {
    ponteiroHidrante h = (ponteiroHidrante) hidrante;
    printf("id %s\n", h->id);
}
