#include "quadra.h"

typedef struct quadra {
    char cep[100], cfill[100], cstrok[100], sw[20];
    double x, y, w, h;
    int numMoradores;
    Arvore arvoreMoradores;
    Arvore arvorePredios;
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
    quadra->arvoreMoradores = criarArvore(Morador_compararChave, NULL);
    quadra->arvorePredios = criarArvore(Predio_compararChave, NULL);
    quadra->numMoradores = 0;
    return quadra;
}

void destruirQuadra(Quadra q) {
    pQuadra quadra = (pQuadra) q;
    destruirArvore(quadra->arvorePredios);
    destruirArvore(quadra->arvoreMoradores);
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

int Quadra_compararChave(Quadra a, Quadra b) {
    pQuadra quadra_a = (pQuadra) a;
    pQuadra quadra_b = (pQuadra) b;

    if (quadra_a->x > quadra_b->x) return 1;
    else if (quadra_a->x < quadra_b->x) return -1;
    else {
        if (quadra_a->y > quadra_b->y) return 1;
        else if (quadra_a->y < quadra_b->y) return -1;
        else return 0;
    }
}

int Quadra_getSize() {
    return sizeof(struct quadra);
}

char* Quadra_getChave(Quadra q) {
    pQuadra quadra = (pQuadra) q;
    return quadra->cep;
}

void Quadra_setMorador(Quadra q, Morador m) {
    pQuadra quadra = (pQuadra) q;
    if (quadra == NULL) return;
    quadra->numMoradores++;
    Arvore_inserir(quadra->arvoreMoradores, m);
}

Node Quadra_getMoradores(Quadra q) {
    pQuadra quadra = (pQuadra) q;
    return Arvore_getRaiz(quadra->arvoreMoradores);
}

bool Quadra_removerMorador(Quadra q, Morador m) {
    pQuadra quadra = (pQuadra) q;
    if (quadra == NULL) return false;
    quadra->numMoradores--;
    return Arvore_removerObjeto(quadra->arvoreMoradores, m);
}

char* Quadra_getDados(Quadra q, char* dados) {
    pQuadra quadra = (pQuadra) q;
    sprintf(dados, "%0.1lf %0.1lf\n %s\n", quadra->x, quadra->y, quadra->cep);
    return dados;
}

void Quadra_setPredio(Quadra q, Predio prd) {
    pQuadra quadra = (pQuadra) q;
    if (quadra == NULL) return;
    Arvore_inserir(quadra->arvorePredios, prd);
}

Node Quadra_getPredios(Quadra q) {
    pQuadra quadra = (pQuadra) q;
    return Arvore_getRaiz(quadra->arvorePredios);
}

bool Quadra_removerPredio(Quadra q, Predio prd) {
    pQuadra quadra = (pQuadra) q;
    if (quadra == NULL) return false;
    return Arvore_removerObjeto(quadra->arvorePredios, prd);
}

void Quadra_set_cfill(Quadra q, char* cor) {
    pQuadra quadra = (pQuadra) q;
    strcpy(quadra->cfill, cor);
}

char* Quadra_get_cfill(Quadra q) {
    pQuadra quadra = (pQuadra) q;
    return quadra->cfill;
}

void Quadra_set_sw(Quadra q, char* sw) {
    pQuadra quadra = (pQuadra) q;
    strcpy(quadra->sw, sw);
}

int Quadra_getNumMoradores(Quadra q) {
    pQuadra quadra = (pQuadra) q;
    return quadra->numMoradores;
}