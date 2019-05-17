#ifndef CIRCULO_H
#define CIRCULO_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef void* Circulo;

Circulo criarCirculo(double x, double y, double r, char *cfill, char *cstrok, char *cw);
void destruirCirculo(Circulo circulo);
double getCirculo_x(Circulo circulo);
double getCirculo_y(Circulo circulo);
double getCirculo_r(Circulo Circulo);
char* getCirculo_cfill(Circulo circulo);
char* getCirculo_cstrok(Circulo circulo);
char* getCirculo_cw(Circulo circulo);
double getCirculo_max_x(Circulo circulo);
double getCirculo_max_y(Circulo circulo);
double getCirculo_min_x(Circulo circulo);
double getCirculo_min_y(Circulo circulo);
void escreverCirculo_svg(Circulo c, FILE *svg);

#endif