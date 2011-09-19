// Fast Raytracer
// Changelog 10.09.16


#include "sphere.h"

/*!
\class Sphere sphere.h
\brief This class implements a sphere object for ray-tracing. 
*/

/*!
\brief Creates a sphere.
*/
/*Sphere::Sphere(const double& rad,const Vector& p,const Vector& e,const Vector& c, int refl)
{
  Sphere::rad=rad;
  Sphere::p=p;
  Sphere::e=e;
  Sphere::c=c;
  // compute the dominant color
  Sphere::f=c[0]>c[1] && c[0]>c[2] ? c[0] : c[1]>c[2] ? c[1] : c[2];
  Sphere::refl=refl;
}*/
Sphere::Sphere(const double& rad,const Vector& p,Vector& e,Vector& c, int refl) : 
	Primitive( e, c, refl )
{
  Sphere::rad=rad;
  Sphere::p=p;
}

/*!
\brief Compute the intersection between the object and a ray
\return 1 if an intersection exists, 0 otherwise
*/
int Sphere::Intersect(const Ray &ray,double& t) 
{
  t=0.0;
  Vector op = p-ray.Origin();
  double b=op*ray.Direction();
  double det=b*b-op*op+rad*rad; 
  if (det<=0.0) return 0; 
  det=sqrt(det); 
  return (t=b-det)>1e-4 ? 1 : ((t=b+det)>1e-4 ? 1 : 0); 
} 
