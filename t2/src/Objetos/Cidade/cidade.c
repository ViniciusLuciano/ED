#include "cidade.h"

struct cidade {
    Lista listaForma;
    Lista listaQuadra;
    Lista listaHidrante;
    Lista listaSemaforo;
    Lista listaRadioBase;
    Lista listaTexto;
};

Cidade criarCidade() {
    Cidade cidade = malloc(sizeof(struct cidade));
    cidade->listaForma = criarLista(1000);
    cidade->listaQuadra = criarLista(1000);
    cidade->listaHidrante = criarLista(1000);
    cidade->listaSemaforo = criarLista(1000);
    cidade->listaRadioBase = criarLista(1000);
    cidade->listaTexto = criarLista(1000);
    return cidade;
}

void destruirCidade(Cidade cidade) {
    destruirLista(cidade->listaForma, (void*)destruirForma);
    destruirLista(cidade->listaQuadra, (void*)destruirQuadra);
    destruirLista(cidade->listaHidrante, (void*)destruirHidrante);
    destruirLista(cidade->listaSemaforo, (void*)destruirSemaforo);
    destruirLista(cidade->listaRadioBase, (void*)destruirRadioBase);
    destruirLista(cidade->listaTexto, (void*)destruirTexto);
    free(cidade);
}

/*
Objeto getCidade_objeto(Cidade cidade, char *id) {
    Objeto obj;
    
    obj = encontrarObjeto(cidade->listaForma, id, formaEquals);
    if(obj != NULL)
        return obj;
    
    obj = encontrarObjeto(cidade->listaQuadra, id, quadraEquals);
    if(obj != NULL)
        return obj;
    
    obj = encontrarObjeto(cidade->listaHidrante, id, hidranteEquals);
    if(obj != NULL)
        return obj;
    
    obj = encontrarObjeto(cidade->listaSemaforo, id, semaforoEquals);
    if(obj != NULL)
        return obj;
    
    obj = encontrarObjeto(cidade->listaRadioBase, id, radioBaseEquals);
    if(obj != NULL)
        return obj;
    
    return NULL;
}
*/

void setCidade_Forma(Cidade cidade, Forma forma) {
    inserirUltimo(cidade->listaForma, forma);
}

void setCidade_Quadra(Cidade cidade, Quadra quadra) {
    inserirUltimo(cidade->listaQuadra, quadra);
}

void setCidade_Hidrante(Cidade cidade, Hidrante hidrante) {
    inserirUltimo(cidade->listaHidrante, hidrante);
}

void setCidade_Semaforo(Cidade cidade, Semaforo semaforo) {
    inserirUltimo(cidade->listaSemaforo, semaforo);
}

void setCidade_RadioBase(Cidade cidade, RadioBase radioBase) {
    inserirUltimo(cidade->listaRadioBase, radioBase);
}

Forma getCidade_Forma(Cidade cidade, char *id) {
    return encontrarObjeto(cidade->listaForma, id, (void*)formaEquals);
}

Quadra getCidade_Quadra(Cidade cidade, char *id) {
    return encontrarObjeto(cidade->listaQuadra, id, (void*)quadraEquals);
}

Hidrante getCidade_Hidrante(Cidade cidade, char *id) {
    return encontrarObjeto(cidade->listaHidrante, id, (void*)hidranteEquals);
}

Semaforo getCidade_Semaforo(Cidade cidade, char *id) {
    return encontrarObjeto(cidade->listaSemaforo, id, (void*)semaforoEquals);
}

RadioBase getCidade_RadioBase(Cidade cidade, char *id) {
    return encontrarObjeto(cidade->listaRadioBase, id, (void*)radioBaseEquals);
}