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

char* tratarDiretorio(char *diretorio, char *nomeArquivo) {

    int num = strlen(diretorio)+strlen(nomeArquivo) + 2;
    char *diretorioFinal;

	if(diretorio[strlen(diretorio) - 1] == '/') {
		diretorioFinal = malloc(num*sizeof(char));
		sprintf(diretorio, "%s%s", diretorio, nomeArquivo);
	} else {
		diretorioFinal = malloc(num*sizeof(char));
		sprintf(diretorio, "%s/%s", diretorio, nomeArquivo);
	}

	return diretorio;
}

void escreverSVG(FILE* SVG, char *dado) {
    fprintf(SVG, dado);
    free(dado);
}

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
	int i = 0;
    FILE *SVG = abrirSVG(dirSVG, obterSemExtensao(nomeArquivoSVG));
    escreverSVG(SVG, iniciarSVG("100", "200")); // ver como proceder com width e height
	while(1) {
		fgets(str, sizeof(str), entrada);
		if(feof(entrada))
			break;

		if(str[0] == 'c'){
            Forma *forma = (Forma*)malloc(sizeof(Forma));

            forma->tipoForma = (Circulo*)malloc(sizeof(Circulo));
            Circulo *circ = ((Circulo*) forma->tipoForma);

			sscanf(str, "%c %d %lf %lf %lf %s %s", &forma->nome, &forma->id, &circ->raio, &forma->x, &forma->y, forma->corD, forma->corB);
			escreverSVG(SVG, escreverCirculo(forma));
            adicionarElemento(raiz, forma); // Adicionar elemento na arvore
		} else if (str[0] == 'r'){
            Forma *forma = (Forma*)malloc(sizeof(Forma));

            forma->tipoForma = (Retangulo*)malloc(sizeof(Retangulo));
            Retangulo *ret = ((Retangulo*) forma->tipoForma);

			sscanf(str, "%c %d %lf %lf %lf %lf %s %s", &forma->nome, &forma->id, &ret->w, &ret->h, &forma->x, &forma->y, forma->corD, forma->corB);
            escreverSVG(SVG, escreverRetangulo(forma));
            adicionarElemento(raiz, forma); // Adicionar elemento na arvore
		} else {
            // AQUI VAI SER O TEXT
		}

		i++;
	}
    escreverSVG(SVG, finalizarSVG());
    fclose(SVG);
}