#ifndef SVG_H
#define SVG_H

#include "headers.h"
#include "formas.h"

void iniciarSVG(FILE *SVG, char *width, char *height);

void finalizarSVG(FILE *SVG);

void escreverCirculo(FILE *SVG, Forma *c);

void escreverRetangulo(FILE *SVG, Forma *r);

#endif