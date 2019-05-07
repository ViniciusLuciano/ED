#include "utils.h"

// Tirar isso daqui
double clamp(double valor, double a, double b) {
    double clmp = valor < a ? a : valor;
    clmp = valor > b ? b : clmp;
    return clmp;
}

bool lerArgumentos(int argc , char *argv[], char *dirEntrada[], char *nomeArquivoEntrada[], char *nomeArquivoConsulta[], char *dirSaida[]) {
    for(int i = 1; i < argc; i++) {
        if(strcmp(argv[i], "-e") == 0) {
            if( i+1 >= argc ) {
                printf("'-e' requer um argumento\n");
                return false;
            }

            *dirEntrada = malloc(128*sizeof(char));   
            strcpy(*dirEntrada, argv[i+1]);

        } else if(strcmp(argv[i], "-f") == 0) {
            if( i+1 >= argc ) {
                printf("'-f' requer um argumento\n");
                return false;
            }

            *nomeArquivoEntrada = malloc(128*sizeof(char));
            strcpy(*nomeArquivoEntrada, argv[i+1]);

        } else if(strcmp(argv[i], "-q") == 0) {
            if( i+1 >= argc ) {
                printf("'-q' requer um argumento\n");
                return false;
            }

            *nomeArquivoConsulta = malloc(128*sizeof(char));
            strcpy(*nomeArquivoConsulta, argv[i+1]);

        } else if(strcmp(argv[i], "-o") == 0) {
            if( i+1 >= argc ) {
                printf("'-o' requer um argumento\n");
                return false;
            }

            *dirSaida = malloc(128*sizeof(char));
            strcpy(*dirSaida, argv[i+1]);
        }
    }

    if(*nomeArquivoEntrada == NULL || *dirSaida == NULL) {
        printf("Requer arquivo de entrada e/ou diretório de saída.\n");
        return false;
    }

    return true;
}

void tratarDiretorio(char *diretorio, char *nomeArquivo, char *diretorioFinal) {
    if(diretorio == NULL) {
        strcpy(diretorioFinal, nomeArquivo);
    } else if(diretorio[strlen(diretorio) - 1] == '/') {
		sprintf(diretorioFinal, "%s%s", diretorio, nomeArquivo);
	} else {
		sprintf(diretorioFinal, "%s/%s", diretorio, nomeArquivo);
	}
}

FILE* abrirArquivo(char *diretorio, char *nomeArquivo, char *modoAbertura) {
    char dirFinal[128];
    tratarDiretorio(diretorio, nomeArquivo, dirFinal);
    FILE* arq = fopen(dirFinal, modoAbertura);
    if(arq == NULL)
        printf("Falha na inicialização do arquivo %s\n", dirFinal);
    return arq;
}

void obterSemExtensao(char *arquivo) {
    for(int i = strlen(arquivo)-1; i > 0; i--) {
        if(arquivo[i] == '.') {
            arquivo[i] = '\0';
            break;
        } else if(arquivo[i] == '/') {
            break;
        }
    }
}

void adicionarExtensao(char *arquivo, char *extensao) {
    obterSemExtensao(arquivo);
    sprintf(arquivo, "%s.%s", arquivo, extensao);
}

void obterNomeArquivo(char *dirArquivo) {
    obterSemExtensao(dirArquivo);
    int index = strlen(dirArquivo) - 1;

    while(index >= 0) {
        if(dirArquivo[index] == '/')
            break;
        index--;
    }

    if(index >= 0)
        strcpy(dirArquivo, dirArquivo + index + 1);
}

void concatenarNomes(char *nome1, char *nome2, char *nomeSaida) {
    sprintf(nomeSaida, "%s-%s", nome1, nome2);
}


// Processa isso na main? Better maybe
void processarArquivoEntrada(FILE *entrada, char *dirSVG, char *nomeArquivoSVG) {

    char str[150], instrucao[10];
    
    Lista listaForma = criarLista(1000);
    Lista listaTexto = criarLista(1000);
    Lista listaQuadra = criarLista(1000);
    Lista listaHidrante = criarLista(1000);
    Lista listaSemaforo = criarLista(1000);
    Lista listaRadioBase = criarLista(1000);

    char cqfill[50] = "pink", cqstrok[50] = "black", sqw[20] = "2px";
    char chfill[50] = "red", chstrok[50] = "black", shw[20] = "2px";
    char crfill[50] = "gray", crstrok[50] = "black", srw[20] = "2px";
    char csfill[50] = "yellow", csstrok[50] = "black", ssw[20] = "2px";
    char cw[20] = "2px", rw[20] = "2px";

	while(true) {

		fgets(str, sizeof(str), entrada);
        sscanf(str, "%s", instrucao);
		if(feof(entrada))
			break;

		if(strcmp(instrucao, "c") == 0){

            char cfill[50], cstrok[50], id[20], bufferCW[20];
            double r, x, y;

            sprintf(bufferCW, "%s", cw);

			sscanf(str, "%*s %s %lf %lf %lf %s %s", id, &r, &x, &y, cstrok, cfill);
            Circulo c = criarCirculo(x, y, r, cfill, cstrok, bufferCW);
            Forma f = criarForma(id, CIRCULO, c);
            inserirUltimo(listaForma, f);

		} else if(strcmp(instrucao, "r") == 0){

            char cfill[50], cstrok[50], id[20], bufferRW[20];
            double w, h, x, y;

            sprintf(bufferRW, "%s", rw);

			sscanf(str, "%*s %s %lf %lf %lf %lf %s %s", id, &w, &h, &x, &y, cstrok, cfill);
            Retangulo r = criarRetangulo(x, y, w, h, cfill, cstrok, bufferRW);
            Forma f = criarForma(id, RETANGULO, r);
            inserirUltimo(listaForma, f);

		} else if(strcmp(instrucao, "t") == 0) {
    
            char bufferTexto[256];
            double x, y;
            sscanf(str, "%*s %lf %lf %256[^\n]", &x, &y, bufferTexto);
            Texto t = criarTexto(x, y, bufferTexto);
            inserirUltimo(listaTexto, t);
            
		} else if(strcmp(instrucao, "q") == 0) {

            char cep[30], bufferCfill[50], bufferCstrok[50], bufferSW[20];
            double x, y, w, h;

            sprintf(bufferCfill,"%s", cqfill);
            sprintf(bufferCstrok,"%s", cqstrok);
            sprintf(bufferSW,"%s", sqw);

            sscanf(str, "%*s %s %lf %lf %lf %lf", cep, &x, &y, &w, &h);
            Quadra q = criarQuadra(cep, x, y, w, h, bufferCfill, bufferCstrok, bufferSW);
            inserirUltimo(listaQuadra, q);

        } else if(strcmp(instrucao, "h") == 0) {

            char id[30], bufferCfill[50], bufferCstrok[50], bufferSW[20];
            double x, y;

            sprintf(bufferCfill,"%s", chfill);
            sprintf(bufferCstrok,"%s", chstrok);
            sprintf(bufferSW,"%s", shw);

            sscanf(str, "%*s %s %lf %lf", id, &x, &y);
            Hidrante h = criarHidrante(id, x, y, bufferCfill, bufferCstrok, bufferSW);
            inserirUltimo(listaHidrante, h);

        } else if(strcmp(instrucao, "s") == 0) {

            char id[30], bufferCfill[50], bufferCstrok[50], bufferSW[20];
            double x, y;

            sprintf(bufferCfill,"%s", csfill);
            sprintf(bufferCstrok,"%s", csstrok);
            sprintf(bufferSW,"%s", ssw);

            sscanf(str, "%*s %s %lf %lf", id, &x, &y);
            Semaforo s = criarSemaforo(id, x, y, bufferCfill, bufferCstrok, bufferSW);
            inserirUltimo(listaSemaforo, s);

        } else if(strcmp(instrucao, "rb") == 0) {

            char id[30], bufferCfill[50], bufferCstrok[50], bufferSW[20];
            double x, y;

            sprintf(bufferCfill,"%s", crfill);
            sprintf(bufferCstrok,"%s", crstrok);
            sprintf(bufferSW,"%s", srw);

            sscanf(str, "%*s %s %lf %lf", id, &x, &y);
            RadioBase rb = criarRadioBase(id, x, y, bufferCfill, bufferCstrok, bufferSW);
            inserirUltimo(listaRadioBase, rb);

        } else if(strcmp(instrucao, "cq") == 0) {

            char bufferCfill[50], bufferCstrok[50], bufferSW[20];
            sscanf(str, "%*s %s %s %s", bufferCfill, bufferCstrok, bufferSW);
            strcpy(cqfill, bufferCfill);
            strcpy(cqstrok, bufferCstrok);
            strcpy(sqw, bufferSW);

        } else if(strcmp(instrucao, "ch") == 0) {

            char bufferCfill[50], bufferCstrok[50], bufferSW[20];
            sscanf(str, "%*s %s %s %s", bufferCfill, bufferCstrok, bufferSW);
            strcpy(chfill, bufferCfill);
            strcpy(chstrok, bufferCstrok);
            strcpy(shw, bufferSW);
             
        } else if(strcmp(instrucao, "cr") == 0) {

            char bufferCfill[50], bufferCstrok[50], bufferSW[20];
            sscanf(str, "%*s %s %s %s", bufferCfill, bufferCstrok, bufferSW);
            strcpy(crfill, bufferCfill);
            strcpy(crstrok, bufferCstrok);
            strcpy(srw, bufferSW);

        } else if(strcmp(instrucao, "cs") == 0) {

            char bufferCfill[50], bufferCstrok[50], bufferSW[20];
            sscanf(str, "%*s %s %s %s", bufferCfill, bufferCstrok, bufferSW);
            strcpy(csfill, bufferCfill);
            strcpy(csstrok, bufferCstrok);
            strcpy(ssw, bufferSW);

        } else if(strcmp(instrucao, "sw") == 0) {

            char bufferCW[20], bufferRW[20];
            sscanf(str, "%*s %s %s", bufferCW, bufferRW);
            strcpy(cw, bufferCW);
            strcpy(rw, bufferRW);

        } else if(strcmp(instrucao, "nx") == 0) {

            int i, nq, nh, ns, nr;
            sscanf(str, "%*s %d %d %d %d %d", &i, &nq, &nh, &ns, &nr);
            setLista_tamanhoMax(listaForma, i);
            setLista_tamanhoMax(listaQuadra, nq);
            setLista_tamanhoMax(listaHidrante, nh);
            setLista_tamanhoMax(listaSemaforo, ns);
            setLista_tamanhoMax(listaRadioBase, nr);

        }

	}
    //imprimirLista(listaHidrante, (void*)imprimirHidrante);
    //imprimirLista(listaForma, (void*)imprimirForma);
    /*
    char nomeArqSVG[64];
    strcpy(nomeArqSVG, nomeArquivoSVG);
    obterNomeArquivo(nomeArqSVG);
    adicionarExtensao(nomeArqSVG, "svg");

    FILE *SVG = abrirArquivo(dirSVG, nomeArqSVG, "w");
    if(SVG == NULL)
        exit(1);
    
    iniciarSVG(SVG);
    // Percorrer listas escrevendo no svg xD
    finalizarSVG(SVG);
    fclose(SVG);
    */
}








/*
void processarArquivoConsulta(char *nomeArquivoEntrada, char *dirSaida, char *dirArquivoConsulta, char *nomeArquivoConsulta, ArvoreBin *raiz) {
    if(nomeArquivoConsulta == NULL) 
        return;
    
    FILE *consulta = abrirArquivo( dirArquivoConsulta, nomeArquivoConsulta, "r" );
    if(consulta == NULL)
        exit(1);

    char nomeArquivoEntradaSemExtensao[64], nomeArquivoConsultaSemExtensao[64];
    strcpy(nomeArquivoEntradaSemExtensao, nomeArquivoEntrada);
    strcpy(nomeArquivoConsultaSemExtensao, nomeArquivoConsulta);

    obterNomeArquivo(nomeArquivoEntradaSemExtensao);
    obterNomeArquivo(nomeArquivoConsultaSemExtensao);

    char nomeEntradaConsultaSemExtensao[128];
    concatenarNomes(nomeArquivoEntradaSemExtensao, nomeArquivoConsultaSemExtensao, nomeEntradaConsultaSemExtensao);

    adicionarExtensao(nomeEntradaConsultaSemExtensao, "txt");
    FILE *arquivoTXT = abrirArquivo(dirSaida, nomeEntradaConsultaSemExtensao, "w");

    adicionarExtensao(nomeEntradaConsultaSemExtensao, "svg");
    FILE *arquivoSVG = abrirArquivo(dirSaida, nomeEntradaConsultaSemExtensao, "w");
    if(arquivoTXT == NULL || arquivoSVG == NULL)
        exit(1);

    iniciarSVG(arquivoSVG);
    escreverArvoreSVG(*raiz, arquivoSVG);
    char str[150], instrucao[10];
    while(true) {
        fgets(str, sizeof(str), consulta);
        sscanf(str, "%s", instrucao);
		if(feof(consulta))
			break;

        if(strcmp(instrucao, "o?") == 0) {
            fprintf(arquivoTXT, "%s", str);
            int j, k;
            sscanf(str, "%*s %d %d", &j, &k);

            Forma *forma1 = encontrarForma(raiz, j);
            Forma *forma2 = encontrarForma(raiz, k);
            if(forma1 == NULL || forma2 == NULL) {
                printf("ID %d/%d não encontrado.\n",j,k );
                exit(1);
            }

            if(formasColidem(forma1, forma2)) {
                fprintf(arquivoTXT, "SIM\n\n");
                retanguloDelimitador(arquivoSVG, forma1, forma2, true);
            } else {
                fprintf(arquivoTXT, "NAO\n\n");
                retanguloDelimitador(arquivoSVG, forma1, forma2, false);
            }
            
        } else if(strcmp(instrucao, "i?") == 0) {
            fprintf(arquivoTXT, "%s", str);
            int j;
            double x, y;
            sscanf(str, "%*s %d %lf %lf", &j, &x, &y);

            Forma *forma = encontrarForma(raiz, j);
            if(forma == NULL) {
                printf("ID %d não encontrado.\n",j);
                exit(1);
            }

            if(pontoInternoForma(x, y, forma)) {
                fprintf(arquivoTXT, "INTERNO\n\n");
                escreverPontoInterno(arquivoSVG, forma, x, y, true);
            } else {
                fprintf(arquivoTXT, "NAO INTERNO\n\n");
                escreverPontoInterno(arquivoSVG, forma, x, y, false);
            }

        } else if (strcmp(instrucao, "d?") == 0) {
            fprintf(arquivoTXT, "%s", str);
            int j, k;
            sscanf(str, "%*s %d %d", &j, &k);
            
            Forma *forma1 = encontrarForma(raiz, j);
            Forma *forma2 = encontrarForma(raiz, k);
            if(forma1 == NULL || forma2 == NULL) {
                printf("ID %d/%d não encontrado.\n",j,k );
                exit(1);
            }

            double dist = distanciaCentro(forma1, forma2);
            fprintf(arquivoTXT, "%lf\n\n", dist);
            retaCentrosMassa(arquivoSVG, forma1, forma2);
            distanciaCentrosMassa(arquivoSVG, forma1, forma2, dist);
            
        } else if(strcmp(instrucao, "bb") == 0) {
            char sufixo[64], cor[64];
            sscanf(str, "%*s %s %s", sufixo, cor);

            char nomeEntradaConsultaSufixo[256];
            obterSemExtensao(nomeEntradaConsultaSemExtensao);
            concatenarNomes(nomeEntradaConsultaSemExtensao, sufixo, nomeEntradaConsultaSufixo );
            adicionarExtensao(nomeEntradaConsultaSufixo, "svg");
            
            FILE *bbSVG = abrirArquivo( dirSaida, nomeEntradaConsultaSufixo, "w");
            if(bbSVG == NULL)
                exit(1);

            iniciarSVG(bbSVG);

            escreverFormasEnvoltas(bbSVG, *raiz, cor);

            finalizarSVG(bbSVG);
            fclose(bbSVG);
        }
    }
    
    finalizarSVG(arquivoSVG);
    fclose(consulta);
    fclose(arquivoTXT);
    fclose(arquivoSVG);
}
*/


void desalocarArgumentos(char *dirEntrada, char *nomeArquivoEntrada, char *nomeArquivoConsulta, char *dirSaida) {
    if(dirEntrada)
        free(dirEntrada);
    if(nomeArquivoEntrada)
        free(nomeArquivoEntrada);
    if(nomeArquivoConsulta)
        free(nomeArquivoConsulta);
    if(dirSaida)
        free(dirSaida);
}