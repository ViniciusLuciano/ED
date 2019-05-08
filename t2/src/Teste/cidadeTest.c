#include "../headers.h"
#include "../Objetos/Cidade/cidade.h"
#include "../Objetos/Quadra/quadra.h"

/*
gcc -o teste cidadeTest.c ../Objetos/Quadra/quadra.c ../Objetos/Cidade/cidade.c ../Utils/Lista/lista.c ../Objetos/Hidrante/hidrante.c ../Objetos/Semaforo/semaforo.c ../Objetos/RadioBase/radioBase.c ../Objetos/Texto/texto.c ../Objetos/Forma/forma.c
*/

int main() {
    Cidade city = criarCidade();
    
    Quadra a = criarQuadra("londrina", 1, 2, 3, 4, "green", "black", "2px");
    Quadra b = criarQuadra("sp", 1, 2, 3, 4, "green", "black", "2px");
    Quadra c = criarQuadra("floripa", 1, 2, 3, 4, "green", "black", "2px");
    Quadra d = criarQuadra("rolandia", 1, 2, 3, 4, "green", "black", "2px");
    Quadra e = criarQuadra("cambe", 1, 2, 3, 4, "green", "black", "2px");

    Hidrante h = criarHidrante("h", 1, 2, "green", "black", "2px");
    Semaforo s = criarSemaforo("s", 1, 2, "green", "black", "2px");
    RadioBase rb = criarRadioBase("rb", 1, 2, "green", "black", "2px");

    setCidade_Quadra(city, a);
    setCidade_Quadra(city, b);
    setCidade_Quadra(city, c);
    setCidade_Quadra(city, d);
    setCidade_Quadra(city, e);

    setCidade_Hidrante(city, h);
    setCidade_Semaforo(city, s);
    setCidade_RadioBase(city, rb);

    Quadra q = getCidade_Quadra(city, "floripa");
    imprimirQuadra(q);

    destruirCidade(city);

    return 0;
}