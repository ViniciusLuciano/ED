#ifndef UTILS_H
#define UTILS_H

#include "headers.h"
#include "svg.h"
#include "./Objetos/Cidade/cidade.h"
#include "./Objetos/Forma/forma.h"
#include "./Objetos/Circulo/circulo.h"
#include "./Objetos/Retangulo/retangulo.h"
#include "./Objetos/Texto/texto.h"
#include "./Objetos/Quadra/quadra.h"
#include "./Objetos/Hidrante/hidrante.h"
#include "./Objetos/Semaforo/semaforo.h"
#include "./Objetos/RadioBase/radioBase.h"
#include "./Utils/Lista/lista.h"
#include "./Utils/Geometria/geometria.h"
#include "./Utils/Colisao/colisao.h"

double clamp(double valor, double a, double b);
void obterNomeArquivo(char *dirArquivo);
FILE* abrirArquivo(char *diretorio, char *nomeArquivo, char *modoAbertura);
bool lerArgumentos(int argc , char *argv[], char *dirEntrada[], char *nomeArquivoEntrada[], char *nomeArquivoConsulta[], char *dirSaida[]);
void tratarDiretorio(char *diretorio, char *nomeArquivo, char *diretorioFinal);
bool processarArquivoEntrada(FILE *entrada, char *dirSVG, char *nomeArquivoSVG, Cidade cidade);
void obterSemExtensao(char *arquivo);
void adicionarExtensao(char *arquivo, char *extensao);
void desalocarArgumentos(char *dirEntrada, char *nomeArquivoEntrada, char *nomeArquivoConsulta, char *dirSaida);
bool processarArquivoConsulta(FILE* arquivoConsulta, char *nomeArquivoEntrada, char *dirSaida, char *nomeArquivoConsulta, Cidade cidade);
FILE *abrirTXT(char *dirSaida, char *nomeArquivo);
void concatenarNomes(char *nome1, char *nome2, char *nomeSaida);

#endif