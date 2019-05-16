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
        escreverCirculo_svg(forma->figura, svg);
    else if(forma->tipoForma == RETANGULO)
        escreverRetangulo_svg(forma->figura, svg);
}

void Forma_escreverFormaEnvoltaSvg(Forma forma, FILE *svg, char *cor) {
    if(forma->tipoForma == CIRCULO) {
        Circulo c = getForma_figura(forma);
        escreverCirculo_svg(c, svg);

        // "Bounding box"
        double posX = getCirculo_min_x(c);
        double posY = getCirculo_min_y(c);
        double lado = 2*getCirculo_r(c);
        fprintf(svg, "<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" stroke=\"%s\" fill-opacity=\"0\" />\n", 
            posX, 
            posY, 
            lado, 
            lado, 
            cor);

    } else if(forma->tipoForma == RETANGULO) {
        Retangulo r = getForma_figura(forma);
        escreverRetangulo_svg(r, svg);

        double *centro = malloc(2*sizeof(double));
        centroDeMassa(forma, centro);

        fprintf(svg, "<ellipse cx=\"%lf\" cy=\"%lf\" rx=\"%lf\" ry=\"%lf\" stroke=\"%s\" fill-opacity=\"0\" />\n", 
            centro[0], 
            centro[1], 
            getRetangulo_w(r)/2, 
            getRetangulo_h(r)/2, 
            cor);
        free(centro);
    }	
}