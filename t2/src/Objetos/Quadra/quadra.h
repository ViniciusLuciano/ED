#ifndef QUADRA_H
#define QUADRA_H

#include "../../headers.h"

typedef void* Quadra;

Quadra criarQuadra(char *cep, double x, double y, double w, double h, char *cfill, char *cstrok, char *sw);
void destruirQuadra(Quadra quadra);
char* getQuadra_cep(Quadra q);
double getQuadra_x(Quadra q);
double getQuadra_y(Quadra q);
double getQuadra_w(Quadra q);
double getQuadra_h(Quadra q);

// Funções relacionadas com a lista
bool quadraEquals(Quadra quadra1, char *cep);
void imprimirQuadra(Quadra quadra);

#endif
