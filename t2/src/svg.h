#ifndef SVG_H
#define SVG_H

#include "headers.h"
#include "geometria.h"
#include "./Objetos/Forma/forma.h"
#include "./Objetos/Circulo/circulo.h"
#include "./Objetos/Retangulo/retangulo.h"

void iniciarSVG(FILE *SVG);
void finalizarSVG(FILE *SVG);
void escreverCirculo(FILE *SVG, Circulo c);
void escreverRetangulo(FILE *SVG, Retangulo r);
//void escreverTexto(FILE *SVG, Texto t);
void escreverretanguloDelimitador(FILE *SVG2, Forma a, Forma b, bool colidem);
void escreverPontoInterno(FILE *SVG, Forma a, double x, double y, bool interno);
void escreverRetaCentrosMassa(FILE *SVG, Forma a, Forma b);
void escreverdistanciaCentrosMassa(FILE *SVG, Forma a, Forma b, double distancia);
//void escreverFormasEnvoltas(FILE *SVG, struct Node* node, char *cor);

#endif