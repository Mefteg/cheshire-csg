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

	Vector getEmission() { return Vector(); };
	Vector getColor() { return Vector(); };
	int getRefl() { return 0; };
	double getF() { return 0; };
};

#endif
