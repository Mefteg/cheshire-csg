// Fast Raytracer
// Changelog 10.09.16


#ifndef __Box__
#define __Box__

#include "primitive.h"

class Box : public Primitive
{ 
protected:
  Vector a,b; //!< End vertices of the box.
public:
  //! Creates a generic box (empty).
  Box() {}
  Box(const Vector&);
  Box(const Vector&,const Vector&, Vector&, Vector&, int);
  Box(const Vector&,const double&);
  Box(Vector*,int);
  Box(const Box&,const Box&);

  //! Destroy a box, empty.
  ~Box() {}

  // Access vertexes
  Vector& operator[] (int);
  Vector operator[] (int) const;

  Vector Center() const;
  Vector Diagonal() const;
  double Radius() const;
  Vector Vertex(int) const;

  double R(const Vector&) const;
  Vector Normal(const Vector&) const;

  // Intersection with a ray
  int Intersect(const Ray& ray) const;
  
  int Intersect(const Ray&, Intersection&);

  int Intersect(const Ray&,double&,double&) const;
  int Intersect(const Ray&,double&,double&,Vector&,Vector&) const;
  int Intersect(const Ray&,double&,Vector&) const;

  int Intersect(const Box&) const;

  int Inside(const Box&) const;
  int Inside(const Vector&) const;

  double Volume() const;
  double Area() const;

  Vector getPosition() { return Center(); };

public:
  static const double epsilon;
};

//! Returns either end vertex of the box.
inline Vector& Box::operator[] (int i) 
{
  if (i==0) return a;
  else return b;
}

//! Overloaded.
inline Vector Box::operator[] (int i) const 
{
  if (i==0) return a;
  else return b;
}

//! Returns the center of the box.
inline Vector Box::Center() const { return 0.5*(a+b); }

//! Returns the half diagonal of the box.
inline Vector Box::Diagonal() const { return 0.5*(b-a); }

//! Returns the radius of the box, i.e. the length of the half diagonal of the box.
inline double Box::Radius() const { return 0.5*Norm(b-a); }

//! Returns the k<SUP>th</SUP> vertex of the box.
inline Vector Box::Vertex(int k) const { return Vector ((k&1)?b[0]:a[0],(k&2)?b[1]:a[1],(k&4)?b[2]:a[2]); }

//! Compute the volume of a box.
inline double Box::Volume() const
{
  Vector side=b-a;
  return side[0]*side[1]*side[2];
}

//! Compute the surface area of a box.
inline double Box::Area() const
{
  Vector side=b-a;
  return 2.0*(side[0]*side[1]+side[0]*side[2]+side[1]*side[2]);
}

//! Computes the minimum distance between the box and a point in space.
inline double Box::R(const Vector& p) const
{
  double r=0.0;

  // Slab
  for (int i=0;i<3;i++)
  {
    if (p[i]<a[i])
    {
      double s=p[i]-a[i];
      r+=s*s;
    }
    else if (p[i]>b[i])
    {
      double s=p[i]-b[i];
      r+=s*s;
    }
  }
  return r;
}

//! Computes the normal vector between a point and a box.
inline Vector Box::Normal(const Vector& p) const
{
  Vector n;

  // Slab
  for (int i=0;i<3;i++)
  {
    if (p[i]<a[i])
    {
      n[i]=p[i]-a[i];
    }
    else if (p[i]>b[i])
    {
      n[i]=p[i]-b[i];
    }
    else
    {
      n[i]=0.0;
    }
  }
  return n;
}
#endif

