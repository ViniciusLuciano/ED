#ifndef LISTA_H
#define LISTA_H

#include "../../headers.h"

typedef void* Lista;
typedef void* Objeto;
typedef void* Node;

Lista criarLista(bool (*equals)(Objeto objeto, Objeto objeto2), void(*destruirObjeto)(Objeto objeto));
void destruirLista(Lista lista);
void Lista_inserir(Lista lista, Objeto objeto);
void Lista_printar(Lista lista, char* (*getChave)(Objeto objeto));
Node Lista_getPrimeiro(Lista lista);
Node Node_getProx(Node node);
Objeto Lista_Node_getObjeto(Node node);


#endif