CC = gcc
COMPILER_FLAGS = -std=c99
LINKER_FLAGS = -lm
EXEC_NAME = siguel
OBJECTS = *.c Utils/Colisao/colisao.c Utils/Geometria/geometria.c Utils/Lista/lista.c Objetos/Cidade/cidade.c Objetos/Circulo/circulo.c Objetos/Forma/forma.c Objetos/Hidrante/hidrante.c Objetos/Quadra/quadra.c Objetos/RadioBase/radioBase.c Objetos/Retangulo/retangulo.c Objetos/Semaforo/semaforo.c Objetos/Texto/texto.c

siguel: $(OBJECTS)
	$(CC) $(OBJECTS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(EXEC_NAME)

clean:
	rm -rf *.c
