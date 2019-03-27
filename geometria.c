#include "geometria.h"

double distancia(double x1, double y1, double x2, double y2) {
    return sqrt(pow(x1-x2, 2) + pow(y1-y2, 2));
}

bool pontoInternoCirculo(double px, double py, Forma *c) {
    Circulo *circulo = (Circulo*) c->tipoForma;
	double cx = c->x, cy = c->y, r = circulo->raio;
    return distancia(px, py, cx, cy) <= r;
}

bool pontoInternoRetangulo(double px, double py, Forma *r) {
    Retangulo *retangulo = (Retangulo*) r->tipoForma;
	double rx = r->x, ry = r->y, w = retangulo->w, h = retangulo->h;
    return px >= rx && px <= rx+w && py >= ry && py <= ry+h;
}

bool pontoInternoForma(double px, double py, Forma *a) {
	if(a->nomeForma == CIRCULO)
		return pontoInternoCirculo(px, py, a);
	else if(a->nomeForma == RETANGULO)
		return pontoInternoRetangulo(px, py, a);
}

void centroDeMassa(Forma *f, double *ponto) {
	if(f->nomeForma == CIRCULO) {
		ponto[0] = f->x;
		ponto[1] = f->y;
	} else if(f->nomeForma == RETANGULO) {
		Retangulo *ret = ((Retangulo*) f->tipoForma);
		ponto[0] = f->x + ret->w/2;
		ponto[1] = f->y + ret->h/2;
	}
}

double distanciaCentro(Forma *j, Forma *k) {
	double *centro1 = malloc(2*sizeof(double));
	double *centro2 = malloc(2*sizeof(double));
	centroDeMassa(j, centro1);
	centroDeMassa(k, centro2);
	return distancia(centro1[0], centro1[1], centro2[0], centro2[1]);
}
