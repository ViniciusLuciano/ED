#ifndef RETANGULO_H
#define RETANGULO_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../Predio/predio.h"
#include "../Quadra/quadra.h"

typedef void* Retangulo;

Retangulo criarRetangulo(double x, double y, double w, double h, char *cfill, char *cstrok, char *rw);
void destruirRetangulo(Retangulo retangulo);
double Retangulo_get_x(Retangulo retangulo);
double Retangulo_get_y(Retangulo retangulo);
double Retangulo_get_w(Retangulo retangulo);
double Retangulo_get_h(Retangulo retangulo);
double Retangulo_get_max_x(Retangulo retangulo);
double Retangulo_get_max_y(Retangulo retangulo);
char* Retangulo_get_cfill(Retangulo r);
void Retangulo_escreverSvg(Retangulo r, FILE *svg);

Retangulo criarRetangulo_Predio(Predio p);
Retangulo criarRetangulo_Quadra(Quadra q);

#endif
