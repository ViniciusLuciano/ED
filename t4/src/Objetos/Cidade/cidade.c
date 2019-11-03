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

    // Separar?
    cidade->tabelaHashEstabelecimentos = criarTabelaHash(1000, estabelecimentoEquals, Estabelecimento_getChave, destruirEstabelecimento);
    cidade->tabelaHashTiposEstabelecimento = criarTabelaHash(1000, tipoEstabelecimentoEquals, TipoEstabelecimento_getChave, destruirTipoEstabelecimento);
    cidade->tabelaHashPessoas = criarTabelaHash(1000, pessoaEquals, Pessoa_getChave, destruirPessoa);
    cidade->tabelaHashMoradores = criarTabelaHash(1000, moradorEquals, Morador_getChave, destruirMorador);

    cidade->arvoreFormas = criarArvore(Forma_compararChave, Forma_getSize(), destruirForma);
    cidade->arvoreQuadras = criarArvore(Quadra_compararChave, Quadra_getSize(), destruirQuadra);
    cidade->arvoreHidrantes = criarArvore(Hidrante_compararChave, Hidrante_getSize(), destruirHidrante);
    cidade->arvoreSemaforos = criarArvore(Semaforo_compararChave, Semaforo_getSize(), destruirSemaforo);
    cidade->arvoreRadioBases = criarArvore(RadioBase_compararChave, RadioBase_getSize(), destruirRadioBase);
    cidade->arvorePredios = criarArvore(Predio_compararChave, Predio_getSize(), destruirPredio);
    cidade->arvoreMuros = criarArvore(Muro_compararChave, Muro_getSize(), destruirMuro);
    cidade->arvoreTextos = criarArvore(Texto_compararChave, Texto_getSize(), destruirTexto);
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

    destruirTabelaHash(cidade->tabelaHashFormas);
    destruirTabelaHash(cidade->tabelaHashQuadras);
    destruirTabelaHash(cidade->tabelaHashHidrantes);
    destruirTabelaHash(cidade->tabelaHashSemaforos);
    destruirTabelaHash(cidade->tabelaHashRadiosBase);
    destruirTabelaHash(cidade->tabelaHashPredios);

    destruirTabelaHash(cidade->tabelaHashEstabelecimentos);
    destruirTabelaHash(cidade->tabelaHashTiposEstabelecimento);
    destruirTabelaHash(cidade->tabelaHashPessoas);
    destruirTabelaHash(cidade->tabelaHashMoradores);

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
}

void Cidade_setMuro(Cidade c, Muro muro) {
    pCidade cidade = (pCidade) c;
    Arvore_inserir(cidade->arvoreMuros, muro);
}

void Cidade_setEstabelecimento(Cidade c, Estabelecimento estabelecimento) {
    pCidade cidade = (pCidade) c;
    TabelaHash_inserir(cidade->tabelaHashEstabelecimentos, estabelecimento);
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
    char dados[150];
    printf("a %s\n", Morador_getDados(morador, dados));
    TabelaHash_inserir(cidade->tabelaHashMoradores, morador);
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

bool Cidade_removerObjeto(Cidade c, char *id) {
    pCidade cidade = (pCidade) c;
    Hidrante h;
    RadioBase rb;
    Semaforo s;
    Quadra q;
    
    if((h = Cidade_getHidrante(c, id)) != NULL) {

        TabelaHash_removerObjeto(cidade->tabelaHashHidrantes, id);
        Arvore_removerObjeto(cidade->arvoreHidrantes, h);
        return true;

    } else if((rb = Cidade_getRadioBase(c, id)) != NULL) {

        TabelaHash_removerObjeto(cidade->tabelaHashRadiosBase, id);
        Arvore_removerObjeto(cidade->arvoreRadioBases, rb);
        return true;

    } else if((s = Cidade_getSemaforo(c, id)) != NULL) {

        TabelaHash_removerObjeto(cidade->tabelaHashSemaforos, id);
        Arvore_removerObjeto(cidade->arvoreSemaforos, s);
        return true;

    } else if((q = Cidade_getQuadra(c, id)) != NULL) {

        TabelaHash_removerObjeto(cidade->tabelaHashQuadras, id);
        Arvore_removerObjeto(cidade->arvoreQuadras, q);
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



void deslocarEquipamentosInternosRetanguloAux(pCidade c, Retangulo r, double dx, double dy, FILE* txt, Node n, char* tipo) {

    Objeto o = Node_getObjeto(n);
    Arvore a; 
    Objeto objCopy;

    if (o == NULL) return;

    double x, y;
    double rx = Retangulo_get_x(r), ry = Retangulo_get_y(r);
    double rx_max = Retangulo_get_max_x(r), ry_max = Retangulo_get_max_y(r);
    char* id;

    if (strcmp(tipo, "quadra") == 0) {

        Retangulo rq = criarRetangulo(Quadra_get_x(o), Quadra_get_y(o), Quadra_get_w(o), Quadra_get_h(o), "", "", "");

        if(retanguloInternoRetangulo(rq, r)) {
            Quadra qc = objetoCopy(o, Quadra_getSize());
            fprintf(txt, "CEP -> %s\n", Quadra_get_cep(o));
            fprintf(txt, "(%.2lf, %.2lf) -> (%.2lf, %.2lf)\n\n",
                Quadra_get_x(o),
                Quadra_get_y(o),
                Quadra_get_x(o) + dx,
                Quadra_get_y(o) + dy
            );
            Quadra_set_x(qc, Quadra_get_x(o) + dx);
            Quadra_set_y(qc, Quadra_get_y(o) + dy);

            deslocarEquipamentosInternosRetanguloAux(c, r, dx, dy, txt, Node_getDir(n), tipo);
            deslocarEquipamentosInternosRetanguloAux(c, r, dx, dy, txt, Node_getEsq(n), tipo); 

            Arvore_removerObjeto(c->arvoreQuadras, o);
            Arvore_inserir(c->arvoreQuadras, qc);
        } else {
            deslocarEquipamentosInternosRetanguloAux(c, r, dx, dy, txt, Node_getDir(n), tipo);
            deslocarEquipamentosInternosRetanguloAux(c, r, dx, dy, txt, Node_getEsq(n), tipo);
        }
        destruirRetangulo(rq);

    } else {
        if (strcmp(tipo, "hidrante") == 0) {

            x = Hidrante_get_x(o);
            y = Hidrante_get_y(o);
            id = Hidrante_get_id(o);
            a = c->arvoreHidrantes;

        } else if (strcmp(tipo, "semaforo") == 0) {

            x = Semaforo_get_x(o);
            y = Semaforo_get_y(o);
            id = Semaforo_get_id(o);
            a = c->arvoreSemaforos;

        } else if (strcmp(tipo, "radioBase") == 0) {

            x = RadioBase_get_x(o);
            y = RadioBase_get_y(o);
            id = RadioBase_get_id(o);
            a = c->arvoreRadioBases;
        }

        if (x >= rx && x <= rx_max && y >= ry && y <= ry_max) {
            if (strcmp(tipo, "hidrante") == 0) {

                objCopy = objetoCopy(o, Hidrante_getSize());
                Hidrante_set_x(objCopy, Hidrante_get_x(o) + dx);
                Hidrante_set_y(objCopy, Hidrante_get_y(o) + dy);

            } else if (strcmp(tipo, "semaforo") == 0) {

                objCopy = objetoCopy(o, Semaforo_getSize());
                Semaforo_set_x(objCopy, Semaforo_get_x(o) + dx);
                Semaforo_set_y(objCopy, Semaforo_get_y(o) + dy);

            } else if (strcmp(tipo, "radioBase") == 0) {

                objCopy = objetoCopy(o, RadioBase_getSize());
                RadioBase_set_x(objCopy, RadioBase_get_x(o) + dx);
                RadioBase_set_y(objCopy, RadioBase_get_y(o) + dy);
            }

            fprintf(txt, "ID -> %s\n", id);
            fprintf(txt, "(%.2lf, %.2lf) -> (%.2lf, %.2lf)\n\n",
                x,
                y,
                x + dx,
                y + dy
            );
            
            deslocarEquipamentosInternosRetanguloAux(c, r, dx, dy, txt, Node_getDir(n), tipo);
            deslocarEquipamentosInternosRetanguloAux(c, r, dx, dy, txt, Node_getEsq(n), tipo);

            Arvore_removerObjeto(a, o);
            Arvore_inserir(a, objCopy);

        } else if (x > rx_max) {
            deslocarEquipamentosInternosRetanguloAux(c, r, dx, dy, txt, Node_getEsq(n), tipo);
        } else if (x < rx) {
            deslocarEquipamentosInternosRetanguloAux(c, r, dx, dy, txt, Node_getDir(n), tipo);
        } else {
            deslocarEquipamentosInternosRetanguloAux(c, r, dx, dy, txt, Node_getDir(n), tipo);
            deslocarEquipamentosInternosRetanguloAux(c, r, dx, dy, txt, Node_getEsq(n), tipo);  
        }
    }
}

// trns
void Cidade_deslocarEquipamentosInternosRetangulo(Cidade c, Retangulo r, double dx, double dy, FILE *txt) {
    pCidade cidade = (pCidade) c;   
    int i;
    fprintf(txt, "-- EQUIPAMENTOS URBANOS MOVIDOS --\n");
    deslocarEquipamentosInternosRetanguloAux(cidade, r, dx, dy, txt, Arvore_getRaiz(cidade->arvoreQuadras), "quadra");
    deslocarEquipamentosInternosRetanguloAux(cidade, r, dx, dy, txt, Arvore_getRaiz(cidade->arvoreHidrantes), "hidrante");
    deslocarEquipamentosInternosRetanguloAux(cidade, r, dx, dy, txt, Arvore_getRaiz(cidade->arvoreSemaforos), "semaforo");
    deslocarEquipamentosInternosRetanguloAux(cidade, r, dx, dy, txt, Arvore_getRaiz(cidade->arvoreRadioBases), "radioBase");
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
    
    // Mudar isso dps zzzzzzzzzzzzzz
    // i = lista_getPrimeiro(cidade->listaPredio);
    // for(i; i!= -1; i = lista_getProx(cidade->listaPredio, i)) {
    //     Predio prd = lista_getObjPosic(cidade->listaPredio, i);
    //     Quadra q = lista_getObjeto(cidade->listaQuadra, Predio_getCep(prd), quadraEquals);
    //     if(q != NULL)
    //         Predio_escreverSvg(prd, Quadra_get_x(q), Quadra_get_y(q), Quadra_get_w(q), Quadra_get_h(q), svg);
    // }
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

void Cidade_processarBombaRaioLuminoso(Cidade c, double x, double y, FILE *svg) {
    pCidade cidade = (pCidade) c;
    Ponto pontoMin = criarPonto(x, y);
    Ponto pontoMax = criarPonto(x, y);
    int i, tamListaSegmentos = (lista_length(cidade->listaPredio)*4) + lista_length(cidade->listaMuro) + 4;

    Segmento* lista_segmentos = (Segmento*)malloc(tamListaSegmentos*sizeof(Segmento));

    // Aqui será definida a lista de segmentos
    i = lista_getPrimeiro(cidade->listaPredio);
    int index = 0;
    for(i; i != -1; i = lista_getProx(cidade->listaPredio, i)) {
        Predio p = lista_getObjPosic(cidade->listaPredio, i);

        Ponto_setMin(pontoMin, Predio_get_x(p), Predio_get_y(p));
        Ponto_setMax(pontoMax, Predio_get_x_max(p), Predio_get_y_max(p));

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

        lista_segmentos[index] = s1; index++;
        lista_segmentos[index] = s2; index++;
        lista_segmentos[index] = s3; index++;
        lista_segmentos[index] = s4; index++;
    }

    i = lista_getPrimeiro(cidade->listaMuro);
    for(i; i != -1; i = lista_getProx(cidade->listaMuro, i)) {
        Muro m = lista_getObjPosic(cidade->listaMuro, i);

        // Eu nao sei onde esta os pontos do muro, portanto tenho que testar os dois ;/
        Ponto p1 = Muro_get_p1(m);
        Ponto p2 = Muro_get_p2(m);

        Ponto_setMin(pontoMin, Ponto_get_x(p1), Ponto_get_y(p1));
        Ponto_setMin(pontoMin, Ponto_get_x(p2), Ponto_get_y(p2));
        Ponto_setMax(pontoMax, Ponto_get_x(p1), Ponto_get_y(p1));
        Ponto_setMax(pontoMax, Ponto_get_x(p2), Ponto_get_y(p2));

        if(Ponto_get_x(p1) == x && Ponto_get_x(p2) == x || Ponto_get_y(p1) == y && Ponto_get_y(p2) == y) 
            continue;

        Vertice v1 = criarVertice(Ponto_get_x(p1), Ponto_get_y(p1), x, y);
        Vertice v2 = criarVertice(Ponto_get_x(p2), Ponto_get_y(p2), x, y);

        Segmento s = criarSegmento(v1, v2);

        Segmento_set_inicio_vertices(s);
        
        lista_segmentos[index] = s; index++;
    }

    tamListaSegmentos = index + 4;

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

            Vertice v_inicio = Vertice_get_inicio(Segmento_get_v1(s)) ? Segmento_get_v1(s) : Segmento_get_v2(s);
            Vertice v_final = Vertice_get_inicio(Segmento_get_v1(s)) ? Segmento_get_v2(s) : Segmento_get_v1(s);
            
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
            Vertice_set_s(v1, s);
            Vertice_set_s(v2, s);

            lista_vertices[index] = v1; index++;
            lista_vertices[index] = v2; index++;
        }
    }

    qsort(lista_vertices, tamListaVertices, sizeof(Vertice), comparador);
    // heapsortMaior(lista_vertices, tamListaVertices, tamListaVertices, Vertice_get_angulo);
    
    // A partir daqui será varrido todos os vertices no sentido horario começando pela esquerda
    Lista segmentos_ativos = criarLista((int)tamListaVertices/2);
    Vertice biombo = criarVertice(Vertice_get_x(lista_vertices[0]), Vertice_get_y(lista_vertices[0]), x, y);
    Vertice_set_s(biombo, Vertice_get_s(lista_vertices[0]));

    for(int i = 0; i < tamListaVertices; i++) {

        Vertice v = lista_vertices[i];
        Segmento sv = Vertice_get_s(v);
        Segmento s_formado_v = buscarSegmentoFormadoComVertice(x, y, v, pontoMin, pontoMax);
        Segmento seg_mais_prox = NULL;

        int j = lista_getPrimeiro(segmentos_ativos);

        // Definindo a menor distancia entre centro e o vertice como MAX
        double menor_dist = INT_MAX;
        for(j; j != -1; j = lista_getProx(segmentos_ativos, j)) {
            Segmento s = lista_getObjPosic(segmentos_ativos, j);
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

        if(Vertice_get_inicio(v)) {
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
                Segmento s1 = criarSegmento(biombo, v_intersec);
                Segmento s2 = criarSegmento(v_intersec, v);

                svg_escreverTriangulo(svg, x, y, biombo, v_intersec);
                //svg_escreverTriangulo(svg, x, y, v_intersec, v);

                biombo = v;
                destruirPonto(intersec_biombo);
            }

            lista_inserirUltimo(segmentos_ativos, sv);

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

                    Segmento s1 = criarSegmento(biombo, v);
                    Segmento s2 = criarSegmento(v, v_intersec);

                    svg_escreverTriangulo(svg, x, y, v, v_intersec);
                    svg_escreverTriangulo(svg, x, y, biombo, v);

                    biombo = v_intersec;
                    Vertice_set_s(biombo, seg_mais_prox);
                    destruirPonto(intersec_biombo);
                 } else {
                     Segmento s = criarSegmento(biombo, v);
                     svg_escreverTriangulo(svg, x, y, biombo, v);
                     biombo = v;
                 }
            }

            lista_excluirObjetoMemoria(segmentos_ativos, sv);
        }

    }
    
    for(int i = 0; i < tamListaVertices; i++) destruirVertice(lista_vertices[i]);
    // lista_destruir(segmentos_ativos, destruirSegmento);
    destruirPonto(pontoMin);
    destruirPonto(pontoMax);
    destruirVertice(v_final);
    destruirVertice(v_inicial);
    free(lista_segmentos);
    free(lista_vertices);
}

void Cidade_escreverArvoreSvg(Cidade c, char t, char* arq) {
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