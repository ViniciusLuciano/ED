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

bool processarArquivoEntrada(FILE *entrada, char *dirSVG, char *nomeArquivoSVG, Cidade *cidade) {

    char str[150], instrucao[10];
    bool primeiraLinha = true;
    
    // Parametros padrao, sem estar setado no .geo
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
        
        if(primeiraLinha) {

            int i, nq, nh, ns, nr, np, nm;
            if(strcmp(instrucao, "nx") == 0) {
                sscanf(str, "%*s %d %d %d %d %d %d %d", &i, &nq, &nh, &ns, &nr, &np, &nm);
            } else {
                i = 1000; nq = 1000; nh = 1000; ns = 1000; nr = 1000; np = 1000; nm = 1000;
            }
            *cidade = criarCidade(i, nq, nh, ns, nr, np, nm);
            primeiraLinha = false;

		}
        
        if(strcmp(instrucao, "c") == 0){

            char cfill[50], cstrok[50], id[20], bufferCW[20];
            double r, x, y;

            sprintf(bufferCW, "%s", cw);

			sscanf(str, "%*s %s %lf %lf %lf %s %s", id, &r, &x, &y, cstrok, cfill);
            Circulo c = criarCirculo(x, y, r, cfill, cstrok, bufferCW);
            Forma f = criarForma(id, CIRCULO, c);
            Cidade_setForma(*cidade, f);
        
		} else if(strcmp(instrucao, "r") == 0){

            char cfill[50], cstrok[50], id[50], bufferRW[20];
            double w, h, x, y;

            sprintf(bufferRW, "%s", rw);

			sscanf(str, "%*s %s %lf %lf %lf %lf %s %s", id, &w, &h, &x, &y, cstrok, cfill);
            Retangulo r = criarRetangulo(x, y, w, h, cfill, cstrok, bufferRW);
            Forma f = criarForma(id, RETANGULO, r);
            Cidade_setForma(*cidade, f);
		} else if(strcmp(instrucao, "t") == 0) {
    
            char bufferTexto[256];
            double x, y;
            sscanf(str, "%*s %lf %lf %256[^\n]", &x, &y, bufferTexto);
            Texto t = criarTexto(x, y, bufferTexto);
            Cidade_setTexto(*cidade, t);
            
		} else if(strcmp(instrucao, "q") == 0) {

            char cep[30], bufferCfill[50], bufferCstrok[50], bufferSW[20];
            double x, y, w, h;

            sprintf(bufferCfill,"%s", cqfill);
            sprintf(bufferCstrok,"%s", cqstrok);
            sprintf(bufferSW,"%s", sqw);

            sscanf(str, "%*s %s %lf %lf %lf %lf", cep, &x, &y, &w, &h);
            Quadra q = criarQuadra(cep, x, y, w, h, bufferCfill, bufferCstrok, bufferSW);
            Cidade_setQuadra(*cidade, q);

        } else if(strcmp(instrucao, "h") == 0) {

            char id[30], bufferCfill[50], bufferCstrok[50], bufferSW[20];
            double x, y;

            sprintf(bufferCfill,"%s", chfill);
            sprintf(bufferCstrok,"%s", chstrok);
            sprintf(bufferSW,"%s", shw);

            sscanf(str, "%*s %s %lf %lf", id, &x, &y);
            Hidrante h = criarHidrante(id, x, y, bufferCfill, bufferCstrok, bufferSW);
            Cidade_setHidrante(*cidade, h);

        } else if(strcmp(instrucao, "s") == 0) {

            char id[30], bufferCfill[50], bufferCstrok[50], bufferSW[20];
            double x, y;

            sprintf(bufferCfill,"%s", csfill);
            sprintf(bufferCstrok,"%s", csstrok);
            sprintf(bufferSW,"%s", ssw);

            sscanf(str, "%*s %s %lf %lf", id, &x, &y);
            Semaforo s = criarSemaforo(id, x, y, bufferCfill, bufferCstrok, bufferSW);
            Cidade_setSemaforo(*cidade, s);

        } else if(strcmp(instrucao, "rb") == 0) {

            char id[30], bufferCfill[50], bufferCstrok[50], bufferSW[20];
            double x, y;

            sprintf(bufferCfill,"%s", crfill);
            sprintf(bufferCstrok,"%s", crstrok);
            sprintf(bufferSW,"%s", srw);

            sscanf(str, "%*s %s %lf %lf", id, &x, &y);
            RadioBase rb = criarRadioBase(id, x, y, bufferCfill, bufferCstrok, bufferSW);
            Cidade_setRadioBase(*cidade, rb);

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

        } else if(strcmp(instrucao, "prd") == 0) {

            char cep[30], face;
            double num, f, p, mrg;

            sscanf(str, "%*s %s %c %lf %lf %lf %lf", cep, &face, &num, &f, &p, &mrg);
            Predio prd = criarPredio(cep, face, num, f, p, mrg);
            Cidade_setPredio(*cidade, prd);

        } else if(strcmp(instrucao, "mur") == 0) {

            double x1, y1, x2, y2;

            sscanf(str, "%*s %lf %lf %lf %lf", &x1, &y1, &x2, &y2);
            Muro m = criarMuro(x1, y1, x2, y2);
            Cidade_setMuro(*cidade, m);
        }
	}
    
    
    char nomeArqSVG[64];
    strcpy(nomeArqSVG, nomeArquivoSVG);
    obterNomeArquivo(nomeArqSVG);
    adicionarExtensao(nomeArqSVG, "svg");

    FILE *arquivoSVG = abrirArquivo(dirSVG, nomeArqSVG, "w");
    if(arquivoSVG == NULL)
        return false;
    
    svg_iniciar(arquivoSVG);
    Cidade_escreverSvg(*cidade, arquivoSVG);
    svg_finalizar(arquivoSVG);
    fclose(arquivoSVG);
}



bool processarArquivoConsulta(FILE* arquivoConsulta, char *nomeArquivoEntrada, char *dirSaida, char *nomeArquivoConsulta, Cidade *cidade) {
    
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
        return false;

    svg_iniciar(arquivoSVG);
    char str[150], instrucao[10];
    while(true) {
        
        fgets(str, sizeof(str), arquivoConsulta);
        sscanf(str, "%s", instrucao);
		if(feof(arquivoConsulta))
			break;

        if(strcmp(instrucao, "o?") == 0) {
            fprintf(arquivoTXT, "\t%s", str);
            char j[20], k[20];
            sscanf(str, "%*s %s %s", j, k);

            Forma forma1 = Cidade_getForma(*cidade, j);
            Forma forma2 = Cidade_getForma(*cidade, k);
            if(forma1 == NULL || forma2 == NULL) {
                printf("ID %s/%s não encontrado.\n", j, k);
                return false;
            }

            if(formasColidem(forma1, forma2)) {
                fprintf(arquivoTXT, "SIM\n\n");
                svg_escreverRetanguloDelimitador(arquivoSVG, forma1, forma2, true);
            } else {
                fprintf(arquivoTXT, "NAO\n\n");
                svg_escreverRetanguloDelimitador(arquivoSVG, forma1, forma2, false);
            }
            
        } else if(strcmp(instrucao, "i?") == 0) {
            fprintf(arquivoTXT, "\t%s", str);
            char j[20];
            double x, y;
            sscanf(str, "%*s %s %lf %lf", j, &x, &y);

            Forma forma = Cidade_getForma(*cidade, j);
            if(forma == NULL) {
                printf("ID %s não encontrado.\n",j);
                return false;
            }

            if(pontoInternoForma(x, y, forma)) {
                fprintf(arquivoTXT, "INTERNO\n\n");
                svg_escreverPontoInterno(arquivoSVG, forma, x, y, true);
            } else {
                fprintf(arquivoTXT, "NAO INTERNO\n\n");
                svg_escreverPontoInterno(arquivoSVG, forma, x, y, false);
            }

        } else if (strcmp(instrucao, "d?") == 0) {
            fprintf(arquivoTXT, "\t%s", str);
            char j[20], k[20];
            sscanf(str, "%*s %s %s", j, k);
            
            Forma forma1 = Cidade_getForma(*cidade, j);
            Forma forma2 = Cidade_getForma(*cidade, k);
            if(forma1 == NULL || forma2 == NULL) {
                printf("ID %s/%s não encontrado.\n",j,k );
                return false;
            }

            double dist = distanciaL2Centro(forma1, forma2);
            fprintf(arquivoTXT, "%lf\n\n", dist);
            svg_escreverRetaCentrosMassa(arquivoSVG, forma1, forma2);
            svg_escreverDistanciaCentrosMassa(arquivoSVG, forma1, forma2, dist);
            
        } else if(strcmp(instrucao, "bb") == 0) {

            char sufixo[64], cor[64];
            sscanf(str, "%*s %s %s", sufixo, cor);

            char nomeEntradaConsultaSufixo[256];
            obterSemExtensao(nomeEntradaConsultaSemExtensao);
            concatenarNomes(nomeEntradaConsultaSemExtensao, sufixo, nomeEntradaConsultaSufixo );
            adicionarExtensao(nomeEntradaConsultaSufixo, "svg");
            
            FILE *bbSVG = abrirArquivo( dirSaida, nomeEntradaConsultaSufixo, "w");
            if(bbSVG == NULL)
                return false;

            svg_iniciar(bbSVG);
            Cidade_escreverFormasEnvoltas(*cidade, bbSVG, cor);
            svg_finalizar(bbSVG);
            fclose(bbSVG);

        } else if(strcmp(instrucao, "dq") == 0) {
            fprintf(arquivoTXT, "\t%s", str);

            char metrica[5], id[20];
            double dist;
            sscanf(str, "%*s %s %s %lf", metrica, id, &dist);

            Hidrante h;
            RadioBase rb;
            Semaforo s;
            double px, py;
         
            if((h = Cidade_getHidrante(*cidade, id)) != NULL) {
                px = Hidrante_get_x(h);
                py = Hidrante_get_y(h);
                
                // Anel grosso de duas cores
                Circulo c1 = criarCirculo(px, py, 7, "none", "orange", "3px");
                Circulo_escreverSvg(c1, arquivoSVG);
                destruirCirculo(c1);

		        Circulo c2 = criarCirculo(px, py, 9, "none", "gold", "3px");
                Circulo_escreverSvg(c2, arquivoSVG);
                destruirCirculo(c2);

                fprintf(arquivoTXT, "ID: %s\nEquipamento: Hidrante\n", id);
                Cidade_removerQuadrasInternasEquipamento(*cidade, px, py, dist, metrica, arquivoTXT);
            } else if((rb = Cidade_getRadioBase(*cidade, id)) != NULL) {
                px = RadioBase_get_x(rb);
                py = RadioBase_get_y(rb);

                Circulo c1 = criarCirculo(px, py, 7, "none", "orange", "3px");
                Circulo_escreverSvg(c1, arquivoSVG);
                destruirCirculo(c1);

		        Circulo c2 = criarCirculo(px, py, 9, "none", "gold", "3px");
                Circulo_escreverSvg(c2, arquivoSVG);
                destruirCirculo(c2);

                fprintf(arquivoTXT, "ID: %s\nEquipamento: Radio Base\n", id);
                Cidade_removerQuadrasInternasEquipamento(*cidade, px, py, dist, metrica, arquivoTXT);
            } else if((s = Cidade_getSemaforo(*cidade, id)) != NULL) {
                px = Semaforo_get_x(s);
                py = Semaforo_get_y(s);

                Circulo c1 = criarCirculo(px, py, 7, "none", "orange", "3px");
                Circulo_escreverSvg(c1, arquivoSVG);
                destruirCirculo(c1);

		        Circulo c2 = criarCirculo(px, py, 9, "none", "gold", "3px");
                Circulo_escreverSvg(c2, arquivoSVG);
                destruirCirculo(c2);

                fprintf(arquivoTXT, "ID: %s\nEquipamento: Semaforo\n", id);
                Cidade_removerQuadrasInternasEquipamento(*cidade, px, py, dist, metrica, arquivoTXT);
            } else {
                fprintf(arquivoTXT, "%s não encontrado.\n", id);
            }

        } else if(strcmp(instrucao, "del") == 0) {
            fprintf(arquivoTXT, "\t%s", str);

            char id[20];
            sscanf(str, "%*s %s", id);

            Hidrante h;
            RadioBase rb;
            Semaforo s;
            Quadra q;
            
            if((h = Cidade_getHidrante(*cidade, id)) != NULL) {
                fprintf(arquivoTXT, "REMOVIDO\nID: %s\nEquipamento: Hidrante\nCoordenada: (%.2lf, %.2lf)\n\n",
                    id,
                    Hidrante_get_x(h),
                    Hidrante_get_y(h)
                );
                Cidade_removerObjeto(*cidade, id);
            } else if((rb = Cidade_getRadioBase(*cidade, id)) != NULL) {
                fprintf(arquivoTXT, "REMOVIDO\nID: %s\nEquipamento: Radio Base\nCoordenada: (%.2lf, %.2lf)\n\n",
                    id,
                    RadioBase_get_x(rb),
                    RadioBase_get_y(rb)
                );
                Cidade_removerObjeto(*cidade, id);
            } else if((s = Cidade_getSemaforo(*cidade, id)) != NULL) {
                fprintf(arquivoTXT, "REMOVIDO\nID: %s\nEquipamento: Semaforo\nCoordenada: (%.2lf, %.2lf)\n\n",
                    id,
                    Semaforo_get_x(s),
                    Semaforo_get_y(s)
                );
                Cidade_removerObjeto(*cidade, id);
            } else if((q = Cidade_getQuadra(*cidade, id)) != NULL) {
                fprintf(arquivoTXT, "REMOVIDO\nCEP: %s\nEquipamento: Quadra\nCoordenada: (%.2lf, %.2lf)\n\n",
                    id,
                    Quadra_get_x(q),
                    Quadra_get_y(q)
                );
                Cidade_removerObjeto(*cidade, id);
            } else {
                fprintf(arquivoTXT, "%s não encontrado.\n", id);
            }
            
        } else if(strcmp(instrucao, "cbq") == 0) {
            fprintf(arquivoTXT, "\t%s", str);
            
            char cstrk[20];
            double x, y, r;
            sscanf(str, "%*s %lf %lf %lf %s", &x, &y, &r, cstrk);
            Circulo c = criarCirculo(x, y, r, "", "", "");
            Cidade_setCstrkQuadrasInternasCirculo(*cidade, c, cstrk, arquivoTXT);
            destruirCirculo(c);

        } else if(strcmp(instrucao, "crd?") == 0) {
            fprintf(arquivoTXT, "\t%s", str);
            // id/cep
            
            char id[20];
            sscanf(str, "%*s %s", id);

            Hidrante h;
            RadioBase rb;
            Semaforo s;
            Quadra q;
            
            if((h = Cidade_getHidrante(*cidade, id)) != NULL) {
                fprintf(arquivoTXT, "ID: %s\nEquipamento: Hidrante\nCoordenada: (%.2lf, %.2lf)\n\n",
                    id,
                    Hidrante_get_x(h),
                    Hidrante_get_y(h)
                );
            } else if((rb = Cidade_getRadioBase(*cidade, id)) != NULL) {
                fprintf(arquivoTXT, "ID: %s\nEquipamento: Radio Base\nCoordenada: (%.2lf, %.2lf)\n\n",
                    id,
                    RadioBase_get_x(rb),
                    RadioBase_get_y(rb)
                );
            } else if((s = Cidade_getSemaforo(*cidade, id)) != NULL) {
                fprintf(arquivoTXT, "ID: %s\nEquipamento: Semaforo\nCoordenada: (%.2lf, %.2lf)\n\n",
                    id,
                    Semaforo_get_x(s),
                    Semaforo_get_y(s)
                );
            } else if((q = Cidade_getQuadra(*cidade, id)) != NULL) {
                fprintf(arquivoTXT, "CEP: %s\nEquipamento: Quadra\nCoordenada: (%.2lf, %.2lf)\n\n",
                    id,
                    Quadra_get_x(q),
                    Quadra_get_y(q)
                );
            } else {
                fprintf(arquivoTXT, "%s não encontrado.\n", id);
            }
            

        } else if(strcmp(instrucao, "trns") == 0) {

            fprintf(arquivoTXT, "\t%s", str);

            double x, y, w, h, dx, dy;
            sscanf(str, "%*s %lf %lf %lf %lf %lf %lf", &x, &y, &w, &h, &dx, &dy);
            Retangulo r = criarRetangulo(x, y, w, h, "", "", "");
            Cidade_deslocarEquipamentosInternosRetangulo(*cidade, r, dx, dy, arquivoTXT);
            destruirRetangulo(r);

        } else if(strcmp(instrucao, "brl") == 0) {
            // ver dps
            double x, y;
            sscanf(str, "%*s %lf %lf", &x, &y);
            Cidade_processarBombaRaioLuminoso(*cidade, x, y, arquivoSVG);

        } else if(strcmp(instrucao, "fi") == 0) {

            double x, y, r;
            int ns;
            sscanf(str, "%*s %lf %lf %d %lf", &x, &y, &ns, &r);
            Cidade_processarFocoIncendio(*cidade, x, y, ns, r, arquivoTXT, arquivoSVG);

        } else if(strcmp(instrucao, "fh") == 0) {

            int k;
            double num;
            char cep[50], face, sinal;
            sscanf(str, "%*s %c%d %s %c %lf", &sinal, &k, cep, &face, &num);
            Cidade_processarObjetosProximos(*cidade, sinal, k, cep, face, num, arquivoTXT, arquivoSVG, "hidrante");
            

        } else if(strcmp(instrucao, "fs") == 0) {

            int k;
            double num;
            char cep[50], face, sinal;
            sscanf(str, "%*s %d %s %c %lf", &k, cep, &face, &num);
            Cidade_processarObjetosProximos(*cidade, '-', k, cep, face, num, arquivoTXT, arquivoSVG, "semaforo");

        }
    }

    Cidade_escreverSvg(*cidade, arquivoSVG);
    svg_finalizar(arquivoSVG);
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

