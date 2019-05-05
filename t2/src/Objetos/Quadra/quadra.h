#ifndef QUADRA_H
#define QUADRA_H

#include "../../headers.h"

typedef void* Quadra;

Quadra criarQuadra(char *cep, double x, double y, double w, double h, char *cfill, char *cstrok, char *sw);
void destruirQuadra(Quadra quadra);
char* getQuadra_cep(Quadra quadra);
double getQuadra_x(Quadra quadra);
double getQuadra_y(Quadra quadra);
double getQuadra_w(Quadra quadra);
double getQuadra_h(Quadra quadra);

// Funções relacionadas com a lista
bool quadraEquals(Quadra quadra, char *cep);
void imprimirQuadra(Quadra quadra);

#endif
