/**
 * \file sphere.h
 * \brief class Sphere header
 * \author Gimenez Tom, Roumier Vincent, Matéo Camille
 * \version 1.0
 * \date 01 octobre 2011
 *
 * Containing Sphere class
 *
 */


#ifndef __Sphere__
#define __Sphere__

#include "primitive.h"

/*! 
 * \class Sphere
 * \brief Sphere class
 * 
 * Sphere is a primitive of the CSG
 * 
 */
class Sphere : public Primitive
{
	public:
	  
	double rad;       //!< Radius
	Vector p;   //!< position, emission, color

	public:
	  
	Sphere() {}
	Sphere(const double&, const Vector&, const Vector&, const Vector&, int);
	
	/*!
	*  \brief Intersecting function
	*
	*  Compute the intersection between a sphere and a ray
	*
	*  \param ray : the ray
	*  \param inter : the intersection
	*/
	int Intersect(const Ray &r,Intersection&);
	
	/*!
	*  \brief Intersecting function
	*
	*  Compute the intersections between a sphere and a ray
	*
	*  \param ray : the ray
	*  \param intermin : the first intersection
	*  \param intermax : the second intersection
	*/
	int Intersect( const Ray &, Intersection&, Intersection& );
	
	/*!
	*  \brief Containing function
	*
	*  Checks if a point is inside the instance
	*
	*  \param a : the point
	*/
	int PMC(const Vector& );

	Vector getPosition(){return p;};
};

#endif
