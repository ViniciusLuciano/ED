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
    char texto[50]; // Deixar?
} Texto;

typedef struct Forma {
    char nome;
    int id;
    double x, y;
    char corB[20];
    char corD[20];
    void *tipoForma;
} Forma;

#endif