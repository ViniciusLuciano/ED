#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "formas.h"
#include "headers.h"

double distancia(double x1, double y1, double x2, double y2);

bool pontoInternoCirculo(double px, double py, Forma *c);

bool pontoInternoRetangulo(double px, double py, Forma *r);

void centroDeMassa(Forma *f, double *ponto);

double distanciaCentro(Forma *j, Forma *k);

#endif