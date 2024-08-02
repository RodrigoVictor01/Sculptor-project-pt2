#include "../include/CutVoxel.hpp"

CutVoxel::CutVoxel(int x, int y, int z){
  this->x = x;
  this->y = y;
  this->z = z;
}

void CutVoxel::draw(Sculptor &sculptor){
  sculptor.cutVoxel(x, y, z);
}