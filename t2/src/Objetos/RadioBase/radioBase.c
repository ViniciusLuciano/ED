#include "radioBase.h"

struct radioBase {
    char id[100], cfill[100], cstrok[100], sw[20];
    double x, y;
};

RadioBase criarRadioBase(char *id, double x, double y, char *cfill, char *cstrok, char *sw) {
    RadioBase radioBase = malloc(sizeof(struct radioBase));
    strcpy(radioBase->id, id);
    radioBase->x = x;
    radioBase->y = y;
    strcpy(radioBase->cfill, cfill);
    strcpy(radioBase->cstrok, cstrok);
    strcpy(radioBase->sw, sw);
    return radioBase;
}

void destruirRadioBase(RadioBase radioBase) {
    free(radioBase);
}

char* getRadioBase_id(RadioBase radioBase) {
    return radioBase->id;
}

double getRadioBase_x(RadioBase radioBase) {
    return radioBase->x;
}

double getRadioBase_y(RadioBase radioBase) {
    return radioBase->y;
}

void setRadioBase_x(RadioBase radioBase, double x) {
    radioBase->x = x;
}

void setRadioBase_y(RadioBase radioBase, double y) {
    radioBase->y = y;
}

void escreverRadioBase_svg(RadioBase rb, FILE *svg) {
    fprintf(svg, "<circle cx=\"%lf\" cy=\"%lf\" r=\"5\" stroke=\"%s\" fill=\"%s\" stroke-width=\"%s\" />\n", 
            rb->x,
            rb->y,
            rb->cstrok, 
            rb->cfill,
            rb->sw);
}

bool radioBaseEquals(RadioBase radioBase, char *id) {
    return strcmp(radioBase->id, id) == 0;
}

void imprimirRadioBase(RadioBase radioBase) {
    printf("id %s\n", radioBase->id);
}
