#ifndef ESTABELECIMENTO_H
#define ESTABELECIMENTO_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef void* Estabelecimento;
typedef void* Pessoa;
typedef void* Predio;

Estabelecimento criarEstabelecimento(char* cnpj, char* cpf, char* codt, char* cep, char face, double num, char* nome);
void destruirEstabelecimento(Estabelecimento estabelecimento);
char* Estabelecimento_get_cnpj(Estabelecimento estabelecimento);
char* Estabelecimento_getDados(Estabelecimento estabelecimento, char* dados);
char* Estabelecimento_getCep(Estabelecimento estabelecimento);
char* Estabelecimento_getCodt(Estabelecimento estabelecimento);
char Estabelecimento_getFace(Estabelecimento estabelecimento);
double Estabelecimento_getNum(Estabelecimento estabelecimento);

void Estabelecimento_setProprietario(Estabelecimento estabelecimento, Pessoa proprietario);
Pessoa Estabelecimento_getProprietario(Estabelecimento estabelecimento);
void Estabelecimento_setPredio(Estabelecimento estabelecimento, Predio predio);
Predio Estabelecimento_getPredio(Estabelecimento estabelecimento);

bool estabelecimentoEquals(Estabelecimento estabelecimento, char *id);
int Estabelecimento_compararChave(Estabelecimento a, Estabelecimento b);

char* Estabelecimento_getChave(Estabelecimento estabelecimento);

#endif