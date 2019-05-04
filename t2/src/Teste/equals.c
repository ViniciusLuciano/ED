#include <stdio.h>
#include "../Objetos/Quadra/quadra.h"
#include "../Utils/Lista/lista.h"

int main() {
    Quadra a = criarQuadra(1, 2, 3, 4, "londrina");
    Quadra b = criarQuadra(1, 2, 3, 4, "sp");
    Quadra c = criarQuadra(1, 2, 3, 4, "c");
    Quadra d = criarQuadra(1, 2, 3, 4, "d");
    Quadra e = criarQuadra(1, 2, 3, 4, "cambe");

    Lista l = criarLista(15);
    inserirUltimo(l, a);
    inserirUltimo(l, b);
    inserirUltimo(l, c);
    inserirUltimo(l, d);
    inserirUltimo(l, e);

    printf("Lista antes de retirar: \n");
    imprimirLista(l, imprimirQuadra);

    printf("\nLista depois de retirar: \n");
    Quadra k = criarQuadra(1, 2, 3, 4, "cambe");
    excluirObjeto(l, k, quadraEquals);
    imprimirLista(l, imprimirQuadra);

    printf("\nEncontrar objeto: \n");
    Quadra xd = encontrarObjeto(l, c, quadraEquals);
    imprimirQuadra(xd);
}
