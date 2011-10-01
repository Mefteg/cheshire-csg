

#ifndef __Cylinder__
#define __Cylinder__


#include "primitive.h"


class Cylinder : public Primitive
{
protected:
  double radius;
  double height;
  Vector bottom;

public:
  Cylinder() {}
  Cylinder(const double&, const Vector&, const double, const Vector&, const Vector&, int);
  int Intersect(const Ray&, Intersection& );
  int Intersect(const Ray&, Intersection&, Intersection& );
  int PMC(const Vector&);

  Vector getPosition() { return Vector(0,0,0); };

};

#endif
