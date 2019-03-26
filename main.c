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

    processarArquivoConsulta(nomeArquivoEntrada, dirSaida, dirEntrada, nomeArquivoConsulta, raiz);
    
    // char *path = calloc(1000, sizeof(char));
    // sprintf(path, "  ");
    // printarArvore(*raiz, path);


    desalocarArgumentos(dirEntrada, nomeArquivoEntrada, nomeArquivoConsulta, dirSaida);
    liberarArvore(raiz);    
}