#include "lista.h"

struct node {
    struct node *prox;
    struct node *ant;
    Objeto objeto;
};

struct lista {
    struct node *primeiro;
    struct node *ultimo;
    int tamanho, tamanhoMax;
};

Lista criarLista(int tamanhoMax) {
    Lista lista = malloc(sizeof(struct lista));
    lista->primeiro = NULL;
    lista->ultimo = NULL;
    lista->tamanho = 0;
    lista->tamanhoMax = tamanhoMax;
    return lista;
}

void setLista_tamanhoMax(Lista lista, int tamanhoMax) {
    lista->tamanhoMax = tamanhoMax;
}

bool inserirPrimeiro(Lista lista, Objeto objeto) {
    
    if(lista->primeiro == NULL) {
        if(lista->tamanho + 1 <= lista->tamanhoMax) {
            Node node = malloc(sizeof(struct node));

            node->ant = NULL;
            node->prox = NULL;
            node->objeto = objeto;
            lista->primeiro = node;
            lista->ultimo = node;
            lista->tamanho++;
            return true;
        }
    } else {
        if(lista->tamanho + 1 <= lista->tamanhoMax) {
            Node node = malloc(sizeof(struct node));

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

bool inserirUltimo(Lista lista, Objeto objeto) {
    if(lista->primeiro == NULL) {
        return inserirPrimeiro(lista, objeto);
    }

    if(lista->tamanho + 1<= lista->tamanhoMax) {
        Node node = malloc(sizeof(struct node));

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

void destruirLista(Lista lista, void(*destruirObjeto)(Objeto objeto)) {
    Node node = (Node) lista->primeiro;

    if(lista->primeiro == NULL) {
        free(lista);
        return;
    }
    
    while(true) {
        if(node->prox == NULL) {
            destruirObjeto(node->objeto);
            free(node);
            free(lista);
            break;
        } else {
            node = node->prox;
            destruirObjeto(node->ant->objeto);
            free(node->ant);
        }
    }

    // for(node; node != NULL; node = node->prox) {
    //     if(node->ant != NULL) {
    //         destruirObjeto(node->ant->objeto);
    //         free(node->ant);
    //     }
    // }
    // destruirObjeto(lista->ultimo->objeto);
    // free(lista->ultimo);
    // free(lista);
}

bool excluirObjeto(Lista lista, 
                    char *identificador, 
                    bool(*objetoEquals)(Objeto objetoLista, char *id), 
                    void(*destruirObjeto)(Objeto objeto)) {

    
    Node node = (Node) lista->primeiro;

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

// Verificar se o node é o primeiro/ ultimo zz
bool excluirLista_Node(Lista lista, Node node, void(*destruirObjeto)(Objeto objeto)) {
    if(node->ant == NULL) {
        lista->primeiro = node->prox;
    } else if(node->prox == NULL) { // Excluir ultimo
        node->ant->prox = NULL;
        lista->ultimo = node->ant;
    } else { // Excluir no meio
        node->ant->prox = node->prox;
        node->prox->ant = node->ant;
    }
    destruirObjeto(node->objeto);
    free(node);
}

Objeto encontrarObjeto(Lista lista, char *identificador, bool (*objetoEquals)(Objeto objetoLista, char *id)) {
    Node node = (Node) lista->primeiro;

    for(node; node != NULL; node = node->prox) {
        if( objetoEquals(node->objeto, identificador) ) {
            return node->objeto;
        }
    }
    return NULL;
}

Node getLista_primeiro(Lista lista) {
    return lista->primeiro;
}

Node getLista_prox(Node node) {
    return node->prox;
}

Node getLista_ant(Node node) {
    return node->ant;
}

Objeto getLista_ObjNode(Node node) {
    return node->objeto;
}

void imprimirLista(Lista lista, void (*imprimirObjeto)(Objeto objeto)) {
    Node node = (Node) lista->primeiro;

    for(node; node != NULL; node = node->prox) {
        imprimirObjeto(node->objeto);
    }
}