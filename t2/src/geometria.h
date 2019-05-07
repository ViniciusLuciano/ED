#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "headers.h"
#include "./Objetos/Circulo/circulo.h"
#include "./Objetos/Retangulo/retangulo.h"
#include "./Objetos/Forma/forma.h"

/*
Circulos e Retangulos são formas
*/

bool pontoInternoForma(double px, double py, Forma f);
void centroDeMassa(Forma f, double *ponto);
double distanciaCentro(Forma j, Forma k);

// São funções usadas apenas nesse arquivo ?
bool pontoInternoRetangulo(double px, double py, Retangulo r);
bool pontoInternoCirculo(double px, double py, Circulo c);
double distancia(double x1, double y1, double x2, double y2);



#endif