#include "svg.h"


void svg_iniciar(FILE *SVG) {
	fprintf(SVG, "<svg> \n");
}

void svg_finalizar(FILE *SVG) {
	fprintf(SVG, "</svg>");
}

void svg_escreverRetanguloDelimitador(FILE *SVG2, Forma f1, Forma f2, bool colidem) {
	double xMin, xMax, yMin, yMax, largura, altura;
	if(Forma_get_tipoForma(f1) == CIRCULO && Forma_get_tipoForma(f2) == RETANGULO) {
		Circulo a = Forma_getFigura(f1);
		Retangulo b = Forma_getFigura(f2);

		xMin = Circulo_get_min_x(a) < Retangulo_get_x(b) ? Circulo_get_min_x(a) : Retangulo_get_x(b);
		xMax = Circulo_get_max_x(a) > Retangulo_get_max_x(b) ? Circulo_get_max_x(a) : Retangulo_get_max_x(b);
		yMin = Circulo_get_min_y(a) < Retangulo_get_y(b) ? Circulo_get_min_y(a) : Retangulo_get_y(b);
		yMax = Circulo_get_max_y(a) > Retangulo_get_max_y(b) ? Circulo_get_max_y(a) : Retangulo_get_max_y(b);

	} else if(Forma_get_tipoForma(f1) == RETANGULO && Forma_get_tipoForma(f2) == CIRCULO) {
		Retangulo a = Forma_getFigura(f1);
		Circulo b = Forma_getFigura(f2);

		xMin = Circulo_get_min_x(b) < Retangulo_get_x(a) ? Circulo_get_min_x(b) : Retangulo_get_x(a);
		xMax = Circulo_get_max_x(b) > Retangulo_get_max_x(a) ? Circulo_get_max_x(b) : Retangulo_get_max_x(a);
		yMin = Circulo_get_min_y(b) < Retangulo_get_y(a) ? Circulo_get_min_y(b) : Retangulo_get_y(a);
		yMax = Circulo_get_max_y(b) > Retangulo_get_max_y(a) ? Circulo_get_max_y(b) : Retangulo_get_max_y(a);

	} else if(Forma_get_tipoForma(f1) == RETANGULO && Forma_get_tipoForma(f2) == RETANGULO) {
		Retangulo a = Forma_getFigura(f1);
		Retangulo b = Forma_getFigura(f2);

		xMin = Retangulo_get_x(a) < Retangulo_get_x(b) ? Retangulo_get_x(a) : Retangulo_get_x(b);
		xMax = Retangulo_get_max_x(a) > Retangulo_get_max_x(b) ? Retangulo_get_max_x(a) : Retangulo_get_max_x(b);
		yMin = Retangulo_get_y(a) < Retangulo_get_y(b) ? Retangulo_get_y(a) : Retangulo_get_y(b);
		yMax = Retangulo_get_max_y(a) > Retangulo_get_max_y(b) ? Retangulo_get_max_y(a) : Retangulo_get_max_y(b);

	} else if(Forma_get_tipoForma(f1) == CIRCULO && Forma_get_tipoForma(f2) == CIRCULO) {
		Circulo a = Forma_getFigura(f1);
		Circulo b = Forma_getFigura(f2);

		xMin = Circulo_get_min_x(a) < Circulo_get_min_x(b) ? Circulo_get_min_x(a) : Circulo_get_min_x(b);
		xMax = Circulo_get_max_x(a) > Circulo_get_max_x(b) ? Circulo_get_max_x(a) : Circulo_get_max_x(b);
		yMin = Circulo_get_min_y(a) < Circulo_get_min_y(b) ? Circulo_get_min_y(a) : Circulo_get_min_y(b);
		yMax = Circulo_get_max_y(a) > Circulo_get_max_y(b) ? Circulo_get_max_y(a) : Circulo_get_max_y(b);

	}
	
	largura = xMax-xMin;
	altura = yMax-yMin;

	if(colidem)
		fprintf(SVG2, "<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" stroke=\"red\" fill-opacity=\"0\" />\n", xMin, yMin, largura, altura);
	else
		fprintf(SVG2, "<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" stroke=\"red\" fill-opacity=\"0\" stroke-dasharray=\"5\" />\n", xMin, yMin, largura, altura);
	
}

void svg_escreverPontoInterno(FILE *SVG, Forma a, double x, double y, bool interno) {
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

void svg_escreverRetaCentrosMassa(FILE *SVG, Forma a, Forma b) {
	double *centro1 = malloc(2*sizeof(double));
	double *centro2 = malloc(2*sizeof(double));
	centroDeMassa(a, centro1);
	centroDeMassa(b, centro2);
	fprintf(SVG, "<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"black\" />\n", centro1[0], centro1[1], centro2[0], centro2[1]);

	free(centro1);
	free(centro2);
}

void svg_escreverDistanciaCentrosMassa(FILE *SVG, Forma a, Forma b, double distancia) {
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
