#include "arvoreBin.h"

ArvoreBin* iniciaArvore() {
    ArvoreBin *raiz = (ArvoreBin*)malloc(sizeof(ArvoreBin));
    if(raiz != NULL) {
        *raiz = NULL;
    }
    return raiz;
}

void liberarNode(struct Node* node) {
    if(node == NULL)
        return;
    liberarNode(node->esq);
    liberarNode(node->dir);
    liberarForma(node);
}

void liberarForma(Node *node) {
    if(node->forma->nomeForma == TEXTO)
        free(((Texto*)node->forma->tipoForma)->texto);
    else if(node->forma->nomeForma == CIRCULO || node->forma->nomeForma == RETANGULO) {
        free(node->forma->corB);
        free(node->forma->corD);
    }
    free(node->forma->tipoForma); // Ponteiro void alocado
    free(node->forma);
    free(node);
}

void liberarArvore(ArvoreBin *raiz) {
    if(raiz == NULL)
        return;
    liberarNode(*raiz);
    free(raiz);
}

int estaVazia(ArvoreBin *raiz) {
    if(raiz == NULL)
        return 1;
    if((*raiz) == NULL)
        return 1;
    return 0;
}

int adicionarElemento(ArvoreBin *raiz, Forma *forma) {
    if(raiz == NULL)
        return 0;

    struct Node* novo;
    novo = (struct Node*)malloc(sizeof(struct Node));
    if(novo == NULL)
        return 0;

    novo->forma = forma;
    novo->dir = NULL;
    novo->esq = NULL;

    if((*raiz) == NULL)
        (*raiz) = novo;
    else {
        struct Node* atual = (*raiz);
        struct Node* ant = NULL;
        while(atual != NULL) {
            
            if(forma->id == atual->forma->id) {
                novo->dir = atual->dir;
                novo->esq = atual->esq;
                if(ant != NULL) {
                    if(forma->id > ant->forma->id) {
                        ant->dir = novo;
                    } else {
                        ant->esq = novo;
                    }
                } else {
                    (*raiz) = novo;
                }
                liberarForma(atual);
                return 1;
            }

            ant = atual;
            if(forma->id > atual->forma->id) {
                atual = atual->dir;
            } else {
                atual = atual->esq;
            }

        }
        if(forma->id > ant->forma->id) {
            ant->dir = novo;
        } else {
            ant->esq = novo;
        }
    }
    return 1;
}

Forma* encontrarForma(ArvoreBin *raiz, int id) {
    if(raiz == NULL) {
        return NULL;
    }
    
    struct Node* atualNode = (*raiz);
    while(atualNode != NULL) {
        if(id == atualNode->forma->id) {
            return atualNode->forma;
        }
        
        if(id > atualNode->forma->id)
            atualNode = atualNode->dir;
        else
            atualNode = atualNode->esq;
    }

    if(atualNode == NULL) {
        return NULL;
    }
}