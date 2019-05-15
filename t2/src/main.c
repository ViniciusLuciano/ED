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

    Cidade cidade = criarCidade();
    processarArquivoEntrada(arquivoEntrada, dirSaida, nomeArquivoEntrada, cidade);
    fclose(arquivoEntrada); 

    if(nomeArquivoConsulta != NULL) {
        FILE *consulta = abrirArquivo( dirEntrada, nomeArquivoConsulta, "r" );
        if(consulta == NULL)
            return 1;
        processarArquivoConsulta(nomeArquivoEntrada, dirSaida, nomeArquivoConsulta, cidade);
        fclose(consulta);
    }
    
    desalocarArgumentos(dirEntrada, nomeArquivoEntrada, nomeArquivoConsulta, dirSaida);
    destruirCidade(cidade);
}