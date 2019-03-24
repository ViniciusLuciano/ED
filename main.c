#include "main.h"

int main(int argc, char* argv[]) {
    
    char *dirEntrada = NULL;
    char *nomeArquivoEntrada = NULL;
    char *nomeArquivoConsulta = NULL;
    char *dirSaida = NULL;
    lerArgumentos(argc, argv, &dirEntrada, &nomeArquivoEntrada, &nomeArquivoConsulta, &dirSaida);

    FILE *arquivoEntrada = abrirArquivo( tratarDiretorio(dirEntrada, nomeArquivoEntrada) );
    ArvoreBin *raiz = iniciaArvore();
    
    processarArquivoEntrada(arquivoEntrada, dirSaida, nomeArquivoEntrada, raiz); // Arquivo de entrada / Arquivo SVG para escrever / raiz da arvore
    fclose(arquivoEntrada);


    desalocarArgumentos(dirEntrada, nomeArquivoEntrada, nomeArquivoConsulta, dirSaida);
    liberarArvore(raiz);    
}