#ifndef PREDIO_H
#define PREDIO_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../../Utils/Arvore/arvore.h"
#include "../Morador/morador.h"

typedef void* Predio;

Predio criarPredio(char *cep, char face, double num, double f, double p, double mrg);
char* Predio_getId(Predio prd);
char Predio_get_face(Predio prd);
char* Predio_getCep(Predio prd);
double Predio_get_x(Predio prd);
double Predio_get_y(Predio prd);
double Predio_get_x_max(Predio prd);
double Predio_get_y_max(Predio prd);
double Predio_get_num(Predio prd);
void Predio_setPosicoes(Predio prd, double quadra_x, double quadra_y, double quadra_w, double quadra_h);
void Predio_escreverSvg(Predio prd, double quadra_x, double quadra_y, double quadra_w, double quadra_h, FILE *svg);
void destruirPredio(Predio prd);
void Predio_setMorador(Predio q, Morador m);
Node Predio_getMoradores(Predio q);
bool Predio_removerMorador(Predio q, Morador m);
//*
bool Predio_removerMoradorE(Predio p, Morador m);
void Predio_setQuadra(Predio prd, Objeto quadra);
Objeto Predio_getQuadra(Predio prd);
int Predio_getNumMoradores(Predio prd);
void Predio_setCor(Predio prd, char* cor);

bool predioEquals(Predio p, char *id);
int Predio_compararChave(Predio a, Predio b);
char* Predio_getDados(Predio p, char* dados);

char* Predio_getChave(Predio p);

#endif