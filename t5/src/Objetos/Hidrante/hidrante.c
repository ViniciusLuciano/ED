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

char* Hidrante_get_id(Hidrante h) {
    pHidrante hidrante = (pHidrante) h;
    return hidrante->id;
}

double Hidrante_get_x(Hidrante h) {
    pHidrante hidrante = (pHidrante) h;
    return hidrante->x;
}

double Hidrante_get_y(Hidrante h) {
    pHidrante hidrante = (pHidrante) h;
    return hidrante->y;
}

void Hidrante_set_x(Hidrante h, double x) {
    pHidrante hidrante = (pHidrante) h;
    hidrante->x = x;
}

void Hidrante_set_y(Hidrante h, double y) {
    pHidrante hidrante = (pHidrante) h;
    hidrante->y = y;
}

void Hidrante_escreverSvg(Hidrante h, FILE *svg) {
    pHidrante hidrante = (pHidrante) h;
    fprintf(svg, "<circle cx=\"%lf\" cy=\"%lf\" r=\"5\" stroke=\"%s\" fill=\"%s\" stroke-width=\"%s\" />\n", 
            hidrante->x,
            hidrante->y,
            hidrante->cstrok, 
            hidrante->cfill,
            hidrante->sw);
    
    fprintf(svg, "<text x=\"%lf\" y=\"%lf\" fill=\"white\" font-size=\"9\" style=\"z-index:100 \">H</text>\n",
            hidrante->x - 3.2,
            hidrante->y + 3);
}

bool hidranteEquals(Hidrante h, char *id) {
    pHidrante hidrante = (pHidrante) h;
    return strcmp(hidrante->id, id) == 0;
}

void Hidrante_imprimir(Hidrante h) {
    pHidrante hidrante = (pHidrante) h;
    printf("id %s | cfill %s\n", hidrante->id, hidrante->cfill);
}

int Hidrante_compararChave(Hidrante a, Hidrante b) {
    pHidrante hidrante_a = (pHidrante) a;
    pHidrante hidrante_b = (pHidrante) b;

    if (hidrante_a->x > hidrante_b->x) return 1;
    else if (hidrante_a->x < hidrante_b->x) return -1;
    else {
        if (hidrante_a->y > hidrante_b->y) return 1;
        else if (hidrante_a->y < hidrante_b->y) return -1;
        else return 0;
    }
}

int Hidrante_getSize() {
    return sizeof(struct hidrante);
}

char* Hidrante_getChave(Hidrante h) {
    pHidrante hidrante = (pHidrante) h;
    return hidrante->id;
}

char* Hidrante_getDados(Hidrante h, char* dados) {
    pHidrante hidrante = (pHidrante) h;
    sprintf(dados, "%0.1lf %0.1lf\n %s\n", hidrante->x, hidrante->y, hidrante->id);
    return dados;
}