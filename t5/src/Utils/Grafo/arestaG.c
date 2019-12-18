#include "arestaG.h"

typedef struct arestaG {
    char ldir[50], lesq[50], nome[64];
    double cmp, vm;
    VerticeG v1, v2;
} *pArestaG;

// Deixar o id dos vertices ou um ponteiro para eles?
ArestaG criarArestaG(VerticeG v1, VerticeG v2, char *ldir, char *lesq, double cmp, double vm, char *nome) {
    ArestaG a = malloc(sizeof(struct arestaG));
    pArestaG arestaG = (pArestaG) a;
    arestaG->v1 = v1;
    arestaG->v2 = v2;
    strcpy(arestaG->ldir, ldir);
    strcpy(arestaG->lesq, lesq);
    strcpy(arestaG->nome, nome);
    arestaG->cmp = cmp;
    arestaG->vm = vm;
    return arestaG;
}

void destruirArestaG(ArestaG a) {
    pArestaG arestaG = (pArestaG) a;
    free(arestaG);
}

bool ArestaG_equals(ArestaG a1, ArestaG a2) {
    pArestaG aresta1 = (pArestaG) a1;
    pArestaG aresta2 = (pArestaG) a2;
    return aresta1->v1 == aresta2->v1 && aresta1->v2 == aresta2->v2;
}

VerticeG ArestaG_get_v1(ArestaG a) {
    pArestaG arestaG = (pArestaG) a;
    return arestaG->v1;
}

VerticeG ArestaG_get_v2(ArestaG a) {
    pArestaG arestaG = (pArestaG) a;
    return arestaG->v2;
}

char* ArestaG_getNome(ArestaG a) {
    pArestaG arestaG = (pArestaG) a;
    return arestaG->nome;
}

double ArestaG_get_cmp(ArestaG a) {
    pArestaG arestaG = (pArestaG) a;
    return arestaG->cmp;
}

double ArestaG_get_vm(ArestaG a) {
    pArestaG arestaG = (pArestaG) a;
    return arestaG->vm;
}

double ArestaG_get_tempo(ArestaG a) {
    pArestaG arestaG = (pArestaG) a;
    if (arestaG->vm == 0) return INFINITY;
    return arestaG->cmp/arestaG->vm;
}

void ArestaG_set_cmp(ArestaG a, double cmp) {
    pArestaG arestaG = (pArestaG) a;
    arestaG->cmp = cmp;
}

void ArestaG_set_vm(ArestaG a, double vm) {
    pArestaG arestaG = (pArestaG) a;
    arestaG->vm = vm;
}