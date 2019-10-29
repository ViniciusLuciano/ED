#ifndef COLISAO_H
#define COLISAO_H

#include "../../headers.h"
#include "../Geometria/geometria.h"
#include "../../Objetos/Circulo/circulo.h"
#include "../../Objetos/Retangulo/retangulo.h"
#include "../../Objetos/Forma/forma.h"
#include "../../utils.h"

bool formasColidem(Forma a, Forma b);
// Funções usada apenas nesse arquivo?
bool colisaoCirculoRetangulo(Circulo c, Retangulo r);
bool colisaoRetanguloRetangulo(Retangulo r1, Retangulo r2);
bool colisaoCirculoCirculo(Circulo c1, Circulo c2);

#endif