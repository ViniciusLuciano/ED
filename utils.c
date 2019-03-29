#include "utils.h"

double clamp(double valor, double a, double b) {
    double clmp = valor < a ? a : valor;
    clmp = valor > b ? b : clmp;
    return clmp;
}

FILE* abrirArquivo(char *diretorio) {
    FILE* arq = fopen(diretorio, "r");
    if(arq == NULL)
        perror("Falha na inicialização do arquivo");
    return arq;
}

bool lerArgumentos(int argc , char *argv[], char *dirEntrada[], char *nomeArquivoEntrada[], char *nomeArquivoConsulta[], char *dirSaida[]) {
    int dirEntradaIndex, nomeArquivoEntradaIndex, nomeArquivoConsultaIndex, dirSaidaIndex;
    for(int i = 1; i < argc; i++) {
        if(strcmp(argv[i], "-e") == 0) {
            if( i+1 >= argc ) {
                printf("'-e' requer um argumento\n");
                return false;
            }
			dirEntradaIndex=i+1;

            *dirEntrada = malloc(strlen(argv[dirEntradaIndex])*sizeof(char));   
            strcpy(*dirEntrada, argv[dirEntradaIndex]);

        } else if(strcmp(argv[i], "-f") == 0) {
            if( i+1 >= argc ) {
                printf("'-f' requer um argumento\n");
                return false;
            }
			nomeArquivoEntradaIndex=i+1;

            *nomeArquivoEntrada = malloc(strlen(argv[nomeArquivoEntradaIndex])*sizeof(char));
            strcpy(*nomeArquivoEntrada, argv[nomeArquivoEntradaIndex]);

        } else if(strcmp(argv[i], "-q") == 0) {
            if( i+1 >= argc ) {
                printf("'-q' requer um argumento\n");
                return false;
            }
			nomeArquivoConsultaIndex=i+1;

            *nomeArquivoConsulta = malloc(strlen(argv[nomeArquivoConsultaIndex])*sizeof(char));
            strcpy(*nomeArquivoConsulta, argv[nomeArquivoConsultaIndex]);

        } else if(strcmp(argv[i], "-o") == 0) {
            if( i+1 >= argc ) {
                printf("'-o' requer um argumento\n");
                return false;
            }
            dirSaidaIndex=i+1;

            *dirSaida = malloc(strlen(argv[dirSaidaIndex])*sizeof(char));
            strcpy(*dirSaida, argv[dirSaidaIndex]);
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

void obterSemExtensao(char *arquivo, char *final) {
    for(int i = strlen(arquivo); i > 0; i--) {
        if(arquivo[i] == '.') {
            strncpy(final, arquivo, i);
            final[i] = '\0';
        }
    }
}

FILE* abrirSVG(char *dir, char *nomeArquivo) {

    int num = strlen(dir) + strlen(nomeArquivo) + 4 + 2; //.svg / \0
    char *caminho = malloc(num*sizeof(char));
    if(dir[strlen(dir) - 1] == '/')
        sprintf(caminho, "%s%s.svg", dir, nomeArquivo);
    else
        sprintf(caminho, "%s/%s.svg", dir, nomeArquivo);

    FILE *SVG = fopen(caminho, "w");
    free(caminho);
    return SVG;
}

void processarArquivoEntrada(FILE *entrada, char *dirSVG, char *nomeArquivoSVG, ArvoreBin *raiz) {

    char str[150], instrucao[10];
    int idText = -1; // Adicionar os textos na arvore

    char *nomeArqSemExtensao = malloc(strlen(nomeArquivoSVG)*sizeof(char));
    obterSemExtensao(nomeArquivoSVG, nomeArqSemExtensao);
    FILE *SVG = abrirSVG(dirSVG, nomeArqSemExtensao);
    if(SVG == NULL) {
        printf("Falha no diretorio de saída\n");
        exit(1);
    }
    free(nomeArqSemExtensao);

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

void concatenarNomes(char *nome1, char *nome2, char *nomeSaida) {
    sprintf(nomeSaida, "%s-%s", nome1, nome2);
}

FILE *abrirTXT(char *dirSaida, char *nomeArquivo) {
    int num = strlen(dirSaida) + strlen(nomeArquivo) + 5; 
    char *caminho = malloc(num*sizeof(char));

    if(dirSaida[strlen(dirSaida) - 1] == '/')
        sprintf(caminho, "%s%s.txt", dirSaida, nomeArquivo);
    else
        sprintf(caminho, "%s/%s.txt", dirSaida, nomeArquivo);

    FILE *arqTXT = fopen(caminho, "w"); 
    if(arqTXT == NULL) {
        perror("Falha na abertura do arquivo de entrada.");
        exit(1);
    }

    free(caminho);
    return arqTXT;
}


void processarArquivoConsulta(char *nomeArquivoEntrada, char *dirSaida, char *dirArquivoConsulta, char *nomeArquivoConsulta, ArvoreBin *raiz) {
    if(nomeArquivoConsulta == NULL) 
        return;
    
    char dirFinalArqConsulta[64];
    tratarDiretorio(dirArquivoConsulta, nomeArquivoConsulta, dirFinalArqConsulta);
    FILE *consulta = abrirArquivo( dirFinalArqConsulta );

    char nomeArquivoEntradaSemExtensao[64];
    char nomeArquivoConsultaSemExtensao[64];
    obterSemExtensao(nomeArquivoEntrada, nomeArquivoEntradaSemExtensao);
    obterSemExtensao(nomeArquivoConsulta, nomeArquivoConsultaSemExtensao);

    char nomeEntradaConsultaSemExtensao[128];
    concatenarNomes(nomeArquivoEntradaSemExtensao, nomeArquivoConsultaSemExtensao, nomeEntradaConsultaSemExtensao);

    FILE *arquivoTXT = abrirTXT(dirSaida, nomeEntradaConsultaSemExtensao);
    FILE *arquivoSVG = abrirSVG(dirSaida, nomeEntradaConsultaSemExtensao);

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
            if(pontoInternoForma(x, y, forma)) {
                fprintf(arquivoTXT, "SIM\n\n");
                escreverPontoInterno(arquivoSVG, forma, x, y, true);
            } else {
                fprintf(arquivoTXT, "NAO\n\n");
                escreverPontoInterno(arquivoSVG, forma, x, y, false);
            }

        } else if (strcmp(instrucao, "d?") == 0) {
            fprintf(arquivoTXT, "%s", str);
            int j, k;
            sscanf(str, "%*s %d %d", &j, &k);
            
            Forma *forma1 = encontrarForma(raiz, j);
            Forma *forma2 = encontrarForma(raiz, k);

            double dist = distanciaCentro(forma1, forma2);
            fprintf(arquivoTXT, "%lf\n\n", dist);
            retaCentrosMassa(arquivoSVG, forma1, forma2);
            distanciaCentrosMassa(arquivoSVG, forma1, forma2, dist);
            
        } else if(strcmp(instrucao, "bb") == 0) {
            char buffer[20], cor[20];
            sscanf(str, "%*s %s %s", buffer, cor);
            char *sufixo = malloc(strlen(buffer)*sizeof(char));
            strcpy(sufixo, buffer);

            char nomeArqEntradaSemExtensao[64], nomeArqConsultaSemExtensao[64];
            obterSemExtensao(nomeArquivoEntrada, nomeArqEntradaSemExtensao);
            obterSemExtensao(nomeArquivoConsulta, nomeArqConsultaSemExtensao);

            char nomeEntradaConsulta[128], nomeEntradaConsultaSufixo[256];
            concatenarNomes(nomeArqEntradaSemExtensao, nomeArqConsultaSemExtensao, nomeEntradaConsulta);
            concatenarNomes(nomeEntradaConsulta, sufixo, nomeEntradaConsultaSufixo);

            FILE *bbSVG = abrirSVG( dirSaida, nomeEntradaConsultaSufixo);
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