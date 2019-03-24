#ifndef SVG_H
#define SVG_H

#include "headers.h"
#include "formas.h"

char* iniciarSVG(char *width, char *height);

char* finalizarSVG();

char* escreverCirculo(Forma *c);

char* escreverRetangulo(Forma *r);

#endif