#include "cidade.h"

typedef struct cidade {
    Lista listaForma;
    Lista listaQuadra;
    Lista listaHidrante;
    Lista listaSemaforo;
    Lista listaRadioBase;
    Lista listaTexto;
    Lista listaPredio;
    Lista listaMuro;

    TabelaHash tabelaHashFormas;
    TabelaHash tabelaHashQuadras;
    TabelaHash tabelaHashHidrantes;
    TabelaHash tabelaHashSemaforos;
    TabelaHash tabelaHashRadiosBase;
    TabelaHash tabelaHashTextos;
    TabelaHash tabelaHashPredios;
    TabelaHash tabelaHashMuros;
    TabelaHash tabelaHashEstabelecimentos;
    TabelaHash tabelaHashTiposEstabelecimento;
    TabelaHash tabelaHashPessoas;
    TabelaHash tabelaHashMoradores;

    Arvore arvoreFormas;
    Arvore arvoreQuadras;
    Arvore arvoreHidrantes;
    Arvore arvoreSemaforos;
    Arvore arvoreRadioBases;
    Arvore arvoreTextos;
    Arvore arvorePredios;
    Arvore arvoreMuros;
    Arvore arvoreMoradores;
    Arvore arvoreEstabelecimentos;
}*pCidade;

Cidade criarCidade(int i, int nq, int nh, int ns, int nr, int np, int nm) {
    Cidade c = malloc(sizeof(struct cidade));
    pCidade cidade = (pCidade) c;
    // cidade->listaForma = criarLista(i);
    // cidade->listaQuadra = criarLista(nq);
    // cidade->listaHidrante = criarLista(nh);
    // cidade->listaSemaforo = criarLista(ns);
    // cidade->listaRadioBase = criarLista(nr);
    // cidade->listaPredio = criarLista(np);
    // cidade->listaMuro = criarLista(nm);
    // cidade->listaTexto = criarLista(1000);

    cidade->tabelaHashFormas = criarTabelaHash(i, formaEquals, Forma_getChave, destruirForma);
    cidade->tabelaHashQuadras = criarTabelaHash(nq, quadraEquals, Quadra_getChave, destruirQuadra);
    cidade->tabelaHashHidrantes = criarTabelaHash(nh, hidranteEquals, Hidrante_getChave, destruirHidrante);
    cidade->tabelaHashSemaforos = criarTabelaHash(ns, semaforoEquals, Semaforo_getChave, destruirSemaforo);
    cidade->tabelaHashRadiosBase = criarTabelaHash(nr, radioBaseEquals, RadioBase_getChave, destruirRadioBase);
    cidade->tabelaHashPredios = criarTabelaHash(np, predioEquals, Predio_getChave, destruirPredio);

    cidade->tabelaHashEstabelecimentos = criarTabelaHash(1000, estabelecimentoEquals, Estabelecimento_getChave, destruirEstabelecimento);
    cidade->tabelaHashTiposEstabelecimento = criarTabelaHash(1000, tipoEstabelecimentoEquals, TipoEstabelecimento_getChave, destruirTipoEstabelecimento);
    cidade->tabelaHashPessoas = criarTabelaHash(1000, pessoaEquals, Pessoa_getChave, destruirPessoa);
    cidade->tabelaHashMoradores = criarTabelaHash(1000, moradorEquals, Morador_getChave, destruirMorador);
    cidade->arvoreMoradores = criarArvore(Morador_compararChave, NULL);
    cidade->arvoreEstabelecimentos = criarArvore(Estabelecimento_compararChave, NULL);

    cidade->arvoreFormas = criarArvore(Forma_compararChave, NULL);
    cidade->arvoreQuadras = criarArvore(Quadra_compararChave, NULL);
    cidade->arvoreHidrantes = criarArvore(Hidrante_compararChave, NULL);
    cidade->arvoreSemaforos = criarArvore(Semaforo_compararChave, NULL);
    cidade->arvoreRadioBases = criarArvore(RadioBase_compararChave, NULL);
    cidade->arvorePredios = criarArvore(Predio_compararChave, NULL);
    cidade->arvoreMuros = criarArvore(Muro_compararChave, destruirMuro);
    cidade->arvoreTextos = criarArvore(Texto_compararChave, destruirTexto);
    return cidade;
}

void destruirCidade(Cidade c) {
    pCidade cidade = (pCidade) c;
    // lista_destruir(cidade->listaForma, destruirForma);
    // lista_destruir(cidade->listaQuadra, destruirQuadra);
    // lista_destruir(cidade->listaHidrante, destruirHidrante);
    // lista_destruir(cidade->listaSemaforo, destruirSemaforo);
    // lista_destruir(cidade->listaRadioBase, destruirRadioBase);
    // lista_destruir(cidade->listaTexto, destruirTexto);
    // lista_destruir(cidade->listaPredio, destruirPredio);
    // lista_destruir(cidade->listaMuro, destruirMuro);

    destruirTabelaHash(cidade->tabelaHashPredios);
    destruirTabelaHash(cidade->tabelaHashFormas);
    destruirTabelaHash(cidade->tabelaHashQuadras);
    destruirTabelaHash(cidade->tabelaHashHidrantes);
    destruirTabelaHash(cidade->tabelaHashSemaforos);
    destruirTabelaHash(cidade->tabelaHashRadiosBase);

    destruirTabelaHash(cidade->tabelaHashEstabelecimentos);
    destruirTabelaHash(cidade->tabelaHashTiposEstabelecimento);
    destruirTabelaHash(cidade->tabelaHashPessoas);
    destruirTabelaHash(cidade->tabelaHashMoradores);
    destruirArvore(cidade->arvoreMoradores);
    destruirArvore(cidade->arvoreEstabelecimentos);

    destruirArvore(cidade->arvoreFormas);
    destruirArvore(cidade->arvoreQuadras);
    destruirArvore(cidade->arvoreHidrantes);
    destruirArvore(cidade->arvoreSemaforos);
    destruirArvore(cidade->arvoreRadioBases);
    destruirArvore(cidade->arvoreTextos);
    destruirArvore(cidade->arvorePredios);
    destruirArvore(cidade->arvoreMuros);
    destruirTNULL();
    free(cidade);
}

void Cidade_setForma(Cidade c, Forma forma) {
    pCidade cidade = (pCidade) c;
    Arvore_inserir(cidade->arvoreFormas, forma);
    TabelaHash_inserir(cidade->tabelaHashFormas, forma);
}

void Cidade_setQuadra(Cidade c, Quadra quadra) {
    pCidade cidade = (pCidade) c;
    Arvore_inserir(cidade->arvoreQuadras, quadra);
    TabelaHash_inserir(cidade->tabelaHashQuadras, quadra);
}

void Cidade_setHidrante(Cidade c, Hidrante hidrante) {
    pCidade cidade = (pCidade) c;
    Arvore_inserir(cidade->arvoreHidrantes, hidrante);
    TabelaHash_inserir(cidade->tabelaHashHidrantes, hidrante);
}

void Cidade_setSemaforo(Cidade c, Semaforo semaforo) {
    pCidade cidade = (pCidade) c;
    Arvore_inserir(cidade->arvoreSemaforos, semaforo);
    TabelaHash_inserir(cidade->tabelaHashSemaforos, semaforo);
}

void Cidade_setRadioBase(Cidade c, RadioBase radioBase) {
    pCidade cidade = (pCidade) c;
    Arvore_inserir(cidade->arvoreRadioBases, radioBase);
    TabelaHash_inserir(cidade->tabelaHashRadiosBase, radioBase);
}

void Cidade_setTexto(Cidade c, Texto texto) {
    pCidade cidade = (pCidade) c;
    Arvore_inserir(cidade->arvoreTextos, texto);
}

void Cidade_setPredio(Cidade c, Predio predio) {
    pCidade cidade = (pCidade) c;
    Arvore_inserir(cidade->arvorePredios, predio);
    TabelaHash_inserir(cidade->tabelaHashPredios, predio);
}

void Cidade_setMuro(Cidade c, Muro muro) {
    pCidade cidade = (pCidade) c;
    Arvore_inserir(cidade->arvoreMuros, muro);
}

void Cidade_setEstabelecimento(Cidade c, Estabelecimento estabelecimento) {
    pCidade cidade = (pCidade) c;
    TabelaHash_inserir(cidade->tabelaHashEstabelecimentos, estabelecimento);
    Arvore_inserir(cidade->arvoreEstabelecimentos, estabelecimento);
}

void Cidade_setTipoEstabelecimento(Cidade c, TipoEstabelecimento tipoEstabelecimento) {
    pCidade cidade = (pCidade) c;
    TabelaHash_inserir(cidade->tabelaHashTiposEstabelecimento, tipoEstabelecimento);
}

void Cidade_setPessoa(Cidade c, Pessoa pessoa) {
    pCidade cidade = (pCidade) c;
    TabelaHash_inserir(cidade->tabelaHashPessoas, pessoa);
}

void Cidade_setMorador(Cidade c, Morador morador) {
    pCidade cidade = (pCidade) c;
    TabelaHash_inserir(cidade->tabelaHashMoradores, morador);
    Arvore_inserir(cidade->arvoreMoradores, morador);
}

Predio Cidade_getPredio(Cidade c, char* cep, char face, double num) {
    pCidade cidade = (pCidade) c;
    char id[100];
    sprintf(id, "%s%c%.0lf", cep, face, num);
    return TabelaHash_getObjeto(cidade->tabelaHashPredios, id);
}

Predio _Cidade_getPredioId(Cidade c, char* id) {
    pCidade cidade = (pCidade) c;
    return TabelaHash_getObjeto(cidade->tabelaHashPredios, id);
}

Forma Cidade_getForma(Cidade c, char *id) {
    pCidade cidade = (pCidade) c;
    return TabelaHash_getObjeto(cidade->tabelaHashFormas, id);
}

Quadra Cidade_getQuadra(Cidade c, char *id) {
    pCidade cidade = (pCidade) c;
    return TabelaHash_getObjeto(cidade->tabelaHashQuadras, id);
}

Hidrante Cidade_getHidrante(Cidade c, char *id) {
    pCidade cidade = (pCidade) c;
    return TabelaHash_getObjeto(cidade->tabelaHashHidrantes, id);
}

Semaforo Cidade_getSemaforo(Cidade c, char *id) {
    pCidade cidade = (pCidade) c;
    return TabelaHash_getObjeto(cidade->tabelaHashSemaforos, id);
}

RadioBase Cidade_getRadioBase(Cidade c, char *id) {
    pCidade cidade = (pCidade) c;
    return TabelaHash_getObjeto(cidade->tabelaHashRadiosBase, id);
}

Estabelecimento Cidade_getEstabelecimento(Cidade c, char* id) {
    pCidade cidade = (pCidade) c;
    return TabelaHash_getObjeto(cidade->tabelaHashEstabelecimentos, id);
}

TipoEstabelecimento Cidade_getTipoEstabelecimento(Cidade c, char* id) {
    pCidade cidade = (pCidade) c;
    return TabelaHash_getObjeto(cidade->tabelaHashTiposEstabelecimento, id);
}

Pessoa Cidade_getPessoa(Cidade c, char* id) {
    pCidade cidade = (pCidade) c;
    return TabelaHash_getObjeto(cidade->tabelaHashPessoas, id);
}

Morador Cidade_getMorador(Cidade c, char* id) {
    pCidade cidade = (pCidade) c;
    return TabelaHash_getObjeto(cidade->tabelaHashMoradores, id);
}

bool _Cidade_removerPredio(Cidade c, char* cep, char face, double num) {
    pCidade cidade = (pCidade) c;
    Predio prd;

    char id[150];
    sprintf(id, "%s%c%.0lf", cep, face, num);

    if((prd = Cidade_getPredio(c, cep, face, num)) != NULL) {

        Arvore_removerObjeto(cidade->arvorePredios, prd);
        TabelaHash_removerObjeto(cidade->tabelaHashPredios, id);
        return true;
    }
    return false;
}

bool _Cidade_removerPredioId(Cidade c, char* id) {
    pCidade cidade = (pCidade) c;
    Predio prd;

    if((prd = _Cidade_getPredioId(c, id)) != NULL) {
    
        Arvore_removerObjeto(cidade->arvorePredios, prd);
        //TabelaHash_removerObjeto(cidade->tabelaHashPredios, id);
        return true;
    }
    return false;
}


bool Cidade_removerObjeto(Cidade c, char *id) {
    pCidade cidade = (pCidade) c;
    Hidrante h;
    RadioBase rb;
    Semaforo s;
    Quadra q;
    Morador m;
    
    if((h = Cidade_getHidrante(c, id)) != NULL) {

        Arvore_removerObjeto(cidade->arvoreHidrantes, h);
        TabelaHash_removerObjeto(cidade->tabelaHashHidrantes, id);
        return true;

    } else if((rb = Cidade_getRadioBase(c, id)) != NULL) {

        Arvore_removerObjeto(cidade->arvoreRadioBases, rb);
        TabelaHash_removerObjeto(cidade->tabelaHashRadiosBase, id);
        return true;

    } else if((s = Cidade_getSemaforo(c, id)) != NULL) {

        Arvore_removerObjeto(cidade->arvoreSemaforos, s);
        TabelaHash_removerObjeto(cidade->tabelaHashSemaforos, id);
        return true;

    } else if((q = Cidade_getQuadra(c, id)) != NULL) {

        Arvore_removerObjeto(cidade->arvoreQuadras, q);
        TabelaHash_removerObjeto(cidade->tabelaHashQuadras, id);
        return true;

    } else if((m = Cidade_getMorador(c, id)) != NULL) {

        TabelaHash_removerObjeto(cidade->tabelaHashMoradores, m);
        return true;
    } 

    return false;
}


void removerQuadrasInternasEquipamentoAux(pCidade c, Node n, double px, double py, double dist, char* op, FILE *txt) {
    Quadra q = Node_getObjeto(n);

    if (q == NULL) return;

    Retangulo r = criarRetangulo(Quadra_get_x(q), Quadra_get_y(q), Quadra_get_w(q), Quadra_get_h(q), "", "", "");

    if(strcmp(op, "L1") == 0) {
        if(retanguloInternoL1(px, py, r, dist)) {
            fprintf(txt, "CEP -> %s\n", Quadra_get_cep(q));
            removerQuadrasInternasEquipamentoAux(c, Node_getDir(n), px, py, dist, op, txt);
            removerQuadrasInternasEquipamentoAux(c, Node_getEsq(n), px, py, dist, op, txt);
            Arvore_removerObjeto(c->arvoreQuadras, q);
        } else {
            removerQuadrasInternasEquipamentoAux(c, Node_getDir(n), px, py, dist, op, txt);
            removerQuadrasInternasEquipamentoAux(c, Node_getEsq(n), px, py, dist, op, txt);
        }
        destruirRetangulo(r);
    } else if(strcmp(op, "L2") == 0) {
        Circulo circ = criarCirculo(px, py, dist, "", "", "");
        if(retanguloInternoCirculo(r, circ)) {
            fprintf(txt, "CEP -> %s\n", Quadra_get_cep(q));
            removerQuadrasInternasEquipamentoAux(c, Node_getDir(n), px, py, dist, op, txt);
            removerQuadrasInternasEquipamentoAux(c, Node_getEsq(n), px, py, dist, op, txt);
            Arvore_removerObjeto(c->arvoreQuadras, q);
        } else {
            removerQuadrasInternasEquipamentoAux(c, Node_getDir(n), px, py, dist, op, txt);
            removerQuadrasInternasEquipamentoAux(c, Node_getEsq(n), px, py, dist, op, txt);
        }
        destruirCirculo(circ);
        destruirRetangulo(r);
    }

}   

void Cidade_removerQuadrasInternasEquipamento(Cidade c, double px, double py, double dist, char *op, FILE *txt) {
    pCidade cidade = (pCidade) c;
    fprintf(txt, "-- CEP(s) REMOVIDOS --\n");
    removerQuadrasInternasEquipamentoAux(cidade, Arvore_getRaiz(cidade->arvoreQuadras), px, py, dist, op, txt);
    fprintf(txt, "----------------------\n\n");
}

// cbq
void Cidade_setCstrkQuadrasInternasCirculo(Cidade cid, Circulo c, char *cstrk, FILE *txt) {
    pCidade cidade = (pCidade) cid;
    fprintf(txt, "-- CEP(s) QUADRAS PINTADAS --\n");

    Node quadras = Arvore_getRaiz(cidade->arvoreQuadras);
    forEach(quadra, quadras) {
        if (Node_getAux(quadra) == 0) {
            Quadra q = Node_getObjeto(quadra);
            Retangulo r = criarRetangulo(Quadra_get_x(q), Quadra_get_y(q), Quadra_get_w(q), Quadra_get_h(q), "", "", "");
            if(retanguloInternoCirculo(r, c)) {
                Quadra_set_cstrk(q, cstrk);
                fprintf(txt, "CEP -> %s\n", Quadra_get_cep(q));
            }
            destruirRetangulo(r);
        }
    }

    fprintf(txt, "-----------------------------\n\n");
}

Objeto objetoCopy(Objeto objeto, int tamanho) {
	Objeto o = malloc(tamanho);
	memcpy(o, objeto, tamanho);
	return o;
}

// trns
// Isso só é possivel pois eu nao do free na arvore ao remover os objetos
void Cidade_deslocarEquipamentosInternosRetangulo(Cidade c, Retangulo r, double dx, double dy, FILE *txt) {
    pCidade cidade = (pCidade) c;   
    int index = 0;
    fprintf(txt, "-- EQUIPAMENTOS URBANOS MOVIDOS --\n");

    int tam1 = fmax(Arvore_length(cidade->arvoreQuadras), Arvore_length(cidade->arvoreHidrantes));
    int tam2 = fmax(tam1, Arvore_length(cidade->arvoreSemaforos));
    int tamLista = fmax(tam2, Arvore_length(cidade->arvoreRadioBases));

    Objeto* lista_objetos = (Objeto*)malloc(tamLista*sizeof(Objeto));
    Node quadras = Arvore_getRaiz(cidade->arvoreQuadras);
    forEach(quadra, quadras) {
        if (Node_getAux(quadra) == 0) {
            Quadra o = Node_getObjeto(quadra);
            Retangulo rq = criarRetangulo(Quadra_get_x(o), Quadra_get_y(o), Quadra_get_w(o), Quadra_get_h(o), "", "", "");
            if(retanguloInternoRetangulo(rq, r)) {
                lista_objetos[index] = o; index++;
            }
            destruirRetangulo(rq);
        }
    }
    for(int i = 0; i < index; i++) {
        Objeto o = lista_objetos[i];
        Quadra_set_x(o, Quadra_get_x(o) + dx);
        Quadra_set_y(o, Quadra_get_y(o) + dy);

        Arvore_removerObjeto(cidade->arvoreQuadras, o);
        Arvore_inserir(cidade->arvoreQuadras, o);
    }


    index = 0;
    Node hidrantes = Arvore_getRaiz(cidade->arvoreHidrantes);
    forEach(hidrante, hidrantes) {
        if (Node_getAux(hidrante) == 0) {
            Hidrante o = Node_getObjeto(hidrante);
            if(pontoInternoRetangulo(Hidrante_get_x(o), Hidrante_get_y(o), r)) {
                lista_objetos[index] = o; index++;
            }
        }
    }
    for(int i = 0; i < index; i++) {
        Objeto o = lista_objetos[i];
        Hidrante_set_x(o, Hidrante_get_x(o) + dx);
        Hidrante_set_y(o, Hidrante_get_y(o) + dy);

        Arvore_removerObjeto(cidade->arvoreHidrantes, o);
        Arvore_inserir(cidade->arvoreHidrantes, o);
    }

    
    index = 0;
    Node semaforos = Arvore_getRaiz(cidade->arvoreSemaforos);
    forEach(semaforo, semaforos) {
        if (Node_getAux(semaforo) == 0) {
            Semaforo o = Node_getObjeto(semaforo);
            if(pontoInternoRetangulo(Semaforo_get_x(o), Semaforo_get_y(o), r)) {
                lista_objetos[index] = o; index++;
            }
        }
    }
    for(int i = 0; i < index; i++) {
        Objeto o = lista_objetos[i];
        Semaforo_set_x(o, Semaforo_get_x(o) + dx);
        Semaforo_set_y(o, Semaforo_get_y(o) + dy);

        Arvore_removerObjeto(cidade->arvoreSemaforos, o);
        Arvore_inserir(cidade->arvoreSemaforos, o);
    }

    index = 0;
    Node radiosBase = Arvore_getRaiz(cidade->arvoreRadioBases);
    forEach(radioBase, radiosBase) {
        if (Node_getAux(radioBase) == 0) {
            RadioBase o = Node_getObjeto(radioBase);
            if(pontoInternoRetangulo(RadioBase_get_x(o), RadioBase_get_y(o), r)) {
                lista_objetos[index] = o; index++;
            }
        }
    }
    for(int i = 0; i < index; i++) {
        Objeto o = lista_objetos[i];
        RadioBase_set_x(o, RadioBase_get_x(o) + dx);
        RadioBase_set_y(o, RadioBase_get_y(o) + dy);

        Arvore_removerObjeto(cidade->arvoreRadioBases, o);
        Arvore_inserir(cidade->arvoreRadioBases, o);
    }
    free(lista_objetos);
    fprintf(txt, "----------------------------------\n");
}

// Usado apenas para o .geo
void Cidade_escreverSvg(Cidade c, FILE *svg) {
    pCidade cidade = (pCidade) c;

    Node formas = Arvore_getRaiz(cidade->arvoreFormas);
    forEach(forma, formas) {
        if (Node_getAux(forma) == 0) {
            Forma f = Node_getObjeto(forma);
            Forma_escreverSvg(f, svg);
        }
    }

    Node textos = Arvore_getRaiz(cidade->arvoreTextos);
    forEach(texto, textos) {
        if (Node_getAux(texto) == 0) {
           Texto t = Node_getObjeto(texto);
           Texto_escreverSvg(t, svg);
        }
    }

    Node quadras = Arvore_getRaiz(cidade->arvoreQuadras);
    forEach(quadra, quadras) {
        if (Node_getAux(quadra) == 0) {
            Quadra q = Node_getObjeto(quadra);
            Quadra_escreverSvg(q, svg);
        }
    }
    //Arvore_resetarAux(cidade->arvoreQuadras);

    Node hidrantes = Arvore_getRaiz(cidade->arvoreHidrantes);
    forEach(hidrante, hidrantes) {
        if (Node_getAux(hidrante) == 0) {
            Hidrante h = Node_getObjeto(hidrante);
            Hidrante_escreverSvg(h, svg);
        }
    }

    Node semaforos = Arvore_getRaiz(cidade->arvoreSemaforos);
    forEach(semaforo, semaforos) {
        if (Node_getAux(semaforo) == 0) {
            Semaforo s = Node_getObjeto(semaforo);
            Semaforo_escreverSvg(s, svg);
        }
    }

    Node radioBases = Arvore_getRaiz(cidade->arvoreRadioBases);
    forEach(radioBase, radioBases) {
        if (Node_getAux(radioBase) == 0) {
            RadioBase rb = Node_getObjeto(radioBase);
            RadioBase_escreverSvg(rb, svg);
        }
    }

    Node muros = Arvore_getRaiz(cidade->arvoreMuros);
    forEach(muro, muros) {
        if (Node_getAux(muro) == 0) {
            Muro m = Node_getObjeto(muro);
            Muro_escreverSvg(m, svg);
        }
    }

    Node predios = Arvore_getRaiz(cidade->arvorePredios);
    forEach(predio, predios) {
        if (Node_getAux(predio) == 0) {
            Predio p = Node_getObjeto(predio);
            Quadra q = Cidade_getQuadra(c, Predio_getCep(p));
            if(q != NULL)
                Predio_escreverSvg(p, Quadra_get_x(q), Quadra_get_y(q), Quadra_get_w(q), Quadra_get_h(q), svg);
        }
    }
}

void Cidade_escreverFormasEnvoltas(Cidade c, FILE *svg, char *cor) {
    pCidade cidade = (pCidade) c;

    Node formas = Arvore_getRaiz(cidade->arvoreFormas);
    forEach(forma, formas) {
        if (Node_getAux(forma) == 0) {
            Forma f = Node_getObjeto(forma);
            Forma_escreverFormaEnvoltaSvg(f, svg, cor);
        }
    }
}

// void imprimirCidade(Cidade c) {
//     pCidade cidade = (pCidade) c;
//     int i = lista_getPrimeiro(cidade->listaForma);
//     for(i; i!= -1; i = lista_getProx(cidade->listaForma, i)) {
//         Forma f = lista_getObjPosic(cidade->listaForma, i);
//         Forma_imprimir(f);
//     }
// }


// Struct e função utilizadas para qsort
typedef struct obj {
        double distancia;
        void *Objeto;
} *pObj;

double get_obj_comparador(Objeto o) {
    pObj objeto = (pObj) o;
    return objeto->distancia;
}

void Cidade_processarFocoIncendio(Cidade c, double x, double y, int ns, double r, FILE *txt, FILE *svg) {
    pCidade cidade = (pCidade) c;
    int tamanhoArvore = Arvore_length(cidade->arvoreSemaforos);

    // Semaforos mais proximos do foco de incendio
    pObj* semaforos_comparar = (pObj*)malloc(tamanhoArvore*sizeof(pObj));

    int index = 0;
    Node semaforos = Arvore_getRaiz(cidade->arvoreSemaforos);
    forEach(semaforo, semaforos) {
        if (Node_getAux(semaforo) == 0) {
            Semaforo s = Node_getObjeto(semaforo);

            double distancia = distanciaL2(x, y, Semaforo_get_x(s), Semaforo_get_y(s));

            pObj o = malloc(sizeof(struct obj));
            o->distancia = distancia;
            o->Objeto = s;

            semaforos_comparar[index] = o;
            index++;
        }
    }

    //qsort(semaforos_comparar, tamanhoLista, sizeof(struct obj), compCrescente);
    heapsortMenor((Objeto*)semaforos_comparar, tamanhoArvore, ns, get_obj_comparador);
    fprintf(txt, "-- SEMAFOROS PRÓXIMOS AO FOCO DE INCENDIO --\n");
    for(int i = tamanhoArvore - ns; i < tamanhoArvore; i++) {
        Semaforo s = ((pObj)semaforos_comparar[i])->Objeto;
        fprintf(txt, "ID -> %s\n", Semaforo_get_id(s));

        Circulo c1 = criarCirculo(Semaforo_get_x(s), Semaforo_get_y(s), 7, "none", "orange", "3px");
        Circulo_escreverSvg(c1, svg);
        destruirCirculo(c1);

        Circulo c2 = criarCirculo(Semaforo_get_x(s), Semaforo_get_y(s), 9, "none", "gold", "3px");
        Circulo_escreverSvg(c2, svg);
        destruirCirculo(c2);

        Muro m = criarMuro(x, y, Semaforo_get_x(s), Semaforo_get_y(s));
        Muro_escreverSvg(m, svg);
        destruirMuro(m);
    }
    for(int i = 0; i < tamanhoArvore; i++) free(semaforos_comparar[i]);
    free(semaforos_comparar);
    fprintf(txt, "-------------------------------------------\n");

    // Hidrantes dentro de uma distancia r do foco de incendio
    Circulo circ = criarCirculo(x, y, r, "", "", "");
    Node hidrantes = Arvore_getRaiz(cidade->arvoreHidrantes);
    forEach(hidrante, hidrantes) {
        if (Node_getAux(hidrante) == 0) {
            Hidrante h = Node_getObjeto(hidrante);
            
            if(pontoInternoCirculo(Hidrante_get_x(h), Hidrante_get_y(h), circ)) {
                fprintf(txt, "ID -> %s\n", Hidrante_get_id(h));

                Circulo c1 = criarCirculo(Hidrante_get_x(h), Hidrante_get_y(h), 7, "none", "orange", "3px");
                Circulo_escreverSvg(c1, svg);
                destruirCirculo(c1);

                Circulo c2 = criarCirculo(Hidrante_get_x(h), Hidrante_get_y(h), 9, "none", "gold", "3px");
                Circulo_escreverSvg(c2, svg);
                destruirCirculo(c2);

                Muro m = criarMuro(x, y, Hidrante_get_x(h), Hidrante_get_y(h));
                Muro_escreverSvg(m, svg);
                destruirMuro(m);
            }
        }
    }
    destruirCirculo(circ);
    fprintf(txt, "-------------------------------------------\n");
}

void Cidade_processarObjetosProximos(Cidade c, char sinal, int k, char cep[], char face, double num, FILE* txt, FILE *svg, char tipo[]) {
    pCidade cidade = (pCidade) c;
    int i;
    double x, y;
    // Lista lista;
    Arvore arvore;

    if(strcmp(tipo, "hidrante") == 0) {
        arvore = cidade->arvoreHidrantes;
    } else if(strcmp(tipo, "semaforo") == 0) {
        arvore = cidade->arvoreSemaforos;
    }

    // int tamanhoLista = lista_length(lista);
    int tamanhoArvore = Arvore_length(arvore);

    Quadra q = Cidade_getQuadra(c, cep);
    if(q == NULL) return;
    if(face == 'N') {
        x = Quadra_get_x(q) + num;
        y = Quadra_get_y(q) + Quadra_get_h(q);
    } else if(face == 'S') {
        x = Quadra_get_x(q) + num;
        y = Quadra_get_y(q);
    } else if(face == 'L') {
        x = Quadra_get_x(q);
        y = Quadra_get_y(q) + num;
    } else if(face == 'O') {
        x = Quadra_get_x(q) + Quadra_get_w(q);
        y = Quadra_get_y(q) + num;
    }

    pObj* objetos_comparar = (pObj*)malloc(tamanhoArvore*sizeof(pObj));

    int index = 0;
    Node objetos = Arvore_getRaiz(arvore);
    forEach(objeto, objetos) {
        if (Node_getAux(objeto) == 0) {
            Objeto o = Node_getObjeto(objeto);
            
            double distancia;
            if(strcmp(tipo, "hidrante") == 0) {
                distancia = distanciaL2(x, y, Hidrante_get_x(o), Hidrante_get_y(o));
            } else if(strcmp(tipo, "semaforo") == 0) {
                distancia = distanciaL2(x, y, Semaforo_get_x(o), Semaforo_get_y(o));
            }

            pObj ob = malloc(sizeof(struct obj));
            ob->distancia = distancia;
            ob->Objeto = o;

            objetos_comparar[index] = ob;
            index++;
        }
    }

    if(sinal == '-')
        heapsortMenor((Objeto*)objetos_comparar, tamanhoArvore, k, get_obj_comparador);
        //qsort(objetos_comparar, lista_length(lista), sizeof(struct obj), compCrescente);
    else
        heapsortMaior((Objeto*)objetos_comparar, tamanhoArvore, k, get_obj_comparador);
        //qsort(objetos_comparar, lista_length(lista), sizeof(struct obj), compDecrescente);
    fprintf(txt, "-- %d %s MAIS %s DO CEP %s --\n", k, ((strcmp(tipo, "hidrante") == 0) ? "HIDRANTES" : "SEMAFOROS"), (sinal == '-' ? "PRÓXIMOS" : "DISTANTES"), cep);
    for(int i = tamanhoArvore - k; i < tamanhoArvore; i++) {
        Objeto o = ((pObj)objetos_comparar[i])->Objeto;
        Circulo c1, c2;
        Muro m;

        if(strcmp(tipo, "hidrante") == 0) {
            fprintf(txt, "ID -> %s\n", Hidrante_get_id(o));
            c1 = criarCirculo(Hidrante_get_x(o), Hidrante_get_y(o), 7, "none", "orange", "3px");
            c2 = criarCirculo(Hidrante_get_x(o), Hidrante_get_y(o), 9, "none", "gold", "3px");
            m = criarMuro(x, y, Hidrante_get_x(o), Hidrante_get_y(o));
        } else if(strcmp(tipo, "semaforo") == 0) {
            fprintf(txt, "ID -> %s\n", Semaforo_get_id(o));
            c1 = criarCirculo(Semaforo_get_x(o), Semaforo_get_y(o), 7, "none", "orange", "3px");
            c2 = criarCirculo(Semaforo_get_x(o), Semaforo_get_y(o), 9, "none", "gold", "3px");
            m = criarMuro(x, y, Semaforo_get_x(o), Semaforo_get_y(o));
        }

        Circulo_escreverSvg(c1, svg);
        destruirCirculo(c1);

        Circulo_escreverSvg(c2, svg);
        destruirCirculo(c2);

        Muro_escreverSvg(m, svg);
        destruirMuro(m);
    }
    for(int i = 0; i < tamanhoArvore; i++) free(objetos_comparar[i]);
    free(objetos_comparar);
    fprintf(txt, "-------------------------------------------\n");
}


int comparador(const void *x, const void *y) {
    Vertice a = *((Vertice*) x);
    Vertice b = *((Vertice*) y);
    if(Vertice_get_angulo(a) < Vertice_get_angulo(b))
        return -1;
    else if(Vertice_get_angulo(a) > Vertice_get_angulo(b))
        return 1;
    else if(Vertice_get_distancia(a) < Vertice_get_distancia(b))
        return -1;
    else if(Vertice_get_distancia(a) > Vertice_get_distancia(b))
        return 1;
    else if(!Vertice_get_inicio(a) && Vertice_get_inicio(b))
        return -1;
    else if(Vertice_get_inicio(a) && !Vertice_get_inicio(b))
        return 1;
    return 0;
}

int _preProcessamento_brl(Cidade c, Ponto* pontoMin, Ponto* pontoMax, Segmento** lista_segmentos, bool brl) {
    pCidade cidade = (pCidade) c;
    double x = Ponto_get_x(*pontoMin);
    double y = Ponto_get_y(*pontoMin);

    int index = 0;
    Node muros = Arvore_getRaiz(cidade->arvoreMuros);
    forEach(muro, muros) {
        if (Node_getAux(muro) == 0) {
            Muro m = Node_getObjeto(muro);

            // Eu nao sei onde esta os pontos do muro, portanto tenho que testar os dois ;/
            Ponto p1 = Muro_get_p1(m);
            Ponto p2 = Muro_get_p2(m);

            Ponto_setMin(*pontoMin, Ponto_get_x(p1), Ponto_get_y(p1));
            Ponto_setMin(*pontoMin, Ponto_get_x(p2), Ponto_get_y(p2));
            Ponto_setMax(*pontoMax, Ponto_get_x(p1), Ponto_get_y(p1));
            Ponto_setMax(*pontoMax, Ponto_get_x(p2), Ponto_get_y(p2));

            if(Ponto_get_x(p1) == x && Ponto_get_x(p2) == x || Ponto_get_y(p1) == y && Ponto_get_y(p2) == y) 
                continue;

            Vertice v1 = criarVertice(Ponto_get_x(p1), Ponto_get_y(p1), x, y);
            Vertice v2 = criarVertice(Ponto_get_x(p2), Ponto_get_y(p2), x, y);

            Segmento s = criarSegmento(v1, v2);

            Segmento_set_inicio_vertices(s);

            Vertice_set_s(v1, s);
            Vertice_set_s(v2, s);
            
            (*lista_segmentos)[index] = s; index++;
        }
    }

    // É o brn, portanto nao utiliza predios
    if (!brl) return index + 4;


    Node predios = Arvore_getRaiz(cidade->arvorePredios);
    forEach(predio, predios) {
        if (Node_getAux(predio) == 0) {
            Predio p = Node_getObjeto(predio);
            Ponto_setMin(*pontoMin, Predio_get_x(p), Predio_get_y(p));
            Ponto_setMax(*pontoMax, Predio_get_x_max(p), Predio_get_y_max(p));

            Vertice v_x1 = criarVertice(Predio_get_x(p), Predio_get_y(p), x, y);
            Vertice v_x2 = criarVertice(Predio_get_x(p), Predio_get_y(p), x, y);
            Vertice v_x_max1 = criarVertice(Predio_get_x_max(p), Predio_get_y(p), x, y);
            Vertice v_x_max2 = criarVertice(Predio_get_x_max(p), Predio_get_y(p), x, y);
            Vertice v_y_max1 = criarVertice(Predio_get_x(p), Predio_get_y_max(p), x, y);
            Vertice v_y_max2 = criarVertice(Predio_get_x(p), Predio_get_y_max(p), x, y);
            Vertice v_xy_max1 = criarVertice(Predio_get_x_max(p), Predio_get_y_max(p), x, y);
            Vertice v_xy_max2 = criarVertice(Predio_get_x_max(p), Predio_get_y_max(p), x, y);

            Segmento s1 = criarSegmento(v_x1, v_x_max1);
            Segmento s2 = criarSegmento(v_x2, v_y_max1);
            Segmento s3 = criarSegmento(v_x_max2, v_xy_max1);
            Segmento s4 = criarSegmento(v_y_max2, v_xy_max2);
            
            Segmento_set_inicio_vertices(s1);
            Segmento_set_inicio_vertices(s2);
            Segmento_set_inicio_vertices(s3);
            Segmento_set_inicio_vertices(s4);

            Vertice_set_s(v_x1, s1);
            Vertice_set_s(v_x_max1, s1);
            Vertice_set_s(v_x2, s2);
            Vertice_set_s(v_y_max1, s2);
            Vertice_set_s(v_x_max2, s3);
            Vertice_set_s(v_xy_max1, s3);
            Vertice_set_s(v_y_max2, s4);
            Vertice_set_s(v_xy_max2, s4);

            (*lista_segmentos)[index] = s1; index++;
            (*lista_segmentos)[index] = s2; index++;
            (*lista_segmentos)[index] = s3; index++;
            (*lista_segmentos)[index] = s4; index++;
        }
    }
    
    // O novo tamanho final da lista de segmentos é index (tanto q percorreu) + 4 (muros)
    return index + 4;
}

void Cidade_processarBombaRaioLuminoso(Cidade c, double x, double y, FILE *svg, bool brl, FILE* txt, FILE* arq) {
    pCidade cidade = (pCidade) c;
    Ponto pontoMin = criarPonto(x, y);
    Ponto pontoMax = criarPonto(x, y);
    double areaAfetada = 0;
    int i, tamListaSegmentos = (Arvore_length(cidade->arvorePredios)*4) + Arvore_length(cidade->arvoreMuros) + 4;

    Segmento* lista_segmentos = (Segmento*)malloc(tamListaSegmentos*sizeof(Segmento));
    tamListaSegmentos = _preProcessamento_brl(c, &pontoMin, &pontoMax, &lista_segmentos, brl);

    int index = tamListaSegmentos - 4;
    // Até aqui foi definida a lista de segmentos,
    // com os vertices marcados de inicio ou fim e seus respectivos angulos em relação à x,y

    // Aqui é definido o ponto max+100 do maior ponto e ponto min-100 do menor ponto
    // Alem disso sao adicionados à lista de segmentos os segmentos de borda

    Ponto_set_x(pontoMin, Ponto_get_x(pontoMin) - 100);
    Ponto_set_y(pontoMin, Ponto_get_y(pontoMin) - 100);
    Ponto_set_x(pontoMax, Ponto_get_x(pontoMax) + 100);
    Ponto_set_y(pontoMax, Ponto_get_y(pontoMax) + 100);

    double x_min = Ponto_get_x(pontoMin);
    double x_max = Ponto_get_x(pontoMax);
    double y_min = Ponto_get_y(pontoMin);
    double y_max = Ponto_get_y(pontoMax);

    Vertice v_ce = criarVertice(x_min, y_min, x, y);
    Vertice v_ce1 = criarVertice(x_min, y_min, x, y);
    Vertice v_cd = criarVertice(x_max, y_min, x, y);
    Vertice v_cd1 = criarVertice(x_max, y_min, x, y);
    Vertice v_be = criarVertice(x_min, y_max, x, y);
    Vertice v_be1 = criarVertice(x_min, y_max, x, y);
    Vertice v_bd = criarVertice(x_max, y_max, x, y);
    Vertice v_bd1 = criarVertice(x_max, y_max, x, y);

    Segmento sc = criarSegmento(v_ce1, v_cd);
    Segmento sd = criarSegmento(v_cd1, v_bd);
    Segmento sb = criarSegmento(v_bd1, v_be);
    Segmento se = criarSegmento(v_be1, v_ce);

    // Muro mb1 = criarMuro(x_min, y_min, x_max, y_min);
    // Muro mb2 = criarMuro(x_max, y_min, x_max, y_max);
    // Muro mb3 = criarMuro(x_min, y_max, x_min, y_min);
    // Muro mb4 = criarMuro(x_max, y_max, x_min, y_max);
    // Muro_escreverSvg(mb1, svg);
    // Muro_escreverSvg(mb2, svg);
    // Muro_escreverSvg(mb3, svg);
    // Muro_escreverSvg(mb4, svg);

    Segmento_set_inicio_vertices(sc);
    Segmento_set_inicio_vertices(sd);
    Segmento_set_inicio_vertices(sb);
    Segmento_set_inicio_vertices(se);

    Vertice_set_s(v_ce1, sc);
    Vertice_set_s(v_cd, sc);
    Vertice_set_s(v_cd1, sd);
    Vertice_set_s(v_bd, sd);
    Vertice_set_s(v_bd1, sb);
    Vertice_set_s(v_be, sb);
    Vertice_set_s(v_be1, se);
    Vertice_set_s(v_ce, se);

    lista_segmentos[index] = sc; index++;
    lista_segmentos[index] = sd; index++;
    lista_segmentos[index] = sb; index++;
    lista_segmentos[index] = se; index++;

    // Aqui será feito o segmento para o corte inicial dos segmentos que interceptam
    Vertice v_inicial = criarVertice(x, y, 0, 0);
    Vertice v_final = criarVertice(Ponto_get_x(pontoMin) - 1, y, 0, 0);
    Segmento s_inicial = criarSegmento(v_inicial, v_final); // Semi reta do ponto inicial até x_min
    Vertice_set_s(v_inicial, s_inicial);
    Vertice_set_s(v_final, s_inicial);

    Vertice_set_inicio(v_inicial, true);
    Vertice_set_inicio(v_final, false);

    // Para verificar a linha de corte inicial, descomentar:
    // Muro mur = criarMuro(x, y, Ponto_get_x(pontoMin) - 1, y);
    // Muro_escreverSvg(mur, svg);
    
    svg_escreverBomba(svg, x, y);

    int tamListaVertices = tamListaSegmentos*2;
    Vertice* lista_vertices = (Vertice*)malloc(tamListaVertices*sizeof(Vertice));
    index = 0;
    for(int i = 0; i < tamListaSegmentos; i++) {
        // Verificar se os segmentos interceptam
        if(verificarSegmentosInterceptam(s_inicial, lista_segmentos[i])) {

            tamListaVertices+=2;
            lista_vertices = (Vertice*)realloc(lista_vertices, tamListaVertices*sizeof(Vertice));
            Segmento s = lista_segmentos[i];

            // x onde s_inicial e segmento interceptam
            double x_inter = buscarXInterseccaoSegmento(s, y);

            Vertice v_inicioS = Vertice_get_inicio(Segmento_get_v1(s)) ? Segmento_get_v1(s) : Segmento_get_v2(s);
            Vertice v_finalS = Vertice_get_inicio(Segmento_get_v1(s)) ? Segmento_get_v2(s) : Segmento_get_v1(s);
            Vertice v_inicio = criarVertice(Vertice_get_x(v_inicioS), Vertice_get_y(v_inicioS), x, y);
            Vertice v_final = criarVertice(Vertice_get_x(v_finalS), Vertice_get_y(v_finalS), x, y);
            
            Vertice v_final_meio = criarVertice(x_inter, y, x, y);
            Vertice_set_inicio(v_final_meio, false);
            Vertice_set_angulo(v_final_meio, M_PI);
            Vertice v_inicial_meio = criarVertice(x_inter, y, x, y);
            Vertice_set_inicio(v_inicial_meio, true);
            Vertice_set_angulo(v_inicial_meio, -M_PI);

            Segmento s1 = criarSegmento(v_inicio, v_final_meio);
            Segmento s2 = criarSegmento(v_inicial_meio, v_final);

            Vertice_set_s(v_inicio, s1);
            Vertice_set_s(v_final_meio, s1);
            Vertice_set_s(v_inicial_meio, s2);
            Vertice_set_s(v_final, s2);

            Segmento_set_inicio_vertices(s1);
            Segmento_set_inicio_vertices(s2);

            lista_vertices[index] = v_inicio; index++;
            lista_vertices[index] = v_final_meio; index++;
            lista_vertices[index] = v_inicial_meio; index++;
            lista_vertices[index] = v_final; index++;

            // Dar free no segmento q foi repartido, pois nao tera mais acesso a ele
            destruirSegmento(s);
        } else {
            Segmento s = lista_segmentos[i];
            Vertice v1 = Segmento_get_v1(s);
            Vertice v2 = Segmento_get_v2(s);    

            lista_vertices[index] = v1; index++;
            lista_vertices[index] = v2; index++;
        }
    }

    qsort(lista_vertices, tamListaVertices, sizeof(Vertice), comparador);
    // heapsortMaior(lista_vertices, tamListaVertices, tamListaVertices, Vertice_get_angulo);
    
    // A partir daqui será varrido todos os vertices no sentido horario começando pela esquerda
    //Lista segmentos_ativos = criarLista((int)tamListaVertices/2);
    Arvore segmentos_ativos = criarArvore(Segmento_compararChave, NULL);
    Vertice biombo = criarVertice(Vertice_get_x(lista_vertices[0]), Vertice_get_y(lista_vertices[0]), x, y);
    Vertice_set_s(biombo, Vertice_get_s(lista_vertices[0]));
    Segmento* lista_segmentos_free = (Segmento*)malloc((tamListaVertices/2)*sizeof(Segmento));
    int indexSf = 0;


    Vertice* lista_pontos;
    int indexPonto = 0;
    if (!brl) {
        lista_pontos = (Ponto*)malloc(tamListaVertices*4*sizeof(Ponto));
    }

    for(int i = 0; i < tamListaVertices; i++) {

        Vertice v = lista_vertices[i];
        Segmento sv = Vertice_get_s(v);
        Segmento s_formado_v = buscarSegmentoFormadoComVertice(x, y, v, pontoMin, pontoMax);
        Segmento seg_mais_prox = NULL;

        Node segmentos = Arvore_getRaiz(segmentos_ativos);

        // Definindo a menor distancia entre centro e o vertice como MAX
        double menor_dist = INT_MAX;
        forEach(segmento, segmentos) {
            if (Node_getAux(segmento) == 0) {
                Segmento s = Node_getObjeto(segmento);
                if(s == sv) continue;

                // Verificar se segmento formado e o da lista interceptam
                if(verificarSegmentosInterceptam(s_formado_v, s)) {
                    // Buscar ponto de intersecção
                    Ponto intersec = buscarPontoInterseccao(s_formado_v, s);
                    double dist_centro_intersec = distanciaL2(x, y, Ponto_get_x(intersec), Ponto_get_y(intersec));
                    if(dist_centro_intersec < menor_dist) {
                        menor_dist = dist_centro_intersec;
                        seg_mais_prox = s;
                    }
                    destruirPonto(intersec);
                }
            }
        }

        if(Vertice_get_inicio(v)) {
            lista_segmentos_free[indexSf] = sv; indexSf++;
            // Circulo c1 = criarCirculo(Vertice_get_x(v), Vertice_get_y(v), 2, "green", "green", "2px");
            // Circulo_escreverSvg(c1, svg);
            

            bool segEhOMaisProx;
            if(distanciaL2(x, y, Vertice_get_x(v), Vertice_get_y(v)) < menor_dist)
                segEhOMaisProx = true;
            else
                segEhOMaisProx = false;

            if(segEhOMaisProx) {
                Ponto intersec_biombo = buscarPontoInterseccao(s_formado_v, Vertice_get_s(biombo));
                Vertice v_intersec = criarVertice(Ponto_get_x(intersec_biombo), Ponto_get_y(intersec_biombo), x, y);

                svg_escreverTriangulo(svg, x, y, biombo, v_intersec, brl);
                svg_escreverTriangulo(svg, x, y, v_intersec, v, brl);
                if (!brl) {
                    areaAfetada += calcularAreaTriangulo(x, y, biombo, v_intersec);
                    areaAfetada += calcularAreaTriangulo(x, y, v_intersec, v);
                    Ponto p1 = criarPonto(Vertice_get_x(biombo), Vertice_get_y(biombo)); 
                    Ponto p2 = criarPonto(Vertice_get_x(v_intersec), Vertice_get_y(v_intersec));
                    Ponto p3 = criarPonto(Vertice_get_x(v_intersec), Vertice_get_y(v_intersec));
                    Ponto p4 = criarPonto(Vertice_get_x(v), Vertice_get_y(v));
                    lista_pontos[indexPonto] = p1; indexPonto++;
                    lista_pontos[indexPonto] = p2; indexPonto++;
                    lista_pontos[indexPonto] = p3; indexPonto++;
                    lista_pontos[indexPonto] = p4; indexPonto++;
                }

                biombo = v;
                destruirPonto(intersec_biombo);
                destruirVertice(v_intersec);
            }

            Arvore_inserir(segmentos_ativos, sv);

        } else {
            // Circulo c1 = criarCirculo(Vertice_get_x(v)-5, Vertice_get_y(v)-5, 2, "red", "red", "2px");
            // Circulo_escreverSvg(c1, svg);
            

            bool segEhOMaisProx;
            if(distanciaL2(x, y, Vertice_get_x(v), Vertice_get_y(v)) <= menor_dist)
                segEhOMaisProx = true;
            else
                segEhOMaisProx = false;

            if(segEhOMaisProx) {
                if(seg_mais_prox != NULL) {
                    Ponto intersec_biombo = buscarPontoInterseccao(s_formado_v, seg_mais_prox);
                    Vertice v_intersec = criarVertice(Ponto_get_x(intersec_biombo), Ponto_get_y(intersec_biombo), x, y);

    
                    svg_escreverTriangulo(svg, x, y, biombo, v, brl);
                    if (!brl) {
                        areaAfetada += calcularAreaTriangulo(x, y, v, v_intersec);
                        areaAfetada += calcularAreaTriangulo(x, y, biombo, v);
                        Ponto p3 = criarPonto(Vertice_get_x(biombo), Vertice_get_y(biombo));
                        Ponto p4 = criarPonto(Vertice_get_x(v), Vertice_get_y(v));
                        lista_pontos[indexPonto] = p3; indexPonto++;
                        lista_pontos[indexPonto] = p4; indexPonto++;
                    }

                    biombo = v_intersec;
                    Vertice_set_s(biombo, seg_mais_prox);
                    destruirPonto(intersec_biombo);
                 } else {
                    svg_escreverTriangulo(svg, x, y, biombo, v, brl);
                    if (!brl) {
                        areaAfetada += calcularAreaTriangulo(x, y, biombo, v);
                        Ponto p1 = criarPonto(Vertice_get_x(biombo), Vertice_get_y(biombo));
                        Ponto p2 = criarPonto(Vertice_get_x(v), Vertice_get_y(v));
                        lista_pontos[indexPonto] = p1; indexPonto++;
                        lista_pontos[indexPonto] = p2; indexPonto++;
                    }
                    biombo = v; // O problema eh nesse caso quando eu do free no sv e consequentemente no biombo
                 }
            }

            Arvore_removerObjeto(segmentos_ativos, sv);
        }

    }

    if (!brl) {
        fprintf(txt, "------- BRN pos %lf %lf -------\n", x, y);
        fprintf(txt, "Área afetada: %lf\n\n", areaAfetada);
        fprintf(txt, "-----------------------------------------\n");

        for(int i = 0; i < indexPonto; i++) {
            double xp = Ponto_get_x(lista_pontos[i]);
            double yp = Ponto_get_y(lista_pontos[i]);
            fprintf(arq, "%lf %lf\n", xp, yp);
            free(lista_pontos[i]);
        }
        free(lista_pontos);
    }
    
    for(int i = 0; i < indexSf; i++) free(lista_segmentos_free[i]);
    free(lista_segmentos_free);
    destruirArvore(segmentos_ativos);
    destruirPonto(pontoMin);
    destruirPonto(pontoMax);
    destruirVertice(v_final);
    destruirVertice(v_inicial);
    free(lista_segmentos);
    free(lista_vertices);
}

void Cidade_escreverArvoreSvg(Cidade c, char t, FILE *arq) {
    pCidade cidade = (pCidade) c;

    if (t == 'q')
        Arvore_escreverSvg(cidade->arvoreQuadras, arq, Quadra_getDados);
    else if (t == 'h')
        Arvore_escreverSvg(cidade->arvoreHidrantes, arq, Hidrante_getDados);
    else if (t == 's')
        Arvore_escreverSvg(cidade->arvoreSemaforos, arq, Semaforo_getDados);
    else if (t == 't')
        Arvore_escreverSvg(cidade->arvoreRadioBases, arq, RadioBase_getDados);
    else if (t == 'p')
        Arvore_escreverSvg(cidade->arvorePredios, arq, Predio_getDados);
    else if (t == 'm')
        Arvore_escreverSvg(cidade->arvoreMuros, arq, Muro_getDados);
}

void Cidade_navegarArvore(Cidade c, char t) {
    pCidade cidade = (pCidade) c;

    char str[150], instrucao[10];
    Node node;
    char dados[150];
    char*(*Objeto_getDados)(Objeto objeto, char* dados);

    if (t == 'q') {
        node = Arvore_getRaiz(cidade->arvoreQuadras);
        Objeto_getDados = Quadra_getDados;
    } else if (t == 'h') {
        node = Arvore_getRaiz(cidade->arvoreHidrantes);
        Objeto_getDados = Hidrante_getDados;
    } else if (t == 's') {
        node = Arvore_getRaiz(cidade->arvoreSemaforos);
        Objeto_getDados = Semaforo_getDados;
    } else if (t == 't') {
        node = Arvore_getRaiz(cidade->arvoreRadioBases);
        Objeto_getDados = RadioBase_getDados;
    } else if (t == 'p') { 
        node = Arvore_getRaiz(cidade->arvorePredios);
        Objeto_getDados = Predio_getDados;
    } else if (t == 'm') {
        node = Arvore_getRaiz(cidade->arvoreMuros);
        Objeto_getDados = Muro_getDados;
    }

    while (true) {
        printf("- Navegar arvore\n");
        printf("- comando-> ");
        fgets(str, 150, stdin);
        sscanf(str, "%s", instrucao);

        if (strcmp(instrucao, "x") == 0) return;
        else if (strcmp(instrucao, "e") == 0) {
            if (Node_getEsq(node) != Arvore_getTNULL())
                node = Node_getEsq(node);
            else {
                printf("NULL\n");
                continue;
            }
        } else if (strcmp(instrucao, "d") == 0) {
            if (Node_getDir(node) != Arvore_getTNULL())
                node = Node_getDir(node);
            else {
                printf("NULL\n");
                continue;
            }
        } else if (strcmp(instrucao, "p") == 0) {
            if (Node_getPai(node) != NULL)
                node = Node_getPai(node);
            else {
                printf("NULL\n");
                continue;
            }
        } 

        if (node == Arvore_getTNULL()) {
            printf("NULL\n");
            continue;
        }
        printf("\nDADOS:\nCor: %s\n%s\n", Node_getCor(node), Objeto_getDados(Node_getObjeto(node), dados));
    }
}

/*
Moradores dos prédios inteiramente contidos na
região delimitada pelo polígono e as quadras que
estão ao menos parcialmente dentro da delimitada
pelo polígono.    
*/  
void Cidade_processarMPLG(Cidade c, Poligono poligono) { // TERMINAR DPS DE PRINTAR E ESCREVER NO ARQUIVO E SVG
    pCidade cidade = (pCidade) c;
    char dados[150];

    Node predios = Arvore_getRaiz(cidade->arvorePredios);
    forEach(predio, predios) {
        if (Node_getAux(predio) == 0) {
            Predio p = Node_getObjeto(predio);
            Retangulo r = criarRetangulo_Predio(p);
            if (RetanguloInternoPoligono(r, poligono)) {
                Node moradores = Predio_getMoradores(p);
                forEach(morador, moradores) {
                    if (Node_getAux(morador) == 0) {
                        Morador m = Node_getObjeto(morador);
                        printf("%s\n", Morador_getDados(m, dados));
                    }
                }
            }
            destruirRetangulo(r);
        }
    }

    Node quadras = Arvore_getRaiz(cidade->arvoreQuadras);
    forEach(quadra, quadras) {
        if (Node_getAux(quadra) == 0) {
            Quadra q = Node_getObjeto(quadra);
            Retangulo r = criarRetangulo_Quadra(q);
            if (RetanguloParcialmenteInternoPoligono(r, poligono)) {
                Node moradores = Quadra_getMoradores(q);
                forEach(morador, moradores) {
                    if (Node_getAux(morador) == 0) {
                        Morador m = Node_getObjeto(morador);
                        printf("%s\n", Morador_getDados(m, dados));
                    }
                }
            }
            destruirRetangulo(r);
        }
    }
}

// Fazer txt e svg
/*
Considere a região delimitada pelo polígono.
Remover as quadras que estejam inteiramente
contidas no poligono. Remover prédios
(inteiramente contidos no poligono) e respectivos
moradores, hidrantes, semáforos, rádios-bases.
*/
void Cidade_processarCATAC(Cidade c, Poligono poligono) {
    pCidade cidade = (pCidade) c;
    int index;

    Objeto* moradores_del = (Objeto*)malloc(Arvore_length(cidade->arvoreMoradores)*sizeof(Objeto));
    Objeto* predios_del = (Objeto*)malloc(Arvore_length(cidade->arvorePredios)*sizeof(Objeto));

    index = 0;
    int indexM = 0;
    Node predios = Arvore_getRaiz(cidade->arvorePredios);
    forEach(predio, predios) {
        if (Node_getAux(predio) == 0) {
            Predio p = Node_getObjeto(predio);
            Quadra q = Predio_getQuadra(p);
            Retangulo r = criarRetangulo_Predio(p);
            if (RetanguloInternoPoligono(r, poligono)) {

                Node moradores = Predio_getMoradores(p);
                forEach(morador, moradores) {
                    if (Node_getAux(morador) == 0) {
                        Morador m = Node_getObjeto(morador);
                        moradores_del[indexM] = m; indexM++;
                    }
                }
                predios_del[index] = p; index++;
            }
            destruirRetangulo(r);
        }
    }


    for (int i = 0; i < indexM; i++) {
        Predio_removerMorador(Morador_getPredio(moradores_del[i]), moradores_del[i]);
        Quadra_removerMorador(Morador_getQuadra(moradores_del[i]), moradores_del[i]);
        Cidade_removerObjeto(c, Morador_get_cpf(moradores_del[i]));
    }
    free(moradores_del);

    for (int i = 0; i < index; i++) {
        Quadra_removerPredio(Predio_getQuadra(predios_del[i]), predios_del[i]);
        _Cidade_removerPredioId(c, Predio_getId(predios_del[i]));
    }
    free(predios_del);



    Objeto* quadras_del = (Objeto*)malloc(Arvore_length(cidade->arvoreQuadras)*sizeof(Objeto));

    index = 0;
    Node quadras = Arvore_getRaiz(cidade->arvoreQuadras);
    forEach(quadra, quadras) {
        if (Node_getAux(quadra) == 0) {
            Quadra q = Node_getObjeto(quadra);
            Retangulo r = criarRetangulo_Quadra(q);
            if (RetanguloInternoPoligono(r, poligono)) {
                quadras_del[index] = q; index++;
            }
            destruirRetangulo(r);
        }
    }

    for (int i = 0; i < index; i++) {
        Cidade_removerObjeto(c, Quadra_get_cep(quadras_del[i]));
    }
    free(quadras_del);



    Objeto* hidrantes_del = (Objeto*)malloc(Arvore_length(cidade->arvoreHidrantes)*sizeof(Objeto));

    index = 0;
    Node hidrantes = Arvore_getRaiz(cidade->arvoreHidrantes);
    forEach(hidrante, hidrantes) {
        if (Node_getAux(hidrante) == 0) {
            Hidrante h = Node_getObjeto(hidrante);
            Ponto p = criarPonto(Hidrante_get_x(h), Hidrante_get_y(h));
            if (PontoInternoPoligono(p, poligono)) {
                hidrantes_del[index] = h; index++;
            }
            destruirPonto(p);
        }
    }
    
    for (int i = 0; i < index; i++) {
        
        Cidade_removerObjeto(c, Hidrante_get_id(hidrantes_del[i]));
    }
    free(hidrantes_del);



    Objeto* semaforos_del = (Objeto*)malloc(Arvore_length(cidade->arvoreSemaforos)*sizeof(Objeto));

    index = 0;
    Node semaforos = Arvore_getRaiz(cidade->arvoreSemaforos);
    forEach(semaforo, semaforos) {
        if (Node_getAux(semaforo) == 0) {
            Semaforo s = Node_getObjeto(semaforo);
            Ponto p = criarPonto(Semaforo_get_x(s), Semaforo_get_y(s));
            if (PontoInternoPoligono(p, poligono)) {
                semaforos_del[index] = s; index++;
            }
            destruirPonto(p);
        }
    }
    for (int i = 0; i < index; i++) {
        Cidade_removerObjeto(c, Semaforo_get_id(semaforos_del[i]));
    }
    free(semaforos_del);



    Objeto* radios_del = (Objeto*)malloc(Arvore_length(cidade->arvoreRadioBases)*sizeof(Objeto));

    index = 0;
    Node radiosBase = Arvore_getRaiz(cidade->arvoreRadioBases);
    forEach(radioBase, radiosBase) {
        if (Node_getAux(radioBase) == 0) {
            RadioBase rb = Node_getObjeto(radioBase);
            Ponto p = criarPonto(RadioBase_get_x(rb), RadioBase_get_y(rb));
            if (PontoInternoPoligono(p, poligono)) {
                radios_del[index] = rb; index++;
            }
            destruirPonto(p);
        }
    }
    for (int i = 0; i < index; i++) {
        Cidade_removerObjeto(c, RadioBase_get_id(radios_del[i]));
    }
    free(radios_del);
}


// Terminar txt e svg
/*
Estabelecimentos comerciais do tipo tp (ou de
qualquer tipo, caso *) que estão inteiramente
dentro da região delimitada pelo polígono.
*/
void Cidade_processarEPLG(Cidade c, Poligono poligono, char* tipo) {
    pCidade cidade = (pCidade) c;

    int index = 0;
    Node estabelecimentos = Arvore_getRaiz(cidade->arvoreEstabelecimentos);
    forEach(estabelecimento, estabelecimentos) {
        if (Node_getAux(estabelecimento) == 0) {
            Estabelecimento e = Node_getObjeto(estabelecimento);
            if (strcmp(Estabelecimento_getCodt(e), tipo) == 0 || strcmp("*", tipo) == 0) {
                Predio prd = Cidade_getPredio(c, Estabelecimento_getCep(e), Estabelecimento_getFace(e), Estabelecimento_getNum(e));
                if (prd != NULL) {
                    Retangulo r = criarRetangulo_Predio(prd);
                    if (RetanguloInternoPoligono(r, poligono)) {
                        printf("ESTABELECIMENTO %s\n", Estabelecimento_getCep(e));
                    }
                    destruirRetangulo(r);
                }
            }
        }
    }

}