#ifndef __Primitive__
#define __Primitive__

#include "node.h"

class Primitive : public Node
{
protected:
	Vector e, c; //!< emission, color
	int refl; //!< reflection type
	double f; //!< Maximum color channel value
public:
	Primitive(void);
	Primitive( Vector&, Vector&, int );
	virtual ~Primitive(void);

	Vector getEmission() { return e; };
	Vector getColor() { return c; };
	int getRefl() { return refl; };
	double getF() { return f; };
};

#endif
