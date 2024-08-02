#ifndef PUTELLIPSOID_HPP
#define PUTELLIPSOID_HPP
#include "FiguraGeometrica.hpp"


class PutEllipsoid : public FiguraGeometrica{
  int xcenter, ycenter, zcenter, rx, ry, rz;
  float r, g, b, a;

  public:
    PutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz, float r, float g, float b, float a);
    void draw(Sculptor &sculptor) override;
};


#endif