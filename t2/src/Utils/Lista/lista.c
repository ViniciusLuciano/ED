#include "lista.h"

typedef struct node {
    struct node *prox;
    struct node *ant;
    Objeto objeto;
} *ponteiroNode;

typedef struct lista {
    struct node *primeiro;
    struct node *ultimo;
    int tamanho, tamanhoMax;
} *ponteiroLista;

Lista criarLista(int tamanhoMax) {
    Lista l = malloc(sizeof(struct lista));
    ponteiroLista lista = (ponteiroLista) l;
    lista->primeiro = NULL;
    lista->ultimo = NULL;
    lista->tamanho = 0;
    lista->tamanhoMax = tamanhoMax;
    return l;
}

bool inserirPrimeiro(Lista l, Objeto objeto) {
    Node n = malloc(sizeof(struct node));

    ponteiroLista lista = (ponteiroLista) l;
    ponteiroNode node = (ponteiroNode) n;
    
    if(lista->primeiro == NULL) {
        if(++lista->tamanho <= lista->tamanhoMax) {
            node->ant = NULL;
            node->prox = NULL;
            node->objeto = objeto;
            lista->primeiro = node;
            lista->ultimo = node;
            lista->tamanho++;
            return true;
        }
    } else {
        if(++lista->tamanho <= lista->tamanhoMax) {
            node->ant = NULL;
            node->prox = lista->primeiro;
            node->objeto = objeto;
            node->prox->ant = node;
            lista->primeiro = node;
            return true;
        }
    }
    free(n);
    return false;
}

bool inserirUltimo(Lista l, Objeto objeto) {
    Node n = malloc(sizeof(struct node));

    ponteiroLista lista = (ponteiroLista) l;
    ponteiroNode node = (ponteiroNode) n;

    if(lista->primeiro == NULL) {
        return inserirPrimeiro(l, objeto);
    }

    if(++lista->tamanho <= lista->tamanhoMax) {
        node->ant = lista->ultimo;
        node->prox = NULL;
        node->objeto = objeto;
        node->ant->prox = node;
        lista->ultimo = node;
        return true;
    }
    free(n);
    return false;
}

bool excluirObjeto(Lista l, Objeto objeto, bool (*objetoEquals)(Objeto objetoLista, Objeto objeto)) {
    ponteiroLista lista = (ponteiroLista) l;
    ponteiroNode node = (ponteiroNode) lista->primeiro;

    for(node; node != NULL; node = node->prox) {
        if( objetoEquals(node->objeto, objeto) ) {
            
            // Excluir inicio
            if(node->ant == NULL) {
                lista->primeiro = node->prox;
            } else if(node->prox == NULL) { // Excluir ultimo
                node->ant->prox = NULL;
                lista->ultimo = node->ant;
            } else { // Excluir no meio
                node->ant->prox = node->prox;
                node->prox->ant = node->ant;
            }
            lista->tamanho--;
            // dar free no objeto aqui
            free(node);
            return true;
        }
    }
    return false;
}

Objeto encontrarObjeto(Lista l, Objeto objeto, bool (*objetoEquals)(Objeto objetoLista, Objeto objeto)) {
    ponteiroLista lista = (ponteiroLista) l;
    ponteiroNode node = (ponteiroNode) lista->primeiro;

    for(node; node != NULL; node = node->prox) {
        if( objetoEquals(node->objeto, objeto) ) {
            return node->objeto;
        }
    }
    return NULL;
}

void imprimirLista(Lista l, void (*imprimirObjeto)(Objeto objeto)) {
    ponteiroLista lista = (ponteiroLista) l;
    ponteiroNode node = (ponteiroNode) lista->primeiro;

    for(node; node != NULL; node = node->prox) {
        imprimirObjeto(node->objeto);
    }
}
