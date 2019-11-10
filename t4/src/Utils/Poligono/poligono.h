#ifndef POLIGONO_H
#define POLIGONO_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../Arvore/arvore.h"
#include "../Segmento/segmento.h"

typedef void* Poligono;

Poligono criarPoligono(FILE* polig);
void destruirPoligono(Poligono poligono);
// void Poligono_escreverSvg(Poligono poligono, FILE *SVG);
double Poligono_get_max_x(Poligono p);
Arvore Poligono_getSegmentos(Poligono p);
void Poligono_escreverSVG(Poligono p, FILE* svg);

#endif