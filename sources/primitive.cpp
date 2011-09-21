#include "primitive.h"


Primitive::Primitive(void)
{
}

Primitive::Primitive(const Vector& e, const Vector& c, int refl )
{
	this->e = e;
	this->c = c;
	this->refl = refl;
	// compute the dominant color
	this->f = c[0]>c[1] && c[0]>c[2] ? c[0] : c[1]>c[2] ? c[1] : c[2];
}

Primitive::~Primitive(void)
{
}
