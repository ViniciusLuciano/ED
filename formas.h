#ifndef FORMAS_H
#define FORMAS_H

#include "headers.h"

typedef struct Circulo {
    double raio;
} Circulo;

typedef struct Retangulo {
    double w, h;
} Retangulo;

typedef struct Texto {
    double x, y;
    char *texto;
} Texto;

typedef struct Forma {
    char nome;
    int id;
    double x, y;
    char corB[50];
    char corD[50];
    void *tipoForma;
} Forma;

#endif