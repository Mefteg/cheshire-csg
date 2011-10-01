/**
 * \file intersection.h
 * \brief class Intersection header
 * \author Gimenez Tom, Roumier Vincent, Matéo Camille
 * \version 1.0
 * \date 01 octobre 2011
 *
 * Intersection is data structure
 *
 */


#include "vector.h"


class Node;

class Intersection
{
	public:
	  
	Intersection(){};
	~Intersection(){};

	double t; 		// distance to the origin
	Node * obj;		// intersected object
	Vector pos;
	Vector normal;

	// Opérateur de tri des intersections
	int operator<(const Intersection & i) const { return t < i.t; }
	int operator>(const Intersection & i) const { return t > i.t; }
};

