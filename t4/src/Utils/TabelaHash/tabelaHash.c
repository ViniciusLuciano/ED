#include "tabelaHash.h"

int mult[10000];

typedef struct node {
	Objeto objeto;
	struct node* prox;
	struct node* ant;
	bool excluido;
} *pNode;

typedef struct tabelaHash {
	pNode *hash;
	int tam;
    bool (*equals)(Objeto objeto, char* chave);
    char* (*getChave)(Objeto objeto);
    void (*destruirObjeto)(Objeto objeto);
} *pTabelaHash;

int encontrarPrimo(int v) {
	int n = 2;
	int numPrimo = 2;
	int index = 0;
	while (n <= v) {
		int divisores = 0;
		for(int i = 1; i <= sqrt(n); i++) {
			if (n%i==0) divisores++;
		}
		if (divisores != 1) n++;
		else {
			mult[index++] = n;
			numPrimo = n;
			n++;
		}
	}

	return numPrimo;
}

TabelaHash criarTabelaHash(int tam, bool (*equals)(Objeto objeto, char* chave), 
                                    char* (*getChave)(Objeto objeto),
                                    void (*destruirObjeto)(Objeto objeto)) {
	pTabelaHash tabelaHash = malloc(sizeof(struct tabelaHash));
	tabelaHash->tam = encontrarPrimo(tam);
	tabelaHash->hash = malloc(tabelaHash->tam*sizeof(pNode));
    tabelaHash->equals = equals;
    tabelaHash->getChave = getChave;
    tabelaHash->destruirObjeto = destruirObjeto;
	for(int i = 0; i < tabelaHash->tam; i++) tabelaHash->hash[i] = NULL;
	return tabelaHash;
}


void destruir(pTabelaHash t, pNode inicio) {
	pNode aux;
	aux = inicio;

	while (aux != NULL) {
		inicio = inicio->prox;
		if (t->destruirObjeto != NULL)
			t->destruirObjeto(aux->objeto);
		free(aux);
		aux = inicio;
	}
}

void destruirTabelaHash(TabelaHash t) {
    pTabelaHash tabelaHash = (pTabelaHash) t;
	for(int i = 0; i < tabelaHash->tam; i++) {
		pNode n = tabelaHash->hash[i];
		if(n != NULL) {
			destruir(tabelaHash, n);
		}
	}
	free(tabelaHash->hash);
	free(tabelaHash);
}

void TabelaHash_inserir(TabelaHash t, Objeto objeto) {
    pTabelaHash tabelaHash = (pTabelaHash) t;
	pNode novo = malloc(sizeof(struct node));
	novo->objeto = objeto;
	novo->prox = NULL;
	novo->ant = NULL;
	novo->excluido = false;

    long long key = TabelaHash_getChaveUnica(t, tabelaHash->getChave(objeto));
	if(tabelaHash->hash[key] == NULL) {
		tabelaHash->hash[key] = novo;
	} else {
		pNode aux = tabelaHash->hash[key];
		while(1) {
			if(aux->prox == NULL) {
				aux->prox = novo;
				novo->ant = aux;
				break;
			}
			aux = aux->prox;
		}
	}
}

bool TabelaHash_removerObjeto(TabelaHash t, char* chave) {
	pTabelaHash tabelaHash = (pTabelaHash) t;
    long long key = TabelaHash_getChaveUnica(t, chave);

	pNode n = tabelaHash->hash[key];

	while (n != NULL && !tabelaHash->equals(n->objeto, chave)) {
		n = n->prox;
	}

	if (n == NULL) return false;


	if (n->ant != NULL) { // Nao é o primeiro
		n->ant->prox = n->prox;
		if (n->prox != NULL)
			n->prox->ant = n->ant;
	} else { // É o primeiro
		tabelaHash->hash[key] = n->prox;
	}

	if (tabelaHash->destruirObjeto != NULL) {
		tabelaHash->destruirObjeto(n->objeto);
	}
	free(n);

	return true;
}

Objeto TabelaHash_getObjeto(TabelaHash t, char* chave) {
    pTabelaHash tabelaHash = (pTabelaHash) t;
    long long key = TabelaHash_getChaveUnica(t, chave);
    
	pNode n = tabelaHash->hash[key];
	while (n != NULL && n->objeto != NULL && !tabelaHash->equals(n->objeto, chave)) {
		n = n->prox;
	}

	if (n == NULL || n->excluido == true) return NULL;

	return n->objeto;
}

// Key
long long TabelaHash_getChaveUnica(TabelaHash t, char* chave) {
    pTabelaHash tabelaHash = (pTabelaHash) t;
	long long total = 0;

	for(int i = 0; i < strlen(chave); i++) {
		total = total + (chave[i]*mult[i]);
	}

	return total%tabelaHash->tam;
}