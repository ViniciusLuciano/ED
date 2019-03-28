#ifndef UTILS_H
#define UTILS_H

#include "headers.h"
#include "formas.h"
#include "arvoreBin.h"
#include "svg.h"
#include "colisao.h"

double clamp(double valor, double a, double b);

FILE *abrirArquivo(char *diretorio);

bool lerArgumentos(int argc , char *argv[], char *dirEntrada[], char *nomeArquivoEntrada[], char *nomeArquivoConsulta[], char *dirSaida[]);

char *tratarDiretorio(char *diretorio, char *nomeArquivo);

void processarArquivoEntrada(FILE *entrada, char *dirSVG, char *nomeArquivoSVG, ArvoreBin *raiz);

char *obterSemExtensao(char *arquivo);

void desalocarArgumentos(char *dirEntrada, char *nomeArquivoEntrada, char *nomeArquivoConsulta, char *dirSaida);

void processarArquivoConsulta(char *nomeArquivoEntrada, char *dirSaida, char *dirArquivoConsulta, char *nomeArquivoConsulta, ArvoreBin *raiz);

FILE *abrirTXT(char *dirSaida, char *nomeArquivo);

char *concatenarNomes(char *nome1, char *nome2);

#endif