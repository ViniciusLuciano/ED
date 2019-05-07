#ifndef TEXTO_H
#define TEXTO_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct texto* Texto;

Texto criarTexto(double x, double y, char *text);
void destruirTexto(Texto texto);
double getHidrante_x(Texto texto);
double getHidrante_y(Texto texto);
char* getTexto_text(Texto texto);

// Funções relacionadas com a lista
void imprimirTexto(Texto texto);

#endif