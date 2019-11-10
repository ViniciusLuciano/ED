#ifndef SEGMENTO_H
#define SEGMENTO_H

#define M_PI 3.141592653589793

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "../Vertice/vertice.h"

typedef void* Segmento;

Segmento criarSegmento(Vertice v1, Vertice v2);
void destruirSegmento(Segmento s);
void Segmento_set_inicio_vertices(Segmento s);
Vertice Segmento_get_v1(Segmento s);
Vertice Segmento_get_v2(Segmento s);
void Segmento_set_distancia(Segmento s, double x, double y);
double Segmento_get_distancia(Segmento s);
int Segmento_compararChave(Segmento a, Segmento b);

#endif