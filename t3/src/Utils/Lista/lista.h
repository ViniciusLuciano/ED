#ifndef LISTA_H
#define LISTA_H

#include "../../headers.h"

typedef void* Objeto;
typedef void* Lista;
typedef void* Node;

Lista criarLista(int tamanhoMax);
void lista_destruir(Lista l, void(*destruirObjeto)(Objeto objeto));
int lista_getLivre(Lista l);
int lista_getPrimeiro(Lista l);
int lista_getProx(Lista l, int i);
int lista_getAnt(Lista l, int i);
bool lista_inserirUltimo(Lista l, Objeto objeto);
bool lista_excluirObjeto(Lista l, 
                    char *id, 
                    bool(*objetoEquals)(Objeto objetoLista, char *id), 
                    void(*destruirObjeto)(Objeto objeto));
bool lista_excluirPosic(Lista l, int i, void(*destruirObjeto)(Objeto objeto));
bool lista_excluirObjetoMemoria(Lista l, Objeto objeto);
Objeto lista_getObjeto(Lista l, char *id, bool (*objetoEquals)(Objeto objetoLista, char *id));
Objeto lista_getObjPosic(Lista l, int i);
void lista_imprimir(Lista l, void (*imprimirObjeto)(Objeto objeto));

int lista_length(Lista l);
bool lista_inserirAntes(Lista l, int pos, Objeto objeto);
bool lista_inserirDepois(Lista l, int pos, Objeto objeto);

#endif
