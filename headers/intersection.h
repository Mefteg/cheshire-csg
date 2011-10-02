/**
 * \file intersection.h
 * \brief class Intersection header
 * \author Gimenez Tom, Roumier Vincent, Matéo Camille
 * \version 1.0
 * \date 01 octobre 2011
 *
 * Containing Intersection class
 *
 */


#include "vector.h"


class Node;

/*! 
 * \class Intersection
 * \brief Intersection class
 * 
 * Intersection is data structure
 * 
 */
class Intersection
{
	public:

	double t;	/*!< Distance to the origin */
	Node * obj;	/*!< Intersected object */
	Vector pos;	/*!< Intersection coordinates */
	Vector normal;  /*!< Intersection normal */
	  
	Intersection(){};
	~Intersection(){};

	// Opérateur de tri des intersections
	int operator<(const Intersection & i) const { return t < i.t; }
	int operator>(const Intersection & i) const { return t > i.t; }
};

