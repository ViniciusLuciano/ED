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
char* Hidrante_getDados(Hidrante h, char* dados);

// Funções relacionadas com a lista
bool hidranteEquals(Hidrante hidrante, char *id);
void Hidrante_imprimir(Hidrante hidrante);
int Hidrante_compararChave(Hidrante a, Hidrante b);
int Hidrante_getSize();

char* Hidrante_getChave(Hidrante hidrante);

#endif