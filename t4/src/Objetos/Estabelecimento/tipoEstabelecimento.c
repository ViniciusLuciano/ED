#include "tipoEstabelecimento.h"

typedef struct tipoEstabelecimento {
    char codt[50], descricao[50];
}*pTipoEstabelecimento;

TipoEstabelecimento criarTipoEstabelecimento(char* codt, char* descricao) {
    TipoEstabelecimento e = malloc(sizeof(struct tipoEstabelecimento));
    pTipoEstabelecimento tipoEstabelecimento = (pTipoEstabelecimento) e;
    strcpy(tipoEstabelecimento->codt, codt);
    strcpy(tipoEstabelecimento->descricao, descricao);
    return tipoEstabelecimento;
}

void destruirTipoEstabelecimento(TipoEstabelecimento e) {
    pTipoEstabelecimento tipoEstabelecimento = (pTipoEstabelecimento) e;
    free(tipoEstabelecimento);
}

char* TipoEstabelecimento_get_codt(TipoEstabelecimento e) {
    pTipoEstabelecimento tipoEstabelecimento = (pTipoEstabelecimento) e;
    return tipoEstabelecimento->codt;
}

bool tipoEstabelecimentoEquals(TipoEstabelecimento e, char *id) {
    pTipoEstabelecimento tipoEstabelecimento = (pTipoEstabelecimento) e;
    return strcmp(tipoEstabelecimento->codt, id) == 0;
}


int TipoEstabelecimento_getSize() {
    return sizeof(struct tipoEstabelecimento);
}

char* TipoEstabelecimento_getChave(TipoEstabelecimento e) {
    pTipoEstabelecimento tipoEstabelecimento = (pTipoEstabelecimento) e;
    return tipoEstabelecimento->codt;
}