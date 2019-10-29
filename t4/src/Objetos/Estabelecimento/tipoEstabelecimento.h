#ifndef TIPO_ESTABELECIMENTO_H
#define TIPO_ESTABELECIMENTO_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef void* TipoEstabelecimento;

TipoEstabelecimento criarTipoEstabelecimento(char* codt, char* descricao);
void destruirTipoEstabelecimento(TipoEstabelecimento tipoEstabelecimento);
char* TipoEstabelecimento_get_cnpj(TipoEstabelecimento tipoEstabelecimento);
void TipoEstabelecimento_escreverSvg(TipoEstabelecimento tipoEstabelecimento, FILE *SVG);


bool tipoEstabelecimentoEquals(TipoEstabelecimento tipoEstabelecimento, char *id);
int TipoEstabelecimento_getSize();

char* TipoEstabelecimento_getChave(TipoEstabelecimento tipoEstabelecimento);

#endif