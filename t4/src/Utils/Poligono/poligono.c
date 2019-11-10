#include "poligono.h"

typedef struct poligono {
    Arvore arvoreSegmentos;
    double min_x, min_y, max_x, max_y;
}*pPoligono;

Poligono criarPoligono(FILE* polig) {
    Poligono p = malloc(sizeof(struct poligono));
    pPoligono poligono = (pPoligono) p;
    poligono->arvoreSegmentos = criarArvore(Segmento_compararChave, destruirSegmento);

    char str[150];
    double xant, yant, xatual, yatual, xprimeiro, yprimeiro;
    bool primeiro = true;

	while(true) {

		fgets(str, sizeof(str), polig);
		if(feof(polig))
			break;

        if (primeiro) {
		    sscanf(str, "%lf %lf", &xant, &yant);
            xprimeiro = xant;
            yprimeiro = yant;
            poligono->min_x = xant;
            poligono->min_y = yant;
            poligono->max_x = xant;
            poligono->max_y = yant;
            primeiro = false;
        } else {
            sscanf(str, "%lf %lf", &xatual, &yatual);

            if (xatual > poligono->max_x) poligono->max_x = xatual;
            if (xatual < poligono->min_x) poligono->min_x = xatual;
            if (yatual > poligono->max_y) poligono->max_y = yatual;
            if (yatual < poligono->min_y) poligono->min_y = yatual;

            Vertice v1 = criarVertice(xant, yant, 0, 0);
            Vertice_set_inicio(v1, true);
            Vertice v2 = criarVertice(xatual, yatual, 0, 0);
            Vertice_set_inicio(v2, false);
            Segmento s = criarSegmento(v1, v2);
            Arvore_inserir(poligono->arvoreSegmentos, s);
            xant = xatual; yant = yatual;
        }
        
    }

    Vertice v1 = criarVertice(xatual, yatual, 0, 0);
    Vertice_set_inicio(v1, true);
    Vertice v2 = criarVertice(xprimeiro, yprimeiro, 0, 0);
    Vertice_set_inicio(v2, false);
    Segmento s = criarSegmento(v1, v2);
    Arvore_inserir(poligono->arvoreSegmentos, s);

    //printf("MAX %lf %lf %lf %lf\n", poligono->max_x, poligono->max_y, poligono->min_x, poligono->min_y);
    return p;
}

void destruirPoligono(Poligono p) {
    pPoligono poligono = (pPoligono) p;
    destruirArvore(poligono->arvoreSegmentos);
    free(poligono);
}

double Poligono_get_max_x(Poligono p) {
    pPoligono poligono = (pPoligono) p;
    return poligono->max_x;
}

Arvore Poligono_getSegmentos(Poligono p) {
    pPoligono poligono = (pPoligono) p;
    return poligono->arvoreSegmentos;
}

void Poligono_escreverSVG(Poligono p, FILE* svg) {
    pPoligono poligono = (pPoligono) p;
    forEach(segmento, Arvore_getRaiz(poligono->arvoreSegmentos)) {
        if(segmento == Arvore_getTNULL()) break;
        if (Node_getAux(segmento) == 0) {
            Segmento s = Node_getObjeto(segmento);
            Vertice v1 = Segmento_get_v1(s);
            Vertice v2 = Segmento_get_v2(s);

            fprintf(svg, "<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" style=\"stroke:rgb(0,0,0);stroke-width:2\" />\n", 
            Vertice_get_x(v1),
            Vertice_get_y(v1),
            Vertice_get_x(v2),
            Vertice_get_y(v2));
        }
    }
}