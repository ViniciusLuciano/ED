#ifndef SVG_H
#define SVG_H

#include "headers.h"
#include "formas.h"
#include "arvoreBin.h"

void iniciarSVG(FILE *SVG, char *width, char *height);

void finalizarSVG(FILE *SVG);

void escreverCirculo(FILE *SVG, Forma *c);

void escreverRetangulo(FILE *SVG, Forma *r);

void retanguloDelimitador(FILE *SVG2, Forma *a, Forma *b, bool colidem);

void escreverArvoreSVG(struct Node* node, FILE *SVG);

void escreverPontoInterno(FILE *SVG, Forma *a, double x, double y, bool interno);

void retaCentrosMassa(FILE *SVG, Forma *a, Forma *b);

#endif