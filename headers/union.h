/**
 * \file union.h
 * \brief class Union header
 * \author Gimenez Tom, Roumier Vincent, Matéo Camille
 * \version 1.0
 * \date 01 octobre 2011
 *
 * Containing Union class
 *
 */


#ifndef __Union__
#define __Union__

#include "opbin.h"

/*! 
 * \class Union
 * \brief Union class
 * 
 * Union is a binary operand of the CSG
 * 
 */
class Union : public OpBin
{
	public:
	  
	Union(void);
	Union(Node* , Node*);
	~Union(void);

	/*!
	*  \brief Intersecting function
	*
	*  Compute the intersection between a union and a ray
	*
	*  \param ray : the ray
	*  \param t : the intersection
	*/
	int Intersect(const Ray&, Intersection&);
	
	/*!
	*  \brief Intersecting function
	*
	*  Compute the intersections between a union and a ray
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
	Vector getPosition() { return (0.5 * left->getPosition() + 0.5 * right->getPosition());  };
	int getRefl() { return 0; };
	double getF() { return 0; };
};

#endif
