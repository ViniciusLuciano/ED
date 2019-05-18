#include <stdio.h>
#include "../geometria.h"
#include "../Objetos/Circulo/circulo.h"
#include "../Objetos/Forma/forma.h"

/*
gcc -o teste geometriaTest.c ../Objetos/Circulo/circulo.c ../Objetos/Forma/forma.c ../geometria.c ../Objetos/Retangulo/retangulo.c -lm
*/

int main() {
    Circulo c = criarCirculo(1, 2, 3, "green", "black", "2px");
    Forma a = criarForma("1", CIRCULO, c);

    printf("%lf\n", Circulo_get_r(getForma_figura(a)));
    
    if(pontoInternoForma(1, 1, a))
        printf("Ponto interno\n");

    return 0;
}