#include "muro.h"

typedef struct muro {
    double x1, y1, x2, y2;
}*pMuro;

Muro criarMuro(double x1, double y1, double x2, double y2) {
    Muro m = malloc(sizeof(struct muro));
    pMuro muro = (pMuro) m;
    muro->x1 = x1;
    muro->y1 = y1;
    muro->x2 = x2;
    muro->y2 = y2;
    return muro;
}

void destruirMuro(Muro m) {
    pMuro muro = (pMuro) m;
    free(muro);
}

void Muro_escreverSvg(Muro m, FILE *svg) {
    pMuro muro = (pMuro) m;
    fprintf(svg, "<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" style=\"stroke:rgb(0,0,0);stroke-width:2\" />\n", 
            muro->x1,
            muro->y1,
            muro->x2,
            muro->y2);
}
