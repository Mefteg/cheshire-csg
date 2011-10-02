/*!
 * \file cylinder.h
 * \brief class Cylinder header
 * \author Gimenez Tom, Roumier Vincent, Matéo Camille
 * \version 1.0
 * \date 01 octobre 2011
 *
 * Containing Cylinder class
 *
 */


#ifndef __Cylinder__
#define __Cylinder__


#include "primitive.h"

/*! 
 * \class Cylinder
 * \brief Cylinder class
 * 
 * Cylinder is a primitive of the CSG
 * 
 */
class Cylinder : public Primitive
{
	protected:
	  
	double radius; /*!< Cylinder radius */
	double height; /*!< Cylinder upper lenght */
	Vector bottom; /*!< Cylinder bottom center */

	public:
	
	Cylinder() {}
	Cylinder(const double&, const Vector&, const double, const Vector&, const Vector&, int);
	int Intersect(const Ray&, Intersection&);
	
	/*!
	*  \brief Intersecting function
	*
	*  Compute the intersections between a cylinder and a ray
	*
	*  \param ray : the ray
	*  \param inter1 : the first intersection
	*  \param inter2 : the second intersection
	*/
	int Intersect(const Ray&, Intersection&, Intersection& );
	
	/*!
	*  \brief PMC function
	*
	*  Compute if the point is in the cylinder
	*
	*  \param point : the point
	*/
	int PMC(const Vector&);

	/*!
	*  \brief Get position function
	*
	*  Compute the cylinder position
	*
	*/	
	Vector getPosition();

};

#endif
