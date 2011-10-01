/**
 * \file node.h
 * \brief class Node header
 * \author Gimenez Tom, Roumier Vincent, Matéo Camille
 * \version 1.0
 * \date 01 octobre 2011
 *
 * Node is abstract class
 *
 */


#ifndef __Node__
#define __Node__

#include "vector.h"
#include "ray.h"
#include "intersection.h"


class Node
{
	public:
	  
	Node(void);
	virtual ~Node(void);

	virtual int Intersect( const Ray &, Intersection&) = 0;
	virtual int Intersect( const Ray &, Intersection&, Intersection& ) = 0;
	virtual int PMC(const Vector&) = 0;

	virtual Vector getPosition() = 0;
	virtual Vector getEmission() = 0;
	virtual Vector getColor() = 0;
	virtual double getF() = 0;
	virtual int getRefl() = 0;
};

#endif
