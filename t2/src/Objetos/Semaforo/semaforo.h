#ifndef SEMAFORO_H
#define SEMAFORO_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct semaforo* Semaforo;

Semaforo criarSemaforo(char *id, double x, double y, char *cfill, char *cstrok, char *sw);
void destruirSemaforo(Semaforo semaforo);
char* getSemaforo_id(Semaforo semaforo);
double getSemaforo_x(Semaforo semaforo);
double getSemaforo_y(Semaforo semaforo);

// Funções relacionadas com a lista
bool semaforoEquals(Semaforo semaforo, char *id);
void imprimirSemaforo(Semaforo semaforo);

#endif