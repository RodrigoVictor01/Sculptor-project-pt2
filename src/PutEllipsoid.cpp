#include "../include/PutEllipsoid.hpp"

PutEllipsoid::PutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz, float r, float g, float b, float a){
  this->xcenter = xcenter;
  this->ycenter = ycenter;
  this->zcenter = zcenter;
  this->rx = rx;
  this->ry = ry;
  this->rz = rz;
  this->r = r;
  this->g = g;
  this->b = b;
  this->a = a;
}

void PutEllipsoid::draw(Sculptor &sculptor){
  sculptor.putEllipsoid(xcenter, ycenter, zcenter, rx, ry, rz);
  sculptor.setColor(r, g, b, a);
}







