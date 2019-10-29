#ifndef ARVORE_H
#define ARVORE_H

#define VERMELHO 1
#define PRETO 0

#include "../../headers.h"

typedef void* Objeto;
typedef void* Arvore;
typedef void* Node;

void destruirArvore(Arvore arvore);
void Arvore_inserir(Arvore arvore, Objeto objeto);
bool Arvore_removerObjeto(Arvore arvore, Objeto objeto);
Arvore criarArvore(int(*compararChave)(Objeto obj1, Objeto obj2), int tamObjeto, 
                                                                void(*destruirObjeto)(Objeto objeto));
Objeto Arvore_getObjeto(Arvore arvore, Objeto objeto);
void Arvore_escreverSvg(Arvore arvore, FILE* svg);
void destruirTNULL();

Node next(Node node);
Node Arvore_getRaiz(Arvore arvore);
int Node_getAux(Node node);
Objeto Node_getObjeto(Node node);
int Arvore_length(Arvore arvore);
Node Node_getDir(Node n);
Node Node_getEsq(Node n);

#endif