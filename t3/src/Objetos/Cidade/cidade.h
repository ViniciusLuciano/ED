#ifndef CIDADE_H
#define CIDADE_H

#include "../../headers.h"
#include "../../Utils/Lista/lista.h"
#include "../../Utils/Geometria/geometria.h"
#include "../../Utils/Sort/sort.h"
#include "../../Utils/Ponto/ponto.h"
#include "../../Utils/Segmento/segmento.h"
#include "../../Utils/Vertice/vertice.h"
#include "../Forma/forma.h"
#include "../Texto/texto.h"
#include "../Quadra/quadra.h"
#include "../Hidrante/hidrante.h"
#include "../Semaforo/semaforo.h"
#include "../RadioBase/radioBase.h"
#include "../Circulo/circulo.h"
#include "../Retangulo/retangulo.h"
#include "../Predio/predio.h"
#include "../Muro/muro.h"

#include <string.h>
#include <stdlib.h>
#include <limits.h>


/*
Uma cidade contem todos os elementos.
*/

typedef void* Cidade;

Cidade criarCidade(int i, int nq, int nh, int ns, int nr, int np, int nm);
void destruirCidade(Cidade cidade);
void Cidade_setForma(Cidade cidade, Forma forma);
void Cidade_setQuadra(Cidade cidade, Quadra quadra);
void Cidade_setHidrante(Cidade cidade, Hidrante hidrante);
void Cidade_setSemaforo(Cidade cidade, Semaforo semaforo);
void Cidade_setRadioBase(Cidade cidade, RadioBase radioBase);
void Cidade_setTexto(Cidade cidade, Texto texto);
void Cidade_setPredio(Cidade cidade, Predio predio);
void Cidade_setMuro(Cidade cidade, Muro muro);
Forma Cidade_getForma(Cidade cidade, char *id);
Quadra Cidade_getQuadra(Cidade cidade, char *id);
Hidrante Cidade_getHidrante(Cidade cidade, char *id);
Semaforo Cidade_getSemaforo(Cidade cidade, char *id);
RadioBase Cidade_getRadioBase(Cidade cidade, char *id);
bool Cidade_removerObjeto(Cidade cidade, char *id);
void Cidade_removerQuadrasInternasEquipamento(Cidade cidade, double px, double py, double dist, char *op, FILE *txt);
void Cidade_setCstrkQuadrasInternasCirculo(Cidade cidade, Circulo c, char *cstrk, FILE *txt);
void Cidade_deslocarEquipamentosInternosRetangulo(Cidade cidade, Retangulo r, double dx, double dy, FILE *txt);
void Cidade_escreverSvg(Cidade cidade, FILE *svg);
void Cidade_escreverFormasEnvoltas(Cidade cidade, FILE *svg, char *cor);
void Cidade_processarFocoIncendio(Cidade c, double x, double y, int ns, double r, FILE *txt, FILE *svg);
void Cidade_processarObjetosProximos(Cidade c, char sinal, int k, char cep[], char face, double num, FILE* txt, FILE *svg, char tipo[]);
void Cidade_processarBombaRaioLuminoso(Cidade c, double x, double y, FILE *svg);

void imprimirCidade(Cidade c);

double obj_getComparador(Objeto objeto);
Objeto obj_getObjeto(Objeto objeto);
#endif