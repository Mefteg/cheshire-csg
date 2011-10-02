/**
 * \file inter.h
 * \brief class Inter header
 * \author Gimenez Tom, Roumier Vincent, Matéo Camille
 * \version 1.0
 * \date 01 octobre 2011
 *
 * Containing inter class
 *
 */


#ifndef __Inter__
#define __Inter__

#include "opbin.h"

/*! 
 * \class Inter
 * \brief Inter class
 * 
 * Inter is a binary operand of the CSG
 * 
 */
class Inter : public OpBin
{
	public:
	  
	Inter(void);
	Inter(Node*, Node*);
	~Inter(void);

	/*!
	*  \brief Intersecting function
	*
	*  Compute the intersection between a intersection and a ray
	*
	*  \param ray : the ray
	*  \param t : the intersection
	*/
	int Intersect(const Ray&, Intersection&);
	
	/*!
	*  \brief Intersecting function
	*
	*  Compute the intersections between a intersection and a ray
	*
	*  \param ray : the ray
	*  \param t1 : the first intersection
	*  \param t2 : the second intersection
	*/
	int Intersect(const Ray&, Intersection&, Intersection&);
	
	/*!
	*  \brief Containing function
	*
	*  Checks if a point is inside the instance
	*
	*  \param u : the point
	*/
	int PMC(const Vector&);

	Vector getEmission() { return Vector(); };
	Vector getColor() { return Vector(); };
	Vector getPosition() { return (0.5 * left->getPosition() + 0.5 * right->getPosition()); };
	int getRefl() { return 0; };
	double getF() { return 0; };
};

#endif
