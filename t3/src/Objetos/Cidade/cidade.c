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
}*pCidade;

Cidade criarCidade(int i, int nq, int nh, int ns, int nr, int np, int nm) {
    Cidade c = malloc(sizeof(struct cidade));
    pCidade cidade = (pCidade) c;
    cidade->listaForma = criarLista(i);
    cidade->listaQuadra = criarLista(nq);
    cidade->listaHidrante = criarLista(nh);
    cidade->listaSemaforo = criarLista(ns);
    cidade->listaRadioBase = criarLista(nr);
    cidade->listaPredio = criarLista(np);
    cidade->listaMuro = criarLista(nm);
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
    lista_destruir(cidade->listaPredio, destruirPredio);
    lista_destruir(cidade->listaMuro, destruirMuro);
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

void Cidade_setPredio(Cidade c, Predio predio) {
    pCidade cidade = (pCidade) c;
    lista_inserirUltimo(cidade->listaPredio, predio);
}

void Cidade_setMuro(Cidade c, Muro muro) {
    pCidade cidade = (pCidade) c;
    lista_inserirUltimo(cidade->listaMuro, muro);
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

    i = lista_getPrimeiro(cidade->listaPredio);
    for(i; i!= -1; i = lista_getProx(cidade->listaPredio, i)) {
        Predio prd = lista_getObjPosic(cidade->listaPredio, i);
        Quadra q = lista_getObjeto(cidade->listaQuadra, Predio_getCep(prd), quadraEquals);
        if(q != NULL)
            Predio_escreverSvg(prd, Quadra_get_x(q), Quadra_get_y(q), Quadra_get_w(q), Quadra_get_h(q), svg);
    }

    i = lista_getPrimeiro(cidade->listaMuro);
    for(i; i!= -1; i = lista_getProx(cidade->listaMuro, i)) {
        Muro m = lista_getObjPosic(cidade->listaMuro, i);
        Muro_escreverSvg(m, svg);
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
    int i, tamanhoLista = lista_length(cidade->listaSemaforo);

    // Semaforos mais proximos do foco de incendio
    pObj* semaforos_comparar = (pObj*)malloc(tamanhoLista*sizeof(pObj));

    i = lista_getPrimeiro(cidade->listaSemaforo);
    int index = 0;
    for(i; i != -1; i = lista_getProx(cidade->listaSemaforo, i)) {
        Semaforo s = lista_getObjPosic(cidade->listaSemaforo, i);

        double distancia = distanciaL2(x, y, Semaforo_get_x(s), Semaforo_get_y(s));

        pObj o = malloc(sizeof(struct obj));
        o->distancia = distancia;
        o->Objeto = s;

        semaforos_comparar[index] = o;
        index++;
    }

    //qsort(semaforos_comparar, tamanhoLista, sizeof(struct obj), compCrescente);
    heapsortMenor((Objeto*)semaforos_comparar, tamanhoLista, ns, get_obj_comparador);
    fprintf(txt, "-- SEMAFOROS PRÓXIMOS AO FOCO DE INCENDIO --\n");
    for(int i = tamanhoLista - ns; i < tamanhoLista; i++) {
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
    for(int i = 0; i < tamanhoLista; i++) free(semaforos_comparar[i]);
    free(semaforos_comparar);
    fprintf(txt, "-------------------------------------------\n");

    // Hidrantes dentro de uma distancia r do foco de incendio
    Circulo circ = criarCirculo(x, y, r, "", "", "");
    i = lista_getPrimeiro(cidade->listaHidrante);
    fprintf(txt, "-- HIDRANTES PRÓXIMOS AO FOCO DE INCENDIO --\n");
    for(i; i != -1; i = lista_getProx(cidade->listaHidrante, i)) {
        Hidrante h = lista_getObjPosic(cidade->listaHidrante, i);
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
    destruirCirculo(circ);
    fprintf(txt, "-------------------------------------------\n");
}

void Cidade_processarObjetosProximos(Cidade c, char sinal, int k, char cep[], char face, double num, FILE* txt, FILE *svg, char tipo[]) {
    pCidade cidade = (pCidade) c;
    int i;
    double x, y;
    Lista lista;

    if(strcmp(tipo, "hidrante") == 0) {
        lista = cidade->listaHidrante;
    } else if(strcmp(tipo, "semaforo") == 0) {
        lista = cidade->listaSemaforo;
    }

    int tamanhoLista = lista_length(lista);

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

    pObj* objetos_comparar = (pObj*)malloc(tamanhoLista*sizeof(pObj));

    i = lista_getPrimeiro(lista);
    int index = 0;
    for(i; i != -1; i = lista_getProx(lista, i)) {
        Objeto o = lista_getObjPosic(lista, i);

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

    if(sinal == '-')
        heapsortMenor((Objeto*)objetos_comparar, tamanhoLista, k, get_obj_comparador);
        //qsort(objetos_comparar, lista_length(lista), sizeof(struct obj), compCrescente);
    else
        heapsortMaior((Objeto*)objetos_comparar, tamanhoLista, k, get_obj_comparador);
        //qsort(objetos_comparar, lista_length(lista), sizeof(struct obj), compDecrescente);
    fprintf(txt, "-- %d %s MAIS %s DO CEP %s --\n", k, ((strcmp(tipo, "hidrante") == 0) ? "HIDRANTES" : "SEMAFOROS"), (sinal == '+' ? "PRÓXIMOS" : "DISTANTES"), cep);
    for(int i = tamanhoLista - k; i < tamanhoLista; i++) {
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
    for(int i = 0; i < tamanhoLista; i++) free(objetos_comparar[i]);
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
