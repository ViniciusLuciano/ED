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
    ponteiroLista lista = (ponteiroLista) l;
    
    if(lista->primeiro == NULL) {
        if(++lista->tamanho <= lista->tamanhoMax) {
            Node n = malloc(sizeof(struct node));
            ponteiroNode node = (ponteiroNode) n;

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
            Node n = malloc(sizeof(struct node));
            ponteiroNode node = (ponteiroNode) n;

            node->ant = NULL;
            node->prox = lista->primeiro;
            node->objeto = objeto;
            node->prox->ant = node;
            lista->primeiro = node;
            lista->tamanho++;
            return true;
        }
    }
    return false;
}

bool inserirUltimo(Lista l, Objeto objeto) {
    ponteiroLista lista = (ponteiroLista) l;

    if(lista->primeiro == NULL) {
        return inserirPrimeiro(l, objeto);
    }

    if(++lista->tamanho <= lista->tamanhoMax) {
        Node n = malloc(sizeof(struct node));
        ponteiroNode node = (ponteiroNode) n;

        node->ant = lista->ultimo;
        node->prox = NULL;
        node->objeto = objeto;
        node->ant->prox = node;
        lista->ultimo = node;
        lista->tamanho++;
        return true;
    }
    return false;
}

void destruirLista(Lista l, void(*destruirObjeto)(Objeto objeto)) {
    ponteiroLista lista = (ponteiroLista) l;
    ponteiroNode node = (ponteiroNode) lista->primeiro;

    if(lista->primeiro == NULL)
        return;
    
    for(node; node != NULL; node = node->prox) {
        if(node->ant != NULL) {
            destruirObjeto(node->ant->objeto);
            free(node->ant);
        }
    }
    destruirObjeto(lista->ultimo->objeto);
    free(lista->ultimo);
    free(lista);
}

bool excluirObjeto(Lista l, 
                    char *identificador, 
                    bool(*objetoEquals)(Objeto objetoLista, char *id), 
                    void(*destruirObjeto)(Objeto objeto)) {

    ponteiroLista lista = (ponteiroLista) l;
    ponteiroNode node = (ponteiroNode) lista->primeiro;

    for(node; node != NULL; node = node->prox) {
        if( objetoEquals(node->objeto, identificador) ) {
            
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
            destruirObjeto(node->objeto);
            free(node);
            return true;
        }
    }
    return false;
}

Objeto encontrarObjeto(Lista l, char *identificador, bool (*objetoEquals)(Objeto objetoLista, char *id)) {
    ponteiroLista lista = (ponteiroLista) l;
    ponteiroNode node = (ponteiroNode) lista->primeiro;

    for(node; node != NULL; node = node->prox) {
        if( objetoEquals(node->objeto, identificador) ) {
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
