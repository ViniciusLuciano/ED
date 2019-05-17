#include "semaforo.h"

typedef struct semaforo {
    char id[100], cfill[100], cstrok[100], sw[20];
    double x, y;
}*pSemaforo;

Semaforo criarSemaforo(char *id, double x, double y, char *cfill, char *cstrok, char *sw) {
    Semaforo s = malloc(sizeof(struct semaforo));
    pSemaforo semaforo = (pSemaforo) s;
    strcpy(semaforo->id, id);
    semaforo->x = x;
    semaforo->y = y;
    strcpy(semaforo->cfill, cfill);
    strcpy(semaforo->cstrok, cstrok);
    strcpy(semaforo->sw, sw);
    return semaforo;
}

void destruirSemaforo(Semaforo s) {
    pSemaforo semaforo = (pSemaforo) s;
    free(semaforo);
}

char* getSemaforo_id(Semaforo s) {
    pSemaforo semaforo = (pSemaforo) s;
    return semaforo->id;
}

double getSemaforo_x(Semaforo s) {
    pSemaforo semaforo = (pSemaforo) s;
    return semaforo->x;
}

double getSemaforo_y(Semaforo s) {
    pSemaforo semaforo = (pSemaforo) s;
    return semaforo->y;
}

void setSemaforo_x(Semaforo s, double x) {
    pSemaforo semaforo = (pSemaforo) s;
    semaforo->x = x;
}

void setSemaforo_y(Semaforo s, double y) {
    pSemaforo semaforo = (pSemaforo) s;
    semaforo->y = y;
}

void escreverSemaforo_svg(Semaforo s, FILE *svg) {
    pSemaforo semaforo = (pSemaforo) s;
    fprintf(svg, "<circle cx=\"%lf\" cy=\"%lf\" r=\"5\" stroke=\"%s\" fill=\"%s\" stroke-width=\"%s\" />\n", 
            semaforo->x,
            semaforo->y,
            semaforo->cstrok, 
            semaforo->cfill,
            semaforo->sw);
}

bool semaforoEquals(Semaforo s, char *id) {
    pSemaforo semaforo = (pSemaforo) s;
    return strcmp(semaforo->id, id) == 0;
}

void imprimirSemaforo(Semaforo s) {
    pSemaforo semaforo = (pSemaforo) s;
    printf("id %semaforo\n", semaforo->id);
}
