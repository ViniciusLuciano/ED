#include "lista.h"

typedef struct node {
    int prox;
    int ant;
    Objeto objeto;
}*pNode;

typedef struct lista {
    pNode node; // lista de nodes
    int primeiro;
    int ultimo;
    int tamanho, tamanhoMax, livre;
}*pLista;

Lista criarLista(int tamanhoMax) {
    Lista l = malloc(sizeof(struct lista));
    pLista lista = (pLista) l;
    
    lista->node = (pNode)malloc(tamanhoMax*sizeof(struct node));
    lista->tamanhoMax = tamanhoMax;
    lista->tamanho = 0;
    // Vai ate o penultimo setando o index do proximo como i+1
    for(int i = 0; i < tamanhoMax - 1; i++) {
        lista->node[i].prox = i+1;
    }
    // Seta o proximo do ultimo como -1
    lista->node[tamanhoMax-1].prox = -1;
    lista->primeiro = -1;
    lista->ultimo = -1;
    lista->livre = 0;

    return lista;
}

void lista_destruir(Lista l, void(*destruirObjeto)(Objeto objeto)) {
    pLista lista = (pLista) l;

    if(lista->primeiro == -1) {
        free(lista->node);
        free(lista);
        return;
    }
    
    int i = lista->primeiro;
    while(true) {
        if(lista->node[i].prox == -1) {
            destruirObjeto(lista->node[i].objeto);
            free(lista->node);
            free(lista);
            break;
        } else {
            i = lista->node[i].prox;
            destruirObjeto(lista->node[lista->node[i].ant].objeto);
        }
    }
}

// Index do livre
int lista_getLivre(Lista l) {
    pLista lista = (pLista) l;
    // Pega o index livre
    int livre = lista->livre;
    // Seta como livre o proximo do node que estava livre
    if(livre != -1)
        lista->livre = lista->node[lista->livre].prox;

    return livre;
}

int lista_getPrimeiro(Lista l) {
    pLista lista = (pLista) l;
    return lista->primeiro;
}

int lista_getProx(Lista l, int i) {
    pLista lista = (pLista) l;
    return lista->node[i].prox;
}

int lista_getAnt(Lista l, int i) {
    pLista lista = (pLista) l;
    return lista->node[i].ant;
}

bool lista_inserirUltimo(Lista l, Objeto objeto) {
    pLista lista = (pLista) l;
    int posLivre = lista_getLivre(l);

    if(posLivre == -1) {
        printf("Lista cheia\n");
        return false;
    }

    if(lista->primeiro == -1) {
        if(lista->tamanho + 1 <= lista->tamanhoMax) {
            lista->node[posLivre].ant = -1;
            lista->node[posLivre].objeto = objeto;
            lista->node[posLivre].prox = -1;
            lista->primeiro = 0;
            lista->ultimo = 0;
            lista->tamanho++;
            return true;
        }
    } else if(lista->tamanho + 1 <= lista->tamanhoMax) {
        lista->node[lista->ultimo].prox = posLivre;
        lista->node[posLivre].objeto = objeto;
        lista->node[posLivre].ant = lista->ultimo;
        lista->node[posLivre].prox = -1;
        lista->tamanho++;
        lista->ultimo = posLivre;
        return true;
    }
    return false;
}

bool lista_excluirObjeto(Lista l, 
                    char *id, 
                    bool(*objetoEquals)(Objeto objetoLista, char *id), 
                    void(*destruirObjeto)(Objeto objeto)) {
    
    pLista lista = (pLista) l;
    for(int i = lista->primeiro; i != -1; i = lista->node[i].prox) {
        if(objetoEquals(lista->node[i].objeto, id)) {
            if(i == lista->primeiro) {
                lista->primeiro = lista->node[i].prox;
            } else if(lista->node[i].prox == -1) {
                lista->node[lista->node[i].ant].prox = -1;
                lista->ultimo = lista->node[i].ant;
            } else {
                lista->node[lista->node[i].ant].prox = lista->node[i].prox;
                lista->node[lista->node[i].prox].ant = lista->node[i].ant;
            }
            lista->tamanho--;
            destruirObjeto(lista->node[i].objeto);
            lista->node[i].prox = lista->livre;
            lista->livre = i;
            return true;
        }
    }
}

bool lista_excluirPosic(Lista l, int i, void(*destruirObjeto)(Objeto objeto)) {
    pLista lista = (pLista) l;
    if(i == lista->primeiro) {
        lista->primeiro = lista->node[i].prox;
    } else if(lista->node[i].prox == -1) {
        lista->node[lista->node[i].ant].prox = -1;
        lista->ultimo = lista->node[i].ant;
    } else {
        lista->node[lista->node[i].ant].prox = lista->node[i].prox;
        lista->node[lista->node[i].prox].ant = lista->node[i].ant;
    }
    lista->tamanho--;
    destruirObjeto(lista->node[i].objeto);
    lista->node[i].prox = lista->livre;
    lista->livre = i;
    return true;
}

Objeto lista_getObjeto(Lista l, char *id, bool (*objetoEquals)(Objeto objetoLista, char *id)) {
    pLista lista = (pLista) l;
    for(int i = lista->primeiro; i != -1; i = lista->node[i].prox) {
        if(objetoEquals(lista->node[i].objeto, id)) {
            return lista->node[i].objeto;
        }
    }
    return NULL;
}

Objeto lista_getObjPosic(Lista l, int i) {
    pLista lista = (pLista) l;
    return lista->node[i].objeto;
}

void lista_imprimir(Lista l, void (*imprimirObjeto)(Objeto objeto)) {
    pLista lista = (pLista) l;

    for(int i = lista->primeiro; i != -1; i = lista->node[i].prox) {
        imprimirObjeto(lista->node[i].objeto);
    }
}
