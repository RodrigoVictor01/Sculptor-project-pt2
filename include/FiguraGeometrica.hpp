#ifndef FIGURAGEOMETRICA_HPP
#define FIGURAGEOMETRICA_HPP

#include "../include/Sculptor.hpp"

class Sculptor;

class FiguraGeometrica {

public:

    FiguraGeometrica();
    virtual ~FiguraGeometrica() {}
    virtual void draw(Sculptor &sculptor) = 0; // Função virtual pura

};

#endif // FIGURAGEOMETRICA_HPP
