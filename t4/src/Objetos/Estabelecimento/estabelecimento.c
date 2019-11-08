#include "estabelecimento.h"

typedef struct estabelecimento {
    char cnpj[50], cpf[50], codt[50], cep[50], nome[50], face;
    double num;
}*pEstabelecimento;

Estabelecimento criarEstabelecimento(char* cnpj, char* cpf, char* codt, char* cep, char face, double num, char* nome) {
    Estabelecimento e = malloc(sizeof(struct estabelecimento));
    pEstabelecimento estabelecimento = (pEstabelecimento) e;
    strcpy(estabelecimento->cnpj, cnpj);
    strcpy(estabelecimento->cpf, cpf);
    strcpy(estabelecimento->codt, codt);
    strcpy(estabelecimento->cep, cep);
    strcpy(estabelecimento->nome, nome);
    estabelecimento->face = face;
    estabelecimento->num = num;
    return estabelecimento;
}

void destruirEstabelecimento(Estabelecimento e) {
    pEstabelecimento estabelecimento = (pEstabelecimento) e;
    free(estabelecimento);
}

char* Estabelecimento_get_cnpj(Estabelecimento e) {
    pEstabelecimento estabelecimento = (pEstabelecimento) e;
    return estabelecimento->cnpj;
}

bool estabelecimentoEquals(Estabelecimento e, char *id) {
    pEstabelecimento estabelecimento = (pEstabelecimento) e;
    return strcmp(estabelecimento->cnpj, id) == 0;
}


int Estabelecimento_getSize() {
    return sizeof(struct estabelecimento);
}

char* Estabelecimento_getChave(Estabelecimento e) {
    pEstabelecimento estabelecimento = (pEstabelecimento) e;
    return estabelecimento->cnpj;
}

char* Estabelecimento_getDados(Estabelecimento estabelecimento, char* dados) {   
    pEstabelecimento e = (pEstabelecimento) estabelecimento;
    sprintf(dados, "CNPJ: %s\nCodt: %s\nCEP: %s\nNome: %s\n\n",
                 e->cnpj, e->codt, e->cep, e->nome);
    return dados;
}

int Estabelecimento_compararChave(Estabelecimento a, Estabelecimento b) {
    pEstabelecimento estabelecimento_a = (pEstabelecimento) a;
    pEstabelecimento estabelecimento_b = (pEstabelecimento) b;
    strcmp(estabelecimento_a->cnpj, estabelecimento_b->cnpj);
}

char* Estabelecimento_getCep(Estabelecimento e) {
    pEstabelecimento estabelecimento = (pEstabelecimento) e;
    return estabelecimento->cep;
}

char* Estabelecimento_getCodt(Estabelecimento e) {
    pEstabelecimento estabelecimento = (pEstabelecimento) e;
    return estabelecimento->codt;
}

char Estabelecimento_getFace(Estabelecimento e) {
    pEstabelecimento estabelecimento = (pEstabelecimento) e;
    return estabelecimento->face;
}

double Estabelecimento_getNum(Estabelecimento e) {
    pEstabelecimento estabelecimento = (pEstabelecimento) e;
    return estabelecimento->num;
}