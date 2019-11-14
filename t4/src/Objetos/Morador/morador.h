#ifndef MORADOR_H
#define MORADOR_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../Pessoa/pessoa.h"

typedef void* Predio;
typedef void* Quadra;
typedef void* Morador;

Morador criarMorador(char* cpf, char* cep, char face, double num, char* complemento);
void destruirMorador(Morador morador);
char* Morador_get_cpf(Morador morador);
void Morador_escreverSvg(Morador morador, FILE *SVG);
char* Morador_getDados(Morador morador, char* dados);
char* Morador_getCep(Morador morador);
void Morador_mudarEndereco(Morador morador, char* cep, char face, double num, char* complemento);
void Morador_setQuadra(Morador m, Quadra quadra);
Quadra Morador_getQuadra(Morador m);
void Morador_setPredio(Morador m, Predio predio);
Predio Morador_getPredio(Morador m);
void Morador_setPessoa(Morador m, Pessoa pessoa);

bool moradorEquals(Morador morador, char *id);

char* Morador_getChave(Morador morador);
int Morador_compararChave(Morador m1, Morador m2);

#endif