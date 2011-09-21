#ifndef __Node__
#define __Node__

// Include Vector class
#include "vector.h"
#include "ray.h"
#include "intersection.h"

class Node
{
public:
	Node(void);
	virtual ~Node(void);

	virtual int Intersect( const Ray &, Intersection&) =0;
	//virtual int Intersect( const Ray &, double &, double & ) =0;

	virtual Vector getPosition() =0;
	virtual Vector getEmission() =0;
	virtual Vector getColor() =0;
	virtual double getF() =0;
	virtual int getRefl() =0;
};

#endif
