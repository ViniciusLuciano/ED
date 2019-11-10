#ifndef TIPO_ESTABELECIMENTO_H
#define TIPO_ESTABELECIMENTO_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../../Utils/Arvore/arvore.h"
#include "estabelecimento.h"

typedef void* TipoEstabelecimento;

TipoEstabelecimento criarTipoEstabelecimento(char* codt, char* descricao);
void destruirTipoEstabelecimento(TipoEstabelecimento tipoEstabelecimento);
char* TipoEstabelecimento_get_cnpj(TipoEstabelecimento tipoEstabelecimento);

bool tipoEstabelecimentoEquals(TipoEstabelecimento tipoEstabelecimento, char *id);

char* TipoEstabelecimento_getChave(TipoEstabelecimento tipoEstabelecimento);

#endif