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

char* Quadra_get_cep(Quadra q) {
    pQuadra quadra = (pQuadra) q;
    return quadra->cep;
}

double Quadra_get_x(Quadra q) {
    pQuadra quadra = (pQuadra) q;
    return quadra->x;
}

double Quadra_get_y(Quadra q) {
    pQuadra quadra = (pQuadra) q;
    return quadra->y;
}

double Quadra_get_w(Quadra q) {
    pQuadra quadra = (pQuadra) q;
    return quadra->w;
}

double Quadra_get_h(Quadra q) {
    pQuadra quadra = (pQuadra) q;
    return quadra->h;
}

// Para o comando cbq
void Quadra_set_cstrk(Quadra q, char *cstrok) {
    pQuadra quadra = (pQuadra) q;
    strcpy(quadra->cstrok, cstrok);
}

void Quadra_set_x(Quadra q, double x) {
    pQuadra quadra = (pQuadra) q;
    quadra->x = x;
}

void Quadra_set_y(Quadra q, double y) {
    pQuadra quadra = (pQuadra) q;
    quadra->y = y;
}

// Terminar isso
void Quadra_escreverSvg(Quadra q, FILE *svg) {
    pQuadra quadra = (pQuadra) q;
    fprintf(svg, "<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" stroke=\"%s\" fill=\"%s\" stroke-width=\"%s\" opacity = \"0.5\" />\n",
            quadra->x,
            quadra->y, 
            quadra->w, 
            quadra->h, 
            quadra->cstrok,
            quadra->cfill,
            quadra->sw);

    fprintf(svg, "<text x=\"%lf\" y=\"%lf\" fill=\"white\" font-size=\"16\" style=\"z-index:100\">%s</text>\n",
            quadra->x,
            quadra->y + 16,
            quadra->cep);
}

bool quadraEquals(Quadra q, char *cep) {
    pQuadra quadra = (pQuadra) q;
    return strcmp(quadra->cep, cep) == 0;
}

void Quadra_imprimir(Quadra q) {
    pQuadra quadra = (pQuadra) q;
    printf("cep %s\n", quadra->cep);
}
