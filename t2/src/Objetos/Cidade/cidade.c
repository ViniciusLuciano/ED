#include "cidade.h"

typedef struct cidade {
    Lista listaForma;
    Lista listaQuadra;
    Lista listaHidrante;
    Lista listaSemaforo;
    Lista listaRadioBase;
    Lista listaTexto;
}*pCidade;

Cidade criarCidade(int i, int nq, int nh, int ns, int nr) {
    Cidade c = malloc(sizeof(struct cidade));
    pCidade cidade = (pCidade) c;
    cidade->listaForma = criarLista(i);
    cidade->listaQuadra = criarLista(nq);
    cidade->listaHidrante = criarLista(nh);
    cidade->listaSemaforo = criarLista(ns);
    cidade->listaRadioBase = criarLista(nr);
    cidade->listaTexto = criarLista(1000);
    return cidade;
}

void destruirCidade(Cidade c) {
    pCidade cidade = (pCidade) c;
    lista_destruir(cidade->listaForma, destruirForma);
    lista_destruir(cidade->listaQuadra, destruirQuadra);
    lista_destruir(cidade->listaHidrante, destruirHidrante);
    lista_destruir(cidade->listaSemaforo, destruirSemaforo);
    lista_destruir(cidade->listaRadioBase, destruirRadioBase);
    lista_destruir(cidade->listaTexto, destruirTexto);
    free(cidade);
}

void Cidade_setForma(Cidade c, Forma forma) {
    pCidade cidade = (pCidade) c;
    lista_inserirUltimo(cidade->listaForma, forma);
}

void Cidade_setQuadra(Cidade c, Quadra quadra) {
    pCidade cidade = (pCidade) c;
    lista_inserirUltimo(cidade->listaQuadra, quadra);
}

void Cidade_setHidrante(Cidade c, Hidrante hidrante) {
    pCidade cidade = (pCidade) c;
    lista_inserirUltimo(cidade->listaHidrante, hidrante);
}

void Cidade_setSemaforo(Cidade c, Semaforo semaforo) {
    pCidade cidade = (pCidade) c;
    lista_inserirUltimo(cidade->listaSemaforo, semaforo);
}

void Cidade_setRadioBase(Cidade c, RadioBase radioBase) {
    pCidade cidade = (pCidade) c;
    lista_inserirUltimo(cidade->listaRadioBase, radioBase);
}

void Cidade_setTexto(Cidade c, Texto texto) {
    pCidade cidade = (pCidade) c;
    lista_inserirUltimo(cidade->listaTexto, texto);
}

Forma Cidade_getForma(Cidade c, char *id) {
    pCidade cidade = (pCidade) c;
    return lista_getObjeto(cidade->listaForma, id, formaEquals);
}

Quadra Cidade_getQuadra(Cidade c, char *id) {
    pCidade cidade = (pCidade) c;
    return lista_getObjeto(cidade->listaQuadra, id, quadraEquals);
}

Hidrante Cidade_getHidrante(Cidade c, char *id) {
    pCidade cidade = (pCidade) c;
    return lista_getObjeto(cidade->listaHidrante, id, hidranteEquals);
}

Semaforo Cidade_getSemaforo(Cidade c, char *id) {
    pCidade cidade = (pCidade) c;
    return lista_getObjeto(cidade->listaSemaforo, id, semaforoEquals);
}

RadioBase Cidade_getRadioBase(Cidade c, char *id) {
    pCidade cidade = (pCidade) c;
    return lista_getObjeto(cidade->listaRadioBase, id, radioBaseEquals);
}

bool Cidade_removerObjeto(Cidade c, char *id) {
    pCidade cidade = (pCidade) c;
    if(lista_excluirObjeto(cidade->listaQuadra, id, quadraEquals, destruirQuadra))
        return true;
    else if(lista_excluirObjeto(cidade->listaHidrante, id, hidranteEquals, destruirHidrante))
        return true;
    else if(lista_excluirObjeto(cidade->listaSemaforo, id, semaforoEquals, destruirSemaforo))
        return true;
    else if(lista_excluirObjeto(cidade->listaRadioBase, id, radioBaseEquals, destruirRadioBase))
        return true;
    return false;
}

// Duvidas ainda??
// dq
void Cidade_removerQuadrasInternasEquipamento(Cidade c, double px, double py, double dist, char *op, FILE *txt) {
    pCidade cidade = (pCidade) c;
    fprintf(txt, "-- CEP(s) REMOVIDOS --\n");
    
    int i = lista_getPrimeiro(cidade->listaQuadra);
    if(i == -1)
        return;

    if(strcmp(op, "L1") == 0) {
    
        // sim
        while(true) {
            Quadra q = lista_getObjPosic(cidade->listaQuadra, i);
            Retangulo r = criarRetangulo(Quadra_get_x(q), Quadra_get_y(q), Quadra_get_w(q), Quadra_get_h(q), "", "", "");

            if(lista_getProx(cidade->listaQuadra, i) == -1) {
                if(retanguloInternoL1(px, py, r, dist)) {
                    fprintf(txt, "CEP -> %s\n", Quadra_get_cep(q));
                    lista_excluirPosic(cidade->listaQuadra, i, destruirQuadra);
                }
                destruirRetangulo(r);
                break;
            } else {
                i = lista_getProx(cidade->listaQuadra, i);
                if(retanguloInternoL1(px, py, r, dist)) {
                    fprintf(txt, "CEP -> %s\n", Quadra_get_cep(q));
                    lista_excluirPosic(cidade->listaQuadra, lista_getAnt(cidade->listaQuadra, i), destruirQuadra);
                }
            }
            destruirRetangulo(r);
        }

    } else if(strcmp(op, "L2") == 0) {
        Circulo c = criarCirculo(px, py, dist, "", "", "");

        while(true) {
            Quadra q = lista_getObjPosic(cidade->listaQuadra, i);
            Retangulo r = criarRetangulo(Quadra_get_x(q), Quadra_get_y(q), Quadra_get_w(q), Quadra_get_h(q), "", "", "");

            if(lista_getProx(cidade->listaQuadra, i) == -1) {
                if(retanguloInternoCirculo(r, c)) {
                    fprintf(txt, "CEP -> %s\n", Quadra_get_cep(q));
                    lista_excluirPosic(cidade->listaQuadra, i, destruirQuadra);
                }
                destruirRetangulo(r);
                break;
            } else {
                i = lista_getProx(cidade->listaQuadra, i);
                if(retanguloInternoCirculo(r, c)) {
                    fprintf(txt, "CEP -> %s\n", Quadra_get_cep(q));
                    lista_excluirPosic(cidade->listaQuadra, lista_getAnt(cidade->listaQuadra, i), destruirQuadra);
                }
            }
            destruirRetangulo(r);
        }
        destruirCirculo(c);
    }
    fprintf(txt, "----------------------\n\n");
}

// cbq
void Cidade_setCstrkQuadrasInternasCirculo(Cidade cid, Circulo c, char *cstrk, FILE *txt) {
    pCidade cidade = (pCidade) cid;
    fprintf(txt, "-- CEP(s) QUADRAS PINTADAS --\n");

    int i = lista_getPrimeiro(cidade->listaQuadra);
    for(i; i != -1; i = lista_getProx(cidade->listaQuadra, i)) {
        Quadra q = lista_getObjPosic(cidade->listaQuadra, i);
        Retangulo r = criarRetangulo(Quadra_get_x(q), Quadra_get_y(q), Quadra_get_w(q), Quadra_get_h(q), "", "", "");
        if(retanguloInternoCirculo(r, c)) {
            Quadra_set_cstrk(q, cstrk);
            fprintf(txt, "CEP -> %s\n", Quadra_get_cep(q));
        }
        destruirRetangulo(r);
    }

    fprintf(txt, "-----------------------------\n\n");
}

// trns
void Cidade_deslocarEquipamentosInternosRetangulo(Cidade c, Retangulo r, double dx, double dy, FILE *txt) {
    pCidade cidade = (pCidade) c;
    int i;
    fprintf(txt, "-- EQUIPAMENTOS URBANOS MOVIDOS --\n");

    i = lista_getPrimeiro(cidade->listaQuadra);
    for(i; i != -1; i = lista_getProx(cidade->listaQuadra, i)) {
        Quadra q = lista_getObjPosic(cidade->listaQuadra, i);
        Retangulo rq = criarRetangulo(Quadra_get_x(q), Quadra_get_y(q), Quadra_get_w(q), Quadra_get_h(q), "", "", "");
        if(retanguloInternoRetangulo(rq, r)) {
            fprintf(txt, "CEP -> %s\n", Quadra_get_cep(q));
            fprintf(txt, "(%.2lf, %.2lf) -> (%.2lf, %.2lf)\n\n",
                Quadra_get_x(q),
                Quadra_get_y(q),
                Quadra_get_x(q) + dx,
                Quadra_get_y(q) + dy
            );
            Quadra_set_x(q, Quadra_get_x(q) + dx);
            Quadra_set_y(q, Quadra_get_y(q) + dy);
        }
        destruirRetangulo(rq);
    }

    i = lista_getPrimeiro(cidade->listaHidrante);
    for(i; i != -1; i = lista_getProx(cidade->listaHidrante, i)) {
        Hidrante h = lista_getObjPosic(cidade->listaHidrante, i);
        if(pontoInternoRetangulo(Hidrante_get_x(h), Hidrante_get_y(h), r)) {
            fprintf(txt, "ID -> %s\n", Hidrante_get_id(h));
            fprintf(txt, "(%.2lf, %.2lf) -> (%.2lf, %.2lf)\n\n",
                Hidrante_get_x(h),
                Hidrante_get_y(h),
                Hidrante_get_x(h) + dx,
                Hidrante_get_y(h) + dy
            );
            Hidrante_set_x(h, Hidrante_get_x(h) + dx);
            Hidrante_set_y(h, Hidrante_get_y(h) + dy);
        }
    }

    i = lista_getPrimeiro(cidade->listaSemaforo);
    for(i; i != -1; i = lista_getProx(cidade->listaSemaforo, i)) {
        Semaforo s = lista_getObjPosic(cidade->listaSemaforo, i);
        if(pontoInternoRetangulo(Semaforo_get_x(s), Semaforo_get_y(s), r)) {
            fprintf(txt, "ID -> %s\n", Semaforo_get_id(s));
            fprintf(txt, "(%.2lf, %.2lf) -> (%.2lf, %.2lf)\n\n",
                Semaforo_get_x(s),
                Semaforo_get_y(s),
                Semaforo_get_x(s) + dx,
                Semaforo_get_y(s) + dy
            );
            Semaforo_set_x(s, Semaforo_get_x(s) + dx);
            Semaforo_set_y(s, Semaforo_get_y(s) + dy);
        }
    }

    i = lista_getPrimeiro(cidade->listaRadioBase);
    for(i; i != -1; i = lista_getProx(cidade->listaRadioBase, i)) {
        RadioBase rb = lista_getObjPosic(cidade->listaRadioBase, i);
        if(pontoInternoRetangulo(RadioBase_get_x(rb), RadioBase_get_y(rb), r)) {
            fprintf(txt, "ID -> %s\n", RadioBase_get_id(rb));
            fprintf(txt, "(%.2lf, %.2lf) -> (%.2lf, %.2lf)\n\n",
                RadioBase_get_x(rb),
                RadioBase_get_y(rb),
                RadioBase_get_x(rb) + dx,
                RadioBase_get_y(rb) + dy
            );
            RadioBase_set_x(rb, RadioBase_get_x(rb) + dx);
            RadioBase_set_y(rb, RadioBase_get_y(rb) + dy);
        }
    }
    fprintf(txt, "----------------------------------\n");
}

// Usado apenas para o .geo
void Cidade_escreverSvg(Cidade c, FILE *svg) {
    pCidade cidade = (pCidade) c;
    int i;

    i = lista_getPrimeiro(cidade->listaForma);
    for(i; i != -1; i = lista_getProx(cidade->listaForma, i)) {
        Forma f = lista_getObjPosic(cidade->listaForma, i);
        Forma_escreverSvg(f, svg);
    }

    i = lista_getPrimeiro(cidade->listaTexto);
    for(i; i != -1; i = lista_getProx(cidade->listaTexto, i)) {
        Texto t = lista_getObjPosic(cidade->listaTexto, i);
        Texto_escreverSvg(t, svg);
    }

    i = lista_getPrimeiro(cidade->listaQuadra);
    for(i; i != -1; i = lista_getProx(cidade->listaQuadra, i)) {
        Quadra q = lista_getObjPosic(cidade->listaQuadra, i);
        Quadra_escreverSvg(q, svg);
    }

    i = lista_getPrimeiro(cidade->listaHidrante);
    for(i; i != -1; i = lista_getProx(cidade->listaHidrante, i)) {
        Hidrante h = lista_getObjPosic(cidade->listaHidrante, i);
        Hidrante_escreverSvg(h, svg);
    }

    i = lista_getPrimeiro(cidade->listaSemaforo);
    for(i; i != -1; i = lista_getProx(cidade->listaSemaforo, i)) {
        Semaforo s = lista_getObjPosic(cidade->listaSemaforo, i);
        Semaforo_escreverSvg(s, svg);
    }

    i = lista_getPrimeiro(cidade->listaRadioBase);
    for(i; i != -1; i = lista_getProx(cidade->listaRadioBase, i)) {
        RadioBase rb = lista_getObjPosic(cidade->listaRadioBase, i);
        RadioBase_escreverSvg(rb, svg);
    }   
}

void Cidade_escreverQuadrasEquipamentosSvg(Cidade c, FILE *svg) {
    pCidade cidade = (pCidade) c;
    int i;

    i = lista_getPrimeiro(cidade->listaQuadra);
    for(i; i!= -1; i = lista_getProx(cidade->listaQuadra, i)) {
        Quadra q = lista_getObjPosic(cidade->listaQuadra, i);
        Quadra_escreverSvg(q, svg);
    }

    i = lista_getPrimeiro(cidade->listaHidrante);
    for(i; i!= -1; i = lista_getProx(cidade->listaHidrante, i)) {
        Hidrante h = lista_getObjPosic(cidade->listaHidrante, i);
        Hidrante_escreverSvg(h, svg);
    }

    i = lista_getPrimeiro(cidade->listaSemaforo);
    for(i; i!= -1; i = lista_getProx(cidade->listaSemaforo, i)) {
        Semaforo s = lista_getObjPosic(cidade->listaSemaforo, i);
        Semaforo_escreverSvg(s, svg);
    }

    i = lista_getPrimeiro(cidade->listaRadioBase);
    for(i; i!= -1; i = lista_getProx(cidade->listaRadioBase, i)) {
        RadioBase rb = lista_getObjPosic(cidade->listaRadioBase, i);
        RadioBase_escreverSvg(rb, svg);
    } 
}

void Cidade_escreverFormasEnvoltas(Cidade c, FILE *svg, char *cor) {
    pCidade cidade = (pCidade) c;
    int i = lista_getPrimeiro(cidade->listaForma);
    for(i; i!= -1; i = lista_getProx(cidade->listaForma, i)) {
        Forma f = lista_getObjPosic(cidade->listaForma, i);
        Forma_escreverFormaEnvoltaSvg(f, svg, cor);
    }
}

void imprimirCidade(Cidade c) {
    pCidade cidade = (pCidade) c;
    int i = lista_getPrimeiro(cidade->listaForma);
    for(i; i!= -1; i = lista_getProx(cidade->listaForma, i)) {
        Forma f = lista_getObjPosic(cidade->listaForma, i);
        Forma_imprimir(f);
    }
}
