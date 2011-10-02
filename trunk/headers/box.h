/**
 * \file box.h
 * \brief class Box header
 * \author Gimenez Tom, Roumier Vincent, Matéo Camille
 * \version 1.0
 * \date 01 octobre 2011
 *
 * Containing Box class
 *
 */


#ifndef __Box__
#define __Box__

#include "primitive.h"

/*! 
 * \class Box
 * \brief Box class
 * 
 * Box is a primitive of the CSG
 * 
 */
class Box : public Primitive
{
	protected:
  
	Vector a; /*!< Box bottom left point */
	Vector b; /*!< Box upper right point */
	
	public:
	
	static const double epsilon;  /*!< Epsilon value used to check intersections and some round off errors */

	  
	//! Creates a generic box (empty).
	Box() {}
	Box(const Vector&);
	Box(const Vector&, const Vector&, const Vector&, const Vector&, int);
	Box(const Vector&, const double&);
	Box(Vector*, int);
	Box(const Box&, const Box&);

	//! Destroy a box, empty.
	~Box() {}

	// Access vertexes
	Vector& operator[](int);
	Vector operator[](int) const;

	Vector Center() const;
	Vector Diagonal() const;
	double Radius() const;
	Vector Vertex(int) const;

	double R(const Vector&) const;
	Vector Normal(const Vector&) const;

	/*!
	*  \brief Intersecting function
	*
	*  Compute the intersection between a box and a ray
	*
	*  \param ray : the ray
	*  \param inter1 : the intersection
	*/
	int Intersect(const Ray&, Intersection&);
	
	/*!
	*  \brief Intersecting function
	*
	*  Compute the intersections between a box and a ray
	*
	*  \param ray : the ray
	*  \param inter1 : the first intersection
	*  \param inter2 : the second intersection
	*/
	int Intersect(const Ray&, Intersection&, Intersection&);
	
	/*!
	*  \brief Intersecting function
	* 
	*   Compute the first positive intersection between an axis aligned box and a ray
	* 
	*  \param ray : the ray
	*  \param t : the first intersection
	*  \param n : the normal at intersection point
	*/
	int Intersect(const Ray&, double&, Vector&) const;
	int Intersect(const Box&) const;

	/*!
	*  \brief Containing function
	*
	*  Checks if a box is inside the instance
	*
	*  \param box : the box
	*/
	int Inside(const Box&) const;
	
	/*!
	*  \brief Containing function
	*
	*  Checks if a point is inside the instance
	*
	*  \param u : the box
	*/
	int Inside(const Vector&) const;

	/*!
	*  \brief Containing function
	*
	*  Checks if a point is inside the instance
	*
	*  \param u : the point
	*/
	int PMC(const Vector&);

	double Volume() const;
	double Area() const;

	Vector getPosition() { return Center(); };
	
};

//! Returns either end vertex of the box.
inline Vector& Box::operator[] (int i)
{
	if (i == 0) return a;
	else return b;
}

//! Overloaded.
inline Vector Box::operator[] (int i) const
{
	if (i == 0) return a;
	else return b;
}

//! Returns the center of the box.
inline Vector Box::Center() const { return 0.5 * (a + b); }

//! Returns the half diagonal of the box.
inline Vector Box::Diagonal() const { return 0.5 * (b - a); }

//! Returns the radius of the box, i.e. the length of the half diagonal of the box.
inline double Box::Radius() const { return 0.5 * Norm(b - a); }

//! Returns the k<SUP>th</SUP> vertex of the box.
inline Vector Box::Vertex(int k) const { return Vector((k&1) ? b[0] : a[0], (k&2) ? b[1] : a[1], (k&4) ? b[2] : a[2]); }

//! Compute the volume of a box.
inline double Box::Volume() const
{
	Vector side = b - a;
	return side[0] * side[1] * side[2];
}

//! Compute the surface area of a box.
inline double Box::Area() const
{
	Vector side = b - a;
	return 2.0 * (side[0] * side[1] + side[0] * side[2] + side[1] * side[2]);
}

//! Computes the minimum distance between the box and a point in space.
inline double Box::R(const Vector& p) const
{
	double r = 0.0;

	// Slab
	for(int i = 0; i < 3; i++)
	{
		if(p[i] < a[i])
		{
			double s = p[i] - a[i];
			r += s * s;
		}
		else if(p[i] > b[i])
		{
		    double s = p[i] - b[i];
		    r += s * s;
		}
	}
	return r;
}

//! Computes the normal vector between a point and a box.
inline Vector Box::Normal(const Vector& p) const
{
	Vector n;

	// Slab
	for(int i = 0; i < 3; i++)
	{
		if(p[i] < a[i]) n[i] = p[i] - a[i];
		else if(p[i]>b[i]) n[i] = p[i] - b[i];
		else n[i] = 0.0;
	}
	return n;
}

#endif

