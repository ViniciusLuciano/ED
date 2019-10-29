#ifndef PESSOA_H
#define PESSOA_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef void* Pessoa;

Pessoa criarPessoa(char* cpf, char* nome, char* sobrenome, char sexo, char* nasc);
void destruirPessoa(Pessoa pessoa);
char* Pessoa_get_cpf(Pessoa pessoa);
void Pessoa_escreverSvg(Pessoa pessoa, FILE *SVG);


bool pessoaEquals(Pessoa pessoa, char *id);
int Pessoa_getSize();

char* Pessoa_getChave(Pessoa pessoa);

#endif