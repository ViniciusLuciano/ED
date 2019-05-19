#include "forma.h"

typedef struct forma {
    char id[20];
    int tipoForma;
    Figura figura;
}*pForma;

Forma criarForma(char *id, int tipoForma, Figura figura) {
    Forma f = malloc(sizeof(struct forma));
    pForma forma = (pForma) f;
    forma->tipoForma = tipoForma;
    strcpy(forma->id, id);
    forma->figura = figura;
    return forma;
}

// Ver se precisa destruir coisas dentro da figura
void destruirForma(Forma f) {
    pForma forma = (pForma) f;
    free(forma->figura);
    free(forma);
}

// Enum
int Forma_get_tipoForma(Forma f) {
    pForma forma = (pForma) f;
    return forma->tipoForma;
}

char* Forma_get_id(Forma f) {
    pForma forma = (pForma) f;
    return forma->id;
}

// Retorna um circulo ou retangulo
Figura Forma_getFigura(Forma f) {
    pForma forma = (pForma) f;
    return forma->figura;
}

bool formaEquals(Forma f, char *id) {
    pForma forma = (pForma) f;
    return strcmp(forma->id, id) == 0;
}

void Forma_imprimir(Forma f) {
    pForma forma = (pForma) f;
    printf("id %s\n", forma->id);
}

void Forma_escreverSvg(Forma f, FILE *svg) {
    pForma forma = (pForma) f;
    if(forma->tipoForma == CIRCULO)
        Circulo_escreverSvg(forma->figura, svg);
    else if(forma->tipoForma == RETANGULO)
        Retangulo_escreverSvg(forma->figura, svg);
}

void Forma_escreverFormaEnvoltaSvg(Forma f, FILE *svg, char *cor) {
    pForma forma = (pForma) f;
    if(forma->tipoForma == CIRCULO) {
        Circulo c = Forma_getFigura(forma);
        Circulo_escreverSvg(c, svg);

        // "Bounding box"
        double posX = Circulo_get_min_x(c);
        double posY = Circulo_get_min_y(c);
        double lado = 2*Circulo_get_r(c);
        fprintf(svg, "<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" stroke=\"%s\" fill-opacity=\"0\" />\n", 
            posX, 
            posY, 
            lado, 
            lado, 
            cor);

    } else if(forma->tipoForma == RETANGULO) {
        Retangulo r = Forma_getFigura(forma);
        Retangulo_escreverSvg(r, svg);

        double *centro = malloc(2*sizeof(double));
        centroDeMassa(forma, centro);

        fprintf(svg, "<ellipse cx=\"%lf\" cy=\"%lf\" rx=\"%lf\" ry=\"%lf\" stroke=\"%s\" fill-opacity=\"0\" />\n", 
            centro[0], 
            centro[1], 
            Retangulo_get_w(r)/2, 
            Retangulo_get_h(r)/2, 
            cor);
        free(centro);
    }	
}