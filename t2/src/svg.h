#ifndef SVG_H
#define SVG_H

#include "headers.h"
#include "./Objetos/Circulo/circulo.h"
#include "./Objetos/Retangulo/retangulo.h"
#include "./Objetos/Forma/forma.h"

void iniciarSVG(FILE *SVG);
void finalizarSVG(FILE *SVG);
void escreverRetanguloDelimitador(FILE *SVG2, Forma a, Forma b, bool colidem);
void escreverPontoInterno(FILE *SVG, Forma a, double x, double y, bool interno);
void escreverRetaCentrosMassa(FILE *SVG, Forma a, Forma b);
void escreverDistanciaCentrosMassa(FILE *SVG, Forma a, Forma b, double distancia);

#endif