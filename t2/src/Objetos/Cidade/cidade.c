#include "cidade.h"

typedef struct cidade {
    Lista listaForma;
    Lista listaQuadra;
    Lista listaHidrante;
    Lista listaSemaforo;
    Lista listaRadioBase;
    Lista listaTexto;
}*pCidade;

Cidade criarCidade() {
    Cidade c = malloc(sizeof(struct cidade));
    pCidade cidade = (pCidade) c;
    cidade->listaForma = criarLista(1000);
    cidade->listaQuadra = criarLista(1000);
    cidade->listaHidrante = criarLista(1000);
    cidade->listaSemaforo = criarLista(1000);
    cidade->listaRadioBase = criarLista(1000);
    cidade->listaTexto = criarLista(1000);
    return cidade;
}

void destruirCidade(Cidade c) {
    pCidade cidade = (pCidade) c;
    destruirLista(cidade->listaForma, destruirForma);
    destruirLista(cidade->listaQuadra, destruirQuadra);
    destruirLista(cidade->listaHidrante, destruirHidrante);
    destruirLista(cidade->listaSemaforo, destruirSemaforo);
    destruirLista(cidade->listaRadioBase, destruirRadioBase);
    destruirLista(cidade->listaTexto, destruirTexto);
    free(cidade);
}

void Cidade_setTamanhoMax(Cidade c, int i, int nq, int nh, int ns, int nr) {
    pCidade cidade = (pCidade) c;
    setLista_tamanhoMax(cidade->listaForma, i);
    setLista_tamanhoMax(cidade->listaQuadra, nq);
    setLista_tamanhoMax(cidade->listaHidrante, nh);
    setLista_tamanhoMax(cidade->listaSemaforo, ns);
    setLista_tamanhoMax(cidade->listaRadioBase, nr);
}

void Cidade_setForma(Cidade c, Forma forma) {
    pCidade cidade = (pCidade) c;
    inserirUltimo(cidade->listaForma, forma);
}

void Cidade_setQuadra(Cidade c, Quadra quadra) {
    pCidade cidade = (pCidade) c;
    inserirUltimo(cidade->listaQuadra, quadra);
}

void Cidade_setHidrante(Cidade c, Hidrante hidrante) {
    pCidade cidade = (pCidade) c;
    inserirUltimo(cidade->listaHidrante, hidrante);
}

void Cidade_setSemaforo(Cidade c, Semaforo semaforo) {
    pCidade cidade = (pCidade) c;
    inserirUltimo(cidade->listaSemaforo, semaforo);
}

void Cidade_setRadioBase(Cidade c, RadioBase radioBase) {
    pCidade cidade = (pCidade) c;
    inserirUltimo(cidade->listaRadioBase, radioBase);
}

void Cidade_setTexto(Cidade c, Texto texto) {
    pCidade cidade = (pCidade) c;
    inserirUltimo(cidade->listaTexto, texto);
}

Forma Cidade_getForma(Cidade c, char *id) {
    pCidade cidade = (pCidade) c;
    return encontrarObjeto(cidade->listaForma, id, formaEquals);
}

Quadra Cidade_getQuadra(Cidade c, char *id) {
    pCidade cidade = (pCidade) c;
    return encontrarObjeto(cidade->listaQuadra, id, quadraEquals);
}

Hidrante Cidade_getHidrante(Cidade c, char *id) {
    pCidade cidade = (pCidade) c;
    return encontrarObjeto(cidade->listaHidrante, id, hidranteEquals);
}

Semaforo Cidade_getSemaforo(Cidade c, char *id) {
    pCidade cidade = (pCidade) c;
    return encontrarObjeto(cidade->listaSemaforo, id, semaforoEquals);
}

RadioBase Cidade_getRadioBase(Cidade c, char *id) {
    pCidade cidade = (pCidade) c;
    return encontrarObjeto(cidade->listaRadioBase, id, radioBaseEquals);
}

bool Cidade_removerObjeto(Cidade c, char *id) {
    pCidade cidade = (pCidade) c;
    if(excluirObjeto(cidade->listaQuadra, id, quadraEquals, destruirQuadra))
        return true;
    else if(excluirObjeto(cidade->listaHidrante, id, hidranteEquals, destruirHidrante))
        return true;
    else if(excluirObjeto(cidade->listaSemaforo, id, semaforoEquals, destruirSemaforo))
        return true;
    else if(excluirObjeto(cidade->listaRadioBase, id, radioBaseEquals, destruirRadioBase))
        return true;
    return false;
}

// Duvidas ainda??
// dq
void Cidade_removerQuadrasInternasEquipamento(Cidade c, double px, double py, double dist, char *op, FILE *txt) {
    pCidade cidade = (pCidade) c;
    fprintf(txt, "-- CEP(s) REMOVIDOS --\n");
    Node node = getLista_primeiro(cidade->listaQuadra);
    if(node == NULL)
        return;

    if(strcmp(op, "L1") == 0) {
    
        // sim
        while(true) {
            Quadra q = getLista_ObjNode(node);
            Retangulo r = criarRetangulo(getQuadra_x(q), getQuadra_y(q), getQuadra_w(q), getQuadra_h(q), "", "", "");

            if(getLista_prox(node) == NULL) {
                if(retanguloInternoL1(px, py, r, dist)) {
                    fprintf(txt, "CEP -> %s\n", getQuadra_cep(q));
                    excluirLista_Node(cidade->listaQuadra, node, destruirQuadra);
                }
                destruirRetangulo(r);
                break;
            } else {
                node = getLista_prox(node);
                if(retanguloInternoL1(px, py, r, dist)) {
                    fprintf(txt, "CEP -> %s\n", getQuadra_cep(q));
                    excluirLista_Node(cidade->listaQuadra, getLista_ant(node), destruirQuadra);
                }
            }
            destruirRetangulo(r);
        }

    } else if(strcmp(op, "L2") == 0) {
        Circulo c = criarCirculo(px, py, dist, "", "", "");

        while(true) {
            Quadra q = getLista_ObjNode(node);
            Retangulo r = criarRetangulo(getQuadra_x(q), getQuadra_y(q), getQuadra_w(q), getQuadra_h(q), "", "", "");

            if(getLista_prox(node) == NULL) {
                if(retanguloInternoCirculo(r, c)) {
                    fprintf(txt, "CEP -> %s\n", getQuadra_cep(q));
                    excluirLista_Node(cidade->listaQuadra, node, destruirQuadra);
                }
                destruirRetangulo(r);
                break;
            } else {
                node = getLista_prox(node);
                if(retanguloInternoCirculo(r, c)) {
                    fprintf(txt, "CEP -> %s\n", getQuadra_cep(q));
                    excluirLista_Node(cidade->listaQuadra, getLista_ant(node), destruirQuadra);
                }
            }
            destruirRetangulo(r);
        }
        destruirCirculo(c);
    }
    fprintf(txt, "\n");
}

// cbq
void Cidade_setCstrkQuadrasInternasCirculo(Cidade cid, Circulo c, char *cstrk, FILE *txt) {
    pCidade cidade = (pCidade) cid;
    Node node = getLista_primeiro(cidade->listaQuadra);
    fprintf(txt, "-- CEP(s) QUADRAS PINTADAS --\n");
    for(node; node != NULL; node = getLista_prox(node)) {
        Quadra q = getLista_ObjNode(node);
        Retangulo r = criarRetangulo(getQuadra_x(q), getQuadra_y(q), getQuadra_w(q), getQuadra_h(q), "", "", "");
        if(retanguloInternoCirculo(r, c)) {
            setQuadra_cstrk(q, cstrk);
            fprintf(txt, "CEP -> %s\n", getQuadra_cep(q));
        }
        destruirRetangulo(r);
    }
}

// trns
void Cidade_deslocarEquipamentosInternosRetangulo(Cidade c, Retangulo r, double dx, double dy, FILE *txt) {
    pCidade cidade = (pCidade) c;
    Node node;
    fprintf(txt, "-- EQUIPAMENTOS URBANOS MOVIDOS --\n");

    node = getLista_primeiro(cidade->listaQuadra);
    for(node; node != NULL; node = getLista_prox(node)) {
        Quadra q = getLista_ObjNode(node);
        Retangulo rq = criarRetangulo(getQuadra_x(q), getQuadra_y(q), getQuadra_w(q), getQuadra_h(q), "", "", "");
        if(retanguloInternoRetangulo(rq, r)) {
            fprintf(txt, "CEP -> %s\n", getQuadra_cep(q));
            fprintf(txt, "(%lf, %lf) -> (%lf, %lf)\n\n",
                getQuadra_x(q),
                getQuadra_y(q),
                getQuadra_x(q) + dx,
                getQuadra_y(q) + dy
            );
            setQuadra_x(q, getQuadra_x(q) + dx);
            setQuadra_y(q, getQuadra_y(q) + dy);
        }
        destruirRetangulo(rq);
    }

    node = getLista_primeiro(cidade->listaHidrante);
    for(node; node != NULL; node = getLista_prox(node)) {
        Hidrante h = getLista_ObjNode(node);
        if(pontoInternoRetangulo(getHidrante_x(h), getHidrante_y(h), r)) {
            fprintf(txt, "ID -> %s\n", getHidrante_id(h));
            fprintf(txt, "(%lf, %lf) -> (%lf, %lf)\n\n",
                getHidrante_x(h),
                getHidrante_y(h),
                getHidrante_x(h) + dx,
                getHidrante_y(h) + dy
            );
            setHidrante_x(h, getHidrante_x(h) + dx);
            setHidrante_y(h, getHidrante_y(h) + dy);
        }
    }

    node = getLista_primeiro(cidade->listaSemaforo);
    for(node; node != NULL; node = getLista_prox(node)) {
        Semaforo s = getLista_ObjNode(node);
        if(pontoInternoRetangulo(getSemaforo_x(s), getSemaforo_y(s), r)) {
            fprintf(txt, "ID -> %s\n", getSemaforo_id(s));
            fprintf(txt, "(%lf, %lf) -> (%lf, %lf)\n\n",
                getSemaforo_x(s),
                getSemaforo_y(s),
                getSemaforo_x(s) + dx,
                getSemaforo_y(s) + dy
            );
            setSemaforo_x(s, getSemaforo_x(s) + dx);
            setSemaforo_y(s, getSemaforo_y(s) + dy);
        }
    }

    node = getLista_primeiro(cidade->listaRadioBase);
    for(node; node != NULL; node = getLista_prox(node)) {
        RadioBase rb = getLista_ObjNode(node);
        if(pontoInternoRetangulo(getRadioBase_x(rb), getRadioBase_y(rb), r)) {
            fprintf(txt, "ID -> %s\n", getRadioBase_id(rb));
            fprintf(txt, "(%lf, %lf) -> (%lf, %lf)\n\n",
                getRadioBase_x(rb),
                getRadioBase_y(rb),
                getRadioBase_x(rb) + dx,
                getRadioBase_y(rb) + dy
            );
            setRadioBase_x(rb, getRadioBase_x(rb) + dx);
            setRadioBase_y(rb, getRadioBase_y(rb) + dy);
        }
    }
}

// Usado apenas para o .geo
void Cidade_escreverSvg(Cidade c, FILE *svg) {
    pCidade cidade = (pCidade) c;
    Node node;
    
    node = getLista_primeiro(cidade->listaForma);
    for(node; node != NULL; node = getLista_prox(node)) {
        Forma f = getLista_ObjNode(node);
        escreverForma_svg(f, svg);
    }

    node = getLista_primeiro(cidade->listaTexto);
    for(node; node != NULL; node = getLista_prox(node)) {
        Texto t = getLista_ObjNode(node);
        escreverTexto_svg(t, svg);
    }

    node = getLista_primeiro(cidade->listaQuadra);
    for(node; node != NULL; node = getLista_prox(node)) {
        Quadra q = getLista_ObjNode(node);
        escreverQuadra_svg(q, svg);
    }

    node = getLista_primeiro(cidade->listaHidrante);
    for(node; node != NULL; node = getLista_prox(node)) {
        Hidrante h = getLista_ObjNode(node);
        escreverHidrante_svg(h, svg);
    }

    node = getLista_primeiro(cidade->listaSemaforo);
    for(node; node != NULL; node = getLista_prox(node)) {
        Semaforo s = getLista_ObjNode(node);
        escreverSemaforo_svg(s, svg);
    }

    node = getLista_primeiro(cidade->listaRadioBase);
    for(node; node != NULL; node = getLista_prox(node)) {
        RadioBase rb = getLista_ObjNode(node);
        escreverRadioBase_svg(rb, svg);
    }   
}

void Cidade_escreverQuadrasEquipamentosSvg(Cidade c, FILE *svg) {
    pCidade cidade = (pCidade) c;
    Node node;

    node = getLista_primeiro(cidade->listaQuadra);
    for(node; node != NULL; node = getLista_prox(node)) {
        Quadra q = getLista_ObjNode(node);
        escreverQuadra_svg(q, svg);
    }

    node = getLista_primeiro(cidade->listaHidrante);
    for(node; node != NULL; node = getLista_prox(node)) {
        Hidrante h = getLista_ObjNode(node);
        escreverHidrante_svg(h, svg);
    }

    node = getLista_primeiro(cidade->listaSemaforo);
    for(node; node != NULL; node = getLista_prox(node)) {
        Semaforo s = getLista_ObjNode(node);
        escreverSemaforo_svg(s, svg);
    }

    node = getLista_primeiro(cidade->listaRadioBase);
    for(node; node != NULL; node = getLista_prox(node)) {
        RadioBase rb = getLista_ObjNode(node);
        escreverRadioBase_svg(rb, svg);
    } 
}

void Cidade_escreverFormasEnvoltas(Cidade c, FILE *svg, char *cor) {
    pCidade cidade = (pCidade) c;
    Node node = getLista_primeiro(cidade->listaForma);
    for(node; node != NULL; getLista_prox(node)) {
        Forma f = getLista_ObjNode(node);
        Forma_escreverFormaEnvoltaSvg(f, svg, cor);
    }
}