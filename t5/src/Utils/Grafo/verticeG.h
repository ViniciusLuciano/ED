#ifndef VERTICEG_H
#define VERTICEG_H

#include "../../headers.h"
#include "../Lista/lista.h"
#include "../Geometria/geometria.h"
#include "arestaG.h"

typedef void* VerticeG;
typedef void* Poligono;

VerticeG criarVerticeG(char *id, double x, double y, int numVert);
void destruirVerticeG(VerticeG v);
double VerticeG_get_x(VerticeG v);
double VerticeG_get_y(VerticeG v);
bool VerticeG_equals(VerticeG v1, char *id);
char* VerticeG_getChave(VerticeG v);
void VerticeG_inserirArestaG(VerticeG v, ArestaG aresta);
int VerticeG_compararChave(VerticeG v1, VerticeG v2);
Lista VerticeG_get_listaArestas(VerticeG v);
int VerticeG_get_numVert(VerticeG v);
bool Vertige_get_inicial(VerticeG v);
void VerticeG_set_inicial(VerticeG v, bool inicial);
void VerticeG_destruirArestasNoPoligono(VerticeG v, Poligono poligono);
VerticeG VerticeG_getPosic(VerticeG v, char posic);

#endif