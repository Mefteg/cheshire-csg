#ifndef __Rotation__
#define __Rotation__

#include "transfo.h"

class Rotation : public Transfo
{
public:
	Rotation(void);
	Rotation(Node*,const Vector,float angle);
	~Rotation(void);

	int Intersect(const Ray&, Intersection&);
	int Intersect(const Ray&, Intersection&, Intersection&);
	int PMC(const Vector&);

	Vector getEmission() { return Vector(); };
	Vector getColor() { return Vector(); };
	Vector getPosition() { return Vector(); };
	int getRefl() { return 0; };
	double getF() { return 0; };

	Matrix4Df mRotate;
	Matrix4Df mRotateInv;

};

#endif