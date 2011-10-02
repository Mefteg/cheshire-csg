/**
 * \file node.h
 * \brief class Node header
 * \author Gimenez Tom, Roumier Vincent, Matéo Camille
 * \version 1.0
 * \date 01 octobre 2011
 *
 * Containing Node class
 *
 */


#ifndef __Node__
#define __Node__

#include "vector.h"
#include "ray.h"
#include "intersection.h"

/*! 
 * \class Node
 * \brief Node class
 * 
 * Node is abstract class
 * 
 */
class Node
{
	public:
	  
	Node(void);
	virtual ~Node(void);

	/*!
	*  \brief Intersecting function
	*
	*  Compute the intersection between a node and a ray
	*
	*  \param ray : the ray
	*  \param t : the intersection
	*/
	virtual int Intersect( const Ray &, Intersection&) = 0;
	
	/*!
	*  \brief Intersecting function
	*
	*  Compute the intersections between a node and a ray
	*
	*  \param ray : the ray
	*  \param t1 : the first intersection
	*  \param t2 : the second intersection
	*/
	virtual int Intersect( const Ray &, Intersection&, Intersection& ) = 0;
	
	/*!
	*  \brief Containing function
	*
	*  Checks if the point is inside the instance
	*
	*  \param u : the point
	*/
	virtual int PMC(const Vector&) = 0;

	virtual Vector getPosition() = 0;
	virtual Vector getEmission() = 0;
	virtual Vector getColor() = 0;
	virtual double getF() = 0;
	virtual int getRefl() = 0;
};

#endif
