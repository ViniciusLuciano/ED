CC = gcc
COMPILER_FLAGS = -std=c99
LINKER_FLAGS = -lm
EXEC_NAME = siguel
OBJECTS = *.c Utils/Colisao/colisao.c Utils/Geometria/geometria.c Utils/Poligono/poligono.c Objetos/Cidade/cidade.c Objetos/Circulo/circulo.c Objetos/Forma/forma.c Objetos/Hidrante/hidrante.c Objetos/Quadra/quadra.c Objetos/RadioBase/radioBase.c Objetos/Retangulo/retangulo.c Objetos/Semaforo/semaforo.c Objetos/Texto/texto.c Objetos/Muro/muro.c Objetos/Predio/predio.c Utils/Sort/sort.c Utils/Ponto/ponto.c Utils/Segmento/segmento.c Utils/Vertice/vertice.c Utils/Arvore/arvore.c Utils/TabelaHash/tabelaHash.c Objetos/Estabelecimento/estabelecimento.c Objetos/Estabelecimento/tipoEstabelecimento.c Objetos/Pessoa/pessoa.c Objetos/Morador/morador.c Utils/Grafo/arestaG.c Utils/Grafo/verticeG.c Utils/Grafo/grafo.c Utils/Lista/lista.c

siguel: $(OBJECTS)
	$(CC) $(OBJECTS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(EXEC_NAME)

clean:
	rm -rf *.o
