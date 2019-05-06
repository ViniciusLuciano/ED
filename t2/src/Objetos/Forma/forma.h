#ifndef FORMA_H
#define FORMA_H

#include <stdlib.h>

/*
Formas podem ser do tipo Circulo/Retangulo/Texto
*/

typedef void* Figura;
typedef struct forma* Forma;

Forma criarForma(int id, int tipoForma, Figura figura);
int getForma_tipoForma(Forma forma);
int getForma_id(Forma forma);
Figura getForma_figura(Forma forma);

#endif
