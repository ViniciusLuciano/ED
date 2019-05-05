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

void destruirLista(Lista l, void (*destruirObjeto)(Objeto objeto));

bool excluirObjeto(Lista l, 
                    char *identificador, 
                    bool(*objetoEquals)(Objeto objetoLista, char *id), 
                    void(*destruirObjeto)(Objeto objeto));
Objeto encontrarObjeto(Lista l, char *identificador, bool (*objetoEquals)(Objeto objetoLista, char *id));

void imprimirLista(Lista l, void (*imprimirObjeto)(Objeto objeto));

#endif
