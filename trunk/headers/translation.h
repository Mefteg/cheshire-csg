/**
 * \file translation.h
 * \brief class Translation header
 * \author Gimenez Tom, Roumier Vincent, Matéo Camille
 * \version 1.0
 * \date 01 octobre 2011
 *
 * Containing Translation class
 *
 */


#ifndef __Translation__
#define __Translation__

#include "transfo.h"

/*! 
 * \class Translation
 * \brief Translation class
 * 
 * Translation is a transformation for the CSG
 * 
 */
class Translation : public Transfo
{

	public:
	  
	Translation(void);
	Translation(Node*, const Vector);
	~Translation(void);

	/*!
	*  \brief Intersecting function
	*
	*  Compute the intersection between a translation and a ray
	*
	*  \param ray : the ray
	*  \param t : the intersection
	*/
	int Intersect(const Ray&, Intersection&);
	
	/*!
	*  \brief Intersecting function
	*
	*  Compute the intersections between a translation and a ray
	*
	*  \param ray : the ray
	*  \param t : the first intersection
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
	Vector getPosition() { return m.MulPt( left->getPosition()); };
	int getRefl() { return 0; };
	double getF() { return 0; };
};

#endif
