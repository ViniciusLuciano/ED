#ifndef LISTA_H
#define LISTA_H

#include "../../headers.h"

typedef void* Objeto;
typedef void* Lista;
typedef void* Node;
typedef void** Stk;

Lista criarLista(int tamanhoMax);
bool inserirPrimeiro(Lista l, Objeto objeto);
bool inserirUltimo(Lista l, Objeto objeto);

// Recebem função objetoEquals do objeto
bool excluirObjeto(Lista l, Objeto objeto, bool (*objetoEquals)(Objeto objetoLista, Objeto objeto));
Objeto encontrarObjeto(Lista l, Objeto objeto, bool (*objetoEquals)(Objeto objetoLista, Objeto objeto));

// Recebe função imprimirObjeto do objeto
void imprimirLista(Lista l, void (*imprimirObjeto)(Objeto objeto));

#endif
