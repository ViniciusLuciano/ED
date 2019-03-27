#include "svg.h"

 // TROCAR TD PRA VOID 


void iniciarSVG(FILE *SVG, char *width, char *height) {
	fprintf(SVG, "<svg width=\"%s\" height=\"%s\">\n", width, height);
}

void finalizarSVG(FILE *SVG) {
	fprintf(SVG, "</svg>");
}

void escreverCirculo(FILE *SVG, Forma *c) {
	Circulo *circ = ((Circulo*) c->tipoForma);
	fprintf(SVG, "<circle cx=\"%lf\" cy=\"%lf\" r=\"%lf\" stroke=\"%s\" fill=\"%s\" />\n", c->x, c->y, circ->raio, c->corB, c->corD);
}

void escreverRetangulo(FILE *SVG, Forma *r) {
	Retangulo *ret = ((Retangulo*) r->tipoForma);
	fprintf(SVG, "<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" stroke=\"%s\" fill=\"%s\" />\n", r->x, r->y, ret->w, ret->h, r->corB, r->corD);
}

void escreverTexto(FILE *SVG, Forma *t) {
	Texto *text = ((Texto*) t->tipoForma);
	fprintf(SVG, "<text x=\"%lf\" y=\"%lf\">%s</text>", t->x, t->y, text->texto);
}

void escreverArvoreSVG(struct Node* node, FILE *SVG) {
	if(node == NULL){
        return;
    }else{
		if(node->forma->nome == 'c')
			escreverCirculo(SVG, node->forma);
		else if(node->forma->nome == 'r')
			escreverRetangulo(SVG, node->forma);
		else if(node->forma->nome == 't')
			escreverTexto(SVG, node->forma);
        escreverArvoreSVG(node->esq, SVG);
        escreverArvoreSVG(node->dir, SVG);
    }
}

void retanguloDelimitador(FILE *SVG2, Forma *a, Forma *b, bool colidem) {
	double xMin, xMax, yMin, yMax, largura, altura;
	if(a->nome == 'c' && b->nome == 'r') {
		Circulo *circ = ((Circulo*) a->tipoForma);
		Retangulo *ret = ((Retangulo*) b->tipoForma);
		xMin = (a->x - circ->raio) < b->x ? (a->x - circ->raio) : b->x;
		xMax = (a->x + circ->raio) > (b->x + ret->w) ? (a->x + circ->raio) : (b->x + ret->w);
		yMin = (a->y - circ->raio) < b->y ? (a->y - circ->raio) : b->y;
		yMax = (a->y + circ->raio) > (b->y + ret->h) ? (a->y + circ->raio) : (b->y + ret->h);

		largura = xMax-xMin;
		altura = yMax-yMin;

	} else if(a->nome == 'r' && b->nome == 'c') {
		Circulo *circ = ((Circulo*) b->tipoForma);
		xMin = (b->x - circ->raio) < a->x ? (b->x - circ->raio) : a->x;
		xMax = (b->x + circ->raio) > a->x ? (b->x + circ->raio) : a->x;
		yMin = (b->y - circ->raio) < a->y ? (b->y - circ->raio) : a->y;
		yMax = (b->y + circ->raio) > a->y ? (b->y + circ->raio) : a->y;

		largura = xMax-xMin;
		altura = yMax-yMin;
        
	} else if(a->nome == 'r' && b->nome == 'r') {
        Retangulo *ret1 = ((Retangulo*) a->tipoForma);
		Retangulo *ret2 = ((Retangulo*) a->tipoForma);
		xMin = a->x < b->x ? a->x : b->x;
		xMax = (a->x + ret1->w) > (b->x + ret2->w) ? (a->x + ret1->w) : (b->x + ret2->w);
		yMin = a->y < b->y ? a->y : b->y;
		yMax = (a->y + ret1->h) > (b->y + ret2->h) ? (a->y + ret1->h) : (b->y + ret2->h);

		largura = xMax-xMin;
		altura = yMax-yMin;
	
	} else if(a->nome == 'c' && b->nome == 'c') {
        Circulo *circ1 = ((Circulo*) a->tipoForma);
		Circulo *circ2 = ((Circulo*) b->tipoForma);

		xMin = (a->x - circ1->raio) < (b->x - circ2->raio) ? (a->x - circ1->raio) : (b->x - circ2->raio);
		xMax = (a->x + circ1->raio) > (b->x + circ2->raio) ? (a->x + circ1->raio) : (b->x + circ2->raio);
		yMin = (a->y - circ1->raio) < (b->y - circ2->raio) ? (a->y - circ1->raio) : (b->y - circ2->raio);
		yMax = (a->y + circ1->raio) > (b->y + circ2->raio) ? (a->y + circ1->raio) : (b->y + circ2->raio);
	}

	if(colidem)
		fprintf(SVG2, "<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" stroke=\"blue\" fill-opacity=\"0\" />\n", xMin, yMin, largura, altura);
	else
		fprintf(SVG2, "<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" stroke=\"blue\" fill-opacity=\"0\" stroke-dasharray=\"5\" />\n", xMin, yMin, largura, altura);
	
}

void escreverPontoInterno(FILE *SVG, Forma *a, double x, double y, bool interno) {
	double *centro = malloc(2*sizeof(double));
	centroDeMassa(a, centro);

	if(interno) {
		fprintf(SVG, "<circle cx=\"%lf\" cy=\"%lf\" r=\"1\" stroke=\"green\" fill=\"green\" />\n", x, y);
		fprintf(SVG, "<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"green\" />", centro[0], centro[1], x, y);
	} else {
		fprintf(SVG, "<circle cx=\"%lf\" cy=\"%lf\" r=\"1\" stroke=\"red\" fill=\"red\" />\n", x, y);
		fprintf(SVG, "<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"red\" />", centro[0], centro[1], x, y);
	}
	
	free(centro);
}

void retaCentrosMassa(FILE *SVG, Forma *a, Forma *b) {
	double *centro1 = malloc(2*sizeof(double));
	double *centro2 = malloc(2*sizeof(double));
	centroDeMassa(a, centro1);
	centroDeMassa(b, centro2);
	fprintf(SVG, "<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"black\" />", centro1[0], centro1[1], centro2[0], centro2[1]);

	free(centro1);
	free(centro2);
}

void distanciaCentrosMassa(FILE *SVG, Forma *a, Forma *b, double distancia) {
	double *centro1 = malloc(2*sizeof(double));
	double *centro2 = malloc(2*sizeof(double));
	centroDeMassa(a, centro1);
	centroDeMassa(b, centro2);

	double posX = (centro1[0] + centro2[0])/2;
	double posY = (centro1[1] + centro2[1])/2;
	fprintf(SVG, "<text x=\"%lf\" y=\"%lf\">%lf</text>", posX, posY, distancia);

	free(centro1);
	free(centro2);
}

void escreverFormasEnvoltas(FILE *SVG, struct Node* node, char *cor) {
	if(node == NULL){
        return;
    }else{
		
		if(node->forma->nome == 'c') {
			escreverCirculo(SVG, node->forma);

			// "Bounding box"
			Circulo *circ = ((Circulo*) node->forma->tipoForma);
			double posX = node->forma->x - circ->raio;
			double posY = node->forma->y - circ->raio;
			double lado = 2*circ->raio;
			fprintf(SVG, "<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" stroke=\"%s\" fill-opacity=\"0\" />\n", posX, posY, lado, lado, cor);
	
		} else if(node->forma->nome == 'r') {
			escreverRetangulo(SVG, node->forma);

			Retangulo *ret = ((Retangulo*) node->forma->tipoForma);
			double *centro = malloc(2*sizeof(double));
			centroDeMassa(node->forma, centro);

			fprintf(SVG, "<ellipse cx=\"%lf\" cy=\"%lf\" rx=\"%lf\" ry=\"%lf\" stroke=\"%s\" fill-opacity=\"0\" />", centro[0], centro[1], ret->w/2, ret->h/2, cor);
		}	

        escreverFormasEnvoltas(SVG, node->esq, cor);
        escreverFormasEnvoltas(SVG, node->dir, cor);
    }
}