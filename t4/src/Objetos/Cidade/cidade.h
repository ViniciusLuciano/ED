#ifndef CIDADE_H
#define CIDADE_H

#include "../../headers.h"
#include "../../Utils/Lista/lista.h"
#include "../../Utils/Geometria/geometria.h"
#include "../../Utils/Sort/sort.h"
#include "../../Utils/Ponto/ponto.h"
#include "../../Utils/Segmento/segmento.h"
#include "../../Utils/Vertice/vertice.h"
#include "../../Utils/Arvore/arvore.h"
#include "../../Utils/TabelaHash/tabelaHash.h"
#include "../Forma/forma.h"
#include "../Texto/texto.h"
#include "../Quadra/quadra.h"
#include "../Hidrante/hidrante.h"
#include "../Semaforo/semaforo.h"
#include "../RadioBase/radioBase.h"
#include "../Circulo/circulo.h"
#include "../Retangulo/retangulo.h"
#include "../Predio/predio.h"
#include "../Muro/muro.h"
#include "../Estabelecimento/tipoEstabelecimento.h"
#include "../Estabelecimento/estabelecimento.h"
#include "../Pessoa/pessoa.h"
#include "../Morador/morador.h"

#include <string.h>
#include <stdlib.h>
#include <limits.h>

#define forEach(item, raiz) \
    for (Node (item) = (raiz); (item) != NULL; (item) = next(item))

/*
Uma cidade contem todos os elementos.
*/

typedef void* Cidade;

Cidade criarCidade(int i, int nq, int nh, int ns, int nr, int np, int nm);
void destruirCidade(Cidade cidade);
void Cidade_setForma(Cidade cidade, Forma forma);
void Cidade_setQuadra(Cidade cidade, Quadra quadra);
void Cidade_setHidrante(Cidade cidade, Hidrante hidrante);
void Cidade_setSemaforo(Cidade cidade, Semaforo semaforo);
void Cidade_setRadioBase(Cidade cidade, RadioBase radioBase);
void Cidade_setTexto(Cidade cidade, Texto texto);
void Cidade_setPredio(Cidade cidade, Predio predio);
void Cidade_setMuro(Cidade cidade, Muro muro);
void Cidade_setEstabelecimento(Cidade c, Estabelecimento estabelecimento);
void Cidade_setTipoEstabelecimento(Cidade c, TipoEstabelecimento tipoEstabelecimento);
void Cidade_setPessoa(Cidade c, Pessoa pessoa);
void Cidade_setMorador(Cidade c, Morador morador);
Predio Cidade_getPredio(Cidade c, char* cep, char face, double num);
Forma Cidade_getForma(Cidade cidade, char *id);
Quadra Cidade_getQuadra(Cidade cidade, char *id);
Hidrante Cidade_getHidrante(Cidade cidade, char *id);
Semaforo Cidade_getSemaforo(Cidade cidade, char *id);
RadioBase Cidade_getRadioBase(Cidade cidade, char *id);
Estabelecimento Cidade_getEstabelecimento(Cidade c, char* id);
TipoEstabelecimento Cidade_getTipoEstabelecimento(Cidade c, char* id);
Pessoa Cidade_getPessoa(Cidade c, char* id);
Morador Cidade_getMorador(Cidade c, char* id);
bool Cidade_removerObjeto(Cidade cidade, char *id);
void Cidade_removerQuadrasInternasEquipamento(Cidade cidade, double px, double py, double dist, char *op, FILE *txt);
void Cidade_setCstrkQuadrasInternasCirculo(Cidade cidade, Circulo c, char *cstrk, FILE *txt);
void Cidade_deslocarEquipamentosInternosRetangulo(Cidade cidade, Retangulo r, double dx, double dy, FILE *txt);
void Cidade_escreverSvg(Cidade cidade, FILE *svg);
void Cidade_escreverFormasEnvoltas(Cidade cidade, FILE *svg, char *cor);
void Cidade_processarFocoIncendio(Cidade c, double x, double y, int ns, double r, FILE *txt, FILE *svg);
void Cidade_processarObjetosProximos(Cidade c, char sinal, int k, char cep[], char face, double num, FILE* txt, FILE *svg, char tipo[]);
void Cidade_processarBombaRaioLuminoso(Cidade c, double x, double y, FILE *svg, bool brl, FILE* txt, FILE* arq);
void Cidade_escreverArvoreSvg(Cidade c, char t, FILE *arq);
void Cidade_navegarArvore(Cidade c, char t);
void Cidade_processarMPLG(Cidade c, Poligono poligono);
void Cidade_processarCATAC(Cidade c, Poligono poligono);
void Cidade_processarEPLG(Cidade c, Poligono poligono, char* tipo);

void imprimirCidade(Cidade c);

double obj_getComparador(Objeto objeto);
Objeto obj_getObjeto(Objeto objeto);
#endif