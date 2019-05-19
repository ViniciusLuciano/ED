#ifndef TEXTO_H
#define TEXTO_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef void* Texto;

Texto criarTexto(double x, double y, char *text);
void destruirTexto(Texto texto);
double Texto_get_x(Texto texto);
double Texto_get_y(Texto texto);
char* Texto_get_text(Texto texto);
void Texto_escreverSvg(Texto t, FILE *svg);

#endif