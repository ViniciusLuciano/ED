#ifndef ARVOREBIN_H
#define ARVOREBIN_H

#include "formas.h"
#include "headers.h"

typedef struct Node {
    Forma* forma;
    struct Node *esq;
    struct Node *dir;
} Node;

typedef struct Node* ArvoreBin;

ArvoreBin* iniciaArvore();

void liberarArvore(ArvoreBin* raiz);

int estaVazia(ArvoreBin* raiz);

int adicionarElemento(ArvoreBin *raiz, Forma *forma);

Forma* encontrarForma(ArvoreBin *raiz, int id);

void printarArvore(struct Node* node, char* path);

#endif