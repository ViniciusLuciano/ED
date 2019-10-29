#ifndef TABELAHASH_H
#define TABELAHASH_H

#include "../../headers.h"

typedef void* Objeto;
typedef void* TabelaHash;


TabelaHash criarTabelaHash(int tam, bool(*equals)(Objeto objeto, char* chave), 
                                    char* (*getChave)(Objeto objeto),
                                    void (*destruirObjeto)(Objeto objeto));
void destruirTabelaHash(TabelaHash t);
void TabelaHash_inserir(TabelaHash t, Objeto objeto);
Objeto TabelaHash_getObjeto(TabelaHash t, char* chave);
int TabelaHash_getChaveUnica(TabelaHash t, char* chave);
bool TabelaHash_removerObjeto(TabelaHash t, char* chave);

#endif