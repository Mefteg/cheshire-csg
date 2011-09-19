// Fast Raytracer
// Changelog 10.09.16

#ifndef __Sphere__
#define __Sphere__

//#include <iostream>
//using namespace std;

#include "vector.h"
#include "ray.h"

// Material types are as follows 
// Diffuse : 0
// Specular : 1
// Refractive : 2

class Sphere
{ 
public:
  double rad;       //!< Radius 
  Vector p, e, c;   //!< position, emission, color 
  double f; //!< Maximum color channel value
  int refl;      //!< Reflection type

public:
  /* Constructeurs */
  Sphere() {}
  Sphere(const double&,const Vector&,const Vector&,const Vector&,int);

  /* Intersection entre un objet et un rayon */
  int Intersect(const Ray &r,double& d) const;
}; 

#endif
