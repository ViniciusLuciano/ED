#ifndef RETANGULO_H
#define RETANGULO_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct retangulo* Retangulo;

Retangulo criarRetangulo(double x, double y, double w, double h, char *cfill, char *cstrok, char *rw);
void destruirRetangulo(Retangulo retangulo);
double getRetangulo_x(Retangulo retangulo);
double getRetangulo_y(Retangulo retangulo);
double getRetangulo_w(Retangulo retangulo);
double getRetangulo_h(Retangulo retangulo);
char* getRetangulo_cfill(Retangulo retangulo);
char* getRetangulo_cstrok(Retangulo retangulo);
char* getRetangulo_rw(Retangulo retangulo);
double getRetangulo_max_x(Retangulo retangulo);
double getRetangulo_max_y(Retangulo retangulo);
void escreverRetangulo_svg(Retangulo r, FILE *svg);

#endif