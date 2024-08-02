#ifndef CUTELLIPSOID_HPP
#define CUTELLIPSOID_HPP
#include "FiguraGeometrica.hpp"


class CutEllipsoid : public FiguraGeometrica{

  int xcenter, ycenter, zcenter, rx, ry, rz;

  public:
    CutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz);
    void draw(Sculptor &sculptor) override;
};



#endif