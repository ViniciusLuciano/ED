#ifndef MURO_H
#define MURO_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef void* Muro;

Muro criarMuro(double x1, double y1, double x2, double y2);
void Muro_escreverSvg(Muro m, FILE *svg);
void destruirMuro(Muro m);


#endif