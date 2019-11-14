#include "morador.h"

typedef struct morador {
    char cpf[20], cep[30], complemento[30], face;
    double num;
    Quadra quadra;
    Predio predio;
    Pessoa pessoa;
}*pMorador;

Morador criarMorador(char* cpf, char* cep, char face, double num, char* complemento) {
    Morador e = malloc(sizeof(struct morador));
    pMorador morador = (pMorador) e;
    strcpy(morador->cpf, cpf);
    strcpy(morador->cep, cep);
    strcpy(morador->complemento, complemento);
    morador->face = face;
    morador->num = num;
    return morador;
}

void destruirMorador(Morador m) {
    pMorador morador = (pMorador) m;
    if (morador != NULL) {
        free(morador);
        morador = NULL;
    }
}

char* Morador_get_cpf(Morador m) {
    pMorador morador = (pMorador) m;
    return morador->cpf;
}

bool moradorEquals(Morador m, char *id) {
    pMorador morador = (pMorador) m;
    return strcmp(morador->cpf, id) == 0;
}

char* Morador_getChave(Morador m) {
    pMorador morador = (pMorador) m;
    return morador->cpf;
}

int Morador_compararChave(Morador m1, Morador m2) {
    pMorador morador1 = (pMorador) m1;
    pMorador morador2 = (pMorador) m2;
    return strcmp(morador1->cpf, morador2->cpf);
}

char* Morador_getDados(Morador morador, char* dados) {   
    pMorador m = (pMorador) morador;
    sprintf(dados, "Nome: %s\nCPF: %s\nEndereço: %s %c %.0lf %s", 
            m->pessoa != NULL ? Pessoa_getNome(m->pessoa) : "nome",
            m->cpf, m->cep, m->face, m->num, m->complemento);
    return dados;
}

char* Morador_getCep(Morador morador) {
    pMorador m = (pMorador) morador;
    return m->cep;
}

void Morador_mudarEndereco(Morador morador, char* cep, char face, double num, char* complemento) {
    pMorador m = (pMorador) morador;
    strcpy(m->cep, cep);
    strcpy(m->complemento, complemento);
    m->face = face;
    m->num = num;
}

void Morador_setQuadra(Morador m, Quadra quadra) {
    pMorador morador = (pMorador) m;
    morador->quadra = quadra;
}

Quadra Morador_getQuadra(Morador m) {
    pMorador morador = (pMorador) m;
    return morador->quadra;
}

void Morador_setPredio(Morador m, Predio predio) {
    pMorador morador = (pMorador) m;
    morador->predio = predio;
}

Predio Morador_getPredio(Morador m) {
    pMorador morador = (pMorador) m;
    return morador->predio;
}

void Morador_setPessoa(Morador m, Pessoa pessoa) {
    pMorador morador = (pMorador) m;
    morador->pessoa = pessoa;
}