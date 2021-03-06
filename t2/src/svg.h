#ifndef SVG_H
#define SVG_H

#include "headers.h"
#include "./Objetos/Circulo/circulo.h"
#include "./Objetos/Retangulo/retangulo.h"
#include "./Objetos/Forma/forma.h"

void svg_iniciar(FILE *SVG);
void svg_finalizar(FILE *SVG);
void svg_escreverRetanguloDelimitador(FILE *SVG, Forma a, Forma b, bool colidem);
void svg_escreverPontoInterno(FILE *SVG, Forma a, double x, double y, bool interno);
void svg_escreverRetaCentrosMassa(FILE *SVG, Forma a, Forma b);
void svg_escreverDistanciaCentrosMassa(FILE *SVG, Forma a, Forma b, double distancia);

#endif