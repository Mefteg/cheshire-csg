#ifndef __Inter__
#define __Inter__

#include "opbin.h"

class Inter : public OpBin
{
public:
	Inter(void);
	Inter(Node*, Node*);
	~Inter(void);

	int Intersect(const Ray&, Intersection&);
    int Intersect(const Ray&, Intersection&, Intersection&);
    int PMC(const Vector&);

	Vector getEmission() { return Vector(); };
	Vector getColor() { return Vector(); };
	Vector getPosition() { return (0.5*left->getPosition()+0.5*right->getPosition()); };
	int getRefl() { return 0; };
	double getF() { return 0; };
};

#endif
