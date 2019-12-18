#ifndef SVG_H
#define SVG_H

#include "headers.h"
#include "./Objetos/Circulo/circulo.h"
#include "./Objetos/Retangulo/retangulo.h"
#include "./Objetos/Forma/forma.h"
#include "./Objetos/Texto/texto.h"
#include "./Utils/Vertice/vertice.h"
#include "./Utils/Grafo/grafo.h"

void svg_iniciar(FILE *SVG);
void svg_finalizar(FILE *SVG);
void svg_escreverRetanguloDelimitador(FILE *SVG, Forma a, Forma b, bool colidem);
void svg_escreverPontoInterno(FILE *SVG, Forma a, double x, double y, bool interno);
void svg_escreverRetaCentrosMassa(FILE *SVG, Forma a, Forma b);
void svg_escreverDistanciaCentrosMassa(FILE *SVG, Forma a, Forma b, double distancia);
void svg_escreverTriangulo(FILE *SVG, double x1, double y1, Vertice v2, Vertice v3, bool brl);
void svg_escreverBomba(FILE *SVG, double x, double y);
void svg_escreverX(FILE* svg, Predio p);
void svg_escreverPercursos(FILE* svg, VerticeG* percursomc, VerticeG* percursomr, char* cormr, char* cormc, FILE* txt);

#endif