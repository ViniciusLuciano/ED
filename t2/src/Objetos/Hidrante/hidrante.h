#ifndef HIDRANTE_H
#define HIDRANTE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct hidrante* Hidrante;

Hidrante criarHidrante(char *id, double x, double y, char *cfill, char *cstrok, char *sw);
void destruirHidrante(Hidrante hidrante);
char* getHidrante_id(Hidrante hidrante);
double getHidrante_x(Hidrante hidrante);
double getHidrante_y(Hidrante hidrante);
void setHidrante_x(Hidrante hidrante, double x);
void setHidrante_y(Hidrante hidrante, double y);

// Funções relacionadas com a lista
bool hidranteEquals(Hidrante hidrante, char *id);
void imprimirHidrante(Hidrante hidrante);

#endif