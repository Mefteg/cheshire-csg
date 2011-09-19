// Blob-Ray Raytracer
// Changelog 05.01.24

#ifndef __Ray__
#define __Ray__

#include "vector.h"

// Ray class
class Ray
{
protected:
  Vector c;     //!< Origin of the ray.
  Vector n;     //!< Direction.
public:
  //! Empty.
  Ray() {}
  //! Destroy a ray.
  ~Ray() {}
  Ray(const Vector&,const Vector&);
  Ray Reflect(const Vector&,const Vector&) const;

  Vector operator()(const double& t) const;

  // Functions to access Vector class components
  Vector Origin() const { return c; }
  Vector Direction() const { return n; }
};

/*!
\brief Creates a ray.
\param p Origin.
\param d Direction.
*/
inline Ray::Ray(const Vector& p, const Vector& d)
{
  c=p;
  n=d;  
}

//! Computes the location of a vertex along the ray.
inline Vector Ray::operator()(const double& t) const 
{ 
  return c+t*n; 
}

#endif

