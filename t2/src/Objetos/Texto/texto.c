#include "texto.h"

struct texto {
    char text[256];
    double x, y;
};

Texto criarTexto(double x, double y, char *text) {
    Texto texto = malloc(sizeof(struct texto));
    texto->x = x;
    texto->y = y;
    strcpy(texto->text, text);
    return texto;
}

void destruirTexto(Texto texto) {
    free(texto);
}

double getTexto_x(Texto texto) {
    return texto->x;
}

double getTexto_y(Texto texto) {
    return texto->y;
}

char* getTexto_text(Texto texto) {
    return texto->text;
}

void escreverTexto_svg(Texto t, FILE *svg) {
	fprintf(svg, "<text x=\"%lf\" y=\"%lf\">%s</text>",
        t->x, 
        t->y, 
        t->text);
}