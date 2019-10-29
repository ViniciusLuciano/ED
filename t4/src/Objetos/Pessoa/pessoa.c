#include "pessoa.h"

typedef struct pessoa {
    char cpf[50], nome[50], sobrenome[50], nasc[50], sexo;
    double num;
}*pPessoa;

Pessoa criarPessoa(char* cpf, char* nome, char* sobrenome, char sexo, char* nasc) {
    Pessoa p = malloc(sizeof(struct pessoa));
    pPessoa pessoa = (pPessoa) p;
    strcpy(pessoa->cpf, cpf);
    strcpy(pessoa->nome, nome);
    strcpy(pessoa->sobrenome, sobrenome);
    strcpy(pessoa->nasc, nasc);
    pessoa->sexo = sexo;
    return pessoa;
}

void destruirPessoa(Pessoa e) {
    pPessoa pessoa = (pPessoa) e;
    free(pessoa);
}

char* Pessoa_get_cpf(Pessoa e) {
    pPessoa pessoa = (pPessoa) e;
    return pessoa->cpf;
}

bool pessoaEquals(Pessoa e, char *id) {
    pPessoa pessoa = (pPessoa) e;
    return strcmp(pessoa->cpf, id) == 0;
}

int Pessoa_getSize() {
    return sizeof(struct pessoa);
}

char* Pessoa_getChave(Pessoa e) {
    pPessoa pessoa = (pPessoa) e;
    return pessoa->cpf;
}