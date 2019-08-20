#ifndef HIDRANTE_H
#define HIDRANTE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef void* Hidrante;

Hidrante criarHidrante(char *id, double x, double y, char *cfill, char *cstrok, char *sw);
void destruirHidrante(Hidrante hidrante);
char* Hidrante_get_id(Hidrante hidrante);
double Hidrante_get_x(Hidrante hidrante);
double Hidrante_get_y(Hidrante hidrante);
void Hidrante_set_x(Hidrante hidrante, double x);
void Hidrante_set_y(Hidrante hidrante, double y);
void Hidrante_escreverSvg(Hidrante hidrante, FILE *SVG);

// Funções relacionadas com a lista
bool hidranteEquals(Hidrante hidrante, char *id);
void Hidrante_imprimir(Hidrante hidrante);

#endif