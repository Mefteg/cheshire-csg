/*!
 * \file triangle.h
 * \brief class Triangle header
 * \author Gimenez Tom, Roumier Vincent, Matéo Camille
 * \version 1.0
 * \date 01 octobre 2011
 *
 * Containing Triangle class
 *
 */


#ifndef __Triangle__
#define __Triangle__


#include "primitive.h"

/*!
 * \class Triangle
 * \brief Triangle class
 *
 * Triangle is a primitive of the CSG
 *
 */
class Triangle : public Primitive
{
	protected:

    Vector p1; /*!< Triangle point p1 */
    Vector p2; /*!< Triangle point p2 */
    Vector p3; /*!< Triangle point p3 */

	public:

	Triangle() {}
	Triangle(const Vector&, const Vector&, const Vector&, const Vector&, const Vector&, int);
	int Intersect(const Ray&, Intersection&);

	/*!
	*  \brief Intersecting function
	*
	*  Compute the intersections between a triangle and a ray
	*
	*  \param ray : the ray
	*  \param inter1 : the first intersection
	*  \param inter2 : the second intersection
	*/
	int Intersect(const Ray&, Intersection&, Intersection& );

	/*!
	*  \brief PMC function
	*
	*  Compute if the point is in the triangle
	*
	*  \param point : the point
	*/
	int PMC(const Vector&);

	/*!
	*  \brief Get position function
	*
	*  Compute the triangle position
	*
	*/
	Vector getPosition();

};

#endif
