#include "semaforo.h"

typedef struct semaforo {
    double comparador;
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

char* Semaforo_get_id(Semaforo s) {
    pSemaforo semaforo = (pSemaforo) s;
    return semaforo->id;
}

double Semaforo_get_x(Semaforo s) {
    pSemaforo semaforo = (pSemaforo) s;
    return semaforo->x;
}

double Semaforo_get_y(Semaforo s) {
    pSemaforo semaforo = (pSemaforo) s;
    return semaforo->y;
}

void Semaforo_set_x(Semaforo s, double x) {
    pSemaforo semaforo = (pSemaforo) s;
    semaforo->x = x;
}

void Semaforo_set_y(Semaforo s, double y) {
    pSemaforo semaforo = (pSemaforo) s;
    semaforo->y = y;
}

void Semaforo_escreverSvg(Semaforo s, FILE *svg) {
    pSemaforo semaforo = (pSemaforo) s;
    fprintf(svg, "<circle cx=\"%lf\" cy=\"%lf\" r=\"5\" stroke=\"%s\" fill=\"%s\" stroke-width=\"%s\" />\n", 
            semaforo->x,
            semaforo->y,
            semaforo->cstrok, 
            semaforo->cfill,
            semaforo->sw);

    fprintf(svg, "<text x=\"%lf\" y=\"%lf\" fill=\"white\" font-size=\"10\" style=\"z-index:100\">S</text>\n",
            semaforo->x - 3,
            semaforo->y + 3);
}

bool semaforoEquals(Semaforo s, char *id) {
    pSemaforo semaforo = (pSemaforo) s;
    return strcmp(semaforo->id, id) == 0;
}

void Semaforo_imprimir(Semaforo s) {
    pSemaforo semaforo = (pSemaforo) s;
    printf("id %s\n", semaforo->id);
}

double Semaforo_get_comparador(Semaforo s) {
    pSemaforo semaforo = (pSemaforo) s;
    return semaforo->comparador;
}

int Semaforo_compararChave(Semaforo a, Semaforo b) {
    pSemaforo semaforo_a = (pSemaforo) a;
    pSemaforo semaforo_b = (pSemaforo) b;

    if (semaforo_a->x > semaforo_b->x) return 1;
    else if (semaforo_a->x < semaforo_b->x) return -1;
    else {
        if (semaforo_a->y > semaforo_b->y) return 1;
        else if (semaforo_a->y < semaforo_b->y) return -1;
        else return 0;
    }
}

int Semaforo_getSize() {
    return sizeof(struct semaforo);
}

char* Semaforo_getChave(Semaforo s) {
    pSemaforo semaforo = (pSemaforo) s;
    return semaforo->id;
}

char* Semaforo_getDados(Semaforo h, char* dados) {
    pSemaforo semaforo = (pSemaforo) h;
    sprintf(dados, "%0.1lf %0.1lf\n %s\n", semaforo->x, semaforo->y, semaforo->id);
    return dados;
}