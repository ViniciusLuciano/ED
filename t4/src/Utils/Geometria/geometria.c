#include "geometria.h"

bool pontoInternoForma(double px, double py, Forma f) {
	if(Forma_get_tipoForma(f) == CIRCULO)
		return pontoInternoCirculo(px, py, Forma_getFigura(f));
	else if(Forma_get_tipoForma(f) == RETANGULO)
		return pontoInternoRetangulo(px, py, Forma_getFigura(f));
}

void centroDeMassa(Forma f, double *ponto) {
	if(Forma_get_tipoForma(f) == CIRCULO) {
		Circulo c = Forma_getFigura(f);

		ponto[0] = Circulo_get_x(c);
		ponto[1] = Circulo_get_y(c);
	} else if(Forma_get_tipoForma(f) == RETANGULO) {
		Retangulo r = Forma_getFigura(f);

		ponto[0] = Retangulo_get_x(r) + Retangulo_get_w(r)/2;
		ponto[1] = Retangulo_get_y(r) + Retangulo_get_h(r)/2;
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
	double cx = Circulo_get_x(c), cy = Circulo_get_y(c), r = Circulo_get_r(c);
    return distanciaL2(px, py, cx, cy) <= r;
}

bool pontoInternoRetangulo(double px, double py, Retangulo r) {
	double rx = Retangulo_get_x(r), ry = Retangulo_get_y(r), w = Retangulo_get_w(r), h = Retangulo_get_h(r);
    return px >= rx && px <= rx+w && py >= ry && py <= ry+h;
}

bool retanguloInternoCirculo(Retangulo r, Circulo c) {
	return pontoInternoCirculo(Retangulo_get_x(r), Retangulo_get_y(r), c) && pontoInternoCirculo(Retangulo_get_max_x(r), Retangulo_get_y(r), c)
	&& pontoInternoCirculo(Retangulo_get_x(r), Retangulo_get_max_y(r), c) && pontoInternoCirculo(Retangulo_get_max_x(r), Retangulo_get_max_y(r), c);
}

bool retanguloInternoRetangulo(Retangulo r1, Retangulo r2) {
	return Retangulo_get_x(r1) > Retangulo_get_x(r2) && Retangulo_get_max_x(r1) < Retangulo_get_max_x(r2)
	&& Retangulo_get_y(r1) > Retangulo_get_y(r2) && Retangulo_get_max_y(r1) < Retangulo_get_max_y(r2);
}

bool retanguloInternoL1(double px, double py, Retangulo r, double dist) {
	return distanciaL1(px, py, Retangulo_get_x(r), Retangulo_get_y(r)) <= dist &&
	distanciaL1(px, py, Retangulo_get_max_x(r), Retangulo_get_y(r)) <= dist &&
	distanciaL1(px, py, Retangulo_get_x(r), Retangulo_get_max_y(r)) <= dist &&
	distanciaL1(px, py, Retangulo_get_max_x(r), Retangulo_get_max_y(r)) <= dist;
}

double calcularAngulo(Ponto p, double x, double y) {
	double ang = atan2(Ponto_get_y(p) - y, Ponto_get_x(p) - x);
	//if(ang < 0) ang+=2*M_PI;
	return ang;
}

double calcularAngulop(double xp, double yp, double x, double y) {
	double ang = atan2(yp - y, xp - x);
	//if(ang < 0) ang+=2*M_PI;
	return ang;
}

bool verficarViradoAEsquerda(Ponto a, Ponto b, Ponto c) {
	double s = (Ponto_get_x(a)*Ponto_get_y(b) - Ponto_get_y(a)*Ponto_get_x(b) +
					  Ponto_get_y(a)*Ponto_get_x(c) - Ponto_get_x(a)*Ponto_get_y(c) + 
					  Ponto_get_x(b)*Ponto_get_y(c) - Ponto_get_y(b)*Ponto_get_x(c))/2;
	return s <= 0;
}

bool verificarSegmentosInterceptam(Segmento s1, Segmento s2) {

	if(s1 == NULL || s2 == NULL) return false;

	Ponto a = Vertice_get_p(Segmento_get_v1(s1));
	Ponto b = Vertice_get_p(Segmento_get_v2(s1));

	Ponto c = Vertice_get_p(Segmento_get_v1(s2));
	Ponto d = Vertice_get_p(Segmento_get_v2(s2));

	return (verficarViradoAEsquerda(c, d, a) ^ verficarViradoAEsquerda(c, d, b)) &&
	 		(verficarViradoAEsquerda(a, b, c) ^ verficarViradoAEsquerda(a, b, d));
}

double buscarXInterseccaoSegmento(Segmento s, double y) {
	// y = ax + b
	// x = (y-b)/a
	Vertice v1 = Segmento_get_v1(s);
	Vertice v2 = Segmento_get_v2(s);

	double x1 = Vertice_get_x(v1);
	double x2 = Vertice_get_x(v2);
	double y1 = Vertice_get_y(v1);
	double y2 = Vertice_get_y(v2);

	if(x2-x1 == 0) return x1; // reta perpendicular
	double a = (y2-y1)/(x2-x1);
	double b = y1 - a*x1;

	return (y-b)/a;
}

Segmento buscarSegmentoFormadoComVertice(double xc, double yc, Vertice v, Ponto pontoMin, Ponto pontoMax) {
	double xv = Vertice_get_x(v), yv = Vertice_get_y(v);
	double a, b;
	if(xv != xc) { // reta perpendicular ver dps
		a = (yv-yc)/(xv-xc);
		b = yc - a*xc;
	}

	double xq, yq;
	// y = ax + b
	// x = (y-b)/a
	if(xc < xv && yc > yv) { 
		xq = (Ponto_get_y(pontoMin) - 50 - b)/a;
		yq = a*(Ponto_get_x(pontoMax) + 50) + b;
		if(distanciaL2(xc, yc, xq, Ponto_get_y(pontoMin) - 50) > distanciaL2(xc, yc, Ponto_get_x(pontoMax) + 50, yq)) {
			yq = Ponto_get_y(pontoMin) - 50;
		} else {
			xq = Ponto_get_x(pontoMax) + 50;
		}
	} else if(xc < xv && yc == yv) { // certo
		xq = Ponto_get_x(pontoMax) + 50;
		yq = yc;
	} else if(xc < xv && yc < yv) {
		xq = (yc + 50 - b)/a;
		yq = a*(Ponto_get_x(pontoMax) + 50) + b;
		if(distanciaL2(xc, yc, xq, yc + 50) > distanciaL2(xc, yc, Ponto_get_x(pontoMax) + 50, yq)) {
			yq = yc + 50;
		} else {
			xq = Ponto_get_x(pontoMax) + 50;
		}
	} else if(xc > xv && yc > yv) {
		xq = (Ponto_get_y(pontoMin) - 50 - b)/a;
		yq = a*(Ponto_get_x(pontoMin) - 50) + b;
		if(distanciaL2(xc, yc, xq, Ponto_get_y(pontoMin) - 50) > distanciaL2(xc, yc, Ponto_get_x(pontoMin) - 50, yq)) {
			yq = Ponto_get_y(pontoMin) - 50;
		} else {
			xq = Ponto_get_x(pontoMin) - 50;
		}
	} else if(xc > xv && yc == yv) { // certo
		xq = Ponto_get_x(pontoMin) - 50;
		yq = yc;
	} else if(xc > xv && yc < yv) {
		xq = (Ponto_get_y(pontoMax) + 50 - b)/a;
		yq = a*(Ponto_get_x(pontoMin) - 50) + b;
		if(distanciaL2(xc, yc, xq, Ponto_get_y(pontoMax) + 50) > distanciaL2(xc, yc, Ponto_get_x(pontoMin) - 50, yq)) {
			yq = Ponto_get_y(pontoMax) + 50;
		} else {
			xq = Ponto_get_x(pontoMin) - 50;
		}
	} else if(xc == xv && yc > yv) { // certo
		xq = xc;
		yq = Ponto_get_y(pontoMin) - 50;
	} else if(xc == xv && yc < yv) { // certo
		xq = xc;
		yq = Ponto_get_y(pontoMax) + 50;
	}

	// ver como vou dar free dps
	Vertice vc = criarVertice(xc, yc, xc, yc);
	Vertice vq = criarVertice(xq, yq, xc, yc);

	Segmento seg = criarSegmento(vc, vq);
	Vertice_set_s(vc, seg);
	Vertice_set_s(vq, seg);

	return seg;
}

Ponto buscarPontoInterseccao(Segmento a, Segmento b) {
	// y = ax + b
	// x = (y-b)/a
	Vertice v1a = Segmento_get_v1(a);
	Vertice v2a = Segmento_get_v2(a);

	Vertice v1b = Segmento_get_v1(b);
	Vertice v2b = Segmento_get_v2(b);

	double x_intersec, y_intersec;
	if(Vertice_get_x(v1a) == Vertice_get_x(v2a)) {

		x_intersec = Vertice_get_x(v1a);
		double a_b = (Vertice_get_y(v1b)-Vertice_get_y(v2b))/(Vertice_get_x(v1b)-Vertice_get_x(v2b));
		double b_b = Vertice_get_y(v1b) - a_b*Vertice_get_x(v1b);
		y_intersec = a_b*x_intersec + b_b;

	} else if(Vertice_get_x(v1b) == Vertice_get_x(v2b)) {

		x_intersec = Vertice_get_x(v1b);
		double a_a = (Vertice_get_y(v1a)-Vertice_get_y(v2a))/(Vertice_get_x(v1a)-Vertice_get_x(v2a));
		double b_a = Vertice_get_y(v1a) - a_a*Vertice_get_x(v1a);
		y_intersec = a_a*x_intersec + b_a;

	} else {

		double a_a = (Vertice_get_y(v1a)-Vertice_get_y(v2a))/(Vertice_get_x(v1a)-Vertice_get_x(v2a));
		double b_a = Vertice_get_y(v1a) - a_a*Vertice_get_x(v1a);

		double a_b = (Vertice_get_y(v1b)-Vertice_get_y(v2b))/(Vertice_get_x(v1b)-Vertice_get_x(v2b));
		double b_b = Vertice_get_y(v1b) - a_b*Vertice_get_x(v1b);

		x_intersec = (b_b - b_a)/(a_a - a_b);
		y_intersec = a_a*x_intersec + b_a;
	}

	return criarPonto(x_intersec, y_intersec);
}

bool _verificarPontoMesmaAlturaVerticePoligono(Ponto p, Segmento s) {
	Vertice v1 = Segmento_get_v1(s);
	Vertice v2 = Segmento_get_v2(s);
	
	// Se for verticie tiver a mesma altura e for de inicio, nao verifica se intercepta
	if (Ponto_get_y(p) == Vertice_get_y(v1) && Vertice_get_inicio(v1)) {
		return true;
	} else if (Ponto_get_y(p) == Vertice_get_y(v2) && Vertice_get_inicio(v2)) {
		return true;
	}

	return false;

}

bool _verificarPontoEstaNoSegmento(Ponto p, Segmento s) {
	Vertice v1 = Segmento_get_v1(s);
	Vertice v2 = Segmento_get_v2(s);
	// y = ax + b

	double x1 = Vertice_get_x(v1);
	double y1 = Vertice_get_y(v1);

	double x2 = Vertice_get_x(v2);
	double y2 = Vertice_get_y(v2);

	double x = Ponto_get_x(p);
	double y = Ponto_get_y(p);
	if (x > x1 && x > x2 || x < x1 && x < x2 || y > y1 && y > y2 || y < y1 && y < y2) return false;

	double a = (Vertice_get_y(v1)-Vertice_get_y(v2))/(Vertice_get_x(v1)-Vertice_get_x(v2));
	double b = Vertice_get_y(v1) - a*Vertice_get_x(v1);
	double yint = a*x + b;
	return yint == y;
}

bool PontoInternoPoligono(Ponto ponto, Poligono poligono) {
	Vertice v1 = criarVertice(Ponto_get_x(ponto), Ponto_get_y(ponto), 0, 0);
	Vertice v2 = criarVertice(Poligono_get_max_x(poligono) + 5, Ponto_get_y(ponto), 0, 0);
	Segmento s_ponto = criarSegmento(v1, v2);

	Node segmentos = Arvore_getRaiz(Poligono_getSegmentos(poligono));
	int numIntersec = 0;
	forEach(segmento, segmentos) {
		if (Node_getAux(segmento) == 0) {
            Segmento s = Node_getObjeto(segmento);

			if (_verificarPontoMesmaAlturaVerticePoligono(ponto, s)) continue;
			if(_verificarPontoEstaNoSegmento(ponto, s)) return true;

			if (verificarSegmentosInterceptam(s_ponto, s)) {
				numIntersec++;
			}
        }
	}
	destruirSegmento(s_ponto);
	if (numIntersec%2 == 0) return false;
	return true;
}

bool _VerticeInternoPoligono(Vertice vertice, Poligono poligono) {
	Vertice v1 = criarVertice(Vertice_get_x(vertice), Vertice_get_y(vertice), 0, 0);
	Vertice v2 = criarVertice(Poligono_get_max_x(poligono) + 1, Vertice_get_y(vertice), 0, 0);
	Segmento s_ponto = criarSegmento(v1, v2);

	Node segmentos = Arvore_getRaiz(Poligono_getSegmentos(poligono));
	int numIntersec = 0;
	forEach(segmento, segmentos) {
		if (Node_getAux(segmento) == 0) {
            Segmento s = Node_getObjeto(segmento);

			if (_verificarPontoMesmaAlturaVerticePoligono(Vertice_get_p(vertice), s)) continue;
			if(_verificarPontoEstaNoSegmento(Vertice_get_p(vertice), s)) return true;

			if (verificarSegmentosInterceptam(s_ponto, s)) {
				numIntersec++;
			}
        }
	}
	destruirSegmento(s_ponto);

	if (numIntersec%2 == 0) return false;
	return true;
}

bool RetanguloInternoPoligono(Retangulo r, Poligono p) {
	Vertice v1 = criarVertice(Retangulo_get_x(r), Retangulo_get_y(r), 0, 0);
	Vertice v2 = criarVertice(Retangulo_get_max_x(r), Retangulo_get_y(r), 0, 0);
	Vertice v3 = criarVertice(Retangulo_get_x(r), Retangulo_get_max_y(r), 0, 0);
	Vertice v4 = criarVertice(Retangulo_get_max_x(r), Retangulo_get_max_y(r), 0, 0);
	Vertice v1_2 = criarVertice(Retangulo_get_x(r), Retangulo_get_y(r), 0, 0);
	Vertice v2_2 = criarVertice(Retangulo_get_max_x(r), Retangulo_get_y(r), 0, 0);
	Vertice v3_2 = criarVertice(Retangulo_get_x(r), Retangulo_get_max_y(r), 0, 0);
	Vertice v4_2 = criarVertice(Retangulo_get_max_x(r), Retangulo_get_max_y(r), 0, 0);

	Segmento s1 = criarSegmento(v1, v2);
	Segmento s2 = criarSegmento(v1_2, v3);
	Segmento s3 = criarSegmento(v2_2, v4);
	Segmento s4 = criarSegmento(v3_2, v4_2);

	if (!_VerticeInternoPoligono(v1, p) || !_VerticeInternoPoligono(v2, p) ||
		!_VerticeInternoPoligono(v3, p) || !_VerticeInternoPoligono(v4, p)) {
			destruirSegmento(s1);
			destruirSegmento(s2);
			destruirSegmento(s3);
			destruirSegmento(s4);
			return false;
	}

	Node segmentos = Arvore_getRaiz(Poligono_getSegmentos(p));
	int numIntersec = 0;
	forEach(segmento, segmentos) {
		if (Node_getAux(segmento) == 0) {
            Segmento s = Node_getObjeto(segmento);
			if (verificarSegmentosInterceptam(s1, s) || verificarSegmentosInterceptam(s2, s) ||
				verificarSegmentosInterceptam(s3, s) || verificarSegmentosInterceptam(s4, s)) {
				destruirSegmento(s1);
				destruirSegmento(s2);
				destruirSegmento(s3);
				destruirSegmento(s4);
				return false;
			}
        }
	}

	destruirSegmento(s1);
	destruirSegmento(s2);
	destruirSegmento(s3);
	destruirSegmento(s4);
	return true;
}

bool RetanguloParcialmenteInternoPoligono(Retangulo r, Poligono p) {
	Ponto p1 = criarPonto(Retangulo_get_x(r), Retangulo_get_y(r));
	Ponto p2 = criarPonto(Retangulo_get_max_x(r), Retangulo_get_y(r));
	Ponto p3 = criarPonto(Retangulo_get_x(r), Retangulo_get_max_y(r));
	Ponto p4 = criarPonto(Retangulo_get_max_x(r), Retangulo_get_max_y(r));

	if (PontoInternoPoligono(p1, p) || PontoInternoPoligono(p2, p) ||
		PontoInternoPoligono(p3, p) || PontoInternoPoligono(p4, p)) {
		destruirPonto(p1);
		destruirPonto(p2);
		destruirPonto(p3);
		destruirPonto(p4);
		return true;
	}

	Vertice v1 = criarVertice(Retangulo_get_x(r), Retangulo_get_y(r), 0, 0);
	Vertice v2 = criarVertice(Retangulo_get_max_x(r), Retangulo_get_y(r), 0, 0);
	Vertice v3 = criarVertice(Retangulo_get_x(r), Retangulo_get_max_y(r), 0, 0);
	Vertice v4 = criarVertice(Retangulo_get_max_x(r), Retangulo_get_max_y(r), 0, 0);
	Vertice v1_2 = criarVertice(Retangulo_get_x(r), Retangulo_get_y(r), 0, 0);
	Vertice v2_2 = criarVertice(Retangulo_get_max_x(r), Retangulo_get_y(r), 0, 0);
	Vertice v3_2 = criarVertice(Retangulo_get_x(r), Retangulo_get_max_y(r), 0, 0);
	Vertice v4_2 = criarVertice(Retangulo_get_max_x(r), Retangulo_get_max_y(r), 0, 0);

	Segmento s1 = criarSegmento(v1, v2);
	Segmento s2 = criarSegmento(v1_2, v3);
	Segmento s3 = criarSegmento(v2_2, v4);
	Segmento s4 = criarSegmento(v3_2, v4_2);

	Node segmentos = Arvore_getRaiz(Poligono_getSegmentos(p));
	int numIntersec = 0;
	forEach(segmento, segmentos) {
		if (Node_getAux(segmento) == 0) {
            Segmento s = Node_getObjeto(segmento);
			if (verificarSegmentosInterceptam(s1, s) || verificarSegmentosInterceptam(s2, s) ||
				verificarSegmentosInterceptam(s3, s) || verificarSegmentosInterceptam(s4, s)) {
				destruirSegmento(s1);
				destruirSegmento(s2);
				destruirSegmento(s3);
				destruirSegmento(s4);
				return true;
			}
        }
	}

	destruirSegmento(s1);
	destruirSegmento(s2);
	destruirSegmento(s3);
	destruirSegmento(s4);
	destruirPonto(p1);
	destruirPonto(p2);
	destruirPonto(p3);
	destruirPonto(p4);
	return false;
}

double calcularAreaTriangulo(double x, double y, Vertice b, Vertice c) {
	double s = fabs(Vertice_get_y(b)*x + Vertice_get_y(c)*Vertice_get_x(b) +
				Vertice_get_x(c)*y - Vertice_get_y(b)*Vertice_get_x(c) -
				Vertice_get_y(c)*x - y*Vertice_get_x(b))/2;
	return s;
}