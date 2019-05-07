#ifndef FORMA_H
#define FORMA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*
Formas podem ser do tipo Circulo/Retangulo
*/

typedef void* Figura;
typedef struct forma* Forma;

Forma criarForma(char *id, int tipoForma, Figura figura);
void destruirForma(Forma forma);
int getForma_tipoForma(Forma forma);
char* getForma_id(Forma forma);
Figura getForma_figura(Forma forma);

// Funções relacionadas com a lista
bool formaEquals(Forma forma, char *id);
void imprimirForma(Forma forma);

#endif
