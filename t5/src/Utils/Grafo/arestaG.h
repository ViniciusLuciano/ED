#ifndef ARESTAG_H
#define ARESTAG_H

#include "../../headers.h"

typedef void* ArestaG;
typedef void* VerticeG;

ArestaG criarArestaG(VerticeG v1, VerticeG v2, char *ldir, char *lesq, double cmp, double vm, char *nome);
void destruirArestaG(ArestaG aresta);
bool ArestaG_equals(ArestaG a1, ArestaG a2);
VerticeG ArestaG_get_v1(ArestaG a);
VerticeG ArestaG_get_v2(ArestaG a);
char* ArestaG_getNome(ArestaG a);
double ArestaG_get_cmp(ArestaG a);
double ArestaG_get_vm(ArestaG a);
double ArestaG_get_tempo(ArestaG a);
void ArestaG_set_cmp(ArestaG a, double cmp);
void ArestaG_set_vm(ArestaG a, double vm);

#endif