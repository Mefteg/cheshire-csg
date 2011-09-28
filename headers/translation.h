#ifndef __Translation__
#define __Translation__

#include "transfo.h"

class Translation : public Transfo
{
public:
	Translation(void);
	Translation(Node*,const Vector);
	~Translation(void);

	int Intersect(const Ray&, Intersection&);
	int Intersect(const Ray&, Intersection&, Intersection&){return 0;};

	Vector getEmission() { return Vector(); };
	Vector getColor() { return Vector(); };
	Vector getPosition() { return Vector(); };
	int getRefl() { return 0; };
	double getF() { return 0; };
};

#endif
