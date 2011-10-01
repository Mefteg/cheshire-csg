/**
 * \file union.h
 * \brief class Union header
 * \author Gimenez Tom, Roumier Vincent, Matéo Camille
 * \version 1.0
 * \date 01 octobre 2011
 *
 * Union is a binary operand of the CSG
 *
 */


#ifndef __Union__
#define __Union__

#include "opbin.h"

class Union : public OpBin
{
	public:
	  
	Union(void);
	Union(Node* , Node*);
	~Union(void);

	int Intersect(const Ray&, Intersection&);
	int Intersect(const Ray&, Intersection&, Intersection&);
	int PMC(const Vector&);

	Vector getEmission() { return Vector(); };
	Vector getColor() { return Vector(); };
	Vector getPosition() { return (0.5 * left->getPosition() + 0.5 * right->getPosition());  };
	int getRefl() { return 0; };
	double getF() { return 0; };
};

#endif
