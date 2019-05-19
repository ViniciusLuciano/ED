#ifndef RADIOBASE_H
#define RADIOBASE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef void* RadioBase;

RadioBase criarRadioBase(char *id, double x, double y, char *cfill, char *cstrok, char *sw);
void destruirRadioBase(RadioBase radioBase);
char* RadioBase_get_id(RadioBase radioBase);
double RadioBase_get_x(RadioBase radioBase);
double RadioBase_get_y(RadioBase radioBase);
void RadioBase_set_x(RadioBase radioBase, double x);
void RadioBase_set_y(RadioBase radioBase, double y);
void RadioBase_escreverSvg(RadioBase radioBase, FILE *svg);

// Funções relacionadas com a lista
bool radioBaseEquals(RadioBase radioBase, char *id);
void RadioBase_imprimir(RadioBase radioBase);

#endif