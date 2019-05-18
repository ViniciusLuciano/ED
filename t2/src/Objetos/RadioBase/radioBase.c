#include "radioBase.h"

typedef struct radioBase {
    char id[100], cfill[100], cstrok[100], sw[20];
    double x, y;
}*pRadioBase;

RadioBase criarRadioBase(char *id, double x, double y, char *cfill, char *cstrok, char *sw) {
    RadioBase rb = malloc(sizeof(struct radioBase));
    pRadioBase radioBase = (pRadioBase) rb;
    strcpy(radioBase->id, id);
    radioBase->x = x;
    radioBase->y = y;
    strcpy(radioBase->cfill, cfill);
    strcpy(radioBase->cstrok, cstrok);
    strcpy(radioBase->sw, sw);
    return radioBase;
}

void destruirRadioBase(RadioBase rb) {
    pRadioBase radioBase = (pRadioBase) rb;
    free(radioBase);
}

char* getRadioBase_id(RadioBase rb) {
    pRadioBase radioBase = (pRadioBase) rb;
    return radioBase->id;
}

double getRadioBase_x(RadioBase rb) {
    pRadioBase radioBase = (pRadioBase) rb;
    return radioBase->x;
}

double getRadioBase_y(RadioBase rb) {
    pRadioBase radioBase = (pRadioBase) rb;
    return radioBase->y;
}

void setRadioBase_x(RadioBase rb, double x) {
    pRadioBase radioBase = (pRadioBase) rb;
    radioBase->x = x;
}

void setRadioBase_y(RadioBase rb, double y) {
    pRadioBase radioBase = (pRadioBase) rb;
    radioBase->y = y;
}

void escreverRadioBase_svg(RadioBase rb, FILE *svg) {
    pRadioBase radioBase = (pRadioBase) rb;
    fprintf(svg, "<circle cx=\"%lf\" cy=\"%lf\" r=\"5\" stroke=\"%s\" fill=\"%s\" stroke-width=\"%s\" />\n", 
            radioBase->x,
            radioBase->y,
            radioBase->cstrok, 
            radioBase->cfill,
            radioBase->sw);
    
    fprintf(svg, "<text x=\"%lf\" y=\"%lf\" fill=\"white\" font-size=\"6\" style=\"z-index:100\">RB</text>\n",
            radioBase->x - 3.6,
            radioBase->y + 2);
}

bool radioBaseEquals(RadioBase rb, char *id) {
    pRadioBase radioBase = (pRadioBase) rb;
    return strcmp(radioBase->id, id) == 0;
}

void imprimirRadioBase(RadioBase rb) {
    pRadioBase radioBase = (pRadioBase) rb;
    printf("id %s\n", radioBase->id);
}
