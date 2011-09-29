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
	Primitive(const Vector&, const Vector&, int );
	virtual ~Primitive(void);

	//virtual Vector Center()=0;
	Vector getEmission() { return e; };
	Vector getColor() { return c; };
	int getRefl() { return refl; };
	double getF() { return f; };
};

#endif
