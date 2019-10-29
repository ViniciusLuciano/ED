#include "morador.h"

typedef struct morador {
    char cpf[20], cep[30], complemento[30], face;
    double num;
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

void destruirMorador(Morador e) {
    pMorador morador = (pMorador) e;
    if (morador != NULL) {
        morador = NULL;
        free(morador);
    }
}

char* Morador_get_cpf(Morador e) {
    pMorador morador = (pMorador) e;
    return morador->cpf;
}

bool moradorEquals(Morador e, char *id) {
    pMorador morador = (pMorador) e;
    return strcmp(morador->cpf, id) == 0;
}

int Morador_getSize() {
    return sizeof(struct morador);
}

char* Morador_getChave(Morador e) {
    pMorador morador = (pMorador) e;
    return morador->cpf;
}

int Morador_compararChave(Morador m1, Morador m2) {
    pMorador morador1 = (pMorador) m1;
    pMorador morador2 = (pMorador) m2;
    return strcmp(morador1->cpf, morador2->cpf);
}

char* Morador_getDados(Morador morador, char* dados) {   
    pMorador m = (pMorador) morador;
    sprintf(dados, "CPF: %s\nCEP: %s\nComplemento: %s\nNumero: %.0lf\n\n", m->cpf, m->cep, m->complemento, m->num);
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