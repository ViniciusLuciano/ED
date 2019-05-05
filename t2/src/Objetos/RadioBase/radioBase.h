#ifndef RADIOBASE_H
#define RADIOBASE_H

#include "../../headers.h"

typedef void* RadioBase;

RadioBase criarRadioBase(char *id, double x, double y, char *cfill, char *cstrok, char *sw);
void destruirRadioBase(RadioBase radioBase);
char* getRadioBase_id(RadioBase radioBase);
double getRadioBase_x(RadioBase radioBase);
double getRadioBase_y(RadioBase radioBase);

// Funções relacionadas com a lista
bool radioBaseEquals(RadioBase radioBase, char *id);
void imprimirRadioBase(RadioBase radioBase);

#endif