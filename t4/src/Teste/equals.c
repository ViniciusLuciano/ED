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

    Lista l = criarLista(10);
    lista_inserirUltimo(l, a);
    lista_inserirUltimo(l, b);
    lista_inserirUltimo(l, c);
    lista_inserirUltimo(l, d);  
    lista_inserirUltimo(l, e);

    printf("Lista antes de retirar: \n");
    lista_imprimir(l, Quadra_imprimir);

    printf("\nLista depois de retirar: \n");
    lista_excluirObjeto(l, "rolandia", quadraEquals, destruirQuadra);
    lista_imprimir(l, Quadra_imprimir);

    printf("\nEncontrar objeto: \n");
    Quadra xd = lista_getObjeto(l, "londrina", quadraEquals);
    Quadra_imprimir(xd);

    lista_destruir(l, destruirQuadra);
}
