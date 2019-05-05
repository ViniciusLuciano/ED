#ifndef HIDRANTE_H
#define HIDRANTE_H

#include "../../headers.h"

typedef void* Hidrante;

Hidrante criarHidrante(char *id, double x, double y, char *cfill, char *cstrok, char *sw);
void destruirHidrante(Hidrante hidrante);
char* getHidrante_id(Hidrante hidrante);
double getHidrante_x(Hidrante hidrante);
double getHidrante_y(Hidrante hidrante);

// Funções relacionadas com a lista
bool quadraEquals(Hidrante hidrante, char *id);
void imprimirHidrante(Hidrante hidrante);

#endif