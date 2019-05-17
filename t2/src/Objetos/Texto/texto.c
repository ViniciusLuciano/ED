#include "texto.h"

typedef struct texto {
    char text[256];
    double x, y;
}*pTexto;

Texto criarTexto(double x, double y, char *text) {
    Texto t = malloc(sizeof(struct texto));
    pTexto texto = (pTexto) t;
    texto->x = x;
    texto->y = y;
    strcpy(texto->text, text);
    return texto;
}

void destruirTexto(Texto t) {
    pTexto texto = (pTexto) t;
    free(texto);
}

double getTexto_x(Texto t) {
    pTexto texto = (pTexto) t;
    return texto->x;
}

double getTexto_y(Texto t) {
    pTexto texto = (pTexto) t;
    return texto->y;
}

char* getTexto_text(Texto t) {
    pTexto texto = (pTexto) t;
    return texto->text;
}

void escreverTexto_svg(Texto t, FILE *svg) {
    pTexto texto = (pTexto) t;
	fprintf(svg, "<text x=\"%lf\" y=\"%lf\">%s</text>",
        texto->x, 
        texto->y, 
        texto->text);
}