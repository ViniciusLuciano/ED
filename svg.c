#include "svg.h"

char* iniciarSVG(char *width, char *height) {
	int num = strlen("<svg width="" height="">\n") + strlen(width) + strlen(height);
	char *string = malloc(num*sizeof(char));
	sprintf(string, "<svg width=\"%s\" height=\"%s\">\n", width, height);
	return string;
}

char* finalizarSVG() {
	int num = strlen("</svg>");
	char *string = malloc(num*sizeof(char));
	sprintf(string, "</svg>");
	return string;
}

char* escreverCirculo(Forma *c) {
	Circulo *circ = ((Circulo*) c->tipoForma);

	char *buffer = malloc(1000*sizeof(char));
	sprintf(buffer,"<circle cx=\"%lf\" cy=\"%lf\" r=\"%lf\" stroke=\"%s\" stroke-width=\"3\" fill=\"%s\" />\n", c->x, c->y, circ->raio, c->corB, c->corD);
	char *string = malloc(strlen(buffer)*sizeof(char));
	sprintf(string, "<circle cx=\"%lf\" cy=\"%lf\" r=\"%lf\" stroke=\"%s\" stroke-width=\"3\" fill=\"%s\" />\n", c->x, c->y, circ->raio, c->corB, c->corD);
	free(buffer);
	return string;
}

char* escreverRetangulo(Forma *r) {
	Retangulo *ret = ((Retangulo*) r->tipoForma);
	
	char *buffer = malloc(1000*sizeof(char));
	sprintf(buffer, "<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" stroke=\"%s\" stroke-width=\"3\" fill=\"%s\" />\n", r->x, r->y, ret->w, ret->h, r->corB, r->corD);
	char *string = malloc(strlen(buffer)*sizeof(char));
	sprintf(string, "<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" stroke=\"%s\" stroke-width=\"3\" fill=\"%s\" />\n", r->x, r->y, ret->w, ret->h, r->corB, r->corD);
	free(buffer);
	return string;
}