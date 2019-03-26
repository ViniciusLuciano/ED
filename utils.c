#include "utils.h"

double clamp(double valor, double a, double b) {
    double xd = valor < a ? a : valor;
    xd = valor > b ? b : valor;
    return xd;
}

FILE* abrirArquivo(char *diretorio) {
    FILE* arq = fopen(diretorio, "r");
    free(diretorio);
    if(arq == NULL) {
        perror("Falha na inicialização do arquivo");
        exit(1);
    } else {
        return arq;
    }
}

void lerArgumentos(int argc , char *argv[], char *dirEntrada[], char *nomeArquivoEntrada[], char *nomeArquivoConsulta[], char *dirSaida[]) {
    int dirEntradaIndex, nomeArquivoEntradaIndex, nomeArquivoConsultaIndex, dirSaidaIndex;
    for(int i = 1; i < argc; i++) {
        if(strcmp(argv[i], "-e") == 0) {
            if( i+1 >= argc ) {
                printf("'-e' requer um argumento\n");
                exit(1);
            }
			dirEntradaIndex=i+1;

        } else if(strcmp(argv[i], "-f") == 0) {
            if( i+1 >= argc ) {
                printf("'-f' requer um argumento\n");
                exit(1);
            }
			nomeArquivoEntradaIndex=i+1;

        } else if(strcmp(argv[i], "-q") == 0) {
            if( i+1 >= argc ) {
                printf("'-q' requer um argumento\n");
                exit(1);
            }
			nomeArquivoConsultaIndex=i+1;

        } else if(strcmp(argv[i], "-o") == 0) {
            if( i+1 >= argc ) {
                printf("'-o' requer um argumento\n");
                exit(1);
            }

            dirSaidaIndex=i+1;
        }
    }

    *dirEntrada = malloc(strlen(argv[dirEntradaIndex])*sizeof(char));
    strcpy(*dirEntrada, argv[dirEntradaIndex]);

    *nomeArquivoEntrada = malloc(strlen(argv[nomeArquivoEntradaIndex])*sizeof(char));
    strcpy(*nomeArquivoEntrada, argv[nomeArquivoEntradaIndex]);

    *nomeArquivoConsulta = malloc(strlen(argv[nomeArquivoConsultaIndex])*sizeof(char));
    strcpy(*nomeArquivoConsulta, argv[nomeArquivoConsultaIndex]);

    *dirSaida = malloc(strlen(argv[dirSaidaIndex])*sizeof(char));
    strcpy(*dirSaida, argv[dirSaidaIndex]);
}

//Precisa dar free
char* tratarDiretorio(char *diretorio, char *nomeArquivo) {

    if(diretorio == NULL) {
        int num = strlen(nomeArquivo) + 1;
        char *diretorioFinal = malloc(num*sizeof(char)); // Pra dar free na funçao que recebe
        strcpy(diretorioFinal, nomeArquivo);
        return diretorioFinal;
    }

    int num = strlen(diretorio)+strlen(nomeArquivo) + 2;
    char *diretorioFinal = malloc(num*sizeof(char));

	if(diretorio[strlen(diretorio) - 1] == '/') {
		sprintf(diretorioFinal, "%s%s", diretorio, nomeArquivo);
	} else {
		sprintf(diretorioFinal, "%s/%s", diretorio, nomeArquivo);
	}

	return diretorioFinal;
}


// Precisa dar free - TROCAR COMO TA FUNCIONANDO
char *obterSemExtensao(char *arquivo) {
   	char *final = malloc((strlen(arquivo) - 4)*sizeof(char));
   	strncpy(final, arquivo, strlen(arquivo) - 4);
    return final;
}

FILE* abrirSVG(char *dir, char *nomeArquivo) {
    int num = strlen(dir) + strlen(nomeArquivo) + 4 + 2; //.svg / \0
    char *caminho = malloc(num*sizeof(char));
    
    if(dir[strlen(dir) - 1] == '/')
        sprintf(caminho, "%s%s.svg", dir, nomeArquivo);
    else
        sprintf(caminho, "%s/%s.svg", dir, nomeArquivo);

    free(nomeArquivo);
    FILE *SVG = fopen(caminho, "w");
    return SVG;
}

void processarArquivoEntrada(FILE *entrada, char *dirSVG, char *nomeArquivoSVG, ArvoreBin *raiz) {

    char str[150];
    FILE *SVG = abrirSVG(dirSVG, obterSemExtensao(nomeArquivoSVG));
    iniciarSVG(SVG, "100", "200"); // ver como proceder com width e height
	while(true) {
		fgets(str, sizeof(str), entrada);
		if(feof(entrada))
			break;

		if(str[0] == 'c'){
            Forma *forma = (Forma*)malloc(sizeof(Forma));

            forma->tipoForma = (Circulo*)malloc(sizeof(Circulo));
            Circulo *circ = ((Circulo*) forma->tipoForma);

			sscanf(str, "%c %d %lf %lf %lf %s %s", &forma->nome, &forma->id, &circ->raio, &forma->x, &forma->y, forma->corD, forma->corB);
            escreverCirculo(SVG, forma);
            adicionarElemento(raiz, forma); // Adicionar elemento na arvore
		} else if (str[0] == 'r'){
            Forma *forma = (Forma*)malloc(sizeof(Forma));

            forma->tipoForma = (Retangulo*)malloc(sizeof(Retangulo));
            Retangulo *ret = ((Retangulo*) forma->tipoForma);

			sscanf(str, "%c %d %lf %lf %lf %lf %s %s", &forma->nome, &forma->id, &ret->w, &ret->h, &forma->x, &forma->y, forma->corD, forma->corB);
            escreverRetangulo(SVG, forma);
            adicionarElemento(raiz, forma); // Adicionar elemento na arvore
		} else {
            // AQUI VAI SER O TEXT
		}

	}
    finalizarSVG(SVG);
    fclose(SVG);
}

//Recebr sem extensao ja
//Precisa dar free
char *concatenarNomes(char *nome1, char *nome2) {
    int num = strlen(nome1) + strlen(nome2) + 2;
    char *final = malloc(num*sizeof(char));
    sprintf(final, "%s-%s", nome1, nome2);
    free(nome1);
    free(nome2);
    return final;
}

FILE *abrirTXT(char *dirSaida, char *nomeArquivo) {
    int num = strlen(dirSaida) + strlen(nomeArquivo) + 5; //.txt
    char *caminho = malloc(num*sizeof(char));

    if(dirSaida[strlen(dirSaida) - 1] == '/')
        sprintf(caminho, "%s%s.txt", dirSaida, nomeArquivo);
    else
        sprintf(caminho, "%s/%s.txt", dirSaida, nomeArquivo);

    FILE *arqTXT = fopen(caminho, "w"); // Ta dando seg fault
    if(arqTXT == NULL) {
        perror("Falha na abertura do arquivo TXT");
        exit(1);
    }

    free(nomeArquivo);
    return arqTXT;
}

void processarArquivoConsulta(char *nomeArquivoEntrada, char *dirSaida, char *dirArquivoConsulta, char *nomeArquivoConsulta, ArvoreBin *raiz) {
    if(nomeArquivoConsulta == NULL)
        return;
    
    FILE *consulta = abrirArquivo( tratarDiretorio(dirArquivoConsulta, nomeArquivoConsulta) );
    FILE *arquivoTXT = abrirTXT(dirSaida, concatenarNomes(obterSemExtensao(nomeArquivoEntrada), obterSemExtensao(nomeArquivoConsulta)));
    // abrirSVG()

    char str[150];
    while(true) {
        fgets(str, sizeof(str), consulta);

		if(feof(consulta))
			break;

        if(str[0] == 'o') {
            fprintf(arquivoTXT, str);
            int j, k;
            sscanf(str, "%*s %d %d", &j, &k);

            Forma *forma1 = encontrarForma(raiz, j);
            Forma *forma2 = encontrarForma(raiz, k);
            if(formasColidem(forma1, forma2))
                fprintf(arquivoTXT, "SIM\n\n");
            else
                fprintf(arquivoTXT, "NAO\n\n");

        } else if(str[0] == 'i') {
            fprintf(arquivoTXT, str);
            int j;
            double x, y;
            sscanf(str, "%*s %d %lf %lf", &j, &x, &y);

            Forma *forma = encontrarForma(raiz, j);
            if(pontoInternoForma(x, y, forma))
                fprintf(arquivoTXT, "SIM\n\n");
            else
                fprintf(arquivoTXT, "NAO\n\n");

        } else if (str[0] == 'd') {
            fprintf(arquivoTXT, str);
            int j, k;
            sscanf(str, "%*s %d %d", &j, &k);
            
            Forma *forma1 = encontrarForma(raiz, j);
            Forma *forma2 = encontrarForma(raiz, k);
            fprintf(arquivoTXT, "%lf\n\n", distanciaCentro(forma1, forma2));
            
        } else if(str[0] == 'b') {
            // Fazer dps
        }
    }

    fclose(consulta);
    fclose(arquivoTXT);
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