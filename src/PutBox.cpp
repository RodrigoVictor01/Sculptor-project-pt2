#include "../include/PutBox.hpp"

PutBox::PutBox(int x0, int x1, int y, int y1, int z0, int z1, float r, float g, float b, float a){
  this->x0 = x0;
  this->x1 = x1;
  this->y0 = y;
  this->y1 = y1;
  this->z0 = z0;
  this->z1 = z1;
  this->r = r;
  this->g = g;
  this->b = b;
  this->a = a;
}

void PutBox::draw(Sculptor &sculptor){
  sculptor.setColor(r, g, b, a);
  sculptor.putBox(x0, x1, y0, y1, z0, z1);
}