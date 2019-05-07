#ifndef SVG_H
#define SVG_H

#include "headers.h"
#include "formas.h"
#include "geometria.h"
#include "./Objetos/Circulo/circulo.h"
#include "./Objetos/Retangulo/retangulo.h"

void iniciarSVG(FILE *SVG);

void finalizarSVG(FILE *SVG);

void escreverCirculo(FILE *SVG, Forma *c);

void escreverRetangulo(FILE *SVG, Forma *r);

void escreverTexto(FILE *SVG, Forma *t);

void retanguloDelimitador(FILE *SVG2, Forma *a, Forma *b, bool colidem);

//void escreverArvoreSVG(struct Node* node, FILE *SVG);

void escreverPontoInterno(FILE *SVG, Forma *a, double x, double y, bool interno);

void retaCentrosMassa(FILE *SVG, Forma *a, Forma *b);

void distanciaCentrosMassa(FILE *SVG, Forma *a, Forma *b, double distancia);

//void escreverFormasEnvoltas(FILE *SVG, struct Node* node, char *cor);

#endif