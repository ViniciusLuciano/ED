#include "main.h"

int main(int argc, char* argv[]) {
    
    char *dirEntrada = NULL;
    char *nomeArquivoEntrada = NULL;
    char *nomeArquivoConsulta = NULL;
    char *dirSaida = NULL;

    bool argumentosCorretos = lerArgumentos(argc, argv, &dirEntrada, &nomeArquivoEntrada, &nomeArquivoConsulta, &dirSaida);
    if(!argumentosCorretos)
        return 1;


    FILE *arquivoEntrada = abrirArquivo( dirEntrada, nomeArquivoEntrada, "r" );
    if(arquivoEntrada == NULL)
        return 1;
    ArvoreBin *raiz = iniciaArvore();


    processarArquivoEntrada(arquivoEntrada, dirSaida, nomeArquivoEntrada, raiz); // Arquivo de entrada / Arquivo SVG para escrever / raiz da arvore
    fclose(arquivoEntrada); 

    // Abrir na main
    processarArquivoConsulta(nomeArquivoEntrada, dirSaida, dirEntrada, nomeArquivoConsulta, raiz);
    
    desalocarArgumentos(dirEntrada, nomeArquivoEntrada, nomeArquivoConsulta, dirSaida);
    liberarArvore(raiz);
}