#ifndef CUTVOXEL_HPP
#define CUTVOXEL_HPP
#include "FiguraGeometrica.hpp"

class CutVoxel : public FiguraGeometrica{
  int x, y, z;


  public:
    CutVoxel(int x, int y, int z);
    void draw(Sculptor &sculptor) override;
};






#endif