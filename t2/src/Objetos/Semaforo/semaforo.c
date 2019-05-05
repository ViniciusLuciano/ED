#include "semaforo.h"

typedef struct semaforo{
    char id[100], cfill[100], cstrok[100], sw[20];
    double x, y;
} *ponteiroSemaforo;

Semaforo criarSemaforo(char *id, double x, double y, char *cfill, char *cstrok, char *sw) {
    ponteiroSemaforo s = malloc(sizeof(struct semaforo));
    Semaforo semaforo = s;
    strcpy(s->id, id);
    s->x = x;
    s->y = y;
    strcpy(s->cfill, cfill);
    strcpy(s->cstrok, cstrok);
    strcpy(s->sw, sw);
    return semaforo;
}

void destruirSemaforo(Semaforo semaforo) {
    ponteiroSemaforo s = (ponteiroSemaforo) semaforo;
    free(s);
}

char* getSemaforo_id(Semaforo semaforo) {
    ponteiroSemaforo s = (ponteiroSemaforo) semaforo;
    return s->id;
}

double getSemaforo_x(Semaforo semaforo) {
    ponteiroSemaforo s = (ponteiroSemaforo) semaforo;
    return s->x;
}

double getSemaforo_y(Semaforo semaforo) {
    ponteiroSemaforo s = (ponteiroSemaforo) semaforo;
    return s->y;
}

bool semaforoEquals(Semaforo semaforo, char *id) {
    ponteiroSemaforo s = (ponteiroSemaforo) semaforo;
    return strcmp(s->id, id) == 0;
}

void imprimirSemaforo(Semaforo semaforo) {
    ponteiroSemaforo s = (ponteiroSemaforo) semaforo;
    printf("id %s\n", s->id);
}
