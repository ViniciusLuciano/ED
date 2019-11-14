#include "estabelecimento.h"

typedef struct estabelecimento {
    char cnpj[50], cpf[50], codt[50], cep[50], nome[50], face;
    double num;
    Pessoa proprietario;
    Predio predio;
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

char* Estabelecimento_getChave(Estabelecimento e) {
    pEstabelecimento estabelecimento = (pEstabelecimento) e;
    return estabelecimento->cnpj;
}

char* Estabelecimento_getDados(Estabelecimento estabelecimento, char* dados) {   
    pEstabelecimento e = (pEstabelecimento) estabelecimento;
    sprintf(dados, "Nome: %s\nCNPJ: %s\nCodt: %s\nEndereço: %s %c %.0lf\n",
                 e->nome, e->cnpj, e->codt, e->cep, e->face, e->num);
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

void Estabelecimento_setProprietario(Estabelecimento e, Pessoa proprietario) {
    pEstabelecimento estabelecimento = (pEstabelecimento) e;
    estabelecimento->proprietario = proprietario;
}

Pessoa Estabelecimento_getProprietario(Estabelecimento e) {
    pEstabelecimento estabelecimento = (pEstabelecimento) e;
    return estabelecimento->proprietario;
}

void Estabelecimento_setPredio(Estabelecimento e, Predio predio) {
    pEstabelecimento estabelecimento = (pEstabelecimento) e;
    estabelecimento->predio = predio;
}

Predio Estabelecimento_getPredio(Estabelecimento e) {
    pEstabelecimento estabelecimento = (pEstabelecimento) e;
    return estabelecimento->predio;
}
 