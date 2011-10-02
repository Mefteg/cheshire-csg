/**
 * \file primitive.h
 * \brief class Primitive header
 * \author Gimenez Tom, Roumier Vincent, Matéo Camille
 * \version 1.0
 * \date 01 octobre 2011
 *
 * Containing Primitive class
 *
 */


#ifndef __Primitive__
#define __Primitive__

#include "node.h"

/*! 
 * \class Primitive
 * \brief Primitive class
 * 
 * Primitive is a kind of node
 * 
 */
class Primitive : public Node
{
	protected:
	  
	Vector e;	/*!< Emission */
	Vector c;	/*!< Color */
	int refl;	/*!< Reflection type */
	double f;	/*!< Maximum color channel value */

	public:
	  
	Primitive(void);
	Primitive(const Vector&, const Vector&, int );
	virtual ~Primitive(void);

	Vector getEmission() { return e; };
	Vector getColor() { return c; };
	int getRefl() { return refl; };
	double getF() { return f; };
};

#endif
