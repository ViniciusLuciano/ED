#ifndef PREDIO_H
#define PREDIO_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef void* Predio;

Predio criarPredio(char *cep, char face, double num, double f, double p, double mrg);
char* Predio_getCep(Predio prd);
void Predio_escreverSvg(Predio prd, double quadra_x, double quadra_y, double quadra_w, double quadra_h, FILE *svg);
void destruirPredio(Predio prd);


#endif