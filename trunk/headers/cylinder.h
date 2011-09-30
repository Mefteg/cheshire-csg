

#ifndef __Cylinder__
#define __Cylinder__


#include "primitive.h"


class Cylinder : public Primitive
{
protected:
  double radius;
  Vector axis;
  Vector top;
  Vector bottom;

public:
  Cylinder() {}
  Cylinder(const double&, const Vector&, const Vector&, const Vector&, const Vector&, const Vector&, int);
  int Intersect(const Ray&, Intersection&);

  Vector getPosition() { return Vector(0,0,0); };

};

#endif