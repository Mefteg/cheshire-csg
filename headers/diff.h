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
	int Intersect(const Ray&, Intersection&,Intersection&){return 0;};

	Vector getEmission() { return Vector(); };
	Vector getColor() { return Vector(); };
	Vector getPosition() { return Vector(); };
	int getRefl() { return 0; };
	double getF() { return 0; };
};

#endif