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
    //ArvoreBin *raiz = iniciaArvore();

    Cidade cidade = criarCidade();
    processarArquivoEntrada(arquivoEntrada, dirSaida, nomeArquivoEntrada, cidade); // Arquivo de entrada / Arquivo SVG para escrever / cidade
    fclose(arquivoEntrada); 

    // Abrir na main
    processarArquivoConsulta(nomeArquivoEntrada, dirSaida, dirEntrada, nomeArquivoConsulta, cidade);
    
    desalocarArgumentos(dirEntrada, nomeArquivoEntrada, nomeArquivoConsulta, dirSaida);
    destruirCidade(cidade);
}