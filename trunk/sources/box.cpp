// Fast Raytracer
// Changelog 10.09.16
#include <stdio.h>
// Self include
#include "box.h"

const double Box::epsilon=1.0e-5; //!< Epsilon value used to check intersections and some round off errors.

/*!
\class Box box.h
\brief This class implements an axis aligned box.

The data structure stores the opposite two corners as vectors.
The center and the radius (diagonal vector) are computed on the
fly by inline functions.

The vertices of a box can be obtained by using the Box::Vertex(int) 
member function which returns one of the eight vertices of the box. 
The two opposite corners can be obtained faster as follows:
\code
Box box(Vector(0.0,0.0,0.0),Vector(1.0,1.0,1.0)); // Unit box
Vector a=box[0]; // Lower vertex
Vector b=box[1]; // Opposite vertex
\endcode


This class provides a set of useful functions, such as the intersection
between a box and a ray. This class also implements the Minkowski sum
of boxes by overloading some operators.
*/

/*!
\brief Create a box given a center point and the half side length.
\param c Center. 
\param r Half side length.
*/
Box::Box(const Vector& c,const double& r)
{
  a=c-Vector(r,r,r);
  b=c+Vector(r,r,r);
}

/*!
\brief Create a box given two opposite corners. Note that this
constructor does not check the coordinates of the two vectors.
\param a,b End vertices.
*/
Box::Box(const Vector& a,const Vector& b, const Vector& e, const Vector &c, int refl) :
	Primitive( e, c, refl )
{
  this->a=a;
  this->b=b;
}

/*!
\brief Create an empty box given one vertex.
*/
Box::Box(const Vector& a)
{
  Box::b=Box::a=a;
}

/*!
\brief Creates the bounding box of a set of points.
\param v Array of vertices.
\param n Number of vertices.
*/
Box::Box(Vector* v, int n)
{
  for (int j=0;j<3;j++)
  {
    a[j]=v[0][j];
    b[j]=v[0][j];
    for (int i=1;i<n;i++)
    {
      if (v[i][j]<a[j])
      {
        a[j]=v[i][j];
      }
      if (v[i][j]>b[j])
      {
        b[j]=v[i][j];
      }
    }
  }
}

/*!
\brief Create a box embedding two boxes.
*/
Box::Box(const Box& x,const Box& y)
{
  a=min(x.a,y.a);
  b=max(x.b,y.b);
}

/*!
\brief Computes the intersection between a box and a ray.
Sorted intersection depths are returned if intersection occurs.
\param ray The ray
\param tmin, tmax Intersection depths
*/
/*int Box::Intersect(const Ray& ray,Intersection& intermin, Intersection& intermax) const
{
  intermin.t =-1e16;
  intermax.t = 1e16;

  Vector p=ray.Origin();
  Vector d=ray.Direction();

  double t;
  // Ox
  if (d[0]<-epsilon)
  {
    t=(a[0]-p[0])/d[0];
    if (t<intermin.t)
      return 0;
    if (t<=intermax.t)
      intermax.t=t;
    t=(b[0]-p[0])/d[0];
    if (t>=intermin.t)
    {
      if (t>intermax.t)
        return 0;
      intermin.t=t;
    }
  }
  else if (d[0]>epsilon)
  {
    t=(b[0]-p[0])/d[0];
    if (t<intermin.t)
      return 0;
    if (t<=intermax.t)
      intermax.t=t;
    t=(a[0]-p[0])/d[0];
    if (t>=intermin.t)
    {
      if (t>intermax.t)
        return 0;
      intermin.t=t;
    }
  }
  else if (p[0]<a[0] || p[0]>b[0])
    return 0;

  // Oy
  if (d[1]<-epsilon)
  {
    t=(a[1]-p[1])/d[1];
    if (t<intermin.t)
      return 0;
    if (t<=intermax.t)
      intermax.t=t;
    t=(b[1]-p[1])/d[1];
    if (t>=intermin.t)
    {
      if (t>intermax.t)
        return 0;
      intermin.t=t;
    }
  }
  else if (d[1]>epsilon)
  {
    t=(b[1]-p[1])/d[1];
    if (t<intermin.t)
      return 0;
    if (t<=intermax.t)
      intermax.t=t;
    t=(a[1]-p[1])/d[1];
    if (t>=intermin.t)
    {
      if (t>intermax.t)
        return 0;
      intermin.t=t;
    }
  }
  else if (p[1]<a[1] || p[1]>b[1])
    return 0;

  // Oz
  if (d[2]<-epsilon)
  {
    t=(a[2]-p[2])/d[2];
    if (t<intermin.t)
      return 0;
    if (t<=intermax.t)
      intermax.t=t;
    t=(b[2]-p[2])/d[2];
    if (t>=intermin.t)
    {
      if (t>intermax.t)
        return 0;
      intermin.t=t;
    }
  }
  else if (d[2]>epsilon)
  {
    t=(b[2]-p[2])/d[2];
    if (t<intermin.t)
      return 0;
    if (t<=intermax.t)
      intermax.t=t;
    t=(a[2]-p[2])/d[2];
    if (t>=intermin.t)
    {
      if (t>intermax.t)
        return 0;
      intermin.t=t;
    }
  }
  else if (p[2]<a[2] || p[2]>b[2])
    return 0;
  return 1;
}*/

int Box::Intersect(const Ray& ray, Intersection& inter) {
	Intersection inter1,inter2;
	int i = this->Intersect(ray, inter1, inter2);
	if(inter1.t > 0.000001)
		//get the nearest intersection
		inter.t = inter1.t;
	else
		inter.t = inter2.t;
	//position of the intersection
	inter.pos = ray(inter.t);
	//pointer to the box
	inter.obj = this;
	return i;
}

/*!
\brief Check the intersection between a box and a ray.

Although intersection depths are computed internally,
none are returned. This function calls the
intersection function and hides arguments in local
variables.

\param ray The ray.
*/
int Box::Intersect(const Ray& ray) const
{
  Intersection int1,int2;
  return Intersect(ray,int1,int2);
}

/*!
\brief Compute the intersection between an axis aligned box and a ray.
Parameters return the sorted intersection depths and the corresponding
normal vector at intersection point.
\param ray The ray.
\param tmin, tmax Minimum and maximum intersection depths.
\param an, bn Normals at intersection point.
*/
int Box::Intersect(const Ray& ray,Intersection& intermin,Intersection& intermax) const
{
  intermin.t =-1e16;
  intermax.t =1e16;

  Vector p=ray.Origin();
  Vector d=ray.Direction();

  double t;

  if (d[0]<-epsilon)
  {
    t=(a[0]-p[0])/d[0];
    if (t<intermin.t)
      return 0;
    if (t<=intermax.t)
    {
      intermax.t=t;
      intermax.normal=Vector(-1.0,0.0,0.0);
    }
    t=(b[0]-p[0])/d[0];
    if (t>=intermin.t)
    {
      if (t>intermax.t)
        return 0;
      intermin.t=t;
      intermin.normal=Vector(1.0,0.0,0.0);
    }
  }
  else if (d[0]>epsilon)
  {
    t=(b[0]-p[0])/d[0];
    if (t<intermin.t)
      return 0;
    if (t<=intermax.t)
    {
      intermax.t=t;
      intermax.normal=Vector(1.0,0.0,0.0);
    }
    t=(a[0]-p[0])/d[0];
    if (t>=intermin.t)
    {
      if (t>intermax.t)
        return 0;
      intermin.t=t;
      intermin.normal=Vector(-1.0,0.0,0.0);
    }
  }
  else if (p[0]<a[0] || p[0]>b[0])
    return 0;

  if (d[1]<-epsilon)
  {
    t=(a[1]-p[1])/d[1];
    if (t<intermin.t)
      return 0;
    if (t<=intermax.t)
    {
      intermax.t=t;
      intermax.normal=Vector(0.0,-1.0,0.0);
    }
    t=(b[1]-p[1])/d[1];
    if (t>=intermin.t)
    {
      if (t>intermax.t)
        return 0;
      intermin.t=t;
      intermin.normal=Vector(0.0,1.0,0.0);
    }
  }
  else if (d[1]>epsilon)
  {
    t=(b[1]-p[1])/d[1];
    if (t<intermin.t)
      return 0;
    if (t<=intermax.t)
    {
      intermax.t=t;
      intermax.normal=Vector(0.0,1.0,0.0);
    }
    t=(a[1]-p[1])/d[1];
    if (t>=intermin.t)
    {
      if (t>intermax.t)
        return 0;
      intermin.t=t;
      intermin.normal=Vector(0.0,-1.0,0.0);
    }
  }
  else if (p[1]<a[1] || p[1]>b[1])
    return 0;

  if (d[2]<-epsilon)
  {
    t=(a[2]-p[2])/d[2];
    if (t<intermin.t)
      return 0;
    if (t<=intermax.t)
    {
      intermax.t=t;
      intermax.normal=Vector(0.0,0.0,-1.0);
    }
    t=(b[2]-p[2])/d[2];
    if (t>=intermin.t)
    {
      if (t>intermax.t)
        return 0;
      intermin.t=t;
      intermin.normal=Vector(0.0,0.0,1.0);
    }
  }
  else if (d[2]>epsilon)
  {
    t=(b[2]-p[2])/d[2];
    if (t<intermin.t)
      return 0;
    if (t<=intermax.t)
    {
      intermax.t=t;
      intermax.normal=Vector(0.0,0.0,1.0);
    }
    t=(a[2]-p[2])/d[2];
    if (t>=intermin.t)
    {
      if (t>intermax.t)
        return 0;
      intermin.t=t;
      intermin.normal=Vector(0.0,0.0,-1.0);
    }
  }
  else if (p[2]<a[2] || p[2]>b[2])
    return 0;

  return 1;
}


/*!
\brief Compute the first positive intersection between an axis 
aligned box and a ray.
\param ray The ray.
\param t Intersection.
\param n Normal at intersection point.
*/
int Box::Intersect(const Ray& ray,double& t,Vector& n) const
{
  double u;
  Vector nu;

/*  if (Box::Intersect(ray,t,u,n,nu))
  {
    if (t>0.0)
    {		
      return 1;
    }
    else if (u>0.0)
    {
      t=u;
      n=nu;
      return 1;
    }
    else
    {
      return 0;
    }
  }*/
  return 0;
}

/*!
\brief Checks if a box is inside the instance.
*/
int Box::Inside(const Box& box) const
{
  return ((a<box.a) && (b>box.b));
}

/*!
\brief Checks if a point is inside the box.
*/
int Box::Inside(const Vector& u) const
{
  return ((a<u) && (b>u));
}
