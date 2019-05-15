#ifndef TEXTO_H
#define TEXTO_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct texto* Texto;

Texto criarTexto(double x, double y, char *text);
void destruirTexto(Texto texto);
double getTexto_x(Texto texto);
double getTexto_y(Texto texto);
char* getTexto_text(Texto texto);
void escreverTexto_svg(FILE *SVG, Texto t);

// Funções relacionadas com a lista
void imprimirTexto(Texto texto);

#endif