#ifndef RADIOBASE_H
#define RADIOBASE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct radioBase* RadioBase;

RadioBase criarRadioBase(char *id, double x, double y, char *cfill, char *cstrok, char *sw);
void destruirRadioBase(RadioBase radioBase);
char* getRadioBase_id(RadioBase radioBase);
double getRadioBase_x(RadioBase radioBase);
double getRadioBase_y(RadioBase radioBase);
void setRadioBase_x(RadioBase radioBase, double x);
void setRadioBase_y(RadioBase radioBase, double y);

// Funções relacionadas com a lista
bool radioBaseEquals(RadioBase radioBase, char *id);
void imprimirRadioBase(RadioBase radioBase);

#endif