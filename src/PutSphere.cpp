#include "../include/PutSphere.hpp"

PutSphere::PutSphere(int xcenter, int ycenter, int zcenter, int radius, float r, float g, float b, float a){
  this->xcenter = xcenter;
  this->ycenter = ycenter;
  this->zcenter = zcenter;
  this->radius = radius;
  this->r = r;
  this->g = g;
  this->b = b;
  this->a = a;
}

void PutSphere::draw(Sculptor &sculptor){
  sculptor.putSphere(xcenter, ycenter, zcenter, radius);
  sculptor.setColor(r, g, b, a);
};