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

void svg_escreverTriangulo(FILE *SVG, double x1, double y1, Vertice v2, Vertice v3, bool brl) {
	//double x1 = Vertice_get_x(v1), y1 = Vertice_get_y(v1);
	double x2 = Vertice_get_x(v2), y2 = Vertice_get_y(v2);
	double x3 = Vertice_get_x(v3), y3 = Vertice_get_y(v3);
	fprintf(SVG, "<polygon points=\"%lf,%lf %lf,%lf %lf,%lf\" style=\"fill: %s; opacity: 0.5\"/>\n", x1, y1, x2, y2, x3, y3, brl ? "orange" : "green");
}

void svg_escreverBomba(FILE *SVG, double x, double y) {
	fprintf(SVG, "<path stroke=\"orange\" stroke-width=\"5\" transform=\"translate(%lf %lf) scale(0.03 0.03)\" d=\"M440.5 88.5l-52 52L415 167c9.4 9.4 9.4 24.6 0 33.9l-17.4 17.4c11.8 26.1 18.4 55.1 "
        "18.4 85.6 0 114.9-93.1 208-208 208S0 418.9 0 304 93.1 96 208 96c30.5 0 59.5 6.6 85.6 18.4L311 97c9.4-9.4 "
        "24.6-9.4 33.9 0l26.5 26.5 52-52 17.1 17zM500 60h-24c-6.6 0-12 5.4-12 12s5.4 12 12 12h24c6.6 0 12-5.4 "
        "12-12s-5.4-12-12-12zM440 0c-6.6 0-12 5.4-12 12v24c0 6.6 5.4 12 12 12s12-5.4 12-12V12c0-6.6-5.4-12-12-12zm33.9 "
        "55l17-17c4.7-4.7 4.7-12.3 0-17-4.7-4.7-12.3-4.7-17 0l-17 17c-4.7 4.7-4.7 12.3 0 17 4.8 4.7 12.4 4.7 17 0zm-67.8 "
        "0c4.7 4.7 12.3 4.7 17 0 4.7-4.7 4.7-12.3 0-17l-17-17c-4.7-4.7-12.3-4.7-17 0-4.7 4.7-4.7 12.3 0 17l17 17zm67.8 "
        "34c-4.7-4.7-12.3-4.7-17 0-4.7 4.7-4.7 12.3 0 17l17 17c4.7 4.7 12.3 4.7 17 0 4.7-4.7 4.7-12.3 0-17l-17-17zM112 "
        "272c0-35.3 28.7-64 64-64 8.8 0 16-7.2 16-16s-7.2-16-16-16c-52.9 0-96 43.1-96 96 0 8.8 7.2 16 16 16s16-7.2 16-16z\"/>",
        x - 6.5, y - 8.5);
}

void svg_escreverX(FILE* svg, Predio p) {
	fprintf(svg, "<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" style=\"stroke:rgb(255,0,0);stroke-width:2\" />\n", 
           Predio_get_x(p),
            Predio_get_y(p),
            Predio_get_x_max(p),
            Predio_get_y_max(p));
	
	fprintf(svg, "<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" style=\"stroke:rgb(255,0,0);stroke-width:2\" />\n", 
           Predio_get_x_max(p),
            Predio_get_y(p),
            Predio_get_x(p),
            Predio_get_y_max(p));
	
	char text[50];
	sprintf(text, "%d", Predio_getNumMoradores(p));
	Texto texto = criarTexto(Predio_get_x_max(p), (Predio_get_y(p) + Predio_get_y_max(p))/2, text);
	Texto_setTamanho(texto, 20);
	Texto_setCor(texto, Predio_getNumMoradores(p) > 0 ? "green" : "red");
	Texto_escreverSvg(texto, svg);
	destruirTexto(texto);
}