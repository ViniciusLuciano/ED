#include "arvore.h"

// Aux utilizado para forEach
typedef struct node {
	Objeto objeto;
	struct node* esq;
	struct node* dir;
	struct node* pai;
	int cor, aux;
} *pNode;

typedef struct arvore {
	pNode* raiz;
	int(*compararChave)(Objeto obj1, Objeto obj2);
	void(*destruirObjeto)(Objeto objeto);
	int tamObjeto; // Tamanho da struct do objeto para o memcpy
	int tamArvore;
} *pArvore;

pNode getTNULL() {
	static pNode TNULL = NULL;

	if (TNULL == NULL) {
		TNULL = (pNode)malloc(sizeof(struct node));
		TNULL->objeto = NULL;
		TNULL->cor = PRETO;
		TNULL->dir = NULL;
		TNULL->esq = NULL;
		TNULL->aux = 0;
	}
	return TNULL;
}

Node Arvore_getTNULL() {
	return getTNULL();
}

char* Node_getCor(Node n) {
	pNode node = (pNode) n;
	return node->cor == VERMELHO ? "Vermelho" : "Preto";
}

void desalocarNode(pArvore a, pNode node) {
    if(node == getTNULL())
        return;
    desalocarNode(a, node->esq);
    desalocarNode(a, node->dir);
    a->destruirObjeto(node->objeto);
    free(node);
}

void destruirArvore(Arvore arvore) {
    pArvore a = (pArvore) arvore;
    if(a->raiz == NULL)
        return;
    desalocarNode(a, (*a->raiz));
    free(a->raiz);
    free(a);
}

void destruirTNULL() {
	free(getTNULL());
}

void rotacionarEsquerda(pNode* raiz, pNode x) {
	pNode y = x->dir;
	x->dir = y->esq;
	if (y->esq != getTNULL()) {
		y->esq->pai = x;
	}
	if (y != getTNULL())
		y->pai = x->pai;

	if (x->pai == NULL) {
		(*raiz) = y;
	} else if (x == x->pai->esq) {
		x->pai->esq = y;
	} else {
		x->pai->dir = y;
	}
	y->esq = x;

	if(x != getTNULL())
		x->pai = y;
}

void rotacionarDireita(pNode* raiz, pNode x) {
	pNode y = x->esq;
	x->esq = y->dir;
	if (y->dir != getTNULL()) {
		y->dir->pai = x;
	}
	if (y != getTNULL())
		y->pai = x->pai;

	if (x->pai == NULL) {
		(*raiz) = y;
	} else if (x == x->pai->dir) {
		x->pai->dir = y;
	} else {
		x->pai->esq = y;
	}
	y->dir = x;

	if (x != getTNULL())
		x->pai = y;
}

void fixInserir(pNode* raiz, pNode k) {
	pNode u;
	while (k->pai->cor == VERMELHO) {
		if (k->pai == k->pai->pai->dir) {
			u = k->pai->pai->esq;
			if (u != NULL && u->cor == VERMELHO) {
				// Caso 3.1
				u->cor = PRETO;
				k->pai->cor = PRETO;
				k->pai->pai->cor = VERMELHO;
				k = k->pai->pai;

			} else {
				if (k == k->pai->esq) {
					// Caso 3.2.2
					k = k->pai;
					rotacionarDireita(raiz, k);
				}

				k->pai->cor = PRETO;
				k->pai->pai->cor = VERMELHO;
				rotacionarEsquerda(raiz, k->pai->pai);
			}

		} else {
			u = k->pai->pai->dir; // Tio

			if (u != NULL && u->cor == VERMELHO) {
				// mirror Caso 3.1
				u->cor = PRETO;
				k->pai->cor = PRETO;
				k->pai->pai->cor = VERMELHO;
				k = k->pai->pai;

			} else {
				if (k == k->pai->dir) {
					// mirror Caso 3.2.2
					k = k->pai;
					rotacionarEsquerda(raiz, k);
				}
				// mirror Caso 3.2.1
				k->pai->cor = PRETO;
				k->pai->pai->cor = VERMELHO;
				rotacionarDireita(raiz, k->pai->pai);
			}
		}
		if (k == (*raiz)) {
			break;
		}
	}
	(*raiz)->cor = PRETO;
}

void Arvore_inserir(Arvore arvore, Objeto objeto) {
    pArvore a = (pArvore) arvore;
	a->tamArvore++;

	pNode novo = (pNode)malloc(sizeof(struct node));
	novo->objeto = objeto;
	novo->cor = VERMELHO;
	novo->dir = getTNULL();
	novo->esq = getTNULL();
	novo->pai = NULL;
	novo->aux = 0;

	pNode anterior = NULL;
	pNode atual = (*a->raiz);
	while (atual != getTNULL()) {
		anterior = atual;

		if (a->compararChave(objeto, atual->objeto) < 0) {
            atual = atual->esq;
		} else {
            atual = atual->dir;
		}
	}

	// Anterior é pai de atual
	novo->pai = anterior;
	if (anterior == NULL) {
		(*a->raiz) = novo;
	} else if (a->compararChave(objeto, anterior->objeto) < 0) {
        anterior->esq = novo;
	} else {
        anterior->dir = novo;
	}


	// O novo é a raiz
	if (novo->pai == NULL) {
		novo->cor = PRETO;
		return;
	}

	if (novo->pai->pai == NULL) {
		return;
	}

	// Arrumar a arvore
	fixInserir(a->raiz, novo);
}

void fixDeletar(pNode* raiz, pNode x) {

	while (x != (*raiz) && x->cor == PRETO) {
		if (x == x->pai->esq) {
			pNode w = x->pai->dir;

			if(w->cor == VERMELHO) {
				w->cor = PRETO;
				x->pai->cor = VERMELHO;
				rotacionarEsquerda(raiz, x->pai);
				w = x->pai->dir;
			}

			if (w->esq->cor == PRETO && w->dir->cor == PRETO) {
				w->cor = VERMELHO;
				x = x->pai;

			} else {

				if (w->dir->cor == PRETO) {
					w->esq->cor = PRETO;
					w->cor = VERMELHO;
					rotacionarDireita(raiz, w);
					w = x->pai->dir;
				}

				w->cor = x->pai->cor;
				x->pai->cor = PRETO;
				w->dir->cor = PRETO;

				rotacionarEsquerda(raiz, x->pai);
				x = (*raiz);
			}

		} else {
			pNode w = x->pai->esq;

			if (w->cor == VERMELHO) {
				w->cor = PRETO;
				w->pai->cor = VERMELHO;
				rotacionarDireita(raiz, x->pai);
				w = x->pai->esq;
			}

			if (w->dir->cor == PRETO && w->esq->cor == PRETO) {
				w->cor = VERMELHO;
				x = x->pai;

			} else {

				if (w->esq->cor == PRETO) {
					w->dir->cor = PRETO;
					w->cor = VERMELHO;
					rotacionarEsquerda(raiz, w);
					w = x->pai->esq;
				}

				w->cor = x->pai->cor;
				x->pai->cor = PRETO;
				w->esq->cor = PRETO;
				rotacionarDireita(raiz, x->pai);
				x = (*raiz);
			}
		}
	}
	x->cor = PRETO;
}


bool Arvore_removerObjeto(Arvore arvore, Objeto objeto) {
    pArvore a = (pArvore) arvore;
	// Encontrar o node que contem a mesma chave
	pNode node = (*a->raiz);
	pNode z = getTNULL();
	pNode x, y;

	while (node != getTNULL()) {
		if (a->compararChave(objeto, node->objeto) == 0) {
			z = node;
			break;
		}

		if(a->compararChave(objeto, node->objeto) >= 0)
            node = node->dir;
        else
            node = node->esq;
	}

	if (z == getTNULL()) {
		printf("Elemento não encontrado.\n");
		return false;
	}

	a->tamArvore--;
	if (z->esq == getTNULL() || z->dir == getTNULL()) {
		y = z;
	} else {
		y = z->dir;
		while (y->esq != getTNULL())
			y = y->esq;
	}

	if (y->esq != getTNULL())
		x = y->esq;
	else
		x = y->dir;

	x->pai = y->pai;
	if (y->pai != NULL) {
		if (y == y->pai->esq)
			y->pai->esq = x;
		else
			y->pai->dir = x;
	} else {
		(*a->raiz) = x;
	}

	if (y != z) {
		memcpy(z->objeto, y->objeto, a->tamObjeto);
	}

	if (y->cor ==  PRETO) {
		fixDeletar(a->raiz, x);
	}

	a->destruirObjeto(y->objeto);
	free(y);
	return true;
}

Arvore criarArvore(int(*compararChave)(Objeto obj1, Objeto obj2), int tamObjeto, 
													void(*destruirObjeto)(Objeto objeto)) {
    pArvore arvore = malloc(sizeof(struct arvore));
    arvore->raiz = (pNode*)malloc(sizeof(pNode));
    (*arvore->raiz) = getTNULL();
    arvore->compararChave = compararChave;
    arvore->tamObjeto = tamObjeto;
	arvore->destruirObjeto = destruirObjeto;
	arvore->tamArvore = 0;
    return arvore;
}

Objeto Arvore_getObjeto(Arvore arvore, Objeto objeto) {
    pArvore a = (pArvore) arvore;
    if (a->raiz == NULL) {
        return NULL;
    }
    
    pNode atualNode = (*a->raiz);
    while (atualNode != NULL) {
        if (a->compararChave(objeto, atualNode->objeto) == 0) {
            return atualNode->objeto;
        }
        
        if (a->compararChave(objeto, atualNode->objeto) > 0)
            atualNode = atualNode->dir;
        else
            atualNode = atualNode->esq;
    }

	a->destruirObjeto(objeto);
    if(atualNode == NULL) {
        return NULL;
    }
}

int Y_PRINT_ARVORE = 15;
void Arvore_escreverSvg_util(pNode node, int x, FILE* svg, char*(*Objeto_getDados)(Objeto objeto, char* dados)) {

	if(node == getTNULL()) return;

	x+=20;
	Arvore_escreverSvg_util(node->esq, x, svg, Objeto_getDados);

	fprintf(svg, "<circle cx=\"%d\" cy=\"%d\" r=\"5\" stroke=\"black\" fill=\"%s\" stroke-width=\"2\" />\n", 
            Y_PRINT_ARVORE,
            x,
            node->cor == VERMELHO ? "red" : "black");
	// fprintf(svg, "<text x=\"%d\" y=\"%d\" fill=\"white\" font-size=\"5\">%.0lf</text>",
    //     Y_PRINT_ARVORE, 
    //     x, 
    //     Hidrante_get_x(node->objeto));

	char dados[150];
	fprintf(svg, "<text x=\"%d\" y=\"%d\" fill=\"blue\" font-size=\"5\">%s</text>",
        Y_PRINT_ARVORE, 
        x, 
        Objeto_getDados(node->objeto, dados));
	Y_PRINT_ARVORE+=13;

	Arvore_escreverSvg_util(node->dir, x, svg, Objeto_getDados);
}

void Arvore_escreverSvg(Arvore arvore, char* nomeArquivo, char*(*Objeto_getDados)(Objeto objeto, char* dados)) {
    pArvore a = (pArvore) arvore;
	FILE* svg = fopen(nomeArquivo, "w");
	fprintf(svg, "<svg>\n");
	Arvore_escreverSvg_util((*a->raiz), 0, svg, Objeto_getDados);
	fprintf(svg, "</svg>\n");
	fclose(svg);
}



Node next(Node node) {
	pNode p = (pNode) node;
	if (p == getTNULL()) return NULL;

	if (p->aux == 0) {
		p->aux++;
		if (p->esq != getTNULL()) p = p->esq;
	} else if (p->aux == 1) {
		p->aux++;
	    if (p->dir != getTNULL()) p = p->dir;
	} else {
		p->aux = 0;
	    p = p->pai;
	}

	return p;
}

Node Arvore_getRaiz(Arvore arvore) {
	pArvore a = (pArvore) arvore;
	return (*a->raiz) == getTNULL() ? NULL : (*a->raiz);
}

int Node_getAux(Node node) {
	pNode n = (pNode) node;
	return n->aux;
}

Objeto Node_getObjeto(Node node) {
	pNode n = (pNode) node;
	return n->objeto;
}

int Arvore_length(Arvore arvore) {
	pArvore a = (pArvore) arvore;
	return a->tamArvore;
}

Node Node_getDir(Node n) {
	pNode node = (pNode) n;
	return node->dir;
}

Node Node_getEsq(Node n) {
	pNode node = (pNode) n;
	return node->esq;
}

Node Node_getPai(Node n) {
	pNode node = (pNode) n;
	return node->pai;
}

void resetarAux(pNode node) {
	if(node == getTNULL())
        return;
	resetarAux(node->dir);
	resetarAux(node->esq);
	node->aux = 0;
}

void Arvore_resetarAux(Arvore arvore) {
	pArvore a = (pArvore) arvore;
	resetarAux(*a->raiz);
}