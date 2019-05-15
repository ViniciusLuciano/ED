#ifndef CIDADE_H
#define CIDADE_H

#include "../../headers.h"
#include "../../Utils/Lista/lista.h"
#include "../../Utils/Geometria/geometria.h"
#include "../Forma/forma.h"
#include "../Texto/texto.h"
#include "../Quadra/quadra.h"
#include "../Hidrante/hidrante.h"
#include "../Semaforo/semaforo.h"
#include "../RadioBase/radioBase.h"
#include "../Circulo/circulo.h"
#include "../Retangulo/retangulo.h"

/*
Uma cidade contem todos os elementos.
Uma cidade não é um TAD!!
*/

typedef struct cidade* Cidade;

Cidade criarCidade();
//Objeto getCidade_objeto(Cidade cidade, char *id);
void destruirCidade(Cidade cidade);
void setCidade_tamanhoMax(Cidade cidade, int i, int nq, int nh, int ns, int nr);
void setCidade_Forma(Cidade cidade, Forma forma);
void setCidade_Quadra(Cidade cidade, Quadra quadra);
void setCidade_Hidrante(Cidade cidade, Hidrante hidrante);
void setCidade_Semaforo(Cidade cidade, Semaforo semaforo);
void setCidade_RadioBase(Cidade cidade, RadioBase radioBase);
void setCidade_Texto(Cidade cidade, Texto texto);
Forma getCidade_Forma(Cidade cidade, char *id);
Quadra getCidade_Quadra(Cidade cidade, char *id);
Hidrante getCidade_Hidrante(Cidade cidade, char *id);
Semaforo getCidade_Semaforo(Cidade cidade, char *id);
RadioBase getCidade_RadioBase(Cidade cidade, char *id);
bool removerCidade_Objeto(Cidade cidade, char *id);
void executeCidade_Quadra(Cidade cidade, double px, double py, double dist, char *op);
void setCidade_CstrkQuadrasInternasCirculo(Cidade cidade, Circulo c, char *cstrk);
void deslocarEquipamentosInternosRetangulo(Cidade cidade, Retangulo r, double dx, double dy);

#endif