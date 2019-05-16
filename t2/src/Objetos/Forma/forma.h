#ifndef FORMA_H
#define FORMA_H

#include "../../headers.h"
#include "../Circulo/circulo.h"
#include "../Retangulo/retangulo.h"

/*
Formas podem ser do tipo Circulo/Retangulo
*/

typedef void* Figura;
typedef struct forma* Forma;

#include "../../svg.h"
#include "../../Utils/Geometria/geometria.h"

Forma criarForma(char *id, int tipoForma, Figura figura);
void destruirForma(Forma forma);
int getForma_tipoForma(Forma forma);
char* getForma_id(Forma forma);
Figura getForma_figura(Forma forma);
void escreverForma_svg(Forma forma, FILE *svg);
void Forma_escreverFormaEnvoltaSvg(Forma forma, FILE *svg, char *cor);

// Funções relacionadas com a lista
bool formaEquals(Forma forma, char *id);
void imprimirForma(Forma forma);

#endif
