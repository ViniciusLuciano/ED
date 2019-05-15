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
void setSemaforo_x(Semaforo semaforo, double x);
void setSemaforo_y(Semaforo semaforo, double y);
void escreverSemaforo_svg(Semaforo s, FILE *svg);

// Funções relacionadas com a lista
bool semaforoEquals(Semaforo semaforo, char *id);
void imprimirSemaforo(Semaforo semaforo);

#endif