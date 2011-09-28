#ifndef __Union__
#define __Union__

#include "opbin.h"

class Union : public OpBin
{
public:
	Union(void);
	Union(Node*, Node*);
	~Union(void);

	int Intersect(const Ray&, Intersection&);
	int Intersect(const Ray&, Intersection&, Intersection&);
    int PMC(const Vector&);

	Vector getEmission() { return Vector(); };
	Vector getColor() { return Vector(); };
	Vector getPosition() { return Vector(); };
	int getRefl() { return 0; };
	double getF() { return 0; };
};

#endif
