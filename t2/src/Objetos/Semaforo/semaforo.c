#include "semaforo.h"

struct semaforo {
    char id[100], cfill[100], cstrok[100], sw[20];
    double x, y;
};

Semaforo criarSemaforo(char *id, double x, double y, char *cfill, char *cstrok, char *sw) {
    Semaforo semaforo = malloc(sizeof(struct semaforo));
    strcpy(semaforo->id, id);
    semaforo->x = x;
    semaforo->y = y;
    strcpy(semaforo->cfill, cfill);
    strcpy(semaforo->cstrok, cstrok);
    strcpy(semaforo->sw, sw);
    return semaforo;
}

void destruirSemaforo(Semaforo semaforo) {
    free(semaforo);
}

char* getSemaforo_id(Semaforo semaforo) {
    return semaforo->id;
}

double getSemaforo_x(Semaforo semaforo) {
    return semaforo->x;
}

double getSemaforo_y(Semaforo semaforo) {
    return semaforo->y;
}

void setSemaforo_x(Semaforo semaforo, double x) {
    semaforo->x = x;
}

void setSemaforo_y(Semaforo semaforo, double y) {
    semaforo->y = y;
}

void escreverSemaforo_svg(Semaforo s, FILE *svg) {
    fprintf(svg, "<circle cx=\"%lf\" cy=\"%lf\" r=\"5\" stroke=\"%s\" fill=\"%s\" stroke-width=\"%s\" />\n", 
            s->x,
            s->y,
            s->cstrok, 
            s->cfill,
            s->sw);
}

bool semaforoEquals(Semaforo semaforo, char *id) {
    return strcmp(semaforo->id, id) == 0;
}

void imprimirSemaforo(Semaforo semaforo) {
    printf("id %semaforo\n", semaforo->id);
}
