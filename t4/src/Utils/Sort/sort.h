#ifndef SORT_H
#define SORT_H

#include "../../Objetos/Cidade/cidade.h"

typedef void* Objeto;

void heapsortMenor(Objeto a[], int n, int valor, double (*getComparator)(Objeto objeto));
void heapsortMaior(Objeto a[], int n, int valor, double (*getComparator)(Objeto objeto));

#endif