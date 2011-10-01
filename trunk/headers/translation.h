/**
 * \file translation.h
 * \brief class Translation header
 * \author Gimenez Tom, Roumier Vincent, Matéo Camille
 * \version 1.0
 * \date 01 octobre 2011
 *
 * Translation is a transformation for the CSG
 *
 */


#ifndef __Translation__
#define __Translation__

#include "transfo.h"

class Translation : public Transfo
{

	public:
	  
	Translation(void);
	Translation(Node*, const Vector);
	~Translation(void);

	int Intersect(const Ray&, Intersection&);
	int Intersect(const Ray&, Intersection&, Intersection&);
	int PMC(const Vector&);

	Vector getEmission() { return Vector(); };
	Vector getColor() { return Vector(); };
	Vector getPosition() { return Vector(); };
	int getRefl() { return 0; };
	double getF() { return 0; };
};

#endif
