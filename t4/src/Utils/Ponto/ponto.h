#ifndef PONTO_H
#define PONTO_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef void* Ponto;

Ponto criarPonto(double x, double y);
void destruirPonto(Ponto p);
double Ponto_get_x(Ponto p);
double Ponto_get_y(Ponto p);
void Ponto_set_x(Ponto p, double x);
void Ponto_set_y(Ponto p, double y);

void Ponto_setMin(Ponto p, double x, double y);
void Ponto_setMax(Ponto p, double x, double y);

int Ponto_getSize();

#endif