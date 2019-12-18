#ifndef FORMA_H
#define FORMA_H

#include "../../headers.h"
#include "../Circulo/circulo.h"
#include "../Retangulo/retangulo.h"

/*
Formas podem ser do tipo Circulo/Retangulo
*/

typedef void* Figura;
typedef void* Forma;

#include "../../svg.h"
#include "../../Utils/Geometria/geometria.h"

Forma criarForma(char *id, int tipoForma, Figura figura);
void destruirForma(Forma forma);
int Forma_get_tipoForma(Forma forma);
char* Forma_get_id(Forma forma);
Figura Forma_getFigura(Forma forma);
void Forma_escreverSvg(Forma forma, FILE *svg);
void Forma_escreverFormaEnvoltaSvg(Forma forma, FILE *svg, char *cor);

// Funções relacionadas com a lista
bool formaEquals(Forma forma, char *id);
void Forma_imprimir(Forma forma);
int Forma_compararChave(Forma a, Forma b);

char* Forma_getChave(Forma f);

#endif
