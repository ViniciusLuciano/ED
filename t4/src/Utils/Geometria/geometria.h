#ifndef GEOMETRIA_H
#define GEOMETRIA_H

#include "../../headers.h"
#include "../../Objetos/Circulo/circulo.h"
#include "../../Objetos/Retangulo/retangulo.h"
#include "../../Objetos/Forma/forma.h"
#include "../../Utils/Ponto/ponto.h"
#include "../../Utils/Segmento/segmento.h"
#include "../../Utils/Poligono/poligono.h"
#include "../../Utils/Arvore/arvore.h"
#include <math.h>

#define forEach(item, raiz) \
    for (Node (item) = (raiz); (item) != NULL; (item) = next(item))

typedef void* Poligono;

bool pontoInternoForma(double px, double py, Forma f);
void centroDeMassa(Forma f, double *ponto);
double distanciaL2Centro(Forma j, Forma k);
bool retanguloInternoCirculo(Retangulo r, Circulo c);

// São funções usadas apenas nesse arquivo ?
bool pontoInternoRetangulo(double px, double py, Retangulo r);
bool pontoInternoCirculo(double px, double py, Circulo c);
double distanciaL1(double x1, double y1, double x2, double y2);
double distanciaL2(double x1, double y1, double x2, double y2);
bool retanguloInternoRetangulo(Retangulo r1, Retangulo r2);
bool retanguloInternoL1(double px, double py, Retangulo r, double dist);
double calcularAngulo(Ponto p, double x, double y);
double calcularAngulop(double xp, double yp, double x, double y);
bool verificarSegmentosInterceptam(Segmento s1, Segmento s2);
double buscarXInterseccaoSegmento(Segmento s, double y);
Segmento buscarSegmentoFormadoComVertice(double xc, double yc, Vertice v, Ponto pontoMin, Ponto pontoMax);
Ponto buscarPontoInterseccao(Segmento a, Segmento b);
bool PontoInternoPoligono(Ponto ponto, Poligono poligono);
bool RetanguloInternoPoligono(Retangulo r, Poligono p);
bool RetanguloParcialmenteInternoPoligono(Retangulo r, Poligono p);
double calcularAreaTriangulo(double x, double y, Vertice b, Vertice c);

#endif