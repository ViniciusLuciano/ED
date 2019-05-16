#include "colisao.h"

bool formasColidem(Forma a, Forma b) {
    if(getForma_tipoForma(a) == CIRCULO && getForma_tipoForma(b) == RETANGULO)
        return colisaoCirculoRetangulo(getForma_figura(a), getForma_figura(b));
    else if(getForma_tipoForma(a) == RETANGULO && getForma_tipoForma(b) == CIRCULO)
        return colisaoCirculoRetangulo(getForma_figura(b), getForma_figura(a));
    else if(getForma_tipoForma(a) == RETANGULO && getForma_tipoForma(b) == RETANGULO)
        return colisaoRetanguloRetangulo(getForma_figura(a), getForma_figura(b));
    else if(getForma_tipoForma(a) == CIRCULO && getForma_tipoForma(b) == CIRCULO)
        return colisaoCirculoCirculo(getForma_figura(a), getForma_figura(b));
}   

bool colisaoCirculoRetangulo(Circulo c, Retangulo r) {
    double xMaisProx = clamp(getCirculo_x(c), getRetangulo_x(r), getRetangulo_max_x(r));
    double yMaisProx = clamp(getCirculo_y(c), getRetangulo_y(r), getRetangulo_max_y(r));

    if( distanciaL2(getCirculo_x(c), getCirculo_y(c), xMaisProx, yMaisProx) < getCirculo_r(c) )
        return true;
    return false;
}

bool colisaoRetanguloRetangulo(Retangulo r1, Retangulo r2) {
    return (getRetangulo_x(r1) < getRetangulo_max_x(r2)) && (getRetangulo_max_x(r1) > getRetangulo_x(r2)) &&
            (getRetangulo_y(r1) < getRetangulo_max_y(r2)) && (getRetangulo_max_y(r1) > getRetangulo_y(r2));
}

bool colisaoCirculoCirculo(Circulo c1, Circulo c2) {
    return distanciaL2(getCirculo_x(c1), getCirculo_y(c1), getCirculo_x(c2), getCirculo_y(c2)) 
    < getCirculo_r(c1) + getCirculo_r(c2);
}