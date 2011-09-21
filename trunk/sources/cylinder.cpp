
# include "cylinder.h"

  double radius;
  Vector axis;
  Vector top;
  Vector bottom;

Cylinder::Cylinder(const double& radius, const Vector& axis, const Vector& top, const Vector& bottom, const Vector& e, const Vector& c, int refl) :
	Primitive(e, c, refl)
{
	this->radius = radius;
	this->axis = axis;
	this->top = top;
	this->bottom = bottom;
}

int Cylinder::Intersect(const Ray&, Intersection&)
{
	return 0;
}
