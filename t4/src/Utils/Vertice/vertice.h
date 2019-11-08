#ifndef VERTICE_H
#define VERTICE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "../Ponto/ponto.h"

typedef void* Vertice;
typedef void* Segmento;

#include "../Segmento/segmento.h"
#include "../../Utils/Geometria/geometria.h"

// Vertice criarVertice(Ponto p, double angulo, double distancia);
// Vertice criarVerticep(double x1, double y1, double angulo, double distancia);
Vertice criarVertice(double x, double y, double x_centro, double y_centro);
void destruirVertice(Vertice v);
double Vertice_get_angulo(Vertice v);
void Vertice_set_inicio(Vertice v, bool inicio);
bool Vertice_get_inicio(Vertice v);
double Vertice_get_x(Vertice v);
double Vertice_get_y(Vertice v);
Ponto Vertice_get_p(Vertice v);
void Vertice_set_s(Vertice v, Segmento s);
Segmento Vertice_get_s(Vertice v);
void Vertice_set_angulo(Vertice v, double angulo);
double Vertice_get_distancia(Vertice v);
int Vertice_getSize();
bool Vertice_equals(Vertice v1, Vertice v2);

#endif