#include "radioBase.h"

typedef struct radioBase{
    char id[100], cfill[100], cstrok[100], sw[20];
    double x, y;
} *ponteiroRadioBase;

RadioBase criarRadioBase(char *id, double x, double y, char *cfill, char *cstrok, char *sw) {
    ponteiroRadioBase rb = malloc(sizeof(struct radioBase));
    RadioBase radioBase = rb;
    strcpy(rb->id, id);
    rb->x = x;
    rb->y = y;
    strcpy(rb->cfill, cfill);
    strcpy(rb->cstrok, cstrok);
    strcpy(rb->sw, sw);
    return radioBase;
}

void destruirRadioBase(RadioBase radioBase) {
    ponteiroRadioBase rb = (ponteiroRadioBase) radioBase;
    free(rb);
}

char* getRadioBase_id(RadioBase radioBase) {
    ponteiroRadioBase rb = (ponteiroRadioBase) radioBase;
    return rb->id;
}

double getRadioBase_x(RadioBase radioBase) {
    ponteiroRadioBase rb = (ponteiroRadioBase) radioBase;
    return rb->x;
}

double getRadioBase_y(RadioBase radioBase) {
    ponteiroRadioBase rb = (ponteiroRadioBase) radioBase;
    return rb->y;
}

bool radioBaseEquals(RadioBase radioBase, char *id) {
    ponteiroRadioBase rb = (ponteiroRadioBase) radioBase;
    return strcmp(rb->id, id) == 0;
}

void imprimirRadioBase(RadioBase radioBase) {
    ponteiroRadioBase rb = (ponteiroRadioBase) radioBase;
    printf("id %s\n", rb->id);
}
