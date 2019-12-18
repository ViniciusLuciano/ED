#ifndef GRAFO_H
#define GRAFO_H

#include "../../headers.h"
#include "../TabelaHash/tabelaHash.h"
#include "../Arvore/arvore.h"
#include "arestaG.h"
#include "verticeG.h"

#include <limits.h>
#include <float.h>

typedef void* Grafo;

Grafo criarGrafo(int numVertices);
void destruirGrafo(Grafo grafo);
void Grafo_inserirVerticeG(Grafo g, VerticeG vertice);
void Grafo_inserirArestaG(Grafo g, ArestaG aresta);
VerticeG Grafo_getVerticeG(Grafo g, char* id);
VerticeG* Dijkstra(Grafo grafo, VerticeG verticeOrigem, VerticeG verticeDestino, double(*comparador)(Objeto objeto));

#endif