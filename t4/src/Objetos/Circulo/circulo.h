#ifndef CIRCULO_H
#define CIRCULO_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef void* Circulo;

Circulo criarCirculo(double x, double y, double r, char *cfill, char *cstrok, char *cw);
void destruirCirculo(Circulo circulo);
double Circulo_get_x(Circulo circulo);
double Circulo_get_y(Circulo circulo);
double Circulo_get_r(Circulo Circulo);
char* Circulo_get_cfill(Circulo circulo);
char* Circulo_get_cstrok(Circulo circulo);
char* Circulo_get_cw(Circulo circulo);
double Circulo_get_max_x(Circulo circulo);
double Circulo_get_max_y(Circulo circulo);
double Circulo_get_min_x(Circulo circulo);
double Circulo_get_min_y(Circulo circulo);
void Circulo_escreverSvg(Circulo c, FILE *svg);

#endif