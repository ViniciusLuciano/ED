#include "lista.h"


typedef struct node {
    struct Objeto* objeto;
    struct node* prox;
    struct node* ant;
} *pNode;

typedef struct lista {
    struct node* inicio;
    bool (*equals)(Objeto objeto, Objeto objeto2);
    void(*destruirObjeto)(Objeto objeto);
    int tamanho;
} *pLista;

Lista criarLista(bool (*equals)(Objeto objeto, Objeto objeto2), void(*destruirObjeto)(Objeto objeto)) {
    pLista lista = malloc(sizeof(struct lista));
    lista->inicio = NULL;   
    lista->tamanho = 0;
    lista->equals = equals;
    lista->destruirObjeto = destruirObjeto;
    return lista;
}

void destruirLista(Lista lista) {
    pLista l = (pLista) lista;
    pNode aux = l->inicio;
    pNode aux2 = l->inicio;
    while (aux != NULL) {
        aux = aux->prox;
        l->destruirObjeto(aux2->objeto);
        free(aux2);
        aux2 = aux;
    }
    free(lista);
}

void Lista_inserir(Lista lista, Objeto objeto) {
    pLista l = (pLista) lista;
    pNode node = malloc(sizeof(struct node));
    node->ant = NULL;
    node->objeto = objeto;
    node->prox = NULL;

    pNode aux = l->inicio;
    if (aux == NULL) {
        l->inicio = node;
        l->tamanho++;
        return;
    }

    for(aux; aux->prox != NULL; aux = aux->prox);
    aux->prox = node;
    node->ant = aux;
    l->tamanho++;
}

void Lista_printar(Lista lista, char* (*getChave)(Objeto objeto)) {
    pLista l = (pLista) lista;
    pNode aux = l->inicio;
    while (aux != NULL) {
        printf(" -> %s\n", getChave(aux->objeto));
        aux = aux->prox;
    }
}

Node Lista_getPrimeiro(Lista lista) {
    pLista l = (pLista) lista;
    return l->inicio;
}

Node Node_getProx(Node node) {
    pNode n = (pNode) node;
    return n->prox;
}

Objeto Lista_Node_getObjeto(Node node) {
    pNode n = (pNode) node;
    return n->objeto;
}