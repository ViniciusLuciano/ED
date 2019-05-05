#include <stdio.h>
#include "../Objetos/Quadra/quadra.h"
#include "../Utils/Lista/lista.h"

/*
gcc -o teste equals.c ../Objetos/Quadra/quadra.c ../Utils/Lista/lista.c
./teste
*/

int main() {
    Quadra a = criarQuadra("londrina", 1, 2, 3, 4, "green", "black", "2px");
    Quadra b = criarQuadra("sp", 1, 2, 3, 4, "green", "black", "2px");
    Quadra c = criarQuadra("floripa", 1, 2, 3, 4, "green", "black", "2px");
    Quadra d = criarQuadra("rolandia", 1, 2, 3, 4, "green", "black", "2px");
    Quadra e = criarQuadra("cambe", 1, 2, 3, 4, "green", "black", "2px");

    Lista l = criarLista(15);
    inserirUltimo(l, a);
    inserirUltimo(l, b);
    inserirUltimo(l, c);
    inserirUltimo(l, d);
    inserirUltimo(l, e);

    printf("Lista antes de retirar: \n");
    imprimirLista(l, imprimirQuadra);
    
    printf("\nLista depois de retirar: \n");
    excluirObjeto(l, "rolandia", quadraEquals, destruirQuadra);
    imprimirLista(l, imprimirQuadra);

    
    printf("\nEncontrar objeto: \n");
    Quadra xd = encontrarObjeto(l, "londrina", quadraEquals);
    imprimirQuadra(xd);

    destruirLista(l, destruirQuadra);
}
