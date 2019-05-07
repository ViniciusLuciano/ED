#ifndef UTILS_H
#define UTILS_H

#include "headers.h"
//#include "formas.h"
//#include "arvoreBin.h"
#include "svg.h"
#include "colisao.h"

double clamp(double valor, double a, double b);

void obterNomeArquivo(char *dirArquivo);

FILE* abrirArquivo(char *diretorio, char *nomeArquivo, char *modoAbertura);

bool lerArgumentos(int argc , char *argv[], char *dirEntrada[], char *nomeArquivoEntrada[], char *nomeArquivoConsulta[], char *dirSaida[]);

void tratarDiretorio(char *diretorio, char *nomeArquivo, char *diretorioFinal);

void processarArquivoEntrada(FILE *entrada, char *dirSVG, char *nomeArquivoSVG, ArvoreBin *raiz);

void obterSemExtensao(char *arquivo);

void adicionarExtensao(char *arquivo, char *extensao);

void desalocarArgumentos(char *dirEntrada, char *nomeArquivoEntrada, char *nomeArquivoConsulta, char *dirSaida);

void processarArquivoConsulta(char *nomeArquivoEntrada, char *dirSaida, char *dirArquivoConsulta, char *nomeArquivoConsulta, ArvoreBin *raiz);

FILE *abrirTXT(char *dirSaida, char *nomeArquivo);

void concatenarNomes(char *nome1, char *nome2, char *nomeSaida);

#endif