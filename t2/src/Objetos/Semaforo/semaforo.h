#ifndef SEMAFORO_H
#define SEMAFORO_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef void* Semaforo;

Semaforo criarSemaforo(char *id, double x, double y, char *cfill, char *cstrok, char *sw);
void destruirSemaforo(Semaforo semaforo);
char* Semaforo_get_id(Semaforo semaforo);
double Semaforo_get_x(Semaforo semaforo);
double Semaforo_get_y(Semaforo semaforo);
void Semaforo_set_x(Semaforo semaforo, double x);
void Semaforo_set_y(Semaforo semaforo, double y);
void Semaforo_escreverSvg(Semaforo s, FILE *svg);

// Funções relacionadas com a lista
bool semaforoEquals(Semaforo semaforo, char *id);
void Semaforo_imprimir(Semaforo semaforo);

#endif