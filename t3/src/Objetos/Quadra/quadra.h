#ifndef QUADRA_H
#define QUADRA_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef void* Quadra;

Quadra criarQuadra(char *cep, double x, double y, double w, double h, char *cfill, char *cstrok, char *sw);
void destruirQuadra(Quadra quadra);
char* Quadra_get_cep(Quadra quadra);
double Quadra_get_x(Quadra quadra);
double Quadra_get_y(Quadra quadra);
double Quadra_get_w(Quadra quadra);
double Quadra_get_h(Quadra quadra);
void Quadra_set_cstrk(Quadra quadra, char *cstrok);
void Quadra_set_x(Quadra quadra, double x);
void Quadra_set_y(Quadra quadra, double y);
void Quadra_escreverSvg(Quadra q, FILE *svg);

// Funções relacionadas com a lista
bool quadraEquals(Quadra quadra, char *cep);
void Quadra_imprimir(Quadra quadra);

#endif
