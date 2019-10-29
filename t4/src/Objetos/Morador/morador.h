#ifndef MORADOR_H
#define MORADOR_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef void* Morador;

Morador criarMorador(char* cpf, char* cep, char face, double num, char* complemento);
void destruirMorador(Morador morador);
char* Morador_get_cnpj(Morador morador);
void Morador_escreverSvg(Morador morador, FILE *SVG);
char* Morador_getDados(Morador morador, char* dados);
char* Morador_getCep(Morador morador);
void Morador_mudarEndereco(Morador morador, char* cep, char face, double num, char* complemento);

bool moradorEquals(Morador morador, char *id);
int Morador_getSize();

char* Morador_getChave(Morador morador);
int Morador_compararChave(Morador m1, Morador m2);

#endif