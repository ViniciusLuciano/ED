#include "main.h"
#include "Utils/Poligono/poligono.h"

int main(int argc, char* argv[]) {
    
    Cidade cidade;
    char *dirEntrada = NULL;
    char *nomeArquivoEntrada = NULL;
    char *nomeArquivoConsulta = NULL;
    char *dirSaida = NULL;
    char *nomeArquivoEC = NULL;
    char *nomeArquivoPM = NULL;
    bool modoInterativo = false;

    bool argumentosCorretos = lerArgumentos(argc, argv, &dirEntrada, &nomeArquivoEntrada, 
                                    &nomeArquivoConsulta, &dirSaida, &nomeArquivoEC, &nomeArquivoPM, &modoInterativo);
    if (!argumentosCorretos)
        return 1;

    FILE *arquivoEntrada = abrirArquivo( dirEntrada, nomeArquivoEntrada, "r" );
    if (arquivoEntrada == NULL)
        return 1;
    processarArquivoEntrada(arquivoEntrada, dirSaida, nomeArquivoEntrada, &cidade);
    fclose(arquivoEntrada);

    if (nomeArquivoEC != NULL) {
        FILE *arquivoEC = abrirArquivo( dirEntrada, nomeArquivoEC, "r" );
        if (arquivoEC == NULL)
            return 1;
        processarArquivoEC(arquivoEC, dirSaida, nomeArquivoEC, &cidade);
        fclose(arquivoEC);
    }

    if (nomeArquivoPM != NULL) {
        FILE *arquivoPM = abrirArquivo( dirEntrada, nomeArquivoPM, "r" );
        if (arquivoPM == NULL)
            return 1;
        processarArquivoPM(arquivoPM, dirSaida, nomeArquivoPM, &cidade);
        fclose(arquivoPM);
    }

    if (nomeArquivoConsulta != NULL) {
        FILE *arquivoConsulta = abrirArquivo( dirEntrada, nomeArquivoConsulta, "r" );
        if (arquivoConsulta == NULL)
            return 1;
        processarArquivoConsulta(arquivoConsulta, nomeArquivoEntrada, dirSaida, nomeArquivoConsulta, dirEntrada, &cidade);
        fclose(arquivoConsulta);
    }

    if (modoInterativo) {
        executarModoInterativo(&cidade, dirSaida, dirEntrada, nomeArquivoEntrada);
    }

    desalocarArgumentos(dirEntrada, nomeArquivoEntrada, nomeArquivoConsulta, dirSaida, nomeArquivoEC, nomeArquivoPM);
    destruirCidade(cidade);
}