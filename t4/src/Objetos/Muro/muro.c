#include "muro.h"

typedef struct muro {
    Ponto p1, p2;
}*pMuro;

Muro criarMuro(double x1, double y1, double x2, double y2) {
    Muro m = malloc(sizeof(struct muro));
    pMuro muro = (pMuro) m;
    muro->p1 = criarPonto(x1, y1);
    muro->p2 = criarPonto(x2, y2);
    return muro;
}

void destruirMuro(Muro m) {
    pMuro muro = (pMuro) m;
    free(muro->p1);
    free(muro->p2);
    free(muro);
}

Ponto Muro_get_p1(Muro m) {
    pMuro muro = (pMuro) m;
    return muro->p1;
}

Ponto Muro_get_p2(Muro m) {
    pMuro muro = (pMuro) m;
    return muro->p2;
}

void Muro_escreverSvg(Muro m, FILE *svg) {
    pMuro muro = (pMuro) m;
    fprintf(svg, "<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" style=\"stroke:rgb(0,0,0);stroke-width:2\" />\n", 
           Ponto_get_x(muro->p1),
            Ponto_get_y(muro->p1),
            Ponto_get_x(muro->p2),
            Ponto_get_y(muro->p2));
}

int Muro_compararChave(Muro a, Muro b) {
    pMuro muro_a = (pMuro) a;
    pMuro muro_b = (pMuro) b;

    if (Ponto_get_x(muro_a->p1) > Ponto_get_x(muro_b->p1)) return 1;
    else if (Ponto_get_x(muro_a->p1) < Ponto_get_x(muro_b->p1)) return -1;
    else {
        if (Ponto_get_y(muro_a->p1) > Ponto_get_y(muro_b->p1)) return 1;
        else if (Ponto_get_y(muro_a->p1) < Ponto_get_y(muro_b->p1)) return -1;
        else return 0;
    }
}

int Muro_getSize() {
    return 2*Ponto_getSize();
}
