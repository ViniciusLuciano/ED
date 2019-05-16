#include "svg.h"


void iniciarSVG(FILE *SVG) {
	fprintf(SVG, "<svg> \n");
}

void finalizarSVG(FILE *SVG) {
	fprintf(SVG, "</svg>");
}

void escreverRetanguloDelimitador(FILE *SVG2, Forma f1, Forma f2, bool colidem) {
	double xMin, xMax, yMin, yMax, largura, altura;
	if(getForma_tipoForma(f1) == CIRCULO && getForma_tipoForma(f2) == RETANGULO) {
		Circulo a = getForma_figura(f1);
		Retangulo b = getForma_figura(f2);

		xMin = getCirculo_min_x(a) < getRetangulo_x(b) ? getCirculo_min_x(a) : getRetangulo_x(b);
		xMax = getCirculo_max_x(a) > getRetangulo_max_x(b) ? getCirculo_max_x(a) : getRetangulo_max_x(b);
		yMin = getCirculo_min_y(a) < getRetangulo_y(b) ? getCirculo_min_y(a) : getRetangulo_y(b);
		yMax = getCirculo_max_y(a) > getRetangulo_max_y(b) ? getCirculo_max_y(a) : getRetangulo_max_y(b);

	} else if(getForma_tipoForma(f1) == RETANGULO && getForma_tipoForma(f2) == CIRCULO) {
		Retangulo a = getForma_figura(f1);
		Circulo b = getForma_figura(f2);

		xMin = getCirculo_min_x(b) < getRetangulo_x(a) ? getCirculo_min_x(b) : getRetangulo_x(a);
		xMax = getCirculo_max_x(b) > getRetangulo_max_x(a) ? getCirculo_max_x(b) : getRetangulo_max_x(a);
		yMin = getCirculo_min_y(b) < getRetangulo_y(a) ? getCirculo_min_y(b) : getRetangulo_y(a);
		yMax = getCirculo_max_y(b) > getRetangulo_max_y(a) ? getCirculo_max_y(b) : getRetangulo_max_y(a);

	} else if(getForma_tipoForma(f1) == RETANGULO && getForma_tipoForma(f2) == RETANGULO) {
		Retangulo a = getForma_figura(f1);
		Retangulo b = getForma_figura(f2);

		xMin = getRetangulo_x(a) < getRetangulo_x(b) ? getRetangulo_x(a) : getRetangulo_x(b);
		xMax = getRetangulo_max_x(a) > getRetangulo_max_x(b) ? getRetangulo_max_x(a) : getRetangulo_max_x(b);
		yMin = getRetangulo_y(a) < getRetangulo_y(b) ? getRetangulo_y(a) : getRetangulo_y(b);
		yMax = getRetangulo_max_y(a) > getRetangulo_max_y(b) ? getRetangulo_max_y(a) : getRetangulo_max_y(b);

	} else if(getForma_tipoForma(f1) == CIRCULO && getForma_tipoForma(f2) == CIRCULO) {
		Circulo a = getForma_figura(f1);
		Circulo b = getForma_figura(f2);

		xMin = getCirculo_min_x(a) < getCirculo_min_x(b) ? getCirculo_min_x(a) : getCirculo_min_x(b);
		xMax = getCirculo_max_x(a) > getCirculo_max_x(b) ? getCirculo_max_x(a) : getCirculo_max_x(b);
		yMin = getCirculo_min_y(a) < getCirculo_min_y(b) ? getCirculo_min_y(a) : getCirculo_min_y(b);
		yMax = getCirculo_max_y(a) > getCirculo_max_y(b) ? getCirculo_max_y(a) : getCirculo_max_y(b);

	}
	
	largura = xMax-xMin;
	altura = yMax-yMin;

	if(colidem)
		fprintf(SVG2, "<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" stroke=\"red\" fill-opacity=\"0\" />\n", xMin, yMin, largura, altura);
	else
		fprintf(SVG2, "<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" stroke=\"red\" fill-opacity=\"0\" stroke-dasharray=\"5\" />\n", xMin, yMin, largura, altura);
	
}

void escreverPontoInterno(FILE *SVG, Forma a, double x, double y, bool interno) {
	double *centro = malloc(2*sizeof(double));
	centroDeMassa(a, centro);

	if(interno) {
		fprintf(SVG, "<circle cx=\"%lf\" cy=\"%lf\" r=\"1\" stroke=\"green\" fill=\"green\" />\n", x, y);
		fprintf(SVG, "<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"green\" />\n", centro[0], centro[1], x, y);
	} else {
		fprintf(SVG, "<circle cx=\"%lf\" cy=\"%lf\" r=\"1\" stroke=\"red\" fill=\"red\" />\n", x, y);
		fprintf(SVG, "<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"red\" />\n", centro[0], centro[1], x, y);
	}
	
	free(centro);
}

void escreverRetaCentrosMassa(FILE *SVG, Forma a, Forma b) {
	double *centro1 = malloc(2*sizeof(double));
	double *centro2 = malloc(2*sizeof(double));
	centroDeMassa(a, centro1);
	centroDeMassa(b, centro2);
	fprintf(SVG, "<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"black\" />\n", centro1[0], centro1[1], centro2[0], centro2[1]);

	free(centro1);
	free(centro2);
}

void escreverDistanciaCentrosMassa(FILE *SVG, Forma a, Forma b, double distancia) {
	double *centro1 = malloc(2*sizeof(double));
	double *centro2 = malloc(2*sizeof(double));
	centroDeMassa(a, centro1);
	centroDeMassa(b, centro2);

	double posX = (centro1[0] + centro2[0])/2;
	double posY = (centro1[1] + centro2[1])/2;
	fprintf(SVG, "<text x=\"%lf\" y=\"%lf\">%lf</text>\n", posX, posY, distancia);

	free(centro1);
	free(centro2);
}
