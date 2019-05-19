#include "colisao.h"

bool formasColidem(Forma a, Forma b) {
    if(Forma_get_tipoForma(a) == CIRCULO && Forma_get_tipoForma(b) == RETANGULO)
        return colisaoCirculoRetangulo(Forma_getFigura(a), Forma_getFigura(b));
    else if(Forma_get_tipoForma(a) == RETANGULO && Forma_get_tipoForma(b) == CIRCULO)
        return colisaoCirculoRetangulo(Forma_getFigura(b), Forma_getFigura(a));
    else if(Forma_get_tipoForma(a) == RETANGULO && Forma_get_tipoForma(b) == RETANGULO)
        return colisaoRetanguloRetangulo(Forma_getFigura(a), Forma_getFigura(b));
    else if(Forma_get_tipoForma(a) == CIRCULO && Forma_get_tipoForma(b) == CIRCULO)
        return colisaoCirculoCirculo(Forma_getFigura(a), Forma_getFigura(b));
}   

bool colisaoCirculoRetangulo(Circulo c, Retangulo r) {
    double xMaisProx = clamp(Circulo_get_x(c), Retangulo_get_x(r), Retangulo_get_max_x(r));
    double yMaisProx = clamp(Circulo_get_y(c), Retangulo_get_y(r), Retangulo_get_max_y(r));

    if( distanciaL2(Circulo_get_x(c), Circulo_get_y(c), xMaisProx, yMaisProx) < Circulo_get_r(c) )
        return true;
    return false;
}

bool colisaoRetanguloRetangulo(Retangulo r1, Retangulo r2) {
    return (Retangulo_get_x(r1) < Retangulo_get_max_x(r2)) && (Retangulo_get_max_x(r1) > Retangulo_get_x(r2)) &&
            (Retangulo_get_y(r1) < Retangulo_get_max_y(r2)) && (Retangulo_get_max_y(r1) > Retangulo_get_y(r2));
}

bool colisaoCirculoCirculo(Circulo c1, Circulo c2) {
    return distanciaL2(Circulo_get_x(c1), Circulo_get_y(c1), Circulo_get_x(c2), Circulo_get_y(c2)) 
    < Circulo_get_r(c1) + Circulo_get_r(c2);
}