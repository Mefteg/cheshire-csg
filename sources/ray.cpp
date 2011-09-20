// Fast Raytracer
// Changelog 10.09.16

#include "ray.h"

/*!
\class Ray ray.h
\brief This class implements a ray which is used in many ray-object intersection 
methods and for ray-tracing. 

The data-structure includes its origin and direction.
*/

/*!
\brief Computes the reflected ray from a ray hitting a surface.

The origin of the ray is defined as the argument intersection point,
and direction is set according to the normal of the surface at 
intersection point. 

\param p Intersection point.
\param normal Surface outgoing normal.
*/
Ray Ray::Reflect(const Vector& p,const Vector& normal) const
{   
  return Ray(p,n-2.0*normal*(n*normal));
}
