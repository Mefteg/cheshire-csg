/**
 * \file sphere.h
 * \brief class Sphere header
 * \author Gimenez Tom, Roumier Vincent, Matéo Camille
 * \version 1.0
 * \date 01 octobre 2011
 *
 * Sphere is a primitive of the CSG
 *
 */


#ifndef __Sphere__
#define __Sphere__

//#include <iostream>
//using namespace std;

#include "primitive.h"

// Material types are as follows
// Diffuse : 0
// Specular : 1
// Refractive : 2

class Sphere : public Primitive
{
	public:
	  
	double rad;       //!< Radius
	Vector p;   //!< position, emission, color

	public:
	  
	Sphere() {}
	Sphere(const double&, const Vector&, const Vector&, const Vector&, int);
	int Intersect(const Ray &r,Intersection&);
	int Intersect( const Ray &, Intersection&, Intersection& );
	int PMC(const Vector& );

	Vector getPosition(){return p;};
};

#endif
