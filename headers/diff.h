#ifndef __Diff__
#define __Diff__

#include "opbin.h"

class Diff : public OpBin
{
public:
	Diff(void);
	Diff(Node*, Node*);
	~Diff(void);

	int Intersect(const Ray&, Intersection&);
	int Intersect(const Ray&, Intersection&, Intersection&);
    int PMC(const Vector&);

	Vector getEmission() { return Vector(); };
	Vector getColor() { return Vector(0,0,0); };
	Vector getPosition() { return left->getPosition(); };
	int getRefl() { return 0; };
	double getF() { return 0; };
};

#endif
