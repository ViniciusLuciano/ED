#include "../headers.h"
#include "../Objetos/Cidade/cidade.h"
#include "../Objetos/Quadra/quadra.h"


int main() {
    Cidade city = criarCidade();
    
    Quadra a = criarQuadra("londrina", 1, 2, 3, 4, "green", "black", "2px");
    Quadra b = criarQuadra("sp", 1, 2, 3, 4, "green", "black", "2px");
    Quadra c = criarQuadra("floripa", 1, 2, 3, 4, "green", "black", "2px");
    Quadra d = criarQuadra("rolandia", 1, 2, 3, 4, "green", "black", "2px");
    Quadra e = criarQuadra("cambe", 1, 2, 3, 4, "green", "black", "2px");

    setCidade_Quadra(city, a);
    setCidade_Quadra(city, b);
    setCidade_Quadra(city, c);
    setCidade_Quadra(city, d);
    setCidade_Quadra(city, e);

    Quadra q = getCidade_Quadra(city, "floripa");
    imprimirQuadra(q);

    destruirCidade(city);

    return 0;
}