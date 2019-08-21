#include "predio.h"

typedef struct predio {
    char cep[50], face;
    double num, f, p, mrg;
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
    return predio;
}

void destruirPredio(Predio prd) {
    pPredio predio = (pPredio) prd;
    free(predio);
}

char* Predio_getCep(Predio prd) {
    pPredio predio = (pPredio) prd;
    return predio->cep;
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
            predio_x,
            predio_y, 
            predio->f, 
            predio->p);

    } else if (predio->face == 'S') {
        predio_x = quadra_x + predio->num - (predio->f/2);
        predio_y = quadra_y + predio->mrg;
        texto_x = quadra_x + predio->num - 3;
        texto_y = quadra_y + predio->mrg + 8;

        fprintf(svg, "<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" stroke=\"black\" fill=\"blue\" stroke-width=\"2\" />\n",
            predio_x,
            predio_y, 
            predio->f, 
            predio->p);

    } else if(predio->face == 'L') {
        predio_x = quadra_x + predio->mrg;
        predio_y = quadra_y + predio->num - (predio->f/2);
        texto_x = quadra_x + predio->mrg + 1;
        texto_y = quadra_y + predio->num;

        fprintf(svg, "<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" stroke=\"black\" fill=\"blue\" stroke-width=\"2\" />\n",
            predio_x,
            predio_y, 
            predio->p, 
            predio->f);

    } else if(predio->face == 'O') {
        predio_x = quadra_x + quadra_w - predio->mrg - predio->p;
        predio_y = quadra_y + predio->num - (predio->f/2);
        texto_x = quadra_x + quadra_w - predio->mrg - 8;
        texto_y = quadra_y + predio->num;

        fprintf(svg, "<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" stroke=\"black\" fill=\"blue\" stroke-width=\"2\" />\n",
            predio_x,
            predio_y, 
            predio->p, 
            predio->f);

    }
    
    fprintf(svg, "<text x=\"%lf\" y=\"%lf\" fill=\"white\" font-size=\"7\" style=\"z-index:100 \">%.0lf</text>\n",
            texto_x,
            texto_y,
            predio->num);
}