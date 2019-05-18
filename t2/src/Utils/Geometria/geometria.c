#include "geometria.h"

bool pontoInternoForma(double px, double py, Forma f) {
	if(getForma_tipoForma(f) == CIRCULO)
		return pontoInternoCirculo(px, py, getForma_figura(f));
	else if(getForma_tipoForma(f) == RETANGULO)
		return pontoInternoRetangulo(px, py, getForma_figura(f));
}

void centroDeMassa(Forma f, double *ponto) {
	if(getForma_tipoForma(f) == CIRCULO) {
		Circulo c = getForma_figura(f);

		ponto[0] = Circulo_get_x(c);
		ponto[1] = Circulo_get_y(c);
	} else if(getForma_tipoForma(f) == RETANGULO) {
		Retangulo r = getForma_figura(f);

		ponto[0] = getRetangulo_x(r) + getRetangulo_w(r)/2;
		ponto[1] = getRetangulo_y(r) + getRetangulo_h(r)/2;
	}
}

double distanciaL2Centro(Forma j, Forma k) {
	double *centro1 = malloc(2*sizeof(double));
	double *centro2 = malloc(2*sizeof(double));
	centroDeMassa(j, centro1);
	centroDeMassa(k, centro2);
	double x1 = centro1[0], y1 = centro1[1], x2 = centro2[0], y2 = centro2[1];
	free(centro1);
	free(centro2);
	return distanciaL2(x1, y1, x2, y2);
}

double distanciaL1(double x1, double y1, double x2, double y2) {
	return fabs(x1-x2)+fabs(y1-y2);
}

double distanciaL2(double x1, double y1, double x2, double y2) {
    return sqrt(pow(x1-x2, 2) + pow(y1-y2, 2));
}

bool pontoInternoCirculo(double px, double py, Circulo c) {
	double cx = Circulo_get_x(c), cy = Circulo_get_x(c), r = Circulo_get_r(c);
    return distanciaL2(px, py, cx, cy) <= r;
}

bool pontoInternoRetangulo(double px, double py, Retangulo r) {
	double rx = getRetangulo_x(r), ry = getRetangulo_y(r), w = getRetangulo_w(r), h = getRetangulo_h(r);
    return px >= rx && px <= rx+w && py >= ry && py <= ry+h;
}

bool retanguloInternoCirculo(Retangulo r, Circulo c) {
	return pontoInternoCirculo(getRetangulo_x(r), getRetangulo_y(r), c) && pontoInternoCirculo(getRetangulo_max_x(r), getRetangulo_y(r), c)
	&& pontoInternoCirculo(getRetangulo_x(r), getRetangulo_max_y(r), c) && pontoInternoCirculo(getRetangulo_max_x(r), getRetangulo_max_y(r), c);
}

bool retanguloInternoRetangulo(Retangulo r1, Retangulo r2) {
	return getRetangulo_x(r1) > getRetangulo_x(r2) && getRetangulo_max_x(r1) < getRetangulo_max_x(r2)
	&& getRetangulo_y(r1) > getRetangulo_y(r2) && getRetangulo_max_y(r1) < getRetangulo_max_y(r2);
}

bool retanguloInternoL1(double px, double py, Retangulo r, double dist) {
	return distanciaL1(px, py, getRetangulo_x(r), getRetangulo_y(r)) <= dist &&
	distanciaL1(px, py, getRetangulo_max_x(r), getRetangulo_y(r)) <= dist &&
	distanciaL1(px, py, getRetangulo_x(r), getRetangulo_max_y(r)) <= dist &&
	distanciaL1(px, py, getRetangulo_max_x(r), getRetangulo_max_y(r));
}