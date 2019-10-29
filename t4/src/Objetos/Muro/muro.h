#ifndef MURO_H
#define MURO_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "../../Utils/Ponto/ponto.h"

typedef void* Muro;

Muro criarMuro(double x1, double y1, double x2, double y2);
Ponto Muro_get_p1(Muro m);
Ponto Muro_get_p2(Muro m);
void Muro_escreverSvg(Muro m, FILE *svg);
void destruirMuro(Muro m);

int Muro_compararChave(Muro a, Muro b);
int Muro_getSize();

#endif