/**
 * \file ray.h
 * \brief class Ray header
 * \author Gimenez Tom, Roumier Vincent, Matéo Camille
 * \version 1.0
 * \date 01 octobre 2011
 *
 * Ray is a data structure
 *
 */


#ifndef __Ray__
#define __Ray__

#include "vector.h"

class Ray
{
	protected:
	  
	Vector c;	//!< Origin of the ray.
	Vector n;	//!< Direction.
	
	public:
	  
	Ray() {}
	~Ray() {}
	Ray(const Vector&,const Vector&);
	Ray Reflect(const Vector&,const Vector&) const;
	Vector operator()(const double& t) const;

	Vector Origin() const { return c; }
	Vector Direction() const { return n; }
};

/**
 * \brief Ray constructor
 * \param p Origin
 * \param d Direction
*/
inline Ray::Ray(const Vector& p, const Vector& d)
{
	c = p;
	n = d;  
}

/**	\brief Computes the location of a vertex along the ray */
inline Vector Ray::operator()(const double& t) const 
{ 
	return c + t * n; 
}

#endif

