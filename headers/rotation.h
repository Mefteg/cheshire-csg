/**
 * \file rotation.h
 * \brief class Rotation header
 * \author Gimenez Tom, Roumier Vincent, Matéo Camille
 * \version 1.0
 * \date 01 octobre 2011
 *
 * Containing Rotation class
 *
 */


#ifndef __Rotation__
#define __Rotation__

#include "transfo.h"

/*! 
 * \class Rotation
 * \brief Rotation class
 * 
 * Rotation is a transformation for the CSG
 * 
 */
class Rotation : public Transfo
{
	public:
	  
	Rotation(void);
	Rotation(Node*, const Vector, float angle);
	~Rotation(void);

	/*!
	*  \brief Intersecting function
	*
	*  Compute the intersection between a rotation and a ray
	*
	*  \param ray : the ray
	*  \param t : the intersection
	*/
	int Intersect(const Ray&, Intersection&);
	
	/*!
	*  \brief Intersecting function
	*
	*  Compute the intersections between a rotation and a ray
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
	Vector getPosition() { return Vector(); };
	int getRefl() { return 0; };
	double getF() { return 0; };

	Matrix4Df mRotate;
	Matrix4Df mRotateInv;

};

#endif