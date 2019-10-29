#include <stdio.h>
#include "../Utils/Geometria/geometria.h"
#include "../Utils/Segmento/segmento.h"
#include "../Utils/Vertice/vertice.h"
#include "../Utils/Ponto/ponto.h"

/*
gcc -o teste segmentosTest.c ../Utils/Geometria/geometria.c ../Utils/Segmento/segmento.c ../Utils/Vertice/vertice.c ../Utils/Ponto/ponto.c ../Objetos/Circulo/circulo.c ../Objetos/Forma/forma.c ../Objetos/Retangulo/retangulo.c -lm
*/

int main() {

    Ponto a = criarPonto(1, 4);
    Ponto b = criarPonto(4, 1);
    Ponto c = criarPonto(1, 2);
    Ponto d = criarPonto(4, 4);

    Vertice va = criarVertice(a, calcularAngulo(a, 0, 0));
    Vertice vb = criarVertice(b, calcularAngulo(b, 0, 0));
    Vertice vc = criarVertice(c, calcularAngulo(c, 0, 0));
    Vertice vd = criarVertice(d, calcularAngulo(d, 0, 0));

    Segmento s1 = criarSegmento(va, vb);
    Segmento s2 = criarSegmento(vc, vd);

    int inter = verificarSegmentosInterceptam(s1, s2);
    printf("%d\n", inter);
    return 0;
}