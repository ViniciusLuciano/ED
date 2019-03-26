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
	fprintf(SVG, "<circle cx=\"%lf\" cy=\"%lf\" r=\"%lf\" stroke=\"%s\" stroke-width=\"3\" fill=\"%s\" />\n", c->x, c->y, circ->raio, c->corB, c->corD);
}

void escreverRetangulo(FILE *SVG, Forma *r) {
	Retangulo *ret = ((Retangulo*) r->tipoForma);
	fprintf(SVG, "<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" stroke=\"%s\" stroke-width=\"3\" fill=\"%s\" />\n", r->x, r->y, ret->w, ret->h, r->corB, r->corD);
}