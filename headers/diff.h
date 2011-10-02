/**
 * \file diff.h
 * \brief class Diff header
 * \author Gimenez Tom, Roumier Vincent, Matéo Camille
 * \version 1.0
 * \date 01 octobre 2011
 *
 * Containing Diff class
 *
 */


#ifndef __Diff__
#define __Diff__

#include "opbin.h"

/*! 
 * \class Diff
 * \brief Diff class
 * 
 * Diff is a binary operand of the CSG
 * 
 */
class Diff : public OpBin
{
	public:
	  
	Diff(void);
	Diff(Node*, Node*);
	~Diff(void);

	/*!
	*  \brief Intersecting function
	*
	*  Compute the intersection between a difference and a ray
	*
	*  \param ray : the ray
	*  \param t : the intersection
	*/
	int Intersect(const Ray&, Intersection&);
	
	/*!
	*  \brief Intersecting function
	*
	*  Compute the intersections between a difference and a ray
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
	Vector getColor() { return Vector(0,0,0); };
	Vector getPosition() { return left->getPosition(); };
	int getRefl() { return 0; };
	double getF() { return 0; };
};

#endif
