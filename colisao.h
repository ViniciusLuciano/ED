#ifndef COLISAO_H
#define COLISAO_H

#include "headers.h"
#include "formas.h"
#include "geometria.h"
#include "utils.h"

bool colisaoCirculoRetangulo(Forma *c, Forma *b);

bool colisaoRetanguloRetangulo(Forma *r1, Forma *r2);

bool colisaoCirculoCirculo(Forma *c1, Forma *c2);

#endif