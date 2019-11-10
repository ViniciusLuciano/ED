#include "predio.h"

typedef struct predio {
    char cep[50], face, id[100];
    double num, f, p, mrg;
    double x, x_max, y, y_max;
    Arvore arvoreMoradores;
    Objeto quadra; // Endereço de memoria da quadra associada
}*pPredio;

Predio criarPredio(char *cep, char face, double num, double f, double p, double mrg) {
    Predio prd = malloc(sizeof(struct predio));
    pPredio predio = (pPredio) prd;
    strcpy(predio->cep, cep);
    predio->face = face;
    predio->num = num;
    predio->f = f;
    predio->p = p;
    predio->mrg = mrg;
    predio->arvoreMoradores = criarArvore(Morador_compararChave, NULL);
    sprintf(predio->id, "%s%c%.0lf", cep, face, num);
    return predio;
}

void destruirPredio(Predio prd) {
    pPredio predio = (pPredio) prd;
    destruirArvore(predio->arvoreMoradores);
    free(predio);
}

char* Predio_getId(Predio prd) {
    pPredio predio = (pPredio) prd;
    return predio->id;
}

char Predio_get_face(Predio prd) {
    pPredio predio = (pPredio) prd;
    return predio->face;
}

char* Predio_getCep(Predio prd) {
    pPredio predio = (pPredio) prd;
    return predio->cep;
}

double Predio_get_x(Predio prd) {
    pPredio predio = (pPredio) prd;
    return predio->x;
}

double Predio_get_y(Predio prd) {
    pPredio predio = (pPredio) prd;
    return predio->y;
}

double Predio_get_x_max(Predio prd) {
    pPredio predio = (pPredio) prd;
    return predio->x_max;
}

double Predio_get_y_max(Predio prd) {
    pPredio predio = (pPredio) prd;
    return predio->y_max;
}

double Predio_get_num(Predio prd) {
    pPredio predio = (pPredio) prd;
    return predio->num;
}

void Predio_setPosicoes(Predio prd, double quadra_x, double quadra_y, double quadra_w, double quadra_h) {
    pPredio predio = (pPredio) prd;
    if(predio->face == 'N') {
        predio->x = quadra_x + predio->num - (predio->f/2);
        predio->y = quadra_y + quadra_h - predio->mrg - predio->p;
    } else if (predio->face == 'S') {
        predio->x = quadra_x + predio->num - (predio->f/2);
        predio->y = quadra_y + predio->mrg;
    } else if(predio->face == 'L') {
        predio->x = quadra_x + predio->mrg;
        predio->y = quadra_y + predio->num - (predio->f/2);
    } else if(predio->face == 'O') {
        predio->x = quadra_x + quadra_w - predio->mrg - predio->p;
        predio->y = quadra_y + predio->num - (predio->f/2);
    }

    if(predio->face == 'N' || predio->face == 'S') {
        predio->x_max = predio->x + predio->f;
        predio->y_max = predio->y + predio->p;
    } else {
        predio->x_max = predio->x + predio->p;
        predio->y_max = predio->y + predio->f;
    }
}

void Predio_escreverSvg(Predio prd, double quadra_x, double quadra_y, double quadra_w, double quadra_h, FILE *svg) {
    pPredio predio = (pPredio) prd;
    double predio_y, predio_x, texto_x, texto_y;

    if(predio->face == 'N') {
        predio_x = quadra_x + predio->num - (predio->f/2);
        predio_y = quadra_y + quadra_h - predio->mrg - predio->p;
        texto_x = quadra_x + predio->num - 3;
        texto_y = quadra_y + quadra_h - predio->mrg - 3;

        fprintf(svg, "<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" stroke=\"black\" fill=\"blue\" stroke-width=\"2\" />\n",
            predio->x,
            predio->y, 
            predio->f, 
            predio->p);

    } else if (predio->face == 'S') {
        predio_x = quadra_x + predio->num - (predio->f/2);
        predio_y = quadra_y + predio->mrg;
        texto_x = quadra_x + predio->num - 3;
        texto_y = quadra_y + predio->mrg + 8;

        fprintf(svg, "<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" stroke=\"black\" fill=\"blue\" stroke-width=\"2\" />\n",
            predio->x,
            predio->y, 
            predio->f,
            predio->p);

    } else if(predio->face == 'L') {
        predio_x = quadra_x + predio->mrg;
        predio_y = quadra_y + predio->num - (predio->f/2);
        texto_x = quadra_x + predio->mrg + 1;
        texto_y = quadra_y + predio->num;

        fprintf(svg, "<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" stroke=\"black\" fill=\"blue\" stroke-width=\"2\" />\n",
            predio->x,
            predio->y, 
            predio->p, 
            predio->f);

    } else if(predio->face == 'O') {
        predio_x = quadra_x + quadra_w - predio->mrg - predio->p;
        predio_y = quadra_y + predio->num - (predio->f/2);
        texto_x = quadra_x + quadra_w - predio->mrg - 8;
        texto_y = quadra_y + predio->num;

        fprintf(svg, "<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" stroke=\"black\" fill=\"blue\" stroke-width=\"2\" />\n",
            predio->x,
            predio->y, 
            predio->p, 
            predio->f);

    }
    
    fprintf(svg, "<text x=\"%lf\" y=\"%lf\" fill=\"white\" font-size=\"7\" style=\"z-index:100 \">%.0lf</text>\n",
            texto_x,
            texto_y,
            predio->num);
    
    // predio->x = predio_x;
    // predio->y = predio_y;
    // if(predio->face == 'N' || predio->face == 'S') {
    //     predio->x_max = predio_x + predio->f;
    //     predio->y_max = predio_y + predio->p;
    // } else {
    //     predio->x_max = predio_x + predio->p;
    //     predio->y_max = predio_y + predio->f;
    // }
}

int Predio_compararChave(Predio a, Predio b) {
    pPredio predio_a = (pPredio) a;
    pPredio predio_b = (pPredio) b;
    if (predio_a->x > predio_b->x) return 1;
    else if (predio_a->x < predio_b->x) return -1;
    else {
        if (predio_a->y > predio_b->y) return 1;
        else if (predio_a->y < predio_b->y) return -1;
        else {
            return 0;
        }
    }
}

char* Predio_getChave(Predio p) {
    pPredio predio = (pPredio) p;
    return predio->id;
}

bool predioEquals(Predio p, char *id) {
    pPredio predio = (pPredio) p;
    return strcmp(predio->id, id) == 0;
}

char* Predio_getDados(Predio p, char* dados) {
    pPredio predio = (pPredio) p;
    sprintf(dados, "%0.1lf %0.1lf\n %s\n", predio->x, predio->y, predio->cep);
    return dados;
}

void Predio_setMorador(Predio p, Morador m) {
    pPredio predio = (pPredio) p;
    if (predio == NULL) return;
    Arvore_inserir(predio->arvoreMoradores, m);
}

Node Predio_getMoradores(Predio q) {
    pPredio predio = (pPredio) q;
    return Arvore_getRaiz(predio->arvoreMoradores);
}

bool Predio_removerMorador(Predio p, Morador m) {
    pPredio predio = (pPredio) p;
    if (predio == NULL) return false;
    return Arvore_removerObjeto(predio->arvoreMoradores, m);
}

void Predio_setQuadra(Predio prd, Objeto quadra) {
    pPredio predio = (pPredio) prd;
    predio->quadra = quadra;
}

Objeto Predio_getQuadra(Predio prd) {
    pPredio predio = (pPredio) prd;
    return predio->quadra;
}