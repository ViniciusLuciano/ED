#include "utils.h"

double clamp(double valor, double a, double b) {
    double clmp = valor < a ? a : valor;
    clmp = valor > b ? b : clmp;
    return clmp;
}

FILE* abrirArquivo(char *diretorio, char *nomeArquivo, char *modoAbertura) {
    char dirFinal[128];
    tratarDiretorio(diretorio, nomeArquivo, dirFinal);
    FILE* arq = fopen(dirFinal, modoAbertura);
    if(arq == NULL)
        printf("Falha na inicialização do arquivo %s\n", dirFinal);
    return arq;
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

void obterSemExtensao(char *arquivo) {
    for(int i = strlen(arquivo)-1; i > 0; i--) {
        if(arquivo[i] == '.') {
            //strncpy(final, arquivo, i);
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

void processarArquivoEntrada(FILE *entrada, char *dirSVG, char *nomeArquivoSVG, ArvoreBin *raiz) {

    char str[150], instrucao[10];
    int idText = -1; // Adicionar os textos na arvore

    char nomeArqSVG[64];
    strcpy(nomeArqSVG, nomeArquivoSVG);
    obterNomeArquivo(nomeArqSVG);

    adicionarExtensao(nomeArqSVG, "svg");
    FILE *SVG = abrirArquivo(dirSVG, nomeArqSVG, "w");
    if(SVG == NULL)
        exit(1);
    

    iniciarSVG(SVG);
	while(true) {
		fgets(str, sizeof(str), entrada);
        sscanf(str, "%s", instrucao);
		if(feof(entrada))
			break;

		if(strcmp(instrucao, "c") == 0){
            Forma *forma = (Forma*)malloc(sizeof(Forma));
            forma->nomeForma = CIRCULO;
            forma->tipoForma = (Circulo*)malloc(sizeof(Circulo));
            Circulo *circ = ((Circulo*) forma->tipoForma);

            char bufferCorD[50], bufferCorB[50];
			sscanf(str, "%*c %d %lf %lf %lf %s %s", &forma->id, &circ->raio, &forma->x, &forma->y, bufferCorB, bufferCorD);

            forma->corB = malloc(strlen(bufferCorB)*sizeof(char));
            forma->corD = malloc(strlen(bufferCorD)*sizeof(char));
            strcpy(forma->corB, bufferCorB);
            strcpy(forma->corD, bufferCorD);

            escreverCirculo(SVG, forma);
            adicionarElemento(raiz, forma); // Adicionar elemento na arvore

		} else if(strcmp(instrucao, "r") == 0){
            Forma *forma = (Forma*)malloc(sizeof(Forma));
            forma->nomeForma = RETANGULO;
            forma->tipoForma = (Retangulo*)malloc(sizeof(Retangulo));
            Retangulo *ret = ((Retangulo*) forma->tipoForma);

            char bufferCorD[50], bufferCorB[50];
			sscanf(str, "%*c %d %lf %lf %lf %lf %s %s", &forma->id, &ret->w, &ret->h, &forma->x, &forma->y, bufferCorB, bufferCorD);
            
            forma->corB = malloc(strlen(bufferCorB)*sizeof(char));
            forma->corD = malloc(strlen(bufferCorD)*sizeof(char));
            strcpy(forma->corB, bufferCorB);
            strcpy(forma->corD, bufferCorD);

            escreverRetangulo(SVG, forma);
            adicionarElemento(raiz, forma); // Adicionar elemento na arvore
		} else if(strcmp(instrucao, "t") == 0) {
            Forma *forma = (Forma*)malloc(sizeof(Forma));
            forma->nomeForma = TEXTO;
            forma->tipoForma = (Texto*)malloc(sizeof(Texto));
            Texto *text = ((Texto*) forma->tipoForma);
    
            char bufferTexto[256];
            sscanf(str, "%*c %lf %lf %256[^\n]", &forma->x, &forma->y, bufferTexto);

            text->texto = malloc(strlen(bufferTexto)*sizeof(char));
            strcpy(text->texto, bufferTexto);
            forma->id = idText;
            idText--;

            escreverTexto(SVG, forma);
            adicionarElemento(raiz, forma);
		}

	}
    
    finalizarSVG(SVG);
    fclose(SVG);
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