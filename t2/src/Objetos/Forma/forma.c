#include "forma.h"

struct forma {
    int id;
    int tipoForma;
    Figura figura;
};

Forma criarForma(int id, int tipoForma, Figura figura) {
    Forma forma = malloc(sizeof(struct forma));
    forma->tipoForma = tipoForma;
    forma->id = id;
    forma->figura = figura;
    return forma;
}

int getForma_tipoForma(Forma forma) {
    return forma->tipoForma;
}

int getForma_id(Forma forma) {
    return forma->id;
}

// Retorna um circulo/retangulo/texto
Figura getForma_figura(Forma forma) {
    return forma->figura;
}