#include "forma.h"

struct forma {
    char id[20];
    int tipoForma;
    Figura figura;
};

Forma criarForma(char *id, int tipoForma, Figura figura) {
    Forma forma = malloc(sizeof(struct forma));
    forma->tipoForma = tipoForma;
    strcpy(forma->id, id);
    forma->figura = figura;
    return forma;
}

// Ver se precisa destruir coisas dentro da figura
void destruirForma(Forma forma) {
    free(forma->figura);
    free(forma);
}

// Enum
int getForma_tipoForma(Forma forma) {
    return forma->tipoForma;
}

char* getForma_id(Forma forma) {
    return forma->id;
}

// Retorna um circulo ou retangulo
Figura getForma_figura(Forma forma) {
    return forma->figura;
}

bool formaEquals(Forma forma, char *id) {
    return strcmp(forma->id, id) == 0;
}

void imprimirForma(Forma forma) {
    printf("id %s\n", forma->id);
}

void escreverForma_svg(Forma forma, FILE *svg) {
    if(forma->tipoForma == CIRCULO)
        escreverCirculo_svg(forma, svg);
    else if(forma->tipoForma == RETANGULO)
        escreverRetangulo_svg(forma, svg);
}