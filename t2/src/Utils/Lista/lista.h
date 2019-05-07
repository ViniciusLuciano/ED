#ifndef LISTA_H
#define LISTA_H

#include "../../headers.h"

typedef void* Objeto;
typedef struct lista* Lista;
typedef struct node* Node;

Lista criarLista(int tamanhoMax);
bool inserirPrimeiro(Lista l, Objeto objeto);
bool inserirUltimo(Lista l, Objeto objeto);
void setLista_tamanhoMax(Lista lista, int tamanhoMax);
void destruirLista(Lista l, void (*destruirObjeto)(Objeto objeto));

bool excluirObjeto(Lista l, 
                    char *identificador, 
                    bool(*objetoEquals)(Objeto objetoLista, char *id), 
                    void(*destruirObjeto)(Objeto objeto));
Objeto encontrarObjeto(Lista l, char *identificador, bool (*objetoEquals)(Objeto objetoLista, char *id));

void imprimirLista(Lista l, void (*imprimirObjeto)(Objeto objeto));

#endif
