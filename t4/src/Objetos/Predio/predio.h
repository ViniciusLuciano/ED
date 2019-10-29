#ifndef PREDIO_H
#define PREDIO_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef void* Predio;

Predio criarPredio(char *cep, char face, double num, double f, double p, double mrg);
char* Predio_getCep(Predio prd);
double Predio_get_x(Predio prd);
double Predio_get_y(Predio prd);
double Predio_get_x_max(Predio prd);
double Predio_get_y_max(Predio prd);
double Predio_get_num(Predio prd);
void Predio_escreverSvg(Predio prd, double quadra_x, double quadra_y, double quadra_w, double quadra_h, FILE *svg);
void destruirPredio(Predio prd);

bool predioEquals(Predio p, char *cep);
int Predio_compararChave(Predio a, Predio b);
int Predio_getSize();

char* Predio_getChave(Predio p);

#endif