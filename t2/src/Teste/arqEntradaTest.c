#include <stdio.h>
#include "../utils.h"

/*
gcc -o teste arqEntradaTest.c ../utils.c ../Objetos/Circulo/circulo.c ../Objetos/Retangulo/retangulo.c ../Objetos/Texto/texto.c ../Objetos/Quadra/quadra.c ../Objetos/Hidrante/hidrante.c ../Objetos/Semaforo/semaforo.c ../Objetos/RadioBase/radioBase.c ../Utils/Lista/lista.c ../Objetos/Forma/forma.c
*/


int main() {

    FILE* a = abrirArquivo("/home/vinicius/codes/evandro/projeto/ED", "arq.txt", "r");
    processarArquivoEntrada(a, "x", "y");
    fclose(a);
    
    return 0;
}