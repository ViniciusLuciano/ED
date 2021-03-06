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

double Texto_get_x(Texto t) {
    pTexto texto = (pTexto) t;
    return texto->x;
}

double Texto_get_y(Texto t) {
    pTexto texto = (pTexto) t;
    return texto->y;
}

char* Texto_get_text(Texto t) {
    pTexto texto = (pTexto) t;
    return texto->text;
}

void Texto_escreverSvg(Texto t, FILE *svg) {
    pTexto texto = (pTexto) t;
	fprintf(svg, "<text x=\"%lf\" y=\"%lf\" font-size=\"5\">%s</text>",
        texto->x, 
        texto->y, 
        texto->text);
}