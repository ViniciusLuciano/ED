#ifndef UTILS_H
#define UTILS_H

#include "headers.h"
#include "formas.h"
#include "arvoreBin.h"
#include "svg.h"
#include <stdio.h>

double clamp(double valor, double a, double b);

FILE *abrirArquivo(char *diretorio);

void lerArgumentos(int argc , char *argv[], char *dirEntrada[], char *nomeArquivoEntrada[], char *nomeArquivoConsulta[], char *dirSaida[]);

char *tratarDiretorio(char *diretorio, char *nomeArquivo);

void processarArquivoEntrada(FILE *entrada, char *dirSVG, char *nomeArquivoSVG, ArvoreBin *raiz);

char *obterSemExtensao(char *arquivo);

#endif