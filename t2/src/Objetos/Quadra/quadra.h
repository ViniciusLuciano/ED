#ifndef QUADRA_H
#define QUADRA_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct quadra* Quadra;

Quadra criarQuadra(char *cep, double x, double y, double w, double h, char *cfill, char *cstrok, char *sw);
void destruirQuadra(Quadra quadra);
char* getQuadra_cep(Quadra quadra);
double getQuadra_x(Quadra quadra);
double getQuadra_y(Quadra quadra);
double getQuadra_w(Quadra quadra);
double getQuadra_h(Quadra quadra);
void setQuadra_cstrk(Quadra quadra, char *cstrok);
void setQuadra_x(Quadra quadra, double x);
void setQuadra_y(Quadra quadra, double y);
void escreverQuadra_svg(Quadra q, FILE *svg);

// Funções relacionadas com a lista
bool quadraEquals(Quadra quadra, char *cep);
void imprimirQuadra(Quadra quadra);

#endif
