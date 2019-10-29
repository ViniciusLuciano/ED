#include "../headers.h"
#include "../Objetos/Cidade/cidade.h"
#include "../Objetos/Quadra/quadra.h"

/*
gcc -o teste cidadeTest.c ../Objetos/Quadra/quadra.c ../Objetos/Cidade/cidade.c ../Utils/Lista/lista.c ../Objetos/Hidrante/hidrante.c ../Objetos/Semaforo/semaforo.c ../Objetos/RadioBase/radioBase.c ../Objetos/Texto/texto.c ../Objetos/Forma/forma.c
*/

int main() {
    Cidade city = criarCidade(10, 10, 10, 10, 10);
    
    Quadra a = criarQuadra("londrina", 1, 2, 3, 4, "green", "black", "2px");
    Quadra b = criarQuadra("sp", 1, 2, 3, 4, "green", "black", "2px");
    Quadra c = criarQuadra("floripa", 1, 2, 3, 4, "green", "black", "2px");
    Quadra d = criarQuadra("rolandia", 1, 2, 3, 4, "green", "black", "2px");
    Quadra e = criarQuadra("cambe", 1, 2, 3, 4, "green", "black", "2px");

    Hidrante h = criarHidrante("h", 1, 2, "green", "black", "2px");
    Semaforo s = criarSemaforo("s", 1, 2, "green", "black", "2px");
    RadioBase rb = criarRadioBase("rb", 1, 2, "green", "black", "2px");

    Cidade_setQuadra(city, a);
    Cidade_setQuadra(city, b);
    Cidade_setQuadra(city, c);
    Cidade_setQuadra(city, d);
    Cidade_setQuadra(city, e);

    Cidade_setHidrante(city, h);
    Cidade_setSemaforo(city, s);
    Cidade_setRadioBase(city, rb);

    Quadra q = Cidade_getQuadra(city, "floripa");
    Quadra_imprimir(q);

    Semaforo xd = Cidade_getSemaforo(city, "s");
    Semaforo_imprimir(xd);

    destruirCidade(city);

    return 0;
}